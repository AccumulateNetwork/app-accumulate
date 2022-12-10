#pragma once

#include <encoding/bytes.h>
#include <common/uvarint.h>

// typedef uint64_t UVarInt_t;
typedef struct UVarInt {
    Bytes data;
} UVarInt;

UVarInt UVarInt_new(buffer_t *b);
// UVarInt UVarInt_init(UVarInt_t *v);
int UVarInt_binarySize(const UVarInt *v);
bool UVarInt_equal(const UVarInt *v, const UVarInt *u);
int UVarInt_copy(UVarInt *v, const UVarInt *u);
Error UVarInt_valid(const Bytes *v);
Error UVarInt_marshalBinary(const UVarInt *self, struct Marshaler *outData);
Error UVarInt_unmarshalBinary(UVarInt *self, struct Unmarshaler *inData);
int UVarInt_binarySize(const UVarInt *v);
Error UVarInt_set(UVarInt *v, uint64_t n);
Error UVarInt_get(const UVarInt *v, uint64_t *n);
