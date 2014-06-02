//
// This file is made available under the terms of the Apache 2.0
// license which is available at http://www.apache.org/licenses/
//


/// @file
/// Internals (implementation) file for TagSoup.
///
/// The Schema contains the definitions of all the elements seen in HTML.
/// What children they can have, what attributes are pre-defined, special
/// magic flags about overlapping &lt;b>&lt;i>like&lt;/b>this&lt;/i>, etc.
//
/// You could argue that the Element class should be nested inside Schema.
/// I won't disagree, but Schema::Element is just too much typing.

#include <stdlib.h>
#include <string.h>
#include <assert.h>


namespace TagSoup
{

/// Element types. Also used to indicate what kinds of things can be found
/// inside the current element, which is why this is a bitmask.
enum ELEMENT_TYPES
{
    TYPE_EMPTY  = 0,
    TYPE_PCDATA = 1 <<  1,
    TYPE_ROOT   = 1 <<  2,
    TYPE_AREA   = 1 <<  3,
    TYPE_BLOCK  = 1 <<  4,
    TYPE_BODY   = 1 <<  5,
    TYPE_CELL   = 1 <<  6,
    TYPE_COL    = 1 <<  7,
    TYPE_DEF    = 1 <<  8,
    TYPE_FORM   = 1 <<  9,
    TYPE_FRAME  = 1 << 10,
    TYPE_HEAD   = 1 << 11,
    TYPE_HTML   = 1 << 12,
    TYPE_INLINE = 1 << 13,
    TYPE_LEGEND = 1 << 14,
    TYPE_LI     = 1 << 15,
    TYPE_NOLINK = 1 << 16,
    TYPE_OPTION = 1 << 17,
    TYPE_OPTIONS= 1 << 18,
    TYPE_P      = 1 << 19,
    TYPE_PARAM  = 1 << 20,
    TYPE_TABLE  = 1 << 21,
    TYPE_TR     = 1 << 22,
    TYPE_ANY    = ~0
};

/// Special processing flags for an element.
enum ELEMENT_FLAGS
{
    FLAG_NONE,          ///< No special processing
    FLAG_RESTART,       ///< Restart the element if "overlapped" by another
    FLAG_CDATA,         ///< Treat content as CDATA
    FLAG_NOFORCE,       ///< Automagically close the element?
    FLAG_NOFREE         ///< Do not free attributes in dtor
};


/// @defgroup attribute_classes Attribute classes
/// The SchemaAttributes and DocAttributes classes are containers for a set
/// of attributes (name/value pairs). The SchemaAttributes are used to define
/// the set of "known" attributes for an element. The DocAttributes are created
/// from a SchemaAttributes and then populated with data we get while parsing
/// the input document.
///
/// These are really containers. We could use STL, but we don't because
/// we want to avoid needless memory use and fragmentation.
///
/// The schema creates about 100 read-only attribute objects at startup.
/// In order to reduce memory fragmentation we create a pool and use the
/// placement-new operator to keep them all in one spot.
/// @{


/// SchemaAttributes are immutable; the name/value data is aliased to
/// fixed constant strings.
class SchemaAttributes
{
    // No copying
    SchemaAttributes(const SchemaAttributes& rhs);
    SchemaAttributes& operator=(const SchemaAttributes& rhs);

public:
    /// Attributes are weakly typed -- only three data types are supported:
    /// CDATA, ID's, and "everything else."
    /// @note See schema.inl before changing the values here.
    enum Type
    {
        TYPE_CDATA = 0, ///< Don't normalize whitespace on output
        TYPE_ID,        ///< Perhaps deleted, to avoid duplicate ID's
        TYPE_OTHER      ///< Everything else; no special handling.
    };

    /// A single attribute entry: a name, value, and a type.
    /// The namecopy field is either NULL or strdup'd, and can
    /// always be free()'d.
    /// @note See schema.inl before changing the order of fields here.
    struct entry
    {
        const char* name;       ///< Attribute name; possibly aliased
        char* value;            ///< Attribute value
        Type type;              ///< Attribute type
        char* namecopy;         ///< Attribute name, can be free'd
    };

    /// Create the pool (single block) of specified size.
    /// @param i Number of entries to allocate
    static void pool(int i);

    /// Create an entry in the pool and return it.
    /// @param data_ Pointer to list of attribute data
    /// @param size Number of items in the data_ list
    static SchemaAttributes* next(entry* data_, int size);

private:
    static int sCount;          ///< Number of entries in the pool
    static SchemaAttributes* sPool;    ///< Block of memory for the pool

    /// Create a constant attribute (in the pool) from an entry list
    /// @param data_ Pointer to list of attribute data
    /// @param size Number of items in the data_ list
    SchemaAttributes(entry* data_, int size)
        : mLength(size), mSize(size), mData(data_)
    {
    }

protected:
    int mLength;                ///< Number of attributes defined
    int mSize;                  ///< Max number of attributes possible
    entry* mData;               ///< Pointer to list of attributes

    /// Ctor
    /// @param length_ Number of items in the data_ list
    /// @param size Desired size of internal attribute list
    /// @param data_ Pointer to iost of attribute data
    SchemaAttributes(int length_, int size, entry* data_)
        : mLength(length_), mSize(size), mData(data_)
    {
    }

public:
    /// Return number of attributes defined
    int length() const
    {
	return mLength;
    }

    /// Return the start of attribute list
    const entry* entries() const
    {
        return mData;
    }
};



/// DocAttributes are mutable, and usually created from a SchemaAttributes (in
/// which case the name pointer is aliased to the SchemaAttributes's name).
/// The set of name/value pairs for DocAttributes can change, but is usually
/// less then a dozen. To avoid memory fragmentation, each DocAttributes object
/// has an internal "heap" to store the name/value list, and we only move
/// to malloc() space if end up needing more than that.
class DocAttributes : public SchemaAttributes
{
    // No copying
    DocAttributes(const DocAttributes& rhs);
    DocAttributes& operator=(const DocAttributes& rhs);

    /// Miscellaneous constants.
    enum _CONSTANTS
    {
        HEAP_SIZE  = 10,   ///< Initial heap size
        HEAP_DELTA = 10    ///< How much to realloc if we need to grow it
    };
    entry mHeap[HEAP_SIZE];     ///< Storage for the attributes

    /// Find an attribute with the given name.
    /// @param name Name of the attribute
    /// @return Attribute entry or NULL if not found.
    entry* lookup(const char* name) const
    {
        entry* vp = mData;
	for (int i = mLength; --i >= 0; vp++)
	    if (strcmp(vp->name, name) == 0)
		return vp;
	return NULL;
    }

    /// Is a value already normalized?
    /// @param value The attribute value
    /// @return True if whitespace-normalized, false if not.
    static bool normalized(const char* value)
    {
        if (isspace(*value))
            return false;
        for (; *value; value++)
            if (isspace(*value) && isspace(value[1]))
                return false;
        return !isspace(*--value);
    }

    /// Normalize an attribute value, return a new allocated copy.
    /// @param value The value to normalize
    /// @return The normalized value. 
    static char* normalize(const char* value)
    {
        // Trim leading and trailing whitespace.
        while (isspace(*value))
            value++;
        char* newvalue = strdup(value);
        char* end = newvalue + strlen(newvalue);
        while (--end >= newvalue && isspace(*end))
            continue;
        *++end = '\0';

        // Collapse multiple spaces.  Efficient enough.
        char* src = newvalue;
        char* dest = newvalue;
        while ((*src++ = *dest) != '\0')
            if (isspace(*dest))
                while (isspace(*dest))
                    dest++;
            else
                dest++;

        return newvalue;
    }

public:
    /// Ctor with an an empty attribute list.
    DocAttributes()
        : SchemaAttributes(0, sizeof mHeap / sizeof mHeap[0], mHeap)
    {
    }

    /// Ctor, created from the schema definition.
    /// @param rhs The SchemaAttributes "template" to use in creating
    DocAttributes(const SchemaAttributes& rhs)
        : SchemaAttributes(rhs.length(),
                sizeof mHeap / sizeof mHeap[0], mHeap)
    {
        if (mLength > mSize)
        {
            mSize = mLength;
            mData = (entry*)malloc(mSize * sizeof *mData);
        }
        const entry* src = rhs.entries();
        entry* vp = mData;
        for (int i = mLength; --i >= 0; vp++, src++)
        {
            vp->name = src->name;
            vp->value = src->value ? strdup(src->value) : NULL;
            vp->type = src->type;
            vp->namecopy = NULL;
        }
    }

    /// Dtor
    ~DocAttributes()
    {
        if (mData != NULL)
        {
            entry* vp = mData;
            for (int i = mLength; --i >= 0; vp++)
            {
                free(vp->value);
                free(vp->namecopy);
            }
            if (mData != mHeap)
                free(mData);
        }
    }

    /// Trim the name/value list to remove any without a value.
    void Clean()
    {
        entry* vp = mData;
        entry* src = mData;
        for (int i = 0; i < mLength; src++)
            if (src->value == NULL)
            {
                free(src->namecopy);
                mLength--;
            }
            else
            {
                *vp++ = *src;
                i++;
            }
    }

    /// Trim the name/value list to remove any ID-like attributes.
    void Anonymize()
    {
        entry* vp = mData;
        entry* src = mData;
        for (int i = 0; i < mLength; src++)
            if (src->type == TYPE_ID || strcmp(src->name, "name") == 0)
            {
                free(src->value);
                free(src->namecopy);
                mLength--;
            }
            else
            {
                *vp++ = *src;
                i++;
            }
    }

    /// Set/add an attribute name/value.
    /// @note Value becomes owned by this; strdup if you need it.
    /// @param name The attribute name
    /// @param value The attribute value
    void set(const char* name, char* value)
    {
        if (strcmp(name, "xmlns") == 0 || strchr(name, ':') != NULL)
        {
            free(value);
            return;
        }
        entry* vp = lookup(name);
        if (vp == NULL)
        {
            // Not found, must add it.  Need more room?
            if (mLength >= mSize - 1)
            {
                mSize += HEAP_DELTA;
                if (mData == mHeap)
                {
                    mData = (entry*)malloc(mSize * sizeof *mData);
                    memcpy(mData, mHeap, sizeof mHeap);
                }
                else
                    mData = (entry*)realloc(mData, mSize * sizeof *mData);
            }

            // Add the entry.
            vp = &mData[mLength++];
            vp->name = strdup(name);
            vp->value = value;
            vp->type = TYPE_CDATA;
            vp->namecopy = const_cast<char*>(vp->name);
        }
        else if (vp->type != TYPE_CDATA)
        {
            // Entry exists; replace old with normalized value
            free(vp->value);
            if (normalized(value))
                vp->value = value;
            else
            {
                vp->value = normalize(value);
                free(value);
            }
        }
        else if (vp->value != value)
        {
            // Entry exists; replace old with new (if not already aliased)
            free(vp->value);
            vp->value = value;
        }
    }
};

/// @}



/// This class serves two purposes.
///     -# It defines the HTML schema. The Element::Type class defines the set
/// of attributes that are defined for the element, as well as various content
/// model and processing flags. In this use, the attributes are immutable
/// SchemaAttributes.
///     -# It contains the state of the input document. In this case, the
/// "schema" element is used as a template, and the actual attributes from
/// the document are stored as DocAttributes in the "mAtts" field.
///
/// The code might be simpler and more clear by creating two separate classes,
/// but c'est la vie.
class Element
{
    // No copying
    Element(const Element& rhs);
    Element& operator=(const Element& rhs);

public:
    /// Element type. This is defined by the data in the file schema.inl
    /// The schema also creates the same number of Element::Type objects,
    /// and we have an pool here for the same reason.
    class Type
    {
        // No copying
        Type(const Type& rhs);
        Type& operator=(const Type& rhs);

        char* mName;                ///< Element name
        SchemaAttributes* mAtts;    ///< Attributes defined for this element
        const Type* mParent;        ///< Parent (containing) element
        unsigned int mModel;        ///< Bitmap of what the element contains
        unsigned int mMemberof;     ///< bitmap of what element is contained in
        unsigned int mFlags;        ///< Processing flags; see ELEMENT_FLAGS

        static int sCount;          ///< Number of type definitions
        static Type* sPool;         ///< Allocated block to hold all of them

    public:
        /// Create the pool (single block) of specified size.
        /// @param i Number of entries to allocate
        static void pool(int i);

        /// Create a type object in the pool from the bits of info and an
        /// existing set of attributes.
        /// @param name The element name
        /// @param model What items/elements the element contain
        /// @param memberof what elements can contain this
        /// @param flags special processing flags
        /// @param atts The defined attrigutes.
        /// @return Pointer to the object (inside the pool).
        static Type* next(const char* name, unsigned int model,
                unsigned int memberof, unsigned int flags,
                SchemaAttributes* atts);

        /// Create a type object, with no existing attributes defined.
        /// @param name_ The element name
        /// @param model What items/elements the element contain
        /// @param memberof what elements can contain this
        /// @param flags special processing flags
        Type(const char* name_, unsigned int model, unsigned int memberof,
                unsigned int flags)
            : mParent(NULL), mModel(model), mMemberof(memberof), mFlags(flags)
        {
            mName = strdup(name_);
            mAtts = new DocAttributes();
        }

    private:
        // Used by next() to build an object that shares the name and
        // attribute list.
        /// @param name_ The element name
        /// @param model What items/elements the element contain
        /// @param memberof what elements can contain this
        /// @param flags special processing flags
        /// @param atts_ Attributes from the schema
        Type(const char* name_, unsigned int model, unsigned int memberof,
                unsigned int flags, const SchemaAttributes* atts_)
            : mName(const_cast<char*>(name_)),
            mAtts(const_cast<SchemaAttributes*>(atts_)),
            mParent(NULL), mModel(model), mMemberof(memberof),
            mFlags(flags | FLAG_NOFREE)
        {
        }

    public:
        /// Dtor
        ~Type()
        {
            if ((mFlags & FLAG_NOFREE) == 0)
            {
                free(mName);
                delete (DocAttributes*)mAtts;
            }
        }

        /// Return the name of the element.
        inline const char* name() const
        {
            return mName;
        }

        /// Return the attributes for the element.
        inline SchemaAttributes& atts() const
        {
            return *mAtts;
        }

        /// Is this element expected to be empty?
        inline bool empty() const
        {
            return mModel == TYPE_EMPTY;
        }

        /// Is a particular content model bit set?
        /// @param bit The bit to test.
        inline bool IsSet(ELEMENT_FLAGS bit) const
        {
            return (mFlags & bit) != 0;
        }

        /// Can this element have a child of the other type?
        /// @param rhs The would-be child element
        inline bool CanContain(const Type& rhs) const
        {
            return (mModel & rhs.mMemberof) != 0;
        }

        /// Return the parent of the element
        inline const Type* parent() const
        {
            return mParent;
        }

        /// Set the parent, if not already specified.
        /// @param parent_ The parent element
        inline void SetParent(const Type* parent_)
        {
            assert(mParent == NULL);
            mParent = parent_;
        }
    };

private:
    const Type& mType;     ///< The type definition
    DocAttributes* mAtts;  ///< The current attributes
    bool mPreclosed;       ///< Did we close-tag the element "magically"?
    Element* mNext;        ///< For users to build a stack

public:
    /// Ctor; create an element from the type definition.
    /// @param type The type definition to use as the template
    Element(const Type& type)
        : mType(type), mPreclosed(false), mNext(NULL)
    {
        mAtts = new DocAttributes(type.atts());
    }

    /// Dtor.
    ~Element()
    {
        delete mAtts;
    }

    /// Delete stack of following elements
    void Delete()
    {
        for (Element* e = this; e; )
        {
            Element* np = e->mNext;
            delete e;
            e = np;
        }
    }

    /// Get the attributes
    inline const DocAttributes& atts() const
    {
        return *mAtts;
    }

    /// Get the next element in the stack.
    inline Element* next() const
    {
        return mNext;
    }

    /// Set the next pointer (used to fix overlapping elements).
    /// @param next_ The element we want next
    inline void SetNext(Element* next_)
    {
        mNext = next_;
    }

    /// Mark that we "pre-closed" the element.
    inline void Preclose()
    {
        mPreclosed = true;
    }

    /// Was the element already closed?
    inline bool IsPreclosed() const
    {
        return mPreclosed;
    }

    /// Get the name of the element.
    inline const char* name() const
    {
        return mType.name();
    }

    /// Is this element empty?
    inline bool empty() const
    {
        return mType.empty();
    }

    /// Does this element have the specified bit set?
    /// @param bit The bit to test.
    inline bool IsSet(ELEMENT_FLAGS bit) const
    {
        return mType.IsSet(bit);
    }

    /// Get the parent element type.
    inline const Type* parent() const
    {
        return mType.parent();
    }

    /// Can this element contain the specified other element?
    /// @param rhs The other element (putative containee).
    inline bool CanContain(const Element* rhs) const
    {
        return mType.CanContain(rhs->mType);
    }

    /// Set/add an attribute name/value.
    /// @note Value becomes owned by this; strdup if you need it.
    /// @param name_ The attribute name
    /// @param value The attribute value
    inline void set(const char* name_, char* value)
    {
        mAtts->set(name_, value);
    }
    /// Remove any ID-like attributes.
    void Anonymize()
    {
        mAtts->Anonymize();
    }
    /// Remove an attributes that do not have a value.
    void Clean()
    {
        mAtts->Clean();
    }
};


/// Schema definition.  All instances share the same definition.
class Schema
{
    // No copying
    Schema(const Schema& rhs);
    Schema& operator=(const Schema& rhs);

    /// Hashtable of text entities.
    static struct lhash_st* sEntities;
    /// Hashtable of element definitions
    static struct lhash_st* sTypes;
    /// Initialize the class-static schema data
    static void init();

    /// Hashtable of element types.
    struct lhash_st* mTypes;

public:
    Schema();
    ~Schema();

    /// Lookup a text entity.
    /// @param name The value found in the input
    /// @return The value to output or NULL to use the original value.
    static const char* TextEntity(const char* name);

    /// Add an element to the schema and return the type definition.
    /// @param name The element name
    /// @param model What items/elements the element contain
    /// @param memberof what elements can contain this
    const class Element::Type* Add(const char* name, int model, int memberof);

    /// Lookup an element type and return it.
    /// @param name The element name
    /// @return The type; NULL if not found.
    const class Element::Type* Lookup(const char* name) const;
};

}
