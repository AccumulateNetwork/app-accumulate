#pragma once

#include <types.h>

Error sha256(const uint8_t *in, unsigned int len,  uint8_t *out, unsigned int out_len);
Error sha256d(const uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len);

#if defined(__x86_64__ ) || defined(__i386__)
#include <common/internal/testing/sha256.h>
typedef SHA256_CTX HashContext;
#else
#include "os.h"
#include "cx.h"
typedef cx_hash_t HashContext;
#endif


int crypto_hash_init(HashContext *hash_context);
int crypto_hash_update(HashContext *hash_context, const void *in, size_t in_len);
int crypto_hash_final(HashContext *hash_context, uint8_t *out, size_t out_len);

