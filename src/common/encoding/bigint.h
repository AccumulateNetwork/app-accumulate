#pragma once

#include <common/encoding/bytes.h>
#include <common/uint256.h>

typedef uint256_t BigInt_t;
typedef struct BigInt {
    Bytes data;
//    Error (*get)(const struct BigInt*, uint256_t *out);
//    Error (*set)(struct BigInt*, const uint256_t *in);
//
//    int (*BinarySize)(const struct BigInt *);
//    bool (*Equal)(const struct BigInt*, const struct BigInt*);
//    int (*Copy)(struct String*, const struct String*);
//    Error (*MarshalBinary)(const struct BigInt *, struct Marshaler *outData);
//    Error (*UnmarshalBinary)(struct BigInt *,const struct Marshaler *data);
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
