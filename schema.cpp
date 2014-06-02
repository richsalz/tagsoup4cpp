//
// This file is made available under the terms of the Apache 2.0
// license which is available at http://www.apache.org/licenses/
//

/// @file
/// An "elements and attributes" schema implementation.

#include <new>

#include "lhash.h"
#include <tagsoup.hpp>
#include "internals.hpp"

using namespace TagSoup;

int SchemaAttributes::sCount = 0;
SchemaAttributes* SchemaAttributes::sPool = 0;

void
SchemaAttributes::pool(int i)
{
    assert(sCount == 0);
    sCount = i;
    sPool = (SchemaAttributes*)malloc(sCount * sizeof *sPool);
}

SchemaAttributes*
SchemaAttributes::next(entry* data_, int size)
{
    assert(--sCount >= 0);
    return new (sPool++) SchemaAttributes(data_, size);
}

int Element::Type::sCount = 0;
Element::Type* Element::Type::sPool = 0;

void
Element::Type::pool(int i)
{
    assert(sCount == 0);
    sCount = i;
    sPool = (Element::Type*)malloc(sCount * sizeof *sPool);
}

Element::Type*
Element::Type::next(const char* name, unsigned int model, unsigned int memberof,
                unsigned int flags, SchemaAttributes* atts)
{
    assert(--sCount >= 0);
    return new (sPool++) Type(name, model, memberof, flags, atts);
}


/// We keep a hash table of text entities found in HTML, and what
/// they should be output when output.
struct entity
{
    const char* text;           ///< The input text string
    const char value[9];        ///< What to output instead

private:
    /// Hash an entity entry, which is the hash of the text value.
    /// @param ep The text entity to hash
    /// @return The hash value
    static unsigned long hash(const entity* ep)
    {
        return lh_strhash(ep->text);
    }

    /// Compare two entries and return their ordering.
    /// @param ep1,ep2 Entries to compare
    /// @return -1, 0, +1 depending on if ep1 is before, same, after ep2
    static int cmp(const entity* ep1, const entity* ep2)
    {
        return strcmp(ep1->text, ep2->text);
    }

public:
    /// Wrapper function to call hash with type-safety.
    /// @param arg A pointer to be cast to the entry
    /// @return What hash returns.
    static unsigned long hash(const void *arg)
    {
        return hash((const entity*)arg);
    }


    /// Wrapper function to call cmp with type-safety.
    /// @param arg1,arg2 Pointers to be cast into the entries to compare
    /// @return What cmp returns.
    static int cmp(const void *arg1, const void *arg2)
    {
        return cmp((const entity*)arg1, (const entity*)arg2);
    }
};

const char*
Schema::TextEntity(const char* name)
{
    if (name == NULL || *name == '\0')
        return 0;

    entity key = { name, "" };
    entity* ep = (entity*)lh_retrieve(sEntities, &key);
    return ep ? ep->value : 0;
}


/// We hash an element name into its type.  The same table used to
/// create the mapping also contains all the data needed to create the
/// Element::Type object in the first place.
struct type
{
    const char* name;           ///< The element name
    unsigned int flags;         ///< Processing flags; see ELEMENT_FLAGS
    const char* parent;         ///< Name of the parent element
    unsigned int model;         ///< Content model
    unsigned int memberof;      ///< What it can be a child of
    Element::Type* ep;          ///< Pointer to the schema definition

private:
    /// Get the hash value for an entry
    static unsigned long hash(const type* tp)
    {
        return lh_strhash(tp->name);
    }

    /// Compare two entries.
    /// @param tp1,tp2 Entries to compare
    /// @return -1, 0, +1 depending on if tp1 is before, same, after tp2
    static int cmp(const type* tp1, const type* tp2)
    {
        return strcmp(tp1->name, tp2->name);
    }

    /// Free an entry.
    static void free(type* tp)
    {
        delete tp->ep;
    }

public:
    /// Wrapper function to call hash with type-safety.
    /// @param arg A pointer to be cast to the entry
    /// @return What hash returns.
    static unsigned long hash(const void *arg)
    {
        return hash((const type*)arg);
    }

    /// Wrapper function to call cmp with type-safety.
    /// @param arg1,arg2 Pointers to be cast into the entries to compare
    /// @return What cmp returns.
    static int cmp(const void *arg1, const void *arg2)
    {
        return cmp((const type*)arg1, (const type*)arg2);
    }

    /// Wrapper function to call free with type-safety.
    /// @param arg Pointer to be cast into the entry to free
    static void free(void* arg)
    {
        free((type*)arg);
    }
};

const Element::Type*
Schema::Lookup(const char* name) const
{
    type key = { name };
    const Element::Type* ep = (const Element::Type*)lh_retrieve(sTypes, &key);
    if (ep == NULL && mTypes != NULL)
        ep = (const Element::Type*)lh_retrieve(mTypes, &key);
    return ep;
}


/// Element definition.
struct schema_def
{
    type* tp;                ///< Pointer to the type definition
    SchemaAttributes::entry* ap;        ///< List of attributes
    int numatts;                        ///< Number of attributes
};


#include "schema.inl"


struct lhash_st* Schema::sEntities;
struct lhash_st* Schema::sTypes;


Schema::Schema()
    : mTypes(NULL)
{
    if (sTypes == NULL)
        init();
}


Schema::~Schema()
{
    if (mTypes)
    {
        lh_doall(mTypes, type::free);
        lh_free(mTypes);
    }
} 


const Element::Type*
Schema::Add(const char* name, int model, int memberof)
{
    if (mTypes == NULL)
        mTypes = lh_new(type::hash, type::cmp);
    Element::Type* ep = new Element::Type(strdup(name), model, memberof, 0);
    lh_insert(mTypes, ep);
    return ep;
}


void
Schema::init()
{
    assert(sTypes == NULL);

    // Get pools.
    int i = 0;
    for (schema_def* dp = definitions; dp->tp; dp++)
        i++;
    SchemaAttributes::pool(i);
    Element::Type::pool(i);

    // Create the schema of element types.
    sTypes = lh_new(type::hash, type::cmp);
    type key = { 0 };
    i = sizeof definitions / sizeof definitions[0];
    for (schema_def* dp = definitions; --i >= 0; dp++)
    {
        SchemaAttributes* ap = SchemaAttributes::next(dp->ap, dp->numatts);
        type& tp = *dp->tp;
        tp.ep = Element::Type::next(tp.name, tp.model, tp.memberof, tp.flags,
                    ap);
        if (tp.parent)
        {
            key.name = tp.parent;
            Element::Type* e = (Element::Type*)lh_retrieve(sTypes, &key);
            assert(e != NULL);
            tp.ep->SetParent(e);
        }
        lh_insert(sTypes, tp.ep);
    }

    // Populate the entity hashtable.
    assert(sEntities == NULL);
    sEntities = lh_new(entity::hash, entity::cmp);
    i = sizeof entities / sizeof entities[0];
    for (entity* ep = entities; --i >= 0; ep++)
        lh_insert(sEntities, ep);
}
