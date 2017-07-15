//
// This file is made available under the terms of the Apache 2.0
// license which is available at http://www.apache.org/licenses/
//

/// @file
/// A sample driver program.
#include <stdlib.h>

#include <tagsoup.hpp>
#include <iostream>
#include <fstream>

using namespace std;


/// Code to test for memory leaks (with valgrind)
static void
test_object_lifetimes()
{
    TagSoup::ostream out(new ofstream("/dev/null"));
    TagSoup::istream in(new ifstream("/dev/null"));

    TagSoup::Parser p(in, out);
    p.parse();
}


/// Sample driver.
int
main()
{
    test_object_lifetimes();
    TagSoup::ostream out(&cout, false);
    TagSoup::istream in(&cin, false);
    TagSoup::Parser p(in, out);
    p.parse();
    return 0;
}
