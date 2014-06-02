#! /bin/sh
LHASH='http://cvs.openssl.org/getfile?f=openssl/crypto/lhash'

echo fetching file lhash.c
wget -O lhash.c "${LHASH}/lhash.c&v=1.30" 2>/dev/null
echo fetching file lhash.h
wget -O lhash.h "${LHASH}/lhash.h&v=1.23" 2>/dev/null

patch <patch.txt
rm -f lhash.c.orig lhash.h.orig
