#pragma once

#include <common/encoding.h>

#ifndef UNIT_TEST
#include "os.h"
#include "cx.h"
#else
#include <openssl/sha.h>
#endif

static Error sha256(uint8_t *in, unsigned int len,  uint8_t *out, unsigned int out_len) {
    if ( !in || !out ) {
        return -1;
    }
    if ( out_len != 32 ) {
        return -1;
    }
#ifndef UNIT_TEST
   int ret = cx_hash_sha256(in, len, out, out_len);
   if ( ret != 0 ) {
	   return ErrorCode[ErrorInvalidHashParameters];
   }
#else
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, in, len);
    SHA256_Final(out, &sha256);
#endif
    return ErrorCode[ErrorNone];
}

static Error sha256d(uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len) {
    uint8_t hash[32];
    Error e = sha256(in,len,hash,sizeof(hash));
    if ( e.code != ErrorNone ) {
        return e;
    }
    return sha256(hash,sizeof(hash),out,out_len);
}
