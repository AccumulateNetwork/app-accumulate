#pragma once

#include <common/encoding/bytes.h>

typedef struct VarInt {
    Bytes data;
//    Error (*get)(const struct VarInt *, VarInt_t *out);
//    Error (*set)(struct VarInt *, VarInt_t in);
//
//    int (*BinarySize)(const struct VarInt *);
//    bool (*Equal)(const struct VarInt*, const struct VarInt*);
//    int (*Copy)(struct VarInt*, const struct VarInt*);
//    Error (*MarshalBinary)(const struct VarInt *, struct Marshaler *outData);
//    Error (*UnmarshalBinary)(struct VarInt *,struct Marshaler *data);
} VarInt;

VarInt VarInt_new(buffer_t *b);
//VarInt VarInt_init(VarInt_t *v);
int    VarInt_binarySize(const VarInt *v);
Error  VarInt_valid(const Bytes *v);
//Error  VarInt_marshalBinary(const VarInt *self, struct Marshaler *outData);
//Error  VarInt_unmarshalBinary(VarInt * self, struct Unmarshaler *inData);
int    VarInt_binarySize(const VarInt *v);
Error  VarInt_set(VarInt *v, int64_t n);
Error  VarInt_get(const VarInt *v, int64_t *n);
