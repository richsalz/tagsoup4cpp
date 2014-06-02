#! /bin/sh

LHASH='https://raw.githubusercontent.com/openssl/openssl/master/crypto/lhash'

echo fetching file lhash.c
wget -q --no-check-certificate -O lhash.c "${LHASH}/lhash.c" #2>/dev/null
echo fetching file lhash.h
wget -q --no-check-certificate -O lhash.h "${LHASH}/lhash.h" #2>/dev/null

patch <patch.txt
rm -f lhash.c.orig lhash.h.orig
