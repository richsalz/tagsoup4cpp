//
// This file is made available under the terms of the Apache 2.0
// license which is available at http://www.apache.org/licenses/
//

#ifndef TAGSOUP_HPP_INCL
#define TAGSOUP_HPP_INCL

/// @mainpage
/// This is a C++ rewrite of John Cowan's "tag soup" parser.
///
/// In his words:
///
/// A SAX-compliant parser written in Java that ... parses HTML as it is
/// found in the wild: poor, nasty and brutish, though quite often far from
/// short. TagSoup is designed for people who have to process this stuff
/// using some semblance of a rational application design. By providing a
/// SAX interface, it allows standard XML tools to be applied to even the
/// worst HTML.

/// @file
/// The scanner/parser, and the classes that defines how a parser
/// gets data (pull model) and pushes out results (SAX-like).

#include <istream>
#include <ostream>
#include <string>

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/// The namespace for the tagsoup HTML parser.
namespace TagSoup
{

/// Input stream. Like a std::istream, but with more pushback space.
class istream
{
    // No copying
    istream(const istream& rhs);
    istream& operator=(const istream& rhs);

    enum _CONSTANTS
    {
        UNREAD_SIZE=10          ///< Number of chars we can pushback/"unread"
    };
    std::istream* mIn;          ///< The actual stream we read from
    bool mMine;                 ///< Delete mIn when we're delete'd?
    int mUnreadCount;           ///< Number of chars unread
    int mUnread[UNREAD_SIZE];   ///< Unread buffer

public:
    /// Ctor.
    /// @param in The input stream
    /// @param mine Giving away ownership of the input stream?
    istream(std::istream* in, bool mine=true)
        : mIn(in), mMine(mine), mUnreadCount(0)
    {
    }

    /// Dtor.
    ~istream()
    {
        if (mMine)
            delete mIn;
    }

    /// Push back, or un-read, a character.
    /// @param c The character to push back.
    void unread(int c);

    /// Get character from pushback (if there is any) or input stream.
    /// @return The character from the appropriate place.
    inline int read()
    {
        return mUnreadCount > 0 ? mUnread[--mUnreadCount] : mIn->get();
    }

    /// Get the EOF marker for the stream. Necessary because C's EOF isn't
    /// guaranteed to be universal (even though it really is).
    /// @return The appropriate value of EOF.
    inline int eof()
    {
        return std::istream::traits_type::eof();
    }
};


/// Output stream.  Has a SAX-like interface. Create your own subclass
/// to customize the output.
class ostream
{
    // No copying
    ostream(const ostream& rhs);
    ostream& operator=(const ostream& rhs);

    std::ostream* mOut;         ///< The actual strem to output to.
    bool mMine;                 ///< Delete mOut when we're delete'd?
    bool mStarted;              ///< Have we output the prolog yet?

public:
    /// Ctor.
    /// @param out The input stream
    /// @param mine Giving away ownership of the input stream?
    ostream(std::ostream* out, bool mine=true)
        : mOut(out), mMine(mine), mStarted(false)
    {
    }

    /// Dtor
    virtual ~ostream()
    {
        mOut->flush();
        if (mMine)
            delete mOut;
    }

    /// Called to output the document prolog.
    virtual void StartDocument()
    {
        *mOut << "<?xml version=\"1.0\"?>\n";
    }

    /// Called to close off the document.
    virtual void EndDocument()
    {
    }

    /// Called to output the start of an element.
    /// @param name Element name
    /// @param names NULL-terminated list of attribute names
    /// @param values NULL-terminated list of attribute values
    virtual void StartElement(const char* name,
            const char** names, const char** values);

    /// Called to output the end of an element.
    /// @param name Element name
    virtual void EndElement(const char* name)
    {
        *mOut << "</" << name << ">";
    }

    /// Called to output ignorable whitespace.
    /// @param buff Pointer to buffer with the characters
    /// @param length Number of chars in buffer to output
    virtual void IgnorableWhitespace(const char* buff, int length)
    {
        Characters(buff, length);
    }

    /// Called to output a buffer of bytes.
    /// @param buff Pointer to buffer with the characters
    /// @param length Number of chars in buffer to output
    virtual void Characters(const char* buff, int length)
    {
        *mOut << std::string(buff, length);
    }

    /// Called to output a comment.
    /// @param buff Pointer to buffer with the characters
    /// @param length Number of chars in buffer to output
    virtual void Comment(const char* buff, int length)
    {
        *mOut << "<!--" << std::string(buff, length) << "-->";
    }

    /// Called to output a processing instruction.
    /// @param target The PI target name
    /// @param data The data for the PI
    virtual void ProcessingInstruction(const char* target, const char* data)
    {
        *mOut << "<? " << target << ' ' << data << "/>";
    }
};

class Element;
class Schema;

/// The parser.  For details on how the transitions and states work,
/// see the comments in the file parser.inl
class Parser
{
    // No copying
    Parser(const Parser& rhs);
    Parser& operator=(const Parser& rhs);

    enum _CONSTANTS
    {
        PIBUFF_SIZE=80          ///< Size of PI buffer
    };

    /// Parser actions.
    enum Action
    {
        A_ADUP_SAVE, A_ADUP_STAGC, A_ANAME, A_ANAME_ADUP,
        A_ANAME_ADUP_STAGC, A_AVAL, A_AVAL_STAGC, A_CDATA, A_CMNT,
        A_DECL, A_EMPTYTAG, A_ENTITY, A_ETAG, A_GI, A_GI_STAGC, A_LF,
        A_LT, A_LT_PCDATA, A_MINUS, A_MINUS2, A_MINUS3, A_PCDATA,
        A_PCDATA_PUSH_SAVE, A_PI, A_PITARGET, A_PITARGET_PI, A_SAVE,
        A_PUSH_SAVE, A_SKIP, A_SP, A_STAGC, A_UNGET, A_UNSAVE
    };

    struct State;

    /// Scanner transition; what to do and where to go next.
    struct Transition
    {
        int c;                  ///< Input character
        Action action;          ///< Action to take
        const State* next;      ///< New state (if not NULL)
    };
    /// Scanner state; a default new state and set of transitions.
    struct State
    {
        Action defaultaction;           ///< Action if no transition found
        const State* defaultstate;      ///< State if no transition found
        Action eofaction;               ///< Action to take on EOF
        int size;                       ///< Number of transitions
        const Transition* table;        ///< Table of transitions
    };

    static const Transition
        T_ANAME[], T_APOS[], T_AVAL[], T_BB[], T_BBC[], T_BBCD[],
        T_BBCDA[], T_BBCDAT[], T_BBCDATA[], T_CCRLF[], T_CDATA[],
        T_CDATA2[], T_CDSECT[], T_CDSECT1[], T_CDSECT2[], T_COM[],
        T_COM2[], T_COM3[], T_COM4[], T_COMCRLF[], T_CRLF[], T_DECL[],
        T_DECL2[], T_EMPTYTAG[], T_EQ[], T_ETAG[], T_GI[],
        T_PCDATA[], T_PI[], T_PICRLF[], T_PITARGET[], T_QUOT[],
        T_STAGC[], T_TAG[], T_TAGWS[];

    static const State
        S_ANAME, S_APOS, S_AVAL, S_BB, S_BBC, S_BBCD,
        S_BBCDA, S_BBCDAT, S_BBCDATA, S_CCRLF, S_CDATA,
        S_CDATA2, S_CDSECT, S_CDSECT1, S_CDSECT2, S_COM,
        S_COM2, S_COM3, S_COM4, S_COMCRLF, S_CRLF, S_DECL,
        S_DECL2, S_EMPTYTAG, S_ENT, S_EQ, S_ETAG, S_GI,
        S_NCR, S_PCDATA, S_PI, S_PICRLF, S_PITARGET, S_QUOT,
        S_STAGC, S_TAG, S_TAGWS, S_XNCR;

    /// @defgroup parser_state Parser state
    /// @{
    istream& mIn;               ///< Input stream
    ostream& mOut;              ///< Output stream
    Schema* mSchema;            ///< Schema definition
    Element* mStack;            ///< Stack of input elements
    bool mVirginStack;          ///< Stack never used?
    Element* mPCDATA;           ///< Current PCDATA element
    Element* mElement;          ///< Current element being parsed
    Element* mSaved;            ///< Saved state
    char* mAttrName;            ///< Current attribute name
    char* mPITarget;            ///< Current PI target being parsed
    char mAttrNameBuff[20];     ///< Small buffer for attribute name
    char mEntityBuff[10];       ///< Small buffer for entity name
    /// @}

    /// @defgroup scanner_state Scanner state
    /// @{
    char* mBuffer;              ///< Token buffer
    int mSize;                  ///< Total buffer size
    int mCount;                 ///< Offset into buffer
    const State* mState;        ///< Current state
    const State* mNextState;    ///< Where to go next
    int mSavedCount;            ///< Saved count when "pushed"
    const State* mSavedState;   ///< Saved state when "pushed"
    /// @}

public:
    /// Ctor
    /// @param in Input stream
    /// @param out Output stream
    Parser(istream& in, ostream& out);

    /// Dtor
    ~Parser();

    /// Parse input, calling methods on output
    void parse();

private:
    /// Push restartables on the stack if possible.
    /// @param e Next element to be started (if we know what it is).
    void restart(Element* e);

    /// Pop the stack irrevocably.
    /// @param deleteit Delete what's currently on the top?
    void pop(bool deleteit);

    /// Pop the stack restartably.
    void restartably_pop();

    /// Push element onto stack.
    void push(Element* e);

    /// Rectify the stack, pushing and popping as needed so that the
    /// argument can be safely pushed.
    /// @param e Element to now push onto the stack
    void rectify(Element* e);

    /// Basic (common) end-tag handling.
    /// @param buff,length Location and length of input 
    void etag_basic(const char* buff, int length);

    /// Return the argument as a valid XML name (and lowercased).
    /// Can pass in a buffer and we'll try to use it.
    /// @param buff,length Location and length of input 
    /// @param out Possible output buffer (if not NULL)
    /// @param outsize Size of output buffer
    /// @return Pointer to out, otherwise pointer to malloc'd space.
    char* makename(const char* buff, int length,
            char* out = 0, int outsize = 0);

    /// Make a C string
    /// @param buff,length Location and length of input 
    /// @return The string, dynamically allocated
    char* makestring(const char* buff, int length);

    /// Save a character on the input stream pushback
    /// @param ch The character to save
    void save(int ch);

    /// Save a string on the input stream pushback.
    /// @param cp The string to save
    void save(const char* cp)
    {
        while (*cp)
            save(*cp++);
    }

    /// Enter the CDATA state
    inline void startCDATA()
    {
        mNextState = &S_CDATA;
    }

    /// Parse a character, depending on our current state
    /// @param c The character to parse
    /// @return True if we should keep going; false on eof
    bool scan(int c);

    /// Push back a character onto the input stream.
    /// @param c The character to push back
    inline void unread(int c)
    {
        mIn.unread(c);
    }

    /// Found an attribute name without a value.
    void adup();

    /// Found an attribute name; a value will follow.
    /// @param buff,length Location and length of input 
    void aname(const char* buff, int length)
    {
        if (mElement == NULL)
            return;
        mAttrName = makename(buff, length, mAttrNameBuff, sizeof mAttrNameBuff);
    }

    /// Found an attribute value.
    /// @param buff,length Location and length of input 
    void aval(const char* buff, int length);

    /// Found an entity reference or character reference.
    /// @param buff,length Location and length of input 
    const char* entity(const char* buff, int length);

    /// Found EOF.
    void eof();

    /// Found an end-tag.
    /// @param buff,length Location and length of input 
    void etag(const char* buff, int length);

    /// Found the general identifier (element type name) of a start-tag.
    /// @param buff,length Location and length of input 
    void gi(const char* buff, int length);

    /// Found character content.
    /// @param buff,length Location and length of input 
    void pcdata(const char* buff, int length);

    /// Found the target part of a processing instruction.
    /// @param buff,length Location and length of input 
    void pitarget(const char* buff, int length)
    {
        if (mElement != NULL)
            return;
        mPITarget = makename(buff, length);
    }

    /// Found the data part of a processing instruction.
    /// @param buff,length Location and length of input 
    void pi(const char* buff, int length);

    /// Found the close of a start-tag.
    /// @param buff,length Location and length of input 
    void stagc(const char* buff, int length);

    /// Found the close of an empty-tag.
    /// @param buff,length Location and length of input 
    void stage(const char* buff, int length)
    {
        if (mElement == NULL)
            return;
        rectify(mElement);
        etag_basic(buff, length);
    }

    /// Found a comment.
    /// @param buff,length Location and length of input 
    void cmnt(const char* buff, int length)
    {
        mOut.Comment(buff, length);
    }

};

}

#endif
