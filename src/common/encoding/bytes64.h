#pragma once

#include <common/encoding/bytes.h>

typedef struct Bytes64_t { uint8_t x[64]; } Bytes64_t;

typedef struct Bytes64 {
    Bytes data;
} Bytes64;

Bytes64 Bytes64_new(buffer_t *b, size_t n);
Bytes64 Bytes64_init(Bytes64_t *v);
bool  Bytes64_equal(const Bytes64 *v, const Bytes64 *u);
int   Bytes64_copy(Bytes64 *dst, const Bytes64 *src);
int   Bytes64_binarySize(const Bytes64 *v);
Error Bytes64_valid(const Bytes* v);
Error Bytes64_get(const Bytes64 *v, Bytes *out);
Error Bytes64_set(Bytes64 *v, const Bytes *in);
Error Bytes64_valid(const Bytes*v);
Error Bytes64_marshalBinary(const Bytes64 *self, struct Marshaler *outData);
Error Bytes64_unmarshalBinary(Bytes64 * self, struct Unmarshaler *inData);
