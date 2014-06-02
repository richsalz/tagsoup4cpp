//
// This file is made available under the terms of the Apache 2.0
// license which is available at http://www.apache.org/licenses/
//

/// @file
/// The scanner and parser.

#include <stdio.h>
#include <tagsoup.hpp>
#include "internals.hpp"

using namespace TagSoup;

#include "parser.inl"

void
istream::unread(int c)
{
    if (c == mIn->eof())
        return;
    assert((size_t)mUnreadCount < UNREAD_SIZE);
    mUnread[mUnreadCount++] = c;
}

void
ostream::StartElement(const char* name, const char** names, const char** values)
{
    *mOut << '<' << name;
    if (!mStarted)
    {
        *mOut << " xmlns='http://www.w3.org/1999/xhtml'";
        mStarted = true;
    }
    for ( ; names[0]; ++names, ++values)
    {
        const char* cp = *values;
        if (strchr(cp, '"') == NULL)
            *mOut << ' ' << *names << "=\"" << cp << '"';
        else
        {
            *mOut << ' ' << *names << "=\"";
            for ( ; *cp; cp++)
                if (*cp == '"')
                    *mOut << "&quot;";
                else
                    *mOut << *cp;
            *mOut << '"';
        }

    }
    *mOut << '>';
}

// The 16bit values of nasty 8bit Windows characters.
static int WindowsCharMap[] =
{
    0x20AC, 0xFFFD, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
    0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0xFFFD, 0x017D, 0xFFFD,
    0xFFFD, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
    0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0xFFFD, 0x017E, 0x0178
};


void
Parser::save(int c)
{
    if (mCount >= mSize - 20)
    {
        if (mState == &S_PCDATA || mState == &S_CDATA)
        {
            // Return a buffer-sized chunk of PCDATA.
            pcdata(mBuffer, mCount);
            mCount = 0;
        }
        else
            mBuffer = (char*)realloc(mBuffer, mSize *= 2);
    }
    mBuffer[mCount++] = (char)c;
}


//
// Scanner implementation
//

bool
Parser::scan(int c)
{
    // Check for 8bit Windows character, ignore them unless in 'text' mode.
    if (c >= 0x80 && c <= 0x9F)
    {
        c = WindowsCharMap[c - 0x80];
        if (c > 0x7F && mState != &S_PCDATA && mState != &S_CDATA)
            return true;
        char buff[12];
        sprintf(buff, "&#x%x;", c);
        save(buff);
        return true;
    }

    // Get action and next state.
    Action action;
    if (c == mIn.eof())
    {
        action = mState->eofaction;
        mNextState = NULL;
    }
    else
    {
        if (c < 0x20 && c != '\n' && c != '\r' && c != '\t')
            return true;
        action = mState->defaultaction;
        mNextState = mState->defaultstate;
        const Transition* tp = mState->table;
        for (int i = mState->size; --i >= 0; tp++)
            if (tp->c == c)
            {
                action = tp->action;
                mNextState = tp->next;
                break;
            }
    }

    switch (action)
    {
    case A_ADUP_SAVE:
        adup();
        mCount = 0;
        save(c);
        break;
    case A_ADUP_STAGC:
        adup();
        stagc(mBuffer, mCount = 0);
        break;
    case A_ANAME:
        aname(mBuffer, mCount);
        mCount = 0;
        break;
    case A_ANAME_ADUP:
        aname(mBuffer, mCount);
        adup();
        mCount = 0;
        break;
    case A_ANAME_ADUP_STAGC:
        aname(mBuffer, mCount);
        adup();
        stagc(mBuffer, mCount = 0);
        break;
    case A_AVAL:
        aval(mBuffer, mCount);
        mCount = 0;
        break;
    case A_AVAL_STAGC:
        aval(mBuffer, mCount);
        stagc(mBuffer, mCount = 0);
        break;
    case A_CDATA:
        // Suppress the final "]]" in the buffer.
        if (mCount > 1)
            mCount -= 2;
        pcdata(mBuffer, mCount);
        mCount = 0;
        break;
    case A_ENTITY:
        if (mState == &S_ENT && c == '#')
        {
            mNextState = &S_NCR;
            save(c);
        }
        else if (mState == &S_NCR && (c == 'x' || c == 'X'))
        {
            mNextState = &S_XNCR;
            save(c);
        }
        else if ((mState == &S_ENT && isalnum(c))
                || (mState == &S_NCR && isdigit(c))
                || (mState == &S_XNCR && isxdigit(c)))
            save(c);
        else
        {
            const char* cp = 
                entity(&mBuffer[mSavedCount + 1], mCount - mSavedCount - 1);
            if (cp)
            {
                mCount = mSavedCount;
                save(cp);
                if (c != ';')
                    unread(c);
            }
            else
                unread(c);
            mNextState = mSavedState;
        }
        break;
    case A_ETAG:
        etag(mBuffer, mCount);
        mCount = 0;
        break;
    case A_DECL:
        // decl(mBuffer, mCount);
        mCount = 0;
        break;
    case A_GI:
        gi(mBuffer, mCount);
        mCount = 0;
        break;
    case A_GI_STAGC:
        gi(mBuffer, mCount);
        stagc(mBuffer, mCount = 0);
        break;
    case A_LF:
        save('\n');
        break;
    case A_LT:
        save('<');
        break;
    case A_LT_PCDATA:
        save('<');
        pcdata(mBuffer, mCount);
        mCount = 0;
        break;
    case A_PCDATA:
        pcdata(mBuffer, mCount);
        mCount = 0;
        break;
    case A_CMNT:
        cmnt(mBuffer, mCount);
        mCount = 0;
        break;
    case A_MINUS3:
        save('-');
        save(' ');
        break;
    case A_MINUS2:
        save('-');
        save(' ');
        // FALLTHROUGH
    case A_MINUS:
        save('-');
        save(c);
        break;
    case A_PI:
        pi(mBuffer, mCount);
        mCount = 0;
        break;
    case A_PITARGET:
        pitarget(mBuffer, mCount);
        mCount = 0;
        break;
    case A_PITARGET_PI:
        pitarget(mBuffer, mCount);
        pi(mBuffer, mCount = 0);
        break;
    case A_PCDATA_PUSH_SAVE:
        pcdata(mBuffer, mCount);
        mCount = 0;
        // FALLTHROUGH
    case A_PUSH_SAVE:
        mSavedState = mState;
        mSavedCount = mCount;
        // FALLTHROUGH
    case A_SAVE:
        save(c);
        break;
    case A_SKIP:
        break;
    case A_SP:
        save(' ');
        break;
    case A_STAGC:
        stagc(mBuffer, mCount);
        mCount = 0;
        break;
    case A_EMPTYTAG:
        if (mCount > 0)
            gi(mBuffer, mCount);
        stage(mBuffer, mCount = 0);
        break;
    case A_UNGET:
        unread(c);
        break;
    case A_UNSAVE:
        if (mCount > 0)
            mCount--;
        pcdata(mBuffer, mCount);
        mCount = 0;
        break;
    }

    if ((mState = mNextState) == NULL)
    {
        eof();
        return false;
    }
    return true;
}


Parser::Parser(TagSoup::istream& in, TagSoup::ostream& out)
    : mIn(in), mOut(out),
    mVirginStack(true), mElement(NULL), mSaved(NULL),
    mAttrName(NULL), mPITarget(NULL),
    mSize(200), mCount(0),
    mState(&S_PCDATA), mNextState(NULL),
    mSavedCount(0), mSavedState(NULL)
{
    mSchema = new Schema();
    mStack = new Element(*mSchema->Lookup("<root>"));
    mPCDATA = new Element(*mSchema->Lookup("<pcdata>"));
    mBuffer = (char*)malloc(mSize);
}


Parser::~Parser()
{
    delete mSchema;
    mStack->Delete();
    mPCDATA->Delete();
    if (mSaved)
        mSaved->Delete();
    delete mElement;
    if (mAttrName != mAttrNameBuff)
        free(mAttrName);
    free(mPITarget);
    free(mBuffer);
}


char*
Parser::makestring(const char* buff, int length)
{
    char* p = (char*)malloc(length + 1);
    memcpy(p, buff, length);
    p[length] = '\0';
    return p;
}

void
Parser::parse()
{
    mOut.StartDocument();
    int c;
    do
    {
        c = mIn.read();
    } while (scan(c));
    mOut.EndDocument();
}

void
Parser::restart(Element* e)
{
    while (mSaved != NULL
            && mStack->CanContain(mSaved)
            && (e == NULL || mSaved->CanContain(e)))
    {
        Element* next = mSaved->next();
        push(mSaved);
        mSaved = next;
    }
}

void
Parser::pop(bool deleteit)
{
    if (mStack == NULL)
        return;

    mOut.EndElement(mStack->name());
    Element* next = mStack->next();
    if (deleteit)
        delete mStack;
    mStack = next;
}

void
Parser::restartably_pop()
{
    Element* popped = mStack;
    pop(false);
    if (popped->IsSet(FLAG_RESTART))
    {
        popped->Anonymize();
        popped->SetNext(mSaved);
        mSaved = popped;
    }
    else
        delete popped;
}

void
Parser::push(Element* e)
{
    mVirginStack = false;
    e->Clean();
    e->SetNext(mStack);
    mStack = e;

    const SchemaAttributes& atts = e->atts();
    int length = atts.length();
    // If you can use GNU variable sized arrays enable this line:
    // const int heapsize = length + 1;
    const int heapsize = 20;
    const char* names[heapsize];
    const char* values[heapsize];
    const char** namesptr = names;
    const char** valuesptr = values;
    bool allocated = length > heapsize - 1;
    if (allocated)
    {
        namesptr = (const char**)malloc((length + 1) * sizeof *namesptr);
        valuesptr = (const char**)malloc((length + 1) * sizeof *valuesptr);
    }
    int i = 0;
    const SchemaAttributes::entry* ep = atts.entries();
    for ( ; i < length; ++i, ++ep)
    {
        namesptr[i] = ep->name;
        valuesptr[i] = ep->value;
    }
    namesptr[i] = valuesptr[i] = NULL;
    mOut.StartElement(e->name(), namesptr, valuesptr);
    if (allocated)
    {
        free(namesptr);
        free(valuesptr);
    }

    if (e->IsSet(FLAG_CDATA))
        startCDATA();
}

void
Parser::rectify(Element* e)
{
    Element* sp;
    for ( ; ; )
    {
        for (sp = mStack; sp != NULL; sp = sp->next())
            if (sp->CanContain(e))
                break;
        if (sp != NULL)
            break;
        const Element::Type* ptype = e->parent();
        if (ptype == NULL)
            break;
        Element* parent = new Element(*ptype);
        parent->SetNext(e);
        e = parent;
    }
    if (sp == NULL)
        // Gaak -- don't know what to do.
        return;

    while (mStack != sp)
    {
        if (mStack == NULL
                || mStack->next() == NULL
                || mStack->next()->next() == NULL)
            break;
        restartably_pop();
    }
    while (e != NULL)
    {
        Element* nexte = e->next();
        if (strcmp(e->name(), "<pcdata>") != 0)
            push(e);
        e = nexte;
        restart(e);
    }
    mElement = NULL;
}

char*
Parser::makename(const char* buff, int length, char* out, int outsize)
{
    int i = length + 2 + 1;
    char* start = i > outsize ? (char*)malloc(length + 2 + 1) : out;

    int colons = 0;
    bool protect = true;
    char* p = start;
    for ( ; --length >= 0; buff++)
    {
        char c = *buff;
        if (isupper(c))
            c = (char)tolower(c);
        if (isalpha(c) || c == '_')
        {
            *p++ = c;
            protect = false;
        }
        else if (isdigit(c) || c == '-' || c == '.')
        {
            if (protect)
                *p++ = '_';
            protect = false;
            *p++ = c;
        }
        else if (c == ':' && ++colons == 1)
        {
            if (protect)
                *p++ = '_';
            // Must still protect first char after the colon (namespace id).
            *p++ = c;
        }
    }
    if (p == start || p[-1] == ':')
        *p++ = '_';
    *p = '\0';
    return start;
}

void
Parser::etag_basic(const char* buff, int length)
{
    mElement = NULL;
    const char* name;
    char* freeme = NULL;
    char namebuff[20];
    if (length != 0)
        name = freeme = makename(buff, length, namebuff, sizeof namebuff);
    else
        name = mStack->name();

    Element* sp;
    bool unforced = false;
    for (sp = mStack; sp != NULL; sp = sp->next())
    {
        if (strcmp(sp->name(), name) == 0)
            break;
        if (sp->IsSet(FLAG_NOFORCE))
            unforced = true;
    }
    if (freeme != namebuff)
        free(freeme);

    if (sp == NULL)
        // Ignore unknown etags.
        return;
    if (sp->next() == NULL || sp->next()->next() == NULL)
        return;
    if (unforced)
        // If inside an FLAG_NOFORCE element, preclose the matching element
        sp->Preclose();
    else
    {
        // Restartably pop everything above us.
        while (mStack != sp)
            restartably_pop();
        pop(true);
    }

    // Pop any preclosed elements now at the top.
    while (mStack->IsPreclosed())
        pop(true);
    restart(NULL);
}

const char*
Parser::entity(const char* buff, int length)
{
    if (length < 1)
        return NULL;

    char mybuff[20];
    char* name = (size_t)length < sizeof mybuff
                    ? mybuff : (char*)malloc(length + 1);
    memcpy(name, buff, length);
    name[length] = '\0';

    const char* cp;
    if (name[0] == '#')
    {
        int i = name[1] == 'x' || name[1] == 'X'
            ? (int)strtol(&name[2], NULL, 16)
            : atoi(&name[1]);
        cp = mEntityBuff;
        sprintf(mEntityBuff, "&#%x;", i);
    }
    else
        cp = Schema::TextEntity(name);

    if (name != mybuff)
        free(name);
    return cp;
}

void
Parser::eof()
{
    if (mVirginStack)
        rectify(mPCDATA);
    while (mStack->next() != NULL)
        pop(true);
}

void
Parser::pi(const char* buff, int length)
{
    if (mElement != NULL
            || mPITarget == NULL
            || strcasecmp(mPITarget, "xml") == 0)
        return;
    if (length > 0 && buff[length - 1] == '?')
        // Remove trailing "?".
        length--;
    if (length < PIBUFF_SIZE)
    {
        char data[PIBUFF_SIZE + 1];
        memcpy(data, buff, length);
        data[length] = '\0';
        mOut.ProcessingInstruction(mPITarget, data);
    }
    else
    {
        char* data = makestring(buff, length);
        mOut.ProcessingInstruction(mPITarget, data);
        free(data);
    }
    free(mPITarget);
    mPITarget = NULL;
}

void
Parser::stagc(const char* buff, int length)
{
    if (mElement == NULL)
        return;
    rectify(mElement);
    if (mStack->empty())
        // Force an immediate end tag.
        etag_basic(buff, length);
}

void
Parser::pcdata(const char* buff, int length)
{
    if (length == 0)
        return;

    int i = length;
    for (const char* p = buff; --i >= 0; p++)
        if (!isspace(*p))
            break;
    if (i < 0 && !mStack->CanContain(mPCDATA))
        mOut.IgnorableWhitespace(buff, length);
    else
    {
        rectify(mPCDATA);
        mOut.Characters(buff, length);
    }
}

void
Parser::etag(const char* buff, int length)
{
    // If this is a CDATA element and the tag doesn't match,
    // or isn't properly formed (junk after the name),
    // restart CDATA mode and process the tag as Characters.
    if (mStack->IsSet(FLAG_CDATA))
    {
        const char* currentName = mStack->name();
        bool matches = strlen(currentName) == (size_t)length
                        && memcmp(currentName, buff, length) == 0;
        if (!matches)
        {
            mOut.Characters("</", 2);
            mOut.Characters(buff, length);
            mOut.Characters(">", 1);
            startCDATA();
            return;
        }
    }
    etag_basic(buff, length);
}


void
Parser::adup()
{
    if (mElement == NULL || mAttrName == NULL)
        return;
    mElement->set(mAttrName, strdup(mAttrName));
    if (mAttrName != mAttrNameBuff)
        free(mAttrName);
    mAttrName = NULL;
}


void
Parser::aval(const char* buff, int length)
{
    if (mElement == NULL || mAttrName == NULL)
        return;
    mElement->set(mAttrName, makestring(buff, length));
    if (mAttrName != mAttrNameBuff)
        free(mAttrName);
    mAttrName = NULL;
}


void
Parser::gi(const char* buff, int length)
{
    if (mElement != NULL)
        return;
    char namebuff[20];
    char* name = makename(buff, length, namebuff, sizeof namebuff);
    if (name == NULL)
        return;
    const Element::Type* type = mSchema->Lookup(name);
    if (type == NULL)
        type = mSchema->Add(name, TYPE_EMPTY, TYPE_ANY);
    if (name != namebuff)
        free(name);

    mElement = new Element(*type);
}
