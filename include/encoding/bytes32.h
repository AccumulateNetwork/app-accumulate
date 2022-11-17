#pragma once

#include <encoding/bytes.h>

typedef struct Bytes32_t { uint8_t x[32]; } Bytes32_t;
typedef struct Bytes32 {
    Bytes data;
} Bytes32;

Bytes32 Bytes32_new(buffer_t *b, size_t n);
Bytes32 Bytes32_init(Bytes32_t *v);
bool  Bytes32_equal(const Bytes32 *v, const Bytes32 *u);
int   Bytes32_copy(Bytes32 *dst, const Bytes32 *src);
int   Bytes32_binarySize(const Bytes32 *v);
Error Bytes32_valid(const Bytes*v);
Error Bytes32_marshalBinary(const struct Bytes32 *self, struct Marshaler *outData);
Error Bytes32_unmarshalBinary(struct Bytes32 * self, struct Unmarshaler *inData);
Error Bytes32_get(const struct Bytes32 *v, Bytes *out);
Error Bytes32_set(struct Bytes32 *v, const Bytes *in);
