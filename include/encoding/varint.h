#pragma once

#include <encoding/bytes.h>

typedef struct VarInt {
    Bytes data;
} VarInt;

VarInt VarInt_new(buffer_t *b);
// VarInt VarInt_init(VarInt_t *v);
int VarInt_binarySize(const VarInt *v);
Error VarInt_valid(const Bytes *v);
// Error  VarInt_marshalBinary(const VarInt *self, struct Marshaler *outData);
// Error  VarInt_unmarshalBinary(VarInt * self, struct Unmarshaler *inData);
int VarInt_binarySize(const VarInt *v);
Error VarInt_set(VarInt *v, int64_t n);
Error VarInt_get(const VarInt *v, int64_t *n);
