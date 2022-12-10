#pragma once

#include <common/varint.h>
#include <encoding/bytes.h>

typedef struct VarInt {
    Bytes data;
} VarInt;

VarInt VarInt_new(buffer_t *b);
int VarInt_binarySize(const VarInt *v);
Error VarInt_valid(const Bytes *v);
int VarInt_binarySize(const VarInt *v);
Error VarInt_set(VarInt *v, int64_t n);
Error VarInt_get(const VarInt *v, int64_t *n);
