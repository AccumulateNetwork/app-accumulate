#include <common/keccak.h>
#ifndef UNIT_TEST
#include "cx.h"
#include "os.h"
#else
#include <common/internal/testing/sha3.h>
#include <string.h>
#endif

Error keccak(const uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len) {
    if (!in || !out) {
        return ErrorCode(ErrorParameterNil);
    }
    if (out_len != 32) {
        return ErrorCode(ErrorParameterInsufficientData);
    }
#ifndef UNIT_TEST
    cx_sha3_t keccak256;
    cx_keccak_init(&keccak256, 256);
    cx_hash((cx_hash_t *) &keccak256, CX_LAST, in, len, out, out_len);
#else
    sha3_context hash256;
    sha3_Init256(&hash256);
    sha3_SetFlags(&hash256, SHA3_FLAGS_KECCAK);
    sha3_Update(&hash256, in, len);
    sha3_Finalize(&hash256);
    memmove(out, hash256.u.sb, out_len);
#endif
    return ErrorCode(ErrorNone);
}
