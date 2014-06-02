//
// vim:set filetype=cpp:
// This file is made available under the terms of the Apache 2.0
// license which is available at http://www.apache.org/licenses/
//

/// @file
/// Parser/scanner data tables.

/// @defgroup transition_table Parser transition table entries
/// If we match the character, do the action and then transition to the
/// specified state. In order to placate doxygen's parser, we have
/// "superfluous" namespace declarations in this section.
/// @{
const TagSoup::Parser::Transition TagSoup::Parser::T_ANAME[] =
{
    { '/',  A_ANAME_ADUP, &S_EMPTYTAG },
    { '=',  A_ANAME, &S_AVAL },
    { '>',  A_ANAME_ADUP_STAGC, &S_PCDATA },
    { ' ',  A_ANAME, &S_EQ },
    { '\r', A_ANAME, &S_EQ },
    { '\n', A_ANAME, &S_EQ },
    { '\t', A_ANAME, &S_EQ }
};

const TagSoup::Parser::Transition TagSoup::Parser::T_APOS[] =
{
    { '&',  A_PUSH_SAVE, &S_ENT },
    { '\'', A_AVAL, &S_TAGWS },
    { ' ',  A_SP,   &S_APOS },
    { '\r', A_SP,   &S_APOS },
    { '\n', A_SP,   &S_APOS },
    { '\t', A_SP,   &S_APOS },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_AVAL[] =
{
    { '"',  A_SKIP, &S_QUOT },
    { '\'', A_SKIP, &S_APOS },
    { '>',  A_AVAL_STAGC, &S_PCDATA },
    { ' ',  A_SKIP, &S_AVAL },
    { '\r', A_SKIP, &S_AVAL },
    { '\n', A_SKIP, &S_AVAL },
    { '\t', A_SKIP, &S_AVAL },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_BB[] =
{
    { 'C',  A_SKIP, &S_BBC },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_BBC[] =
{
    { 'D',  A_SKIP, &S_BBCD },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_BBCD[] =
{
    { 'A',  A_SKIP, &S_BBCDA },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_BBCDA[] =
{
    { 'T',  A_SKIP, &S_BBCDAT },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_BBCDAT[] =
{
    { 'A',  A_SKIP, &S_BBCDATA },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_BBCDATA[] =
{
    { '[',  A_SKIP, &S_CDSECT },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_CCRLF[] =
{
    { '\n', A_SKIP, &S_CDATA },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_CDATA[] =
{
    { '<',  A_SAVE, &S_CDATA2 },
    { '\r', A_LF,   &S_CCRLF },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_CDATA2[] =
{
    { '/',  A_UNSAVE, &S_ETAG },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_CDSECT[] =
{
    { ']',  A_SAVE, &S_CDSECT1 },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_CDSECT1[] =
{
    { ']',  A_SAVE, &S_CDSECT2 },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_CDSECT2[] =
{
    { '>',  A_CDATA, &S_PCDATA },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_COM[] =
{
    { '-',  A_SKIP, &S_COM2 },
    { '\r', A_LF,   &S_COMCRLF },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_COM2[] =
{
    { '-',  A_SKIP, &S_COM3 },
    { '\r', A_LF,   &S_COMCRLF },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_COM3[] =
{
    { '-',  A_SKIP, &S_COM4 },
    { '\r', A_LF,   &S_COMCRLF },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_COM4[] =
{
    { '-',  A_MINUS3, &S_COM4 },
    { '>',  A_CMNT, &S_PCDATA },
    { '\r', A_LF,   &S_COMCRLF },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_COMCRLF[] =
{
    { '\n', A_SKIP, &S_COM },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_CRLF[] =
{
    { '\n', A_SKIP, &S_PCDATA },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_DECL[] =
{
    { '-',  A_SKIP, &S_COM },
    { '>',  A_SKIP, &S_PCDATA },
    { '[',  A_SKIP, &S_BB },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_DECL2[] =
{
    { '>',  A_DECL, &S_PCDATA },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_EMPTYTAG[] =
{
    { '>',  A_EMPTYTAG, &S_PCDATA },
    { ' ',  A_SKIP, &S_TAGWS },
    { '\r', A_SKIP, &S_TAGWS },
    { '\n', A_SKIP, &S_TAGWS },
    { '\t', A_SKIP, &S_TAGWS },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_EQ[] =
{
    { '=',  A_SKIP, &S_AVAL },
    { '>',  A_ADUP_STAGC, &S_PCDATA },
    { ' ',  A_SKIP, &S_EQ },
    { '\r', A_SKIP, &S_EQ },
    { '\n', A_SKIP, &S_EQ },
    { '\t', A_SKIP, &S_EQ },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_ETAG[] =
{
    { '>',  A_ETAG, &S_PCDATA },
    { ' ',  A_SKIP, &S_ETAG },
    { '\r', A_SKIP, &S_ETAG },
    { '\n', A_SKIP, &S_ETAG },
    { '\t', A_SKIP, &S_ETAG },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_GI[] =
{
    { '/',  A_SKIP, &S_EMPTYTAG },
    { '>',  A_GI_STAGC, &S_PCDATA },
    { ' ',  A_GI, &S_TAGWS },
    { '\r', A_GI, &S_TAGWS },
    { '\n', A_GI, &S_TAGWS },
    { '\t', A_GI, &S_TAGWS },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_PCDATA[] =
{
    { '&',  A_PCDATA_PUSH_SAVE, &S_ENT },
    { '<',  A_PCDATA, &S_TAG },
    { '\r', A_LF,   &S_CRLF },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_PI[] =
{
    { '>',  A_PI,   &S_PCDATA },
    { '\r', A_LF,   &S_PICRLF },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_PICRLF[] =
{
    { '\n', A_SKIP, &S_PI },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_PITARGET[] =
{
    { '>',  A_PITARGET_PI, &S_PCDATA },
    { ' ',  A_PITARGET, &S_PI },
    { '\r', A_PITARGET, &S_PI },
    { '\n', A_PITARGET, &S_PI },
    { '\t', A_PITARGET, &S_PI },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_QUOT[] =
{
    { '"',  A_AVAL, &S_TAGWS },
    { '&',  A_PUSH_SAVE, &S_ENT },
    { ' ',  A_SP,   &S_QUOT },
    { '\r', A_SP,   &S_QUOT },
    { '\n', A_SP,   &S_QUOT },
    { '\t', A_SP,   &S_QUOT },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_STAGC[] =
{
    { '>',  A_AVAL_STAGC, &S_PCDATA },
    { ' ',  A_AVAL, &S_TAGWS },
    { '\r', A_AVAL, &S_TAGWS },
    { '\n', A_AVAL, &S_TAGWS },
    { '\t', A_AVAL, &S_TAGWS },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_TAG[] =
{
    { '!',  A_SKIP, &S_DECL },
    { '/',  A_SKIP, &S_ETAG },
    { '?',  A_SKIP, &S_PITARGET },
    { ' ',  A_LT,   &S_PCDATA },
    { '\r', A_LT,   &S_PCDATA },
    { '\n', A_LT,   &S_PCDATA },
    { '\t', A_LT,   &S_PCDATA },
};

const TagSoup::Parser::Transition TagSoup::Parser::T_TAGWS[] =
{
    { '/',  A_SKIP, &S_EMPTYTAG },
    { '>',  A_STAGC, &S_PCDATA },
    { ' ',  A_SKIP, &S_TAGWS },
    { '\r', A_SKIP, &S_TAGWS },
    { '\n', A_SKIP, &S_TAGWS },
    { '\t', A_SKIP, &S_TAGWS },
};

/// @}

/// @defgroup state_machine Parser state machine
/// Most states have a transition table that specifies where to go next.
/// All of them have a default setting if we don't match, and an action to
/// do if we hit EOF. For example, while collecting an attribute value
/// (S_AVAL state), we keep keep collecting until we see the close-quote.
/// @{

/// Create a state entry that uses a transition table.
/// Used to create the TagSoup::Parser::S_ANAME, etc., globals.
/// @param x The base name of the state and transition table
/// @param defaultaction Value of the defaultaction field
/// @param defaultstate Value of the defaultstate field
/// @param eofaction Valeu for the eofaction field
#define ENTRY(x, defaultaction, defaultstate, eofaction) \
const TagSoup::Parser::State TagSoup::Parser::S_##x = { \
    defaultaction, &defaultstate, eofaction, \
    sizeof Parser::T_##x / sizeof Parser::T_##x[0], T_##x }

/// Create a state entry that has no transition table.
/// @param x The base name of the state
/// @param defaultaction Value of the defaultaction field
/// @param defaultstate Value of the defaultstate field
/// @param eofaction Valeu for the eofaction field
#define ENTRY1(x, defaultaction, defaultstate, eofaction) \
const TagSoup::Parser::State TagSoup::Parser::S_##x = { \
    defaultaction, &defaultstate, eofaction, \
    0, NULL }

/// @note We do not document all the individal state machine entries.
/// @}

/// @cond UNDOCUMENTED
ENTRY(ANAME, A_SAVE, S_ANAME, A_ANAME_ADUP_STAGC);
ENTRY(APOS, A_SAVE, S_APOS, A_AVAL_STAGC);
ENTRY(AVAL, A_SAVE, S_STAGC, A_AVAL_STAGC);
ENTRY(BB, A_SKIP, S_DECL, A_SKIP);
ENTRY(BBC, A_SKIP, S_DECL, A_SKIP);
ENTRY(BBCD, A_SKIP, S_DECL, A_SKIP);
ENTRY(BBCDA, A_SKIP, S_DECL, A_SKIP);
ENTRY(BBCDAT, A_SKIP, S_DECL, A_SKIP);
ENTRY(BBCDATA, A_SKIP, S_DECL, A_SKIP);
ENTRY(CCRLF, A_UNGET, S_CDATA, A_SKIP);
ENTRY(CDATA, A_SAVE, S_CDATA, A_PCDATA);
ENTRY(CDATA2, A_SAVE, S_CDATA, A_UNSAVE);
ENTRY(CDSECT, A_SAVE, S_CDSECT, A_SKIP);
ENTRY(CDSECT1, A_SAVE, S_CDSECT, A_SKIP);
ENTRY(CDSECT2, A_SAVE, S_CDSECT, A_SKIP);
ENTRY(COM, A_SAVE, S_COM2, A_CMNT);
ENTRY(COM2, A_SAVE, S_COM2, A_CMNT);
ENTRY(COM3, A_MINUS, S_COM2, A_CMNT);
ENTRY(COM4, A_MINUS2, S_COM2, A_CMNT);
ENTRY(COMCRLF, A_UNGET, S_COM, A_CMNT);
ENTRY(CRLF, A_UNGET, S_PCDATA, A_SKIP);
ENTRY(DECL, A_SAVE, S_DECL2, A_SKIP);
ENTRY(DECL2, A_SAVE, S_DECL2, A_SKIP);
ENTRY(EMPTYTAG, A_SAVE, S_ANAME, A_SAVE);
ENTRY1(ENT, A_ENTITY, S_ENT, A_ENTITY);
ENTRY(EQ, A_ADUP_SAVE, S_ANAME, A_ADUP_STAGC);
ENTRY(ETAG, A_SAVE, S_ETAG, A_ETAG);
ENTRY(GI, A_SAVE, S_GI, A_SKIP);
ENTRY1(NCR, A_ENTITY, S_NCR, A_ENTITY);
ENTRY(PCDATA, A_SAVE, S_PCDATA, A_PCDATA);
ENTRY(PI, A_SAVE, S_PI, A_PI);
ENTRY(PICRLF, A_UNGET, S_PI, A_PI);
ENTRY(PITARGET, A_SAVE, S_PITARGET, A_PITARGET_PI);
ENTRY(QUOT, A_SAVE, S_QUOT, A_AVAL_STAGC);
ENTRY(STAGC, A_SAVE, S_STAGC, A_AVAL_STAGC);
ENTRY(TAG, A_SAVE, S_GI, A_LT_PCDATA);
ENTRY(TAGWS, A_SAVE, S_ANAME, A_STAGC);
ENTRY1(XNCR, A_ENTITY, S_XNCR, A_ENTITY);
/// @endcond

#undef ENTRY
#undef ENTRY1

