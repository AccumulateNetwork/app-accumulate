#pragma once

#include <common/encoding/bytes.h>
#include <common/uint256.h>

typedef uint256_t BigInt_t;
typedef struct BigInt {
    Bytes data;
} BigInt;

BigInt BigInt_new(buffer_t *b);
BigInt BigInt_init(BigInt_t *v);
int    BigInt_binarySize(const BigInt *v);
Error  BigInt_valid(const Bytes *v);
bool   BigInt_equal(const BigInt *v, const BigInt *u);
int    BigInt_copy(BigInt *dst, const BigInt *src);
Error  BigInt_marshalBinary(const BigInt *self, struct Marshaler *outData);
Error  BigInt_unmarshalBinary(BigInt * self, struct Unmarshaler *inData);
Error  BigInt_get(const struct BigInt* v, uint256_t *u);
Error  BigInt_set(struct BigInt *v, const uint256_t *u);
Error  BigInt_setFromString(struct BigInt *v, const char *in, size_t inLen);
Error  BigInt_setFromHex(struct BigInt *v, const char *in, size_t inLen);
