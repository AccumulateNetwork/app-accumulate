
#include <types.h>
#include <common/error.h>



#ifndef UNIT_TEST
#include "os.h"
#include "cx.h"
#else
#include <common/internal/testing/sha256.h>
#endif

Error sha256(const uint8_t *in, unsigned int len,  uint8_t *out, unsigned int out_len) {
    if ( !in || !out ) {
        return ErrorCode(ErrorParameterNil);
    }
    if ( out_len != 32 ) {
        return ErrorCode(ErrorParameterInsufficientData);
    }
#ifndef UNIT_TEST
   cx_hash_sha256(in, len, out, out_len);
#else
    SHA256_CTX sha256;
    sha256_init(&sha256);
    sha256_update(&sha256, in, len);
    sha256_final(&sha256, out);
#endif
    return ErrorCode(ErrorNone);
}

Error sha256d(const uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len) {
    uint8_t hash[32];
    Error e = sha256(in,len,hash,sizeof(hash));
    if ( e.code != ErrorNone ) {
        return e;
    }
    return sha256(hash,sizeof(hash),out,out_len);
}
