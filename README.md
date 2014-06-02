tagsoup4cpp
===========

This is a C++ implementation of John Cowan's tagsoup HTML parser.

It is more than a translation, because I removed as much of the generic
framework as I could, so this code is only useful for converting HTML
into XHTML.  I also tried to be ruthlessly efficient. Part of that
includes (manually) alias'ing pointers, handing off ownership across
class boundaries with impunity, and so on.  Therefore, if you try to use
this code in other packages, make sure you understand the lifetimes of
the various pointers; valgrind is your friend here.

Thanks to John Cowan for the original code. Any bugs are mine.
The brilliance of TagSoup is in its tables and scanner callbacks.
It should therefore not be surprising that that code is basically
unchanged, while the scaffolding had the major surgery.

The code in schema.hpp needs a hashtable package. I used "lhash" from
OpenSSL, with a few patches so that it can be used standalone (i.e.,
without the rest of OpenSSL).  The "getlhash" script fetches the files
from the OpenSSL CVS repository and patches them.

The rest of the code is distributed under the Apache 2.0 license. It
is derived from a version of tagsoup which was obtained under the same
license.

--Rich Salz <rich.salz@gmail.com>
  October, 2012
