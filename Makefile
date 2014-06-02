##  Copyright (c) 2007, 2008 IBM.  All rights reserved.
##  This file is made available under the terms of the Apache 2.0
##  license which is available at http://www.apache.org/licenses/

SHELL = /bin/sh

# With -Wunreachable-code, g++4.0 complains about <allocator.h> etc
#UNREACH = -Wunreachable-code
WARNINGS = -Wall -Werror \
	   -Wconversion -Wunused -Wwrite-strings -Wstrict-overflow=4 \
	   -Wmissing-include-dirs -Wcast-qual -Wundef -Wlogical-op \
	   -Wmissing-declarations -Wformat -Wmissing-format-attribute \
	   -Wformat-nonliteral -Wformat-security -Wswitch-enum -Wshadow \
	   -Wpointer-arith -Wcast-align -Wsign-compare -Wmissing-noreturn \
	   $(UNREACH)
DEFS	 = -I.
OPT	 = -g
CFLAGS   = $(DEFS) $(OPT)
CXXFLAGS = $(CFLAGS) $(WARNINGS)

SOURCES  = lhash.c parser.cpp schema.cpp
OBJECTS  = lhash.o parser.o   schema.o

TS_SOURCE_FILES = \
	tagsoup.hpp internals.hpp parser.cpp parser.inl schema.cpp schema.inl \
	test.cpp
TS_DIST_FILES = \
	README Makefile Doxyfile getlhash.sh patch.txt


.PHONY: all
all: libtagsoup.a test tags cscope.out doxy.out

.PHONY: zip
zip: ts4cpp.zip
ts4cpp.zip: $(TS_DIST_FILES) $(TS_SOURCE_FILES)
	@rm -rf ts4cpp
	@mkdir ts4cpp
	cp $(TS_DIST_FILES) $(TS_SOURCE_FILES) ts4cpp
	zip -q $@ ts4cpp/*
	@rm -rf ts4cpp

.PHONY: install
install: all
	install tagsoup.h /usr/local/include
	install libtagsoup.a /usr/local/lib

doxy.out: $(TS_SOURCE_FILES) Doxyfile
	@rm -rf doxy
	doxygen Doxyfile >doxygen.errs 2>&1
	cat doxygen.errs
	@test ! -s doxygen.errs
	touch $@

tags: $(TS_SOURCE_FILES)
	-ctags $(TS_SOURCE_FILES)
cscope.out: $(TS_SOURCE_FILES)
	-cscope -b $(TS_SOURCE_FILES)

libtagsoup.a: $(OBJECTS)
	@rm -f $@
	ar r $@ $(OBJECTS)

test: test.cpp libtagsoup.a
	$(CXX) $(CXXFLAGS) -o $@ test.cpp libtagsoup.a

.PHONY: clean
clean:
	rm -f foo core* tags cscope.out gmon.out test libtagsoup.a $(OBJECTS)
	rm -rf doxy doxy.out doxygen.errs ts4cpp ts4cpp.zip
.PHONY: distclean realclean
distclean realclean: clean
	rm -f lhash.h lhash.c

# Dependencies
lhash.o: lhash.h
parser.o: tagsoup.hpp internals.hpp parser.inl
schema.o: tagsoup.hpp internals.hpp lhash.h schema.inl
test.o:	tagsoup.hpp
