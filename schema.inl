//
// vim:set filetype=cpp:
// This file is made available under the terms of the Apache 2.0
// license which is available at http://www.apache.org/licenses/
//

/// @file
/// The schema for HTML.  Hah, that's funny, isn't it?

/// Table of all text entities.
static entity entities[] =
{
    { "Aacute", "&#xC1;" }, { "aacute", "&#x00E1;" },
    { "Acirc", "&#xC2;" }, { "acirc", "&#x00E2;" },
    { "acute", "&#xB4;" }, { "AElig", "&#x00C6;" },
    { "aelig", "&#xE6;" }, { "Agrave", "&#x00C0;" },
    { "agrave", "&#xE0;" }, { "alefsym", "&#x2135;" },
    { "Alpha", "&#x391;" }, { "alpha", "&#x03B1;" },
    { "amp", "&#x26;" }, { "and", "&#x2227;" },
    { "ang", "&#x2220;" }, { "apos", "'" },
    { "Aring", "&#xC5;" }, { "aring", "&#x00E5;" },
    { "asymp", "&#x2248;" }, { "Atilde", "&#xC3;" },
    { "atilde", "&#xE3;" }, { "Auml", "&#x00C4;" },
    { "auml", "&#xE4;" }, { "bdquo", "&#x201E;" },
    { "Beta", "&#x392;" }, { "beta", "&#x03B2;" },
    { "brvbar", "&#xA6;" }, { "bull", "&#x2022;" },
    { "cap", "&#x2229;" }, { "Ccedil", "&#xC7;" },
    { "ccedil", "&#xE7;" }, { "cedil", "&#x00B8;" },
    { "cent", "&#xA2;" }, { "Chi", "&#x03A7;" },
    { "chi", "&#x3C7;" }, { "circ", "&#x02C6;" },
    { "clubs", "&#x2663;" }, { "cong", "&#x2245;" },
    { "copy", "&#xA9;" }, { "crarr", "&#x21B5;" },
    { "cup", "&#x222A;" }, { "curren", "&#xA4;" },
    { "Dagger", "&#x2021;" }, { "dagger", "&#x2020;" },
    { "dArr", "&#x21D3;" }, { "darr", "&#x2193;" },
    { "deg", "&#xB0;" }, { "Delta", "&#x0394;" },
    { "delta", "&#x3B4;" }, { "diams", "&#x2666;" },
    { "divide", "&#xF7;" }, { "Eacute", "&#x00C9;" },
    { "eacute", "&#xE9;" }, { "Ecirc", "&#x00CA;" },
    { "ecirc", "&#xEA;" }, { "Egrave", "&#x00C8;" },
    { "egrave", "&#xE8;" }, { "empty", "&#x2205;" },
    { "emsp", "&#x2003;" }, { "ensp", "&#x2002;" },
    { "Epsilon", "&#x395;" }, { "epsilon", "&#x03B5;" },
    { "equiv", "&#x2261;" }, { "Eta", "&#x397;" },
    { "eta", "&#x3B7;" }, { "ETH", "&#x00D0;" },
    { "eth", "&#xF0;" }, { "Euml", "&#x00CB;" },
    { "euml", "&#xEB;" }, { "euro", "&#x20AC;" },
    { "exist", "&#x2203;" }, { "fnof", "&#x192;" },
    { "forall", "&#x2200;" }, { "frac12", "&#xBD;" },
    { "frac14", "&#xBC;" }, { "frac34", "&#x00BE;" },
    { "frasl", "&#x2044;" }, { "Gamma", "&#x393;" },
    { "gamma", "&#x3B3;" }, { "ge", "&#x2265;" },
    { "gt", "&#x3E;" }, { "hArr", "&#x21D4;" },
    { "harr", "&#x2194;" }, { "hearts", "&#x2665;" },
    { "hellip", "&#x2026;" }, { "Iacute", "&#xCD;" },
    { "iacute", "&#xED;" }, { "Icirc", "&#x00CE;" },
    { "icirc", "&#xEE;" }, { "iexcl", "&#x00A1;" },
    { "Igrave", "&#xCC;" }, { "igrave", "&#x00EC;" },
    { "image", "&#x2111;" }, { "infin", "&#x221E;" },
    { "int", "&#x222B;" }, { "Iota", "&#x399;" },
    { "iota", "&#x3B9;" }, { "iquest", "&#x00BF;" },
    { "isin", "&#x2208;" }, { "Iuml", "&#xCF;" },
    { "iuml", "&#xEF;" }, { "Kappa", "&#x039A;" },
    { "kappa", "&#x3BA;" }, { "Lambda", "&#x039B;" },
    { "lambda", "&#x3BB;" }, { "lang", "&#x2329;" },
    { "laquo", "&#xAB;" }, { "lArr", "&#x21D0;" },
    { "larr", "&#x2190;" }, { "lceil", "&#x2308;" },
    { "ldquo", "&#x201C;" }, { "le", "&#x2264;" },
    { "lfloor", "&#x230A;" }, { "lowast", "&#x2217;" },
    { "loz", "&#x25CA;" }, { "lrm", "&#x200E;" },
    { "lsaquo", "&#x2039;" }, { "lsquo", "&#x2018;" },
    { "lt", "&#x3C;" }, { "macr", "&#x00AF;" },
    { "mdash", "&#x2014;" }, { "micro", "&#xB5;" },
    { "middot", "&#xB7;" }, { "minus", "&#x2212;" },
    { "Mu", "&#x39C;" }, { "mu", "&#x03BC;" },
    { "nabla", "&#x2207;" }, { "nbsp", "&#xA0;" },
    { "ndash", "&#x2013;" }, { "ne", "&#x2260;" },
    { "ni", "&#x220B;" }, { "not", "&#xAC;" },
    { "notin", "&#x2209;" }, { "nsub", "&#x2284;" },
    { "Ntilde", "&#xD1;" }, { "ntilde", "&#x00F1;" },
    { "Nu", "&#x39D;" }, { "nu", "&#x03BD;" },
    { "Oacute", "&#xD3;" }, { "oacute", "&#x00F3;" },
    { "Ocirc", "&#xD4;" }, { "ocirc", "&#x00F4;" },
    { "OElig", "&#x152;" }, { "oelig", "&#x0153;" },
    { "Ograve", "&#xD2;" }, { "ograve", "&#x00F2;" },
    { "oline", "&#x203E;" }, { "Omega", "&#x3A9;" },
    { "omega", "&#x3C9;" }, { "Omicron", "&#x039F;" },
    { "omicron", "&#x3BF;" }, { "oplus", "&#x2295;" },
    { "or", "&#x2228;" }, { "ordf", "&#xAA;" },
    { "ordm", "&#xBA;" }, { "Oslash", "&#x00D8;" },
    { "oslash", "&#xF8;" }, { "Otilde", "&#x00D5;" },
    { "otilde", "&#xF5;" }, { "otimes", "&#x2297;" },
    { "Ouml", "&#xD6;" }, { "ouml", "&#x00F6;" },
    { "para", "&#xB6;" }, { "part", "&#x2202;" },
    { "permil", "&#x2030;" }, { "perp", "&#x22A5;" },
    { "Phi", "&#x3A6;" }, { "phi", "&#x03C6;" },
    { "Pi", "&#x3A0;" }, { "pi", "&#x03C0;" },
    { "piv", "&#x3D6;" }, { "plusmn", "&#x00B1;" },
    { "pound", "&#xA3;" }, { "Prime", "&#x2033;" },
    { "prime", "&#x2032;" }, { "prod", "&#x220F;" },
    { "prop", "&#x221D;" }, { "Psi", "&#x3A8;" },
    { "psi", "&#x3C8;" }, { "quot", "&#x0022;" },
    { "radic", "&#x221A;" }, { "rang", "&#x232A;" },
    { "raquo", "&#xBB;" }, { "rArr", "&#x21D2;" },
    { "rarr", "&#x2192;" }, { "rceil", "&#x2309;" },
    { "rdquo", "&#x201D;" }, { "real", "&#x211C;" },
    { "reg", "&#xAE;" }, { "rfloor", "&#x230B;" },
    { "Rho", "&#x3A1;" }, { "rho", "&#x03C1;" },
    { "rlm", "&#x200F;" }, { "rsaquo", "&#x203A;" },
    { "rsquo", "&#x2019;" }, { "sbquo", "&#x201A;" },
    { "Scaron", "&#x160;" }, { "scaron", "&#x0161;" },
    { "sdot", "&#x22C5;" }, { "sect", "&#xA7;" },
    { "shy", "&#xAD;" }, { "Sigma", "&#x03A3;" },
    { "sigma", "&#x3C3;" }, { "sigmaf", "&#x03C2;" },
    { "sim", "&#x223C;" }, { "spades", "&#x2660;" },
    { "sub", "&#x2282;" }, { "sube", "&#x2286;" },
    { "sum", "&#x2211;" }, { "sup", "&#x2283;" },
    { "sup1", "&#xB9;" }, { "sup2", "&#x00B2;" },
    { "sup3", "&#xB3;" }, { "supe", "&#x2287;" },
    { "szlig", "&#xDF;" }, { "Tau", "&#x03A4;" },
    { "tau", "&#x3C4;" }, { "there4", "&#x2234;" },
    { "Theta", "&#x398;" }, { "theta", "&#x03B8;" },
    { "thetasym", "&#x3D1;" }, { "thinsp", "&#x2009;" },
    { "THORN", "&#xDE;" }, { "thorn", "&#x00FE;" },
    { "tilde", "&#x2DC;" }, { "times", "&#x00D7;" },
    { "trade", "&#x2122;" }, { "Uacute", "&#xDA;" },
    { "uacute", "&#xFA;" }, { "uArr", "&#x21D1;" },
    { "uarr", "&#x2191;" }, { "Ucirc", "&#xDB;" },
    { "ucirc", "&#xFB;" }, { "Ugrave", "&#x00D9;" },
    { "ugrave", "&#xF9;" }, { "uml", "&#x00A8;" },
    { "upsih", "&#x3D2;" }, { "Upsilon", "&#x03A5;" },
    { "upsilon", "&#x3C5;" }, { "Uuml", "&#x00DC;" },
    { "uuml", "&#xFC;" }, { "weierp", "&#x2118;" },
    { "Xi", "&#x39E;" }, { "xi", "&#x03BE;" },
    { "Yacute", "&#xDD;" }, { "yacute", "&#x00FD;" },
    { "yen", "&#xA5;" }, { "Yuml", "&#x0178;" },
    { "yuml", "&#xFF;" }, { "Zeta", "&#x0396;" },
    { "zeta", "&#x3B6;" }, { "zwj", "&#x200D;" },
    { "zwnj", "&#x200C;" }
};

/// We want inline literal strings, this macro casts-away const'ness.
/// @param s The string literal cocast
#define C(s) const_cast<char*>(s)

/// Create an attribute (with no value) of type "other"
/// @param str The name of the attribute
#define OTHER_ATTR(str) { str, NULL, DocAttributes::TYPE_OTHER }

/// Create an ID attribute
/// @param str The name of the attribute
/// @param val The default value of the attribute
#define ID_ATTR(str, val) { str, val, DocAttributes::TYPE_ID }

/// Define the standard base attributes that are used by almost everyone
#define STD_BASE_ATTRS \
    { "class" }, { "dir" }, ID_ATTR("id", NULL), { "lang" }

/// Define a set of schema attributes that are just the standard base ones
/// @param AT_xxx the name of the attribute definition.
#define JUST_STD_BASE_ATTRS(AT_xxx) \
    static SchemaAttributes::entry AT_xxx[] = { STD_BASE_ATTRS }

/// Just in case the compiler doesn't collapse identical string constants.
static const char* BODY = "body";

/// @note We do not document all the individal element and attribute entries.
/// @cond UNDOCUMENTED
static type TT_root = { "<root>", 0, NULL,
    TYPE_ROOT, TYPE_EMPTY
};

static type TT_html = { "html", FLAG_NONE, "<root>",
    TYPE_HTML, TYPE_ROOT
};
JUST_STD_BASE_ATTRS(AT_html);

static type TT_frameset = { "frameset", FLAG_NONE, "html",
    TYPE_FRAME, TYPE_FRAME | TYPE_HTML
};
JUST_STD_BASE_ATTRS(AT_frameset);

static type TT_frame = { "frame", FLAG_NONE, "frameset",
    TYPE_EMPTY, TYPE_FRAME
};
static SchemaAttributes::entry AT_frame[] = { STD_BASE_ATTRS,
    { "frameborder", C("1") }, OTHER_ATTR("noresize"),
    { "scrolling", C("auto") }
};

static type TT_noframes = { "noframes", FLAG_NONE, "html",
    TYPE_BODY | TYPE_BLOCK | TYPE_INLINE, TYPE_BLOCK | TYPE_HTML | TYPE_FRAME
};
JUST_STD_BASE_ATTRS(AT_noframes);

static type TT_script = { "script", FLAG_CDATA, "html",
    TYPE_PCDATA, TYPE_ANY & ~TYPE_ROOT
};
static SchemaAttributes::entry AT_script[] = { STD_BASE_ATTRS,
    OTHER_ATTR("defer")
};

static type TT_head = { "head", FLAG_NONE, "html",
    TYPE_HEAD, TYPE_HTML
};
JUST_STD_BASE_ATTRS(AT_head);

static type TT_base = { "base", FLAG_NONE, "head",
    TYPE_EMPTY, TYPE_HEAD
};
JUST_STD_BASE_ATTRS(AT_base);

static type TT_isindex = { "isindex", FLAG_NONE, "head",
    TYPE_EMPTY, TYPE_HEAD
};
JUST_STD_BASE_ATTRS(AT_isindex);

static type TT_link = { "link", FLAG_NONE, "head",
    TYPE_EMPTY, TYPE_HEAD
};
static SchemaAttributes::entry AT_link[] = { STD_BASE_ATTRS,
    { "hreflang" }
};

static type TT_meta = { "meta", FLAG_NONE, "head",
    TYPE_EMPTY, TYPE_HEAD
};
static SchemaAttributes::entry AT_meta[] = { STD_BASE_ATTRS,
    { "http-equiv" }, { "name" }
};

static type TT_style = { "style", FLAG_CDATA, "head",
    TYPE_PCDATA, TYPE_HEAD | TYPE_INLINE
};
JUST_STD_BASE_ATTRS(AT_style);

static type TT_title = { "title", FLAG_NONE, "head",
    TYPE_PCDATA, TYPE_HEAD
};
JUST_STD_BASE_ATTRS(AT_title);

static type TT_body = { "body", FLAG_NONE, "html",
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_HTML | TYPE_BODY
};
JUST_STD_BASE_ATTRS(AT_body);

static type TT_pcdata = { "<pcdata>", 0, BODY,
    TYPE_EMPTY, TYPE_PCDATA
};
static type TT_object = { "object", 0, BODY,
    TYPE_PCDATA | TYPE_PARAM | TYPE_INLINE | TYPE_BLOCK,
    TYPE_HEAD | TYPE_INLINE | TYPE_NOLINK
};
static SchemaAttributes::entry AT_object[] = { STD_BASE_ATTRS,
    { "align" }, OTHER_ATTR("declare"), { "tabindex" }
};

static type TT_param = { "param", FLAG_NONE, "object",
    TYPE_EMPTY, TYPE_PARAM
};
static SchemaAttributes::entry AT_param[] = { STD_BASE_ATTRS,
    { "valuetype", C("data") }
};

static type TT_a = { "a", 0, BODY,
    TYPE_PCDATA | TYPE_NOLINK, TYPE_INLINE
};
static SchemaAttributes::entry AT_a[] = { STD_BASE_ATTRS,
    { "hreflang" }, { "shape", C("rect") }, { "tabindex" }
};

static type TT_abbr = { "abbr", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_abbr);

static type TT_acronym = { "acronym", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_acronym);

static type TT_address = { "address", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_P, TYPE_BLOCK
};
JUST_STD_BASE_ATTRS(AT_address);

static type TT_applet = { "applet", 0, BODY,
    TYPE_PCDATA | TYPE_PARAM | TYPE_INLINE | TYPE_BLOCK, TYPE_INLINE | TYPE_NOLINK
};
static SchemaAttributes::entry AT_applet[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_map = { "map", 0, BODY,
    TYPE_BLOCK | TYPE_AREA, TYPE_INLINE
};
JUST_STD_BASE_ATTRS(AT_map);

static type TT_b = { "b", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_b);

static type TT_basefont = { "basefont", 0, BODY,
    TYPE_EMPTY, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_basefont);

static type TT_bdo = { "bdo", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_bdo);

static type TT_big = { "big", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_big);

static type TT_blockquote = { "blockquote", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_BLOCK
};
JUST_STD_BASE_ATTRS(AT_blockquote);

static type TT_br = { "br", 0, BODY,
    TYPE_EMPTY, TYPE_INLINE | TYPE_NOLINK
};
static SchemaAttributes::entry AT_br[] = { STD_BASE_ATTRS,
    { "clear", C("none") }
};

static type TT_center = { "center", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_BLOCK
};
JUST_STD_BASE_ATTRS(AT_center);

static type TT_cite = { "cite", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_cite);

static type TT_code = { "code", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_code);

static type TT_del = { "del", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_INLINE | TYPE_BLOCK
};
JUST_STD_BASE_ATTRS(AT_del);

static type TT_dfn = { "dfn", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_dfn);

static type TT_dir = { "dir", 0, BODY,
    TYPE_LI, TYPE_BLOCK
};
static SchemaAttributes::entry AT_dir[] = { STD_BASE_ATTRS,
    OTHER_ATTR("compact")
};

static type TT_div = { "div", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_BLOCK
};
static SchemaAttributes::entry AT_div[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_dl = { "dl", 0, BODY,
    TYPE_DEF, TYPE_BLOCK
};
static SchemaAttributes::entry AT_dl[] = { STD_BASE_ATTRS,
    OTHER_ATTR("compact")
};

static type TT_em = { "em", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_em);

static type TT_font = { "font", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_font);

static type TT_form = { "form", FLAG_NOFORCE, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_NOLINK | TYPE_BLOCK | TYPE_TR | TYPE_CELL, TYPE_BLOCK | TYPE_FORM,
};
static SchemaAttributes::entry AT_form[] = { STD_BASE_ATTRS,
    { "enctype", C("application/x-www-form-urlencoded") },
    { "method", C("get") }
};

static type TT_h1 = { "h1", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_BLOCK
};
static SchemaAttributes::entry AT_h1[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_h2 = { "h2", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_BLOCK
};
static SchemaAttributes::entry AT_h2[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_h3 = { "h3", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_BLOCK
};
static SchemaAttributes::entry AT_h3[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_h4 = { "h4", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_BLOCK
};
static SchemaAttributes::entry AT_h4[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_h5 = { "h5", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_BLOCK
};
static SchemaAttributes::entry AT_h5[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_h6 = { "h6", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_BLOCK
};
static SchemaAttributes::entry AT_h6[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_hr = { "hr", 0, BODY,
    TYPE_EMPTY, TYPE_BLOCK
};
static SchemaAttributes::entry AT_hr[] = { STD_BASE_ATTRS,
    { "hr" }, OTHER_ATTR("noshade")
};

static type TT_i = { "i", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_i);

static type TT_iframe = { "iframe", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_INLINE | TYPE_NOLINK
};
static SchemaAttributes::entry AT_iframe[] = { STD_BASE_ATTRS,
    { "align" }, { "frameborder", C("1") }, { "scrolling", C("auto") }
};

static type TT_img = { "img", 0, BODY,
    TYPE_EMPTY, TYPE_INLINE | TYPE_NOLINK
};
static SchemaAttributes::entry AT_img[] = { STD_BASE_ATTRS,
    { "align" }, OTHER_ATTR("ismap")
};

static type TT_ins = { "ins", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_INLINE | TYPE_BLOCK
};
JUST_STD_BASE_ATTRS(AT_ins);

static type TT_kbd = { "kbd", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_kbd);

static type TT_menu = { "menu", 0, BODY,
    TYPE_LI, TYPE_BLOCK
};
static SchemaAttributes::entry AT_menu[] = { STD_BASE_ATTRS,
    OTHER_ATTR("compact")
};

static type TT_noscript = { "noscript", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_BLOCK
};
JUST_STD_BASE_ATTRS(AT_noscript);

static type TT_ol = { "ol", 0, BODY,
    TYPE_LI, TYPE_BLOCK
};
static SchemaAttributes::entry AT_ol[] = { STD_BASE_ATTRS,
    OTHER_ATTR("compact"), { "start" }
};

static type TT_p = { "p", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_BLOCK | TYPE_P
};
static SchemaAttributes::entry AT_p[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_pre = { "pre", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_BLOCK
};
static SchemaAttributes::entry AT_pre[] = { STD_BASE_ATTRS,
    { "width" }
};

static type TT_q = { "q", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_q);

static type TT_s = { "s", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_s);

static type TT_samp = { "samp", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_samp);

static type TT_small = { "small", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_small);

static type TT_span = { "span", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_span);

static type TT_strike = { "strike", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_strike);

static type TT_strong = { "strong", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_strong);

static type TT_sub = { "sub", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_sub);

static type TT_sup = { "sup", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_sup);

static type TT_table = { "table", FLAG_NOFORCE, BODY,
    TYPE_FORM | TYPE_TABLE, TYPE_BLOCK
};
static SchemaAttributes::entry AT_table[] = { STD_BASE_ATTRS,
    { "align" }, { "frame" }, { "rules" }
};

static type TT_tt = { "tt", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_tt);

static type TT_u = { "u", FLAG_RESTART, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_u);

static type TT_ul = { "ul", 0, BODY,
    TYPE_LI, TYPE_BLOCK
};
static SchemaAttributes::entry AT_ul[] = { STD_BASE_ATTRS,
    OTHER_ATTR("compact"), { "type" }
};

static type TT_var = { "var", 0, BODY,
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
JUST_STD_BASE_ATTRS(AT_var);

static type TT_area = { "area", FLAG_NONE, "map",
    TYPE_EMPTY, TYPE_AREA
};
static SchemaAttributes::entry AT_area[] = { STD_BASE_ATTRS,
    OTHER_ATTR("nohref"), { "shape", C("rect") }, { "tabindex" }
};

static type TT_button = { "button", FLAG_NONE, "form",
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_INLINE | TYPE_NOLINK
};
static SchemaAttributes::entry AT_button[] = { STD_BASE_ATTRS,
    OTHER_ATTR("disabled"), { "tabindex" }, ID_ATTR("type", C("submit"))
};

static type TT_fieldset = { "fieldset", FLAG_NONE, "form",
    TYPE_PCDATA | TYPE_LEGEND | TYPE_INLINE | TYPE_BLOCK, TYPE_BLOCK
};
JUST_STD_BASE_ATTRS(AT_fieldset);

static type TT_legend = { "legend", FLAG_NONE, "fieldset",
    TYPE_PCDATA | TYPE_INLINE, TYPE_LEGEND
};
static SchemaAttributes::entry AT_legend[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_input = { "input", FLAG_NONE, "form",
    TYPE_EMPTY, TYPE_INLINE | TYPE_NOLINK
};
static SchemaAttributes::entry AT_input[] = { STD_BASE_ATTRS,
    { "align" }, OTHER_ATTR("checked"), OTHER_ATTR("disabled"),
    OTHER_ATTR("ismap"), { "maxlength" }, OTHER_ATTR("readonly"),
    { "tabindex" }, ID_ATTR("type", C("text"))
};

static type TT_label = { "label", FLAG_NONE, "form",
    TYPE_PCDATA | TYPE_INLINE, TYPE_INLINE | TYPE_NOLINK
};
static SchemaAttributes::entry AT_label[] = { STD_BASE_ATTRS,
    OTHER_ATTR("for")
};

static type TT_select = { "select", FLAG_NONE, "form",
    TYPE_OPTIONS, TYPE_INLINE
};
static SchemaAttributes::entry AT_select[] = { STD_BASE_ATTRS,
    OTHER_ATTR("disabled"), OTHER_ATTR("multiple"), { "size" },
    { "tabindex" }
};

static type TT_optgroup = { "optgroup", FLAG_NONE, "select",
    TYPE_OPTIONS, TYPE_OPTIONS
};
static SchemaAttributes::entry AT_optgroup[] = { STD_BASE_ATTRS,
    OTHER_ATTR("disabled")
};

static type TT_option = { "option", FLAG_NONE, "select",
    TYPE_PCDATA, TYPE_OPTION | TYPE_OPTIONS
};
static SchemaAttributes::entry AT_option[] = { STD_BASE_ATTRS,
    OTHER_ATTR("disabled"), OTHER_ATTR("selected")
};

static type TT_textarea = { "textarea", FLAG_NONE, "form",
    TYPE_PCDATA, TYPE_INLINE
};
static SchemaAttributes::entry AT_textarea[] = { STD_BASE_ATTRS,
    { "cols" }, OTHER_ATTR("disabled"), OTHER_ATTR("readonly"),
    { "rows" }, { "tabindex" }
};

static type TT_caption = { "caption", FLAG_NONE, "table",
    TYPE_PCDATA | TYPE_INLINE, TYPE_TABLE
};
static SchemaAttributes::entry AT_caption[] = { STD_BASE_ATTRS,
    { "align" }
};

static type TT_col = { "col", FLAG_NONE, "table",
    TYPE_EMPTY, TYPE_COL | TYPE_TABLE
};
static SchemaAttributes::entry AT_col[] = { STD_BASE_ATTRS,
    { "align" }, { "span", C("1") }, { "valign" }
};

static type TT_colgroup = { "colgroup", FLAG_NONE, "table",
    TYPE_COL, TYPE_TABLE
};
static SchemaAttributes::entry AT_colgroup[] = { STD_BASE_ATTRS,
    { "align" }, { "span", C("1") }, { "valign" }
};

static type TT_tbody = { "tbody", FLAG_NONE, "table",
    TYPE_TR, TYPE_TABLE
};
static SchemaAttributes::entry AT_tbody[] = { STD_BASE_ATTRS,
    { "align" }, { "valign" }
};

static type TT_tfoot = { "tfoot", FLAG_NONE, "table",
    TYPE_TR, TYPE_TABLE
};
static SchemaAttributes::entry AT_tfoot[] = { STD_BASE_ATTRS,
    { "align" }, { "valign" }
};

static type TT_thead = { "thead", FLAG_NONE, "table",
    TYPE_TR, TYPE_TABLE
};
static SchemaAttributes::entry AT_thead[] = { STD_BASE_ATTRS,
    { "align" }, { "valign" }
};

static type TT_tr = { "tr", FLAG_NONE, "tbody",
    TYPE_FORM | TYPE_CELL, TYPE_TR | TYPE_TABLE
};
static SchemaAttributes::entry AT_tr[] = { STD_BASE_ATTRS,
    { "align" }, { "valign" }
};

static type TT_td = { "td", FLAG_NONE, "tr",
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_CELL
};
static SchemaAttributes::entry AT_td[] = { STD_BASE_ATTRS,
    { "align" }, { "colspan", C("1") }, OTHER_ATTR("headers"),
    OTHER_ATTR("nowrap"), { "rowspan", C("1") }, { "scope" },
    { "valign" }
};

static type TT_th = { "th", FLAG_NONE, "tr",
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_CELL
};
static SchemaAttributes::entry AT_th[] = { STD_BASE_ATTRS,
    { "align" }, { "colspan", C("1") }, OTHER_ATTR("headers"),
    OTHER_ATTR("nowrap"), { "rowspan", C("1") }, { "scope" },
    { "valign" }
};

static type TT_dd = { "dd", FLAG_NONE, "dl",
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_DEF
};
JUST_STD_BASE_ATTRS(AT_dd);

static type TT_dt = { "dt", FLAG_NONE, "dl",
    TYPE_PCDATA | TYPE_INLINE, TYPE_DEF
};
JUST_STD_BASE_ATTRS(AT_dt);

static type TT_li = { "li", FLAG_NONE, "ul",
    TYPE_PCDATA | TYPE_INLINE | TYPE_BLOCK, TYPE_LI
};
static SchemaAttributes::entry AT_li[] = { STD_BASE_ATTRS,
    { "value" }
};
/// @endcond

#undef C
#undef OTHER_ATTR
#undef ID_ATTR
#undef STD_BASE_ATTRS
#undef JUST_STD_BASE_ATTRS

/// Define an entry that has specified attributes.
/// @param s The base name of the element and attribute structures
#define ENTRY(s) { &TT_##s, AT_##s, sizeof AT_##s / sizeof AT_##s[0] }

/// Define an entry that with no attributes
/// @param s The base name of the element structure
#define NOATTRS(s) { &TT_##s, 0, 0 }

/// Table of all element definitions.
static schema_def definitions[] = 
{
    NOATTRS(root), ENTRY(html), ENTRY(frameset), ENTRY(frame),
    ENTRY(noframes), ENTRY(script), ENTRY(head), ENTRY(base),
    ENTRY(isindex), ENTRY(link), ENTRY(meta), ENTRY(style),
    ENTRY(title), ENTRY(body), NOATTRS(pcdata), ENTRY(object),
    ENTRY(param), ENTRY(a), ENTRY(abbr), ENTRY(acronym),
    ENTRY(address), ENTRY(applet), ENTRY(map), ENTRY(b),
    ENTRY(basefont), ENTRY(bdo), ENTRY(big), ENTRY(blockquote),
    ENTRY(br), ENTRY(center), ENTRY(cite), ENTRY(code),
    ENTRY(del), ENTRY(dfn), ENTRY(dir), ENTRY(div), ENTRY(dl),
    ENTRY(em), ENTRY(font), ENTRY(form), ENTRY(h1), ENTRY(h2),
    ENTRY(h3), ENTRY(h4), ENTRY(h5), ENTRY(h6), ENTRY(hr), ENTRY(i),
    ENTRY(iframe), ENTRY(img), ENTRY(ins), ENTRY(kbd), ENTRY(menu),
    ENTRY(noscript), ENTRY(ol), ENTRY(p), ENTRY(pre), ENTRY(q),
    ENTRY(s), ENTRY(samp), ENTRY(small), ENTRY(span), ENTRY(strike),
    ENTRY(strong), ENTRY(sub), ENTRY(sup), ENTRY(table), ENTRY(tt),
    ENTRY(u), ENTRY(ul), ENTRY(var), ENTRY(area), ENTRY(button),
    ENTRY(fieldset), ENTRY(legend), ENTRY(input), ENTRY(label),
    ENTRY(select), ENTRY(optgroup), ENTRY(option), ENTRY(textarea),
    ENTRY(caption), ENTRY(col), ENTRY(colgroup), ENTRY(tbody),
    ENTRY(tfoot), ENTRY(thead), ENTRY(tr), ENTRY(td), ENTRY(th),
    ENTRY(dd), ENTRY(dt), ENTRY(li)
};

#undef NOATTRS
#undef ENTRY
