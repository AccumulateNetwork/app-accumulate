#pragma once

#include <common/encoding/bytes.h>

//typedef uint64_t UVarInt_t;
typedef struct UVarInt {
    Bytes data;
//    Error (*get)(const struct UVarInt *, UVarInt_t *out);
//    Error (*set)(struct UVarInt *, UVarInt_t in);
//
//    int (*BinarySize)(const struct UVarInt *);
//    bool (*Equal)(const struct UVarInt*, const struct UVarInt*);
//    int (*Copy)(struct UVarInt*, const struct UVarInt*);
//    Error (*MarshalBinary)(const struct UVarInt *, struct Marshaler *outData);
//    Error (*UnmarshalBinary)(struct UVarInt *,struct Marshaler *data);
} UVarInt;

UVarInt UVarInt_new(buffer_t *b);
//UVarInt UVarInt_init(UVarInt_t *v);
int     UVarInt_binarySize(const UVarInt *v);
bool    UVarInt_equal(const UVarInt *v, const UVarInt *u);
int     UVarInt_copy(UVarInt *v, const UVarInt *u);
Error   UVarInt_valid(const Bytes *v);
Error   UVarInt_marshalBinary(const UVarInt *self, struct Marshaler *outData);
Error   UVarInt_unmarshalBinary(UVarInt * self, struct Unmarshaler *inData);
int     UVarInt_binarySize(const UVarInt *v);
Error   UVarInt_set(UVarInt *v, uint64_t n);
Error   UVarInt_get(const UVarInt *v, uint64_t *n);
