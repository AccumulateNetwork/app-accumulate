
#include <common/error.h>
#include <common/sha256.h>

Error sha256(const uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len) {
    if (!in || !out) {
        return ErrorCode(ErrorParameterNil);
    }
    if (out_len != 32) {
        return ErrorCode(ErrorParameterInsufficientData);
    }
#if defined(__x86_64__) || defined(__i386__)
    SHA256_CTX sha256;
    sha256_init(&sha256);
    sha256_update(&sha256, in, len);
    sha256_final(&sha256, out);
#else
    cx_hash_sha256(in, len, out, out_len);
#endif
    return ErrorCode(ErrorNone);
}

Error sha256d(const uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len) {
    uint8_t hash[32];
    Error e = sha256(in, len, hash, sizeof(hash));
    if (e.code != ErrorNone) {
        return e;
    }
    return sha256(hash, sizeof(hash), out, out_len);
}

int crypto_hash_init(HashContext *hash_context) {
#if defined(__x86_64__) || defined(__i386__)
    sha256_init(hash_context);
    return 0;
#else
    return cx_sha256_init_no_throw(hash_context);
#endif
}

int crypto_hash_update(HashContext *hash_context, const void *in, size_t in_len) {
#if defined(__x86_64__) || defined(__i386__)
    sha256_update(hash_context, in, in_len);
    return 0;
#else
    return cx_hash_no_throw(&hash_context->header, 0, in, in_len, NULL, 0);
#endif
}

int crypto_hash_final(HashContext *hash_context, uint8_t *out, size_t out_len) {
#if defined(__x86_64__) || defined(__i386__)
    sha256_final(hash_context, out);
    return 0;
#else
    return cx_hash_no_throw(&hash_context->header, CX_LAST, NULL, 0, out, out_len);
#endif
}
