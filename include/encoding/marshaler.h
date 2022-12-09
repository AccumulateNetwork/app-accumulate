#pragma once

#include <encoding/bytes.h>
#include <encoding/rawjson.h>

typedef struct Marshaler {
    buffer_t buffer;
} Marshaler;

typedef struct Unmarshaler {
    buffer_t buffer;
    buffer_t *mempool;  // mempool to store pointers and stuff
} Unmarshaler;

Marshaler NewMarshaler(buffer_t *buffer);
buffer_t marshalerGetEncodedBuffer(Marshaler *m);

int marshalerWriteField(Marshaler *m, uint64_t field);
int marshalerWriteInt(Marshaler *m, int64_t v);
int marshalerWriteUInt(Marshaler *m, uint64_t v);
int marshalerWriteVarInt(Marshaler *m, const struct VarInt *v);
int marshalerWriteUVarInt(Marshaler *m, const struct UVarInt *v);
int marshalerWriteRaw(Marshaler *m, const struct Bytes *v);
int marshalerWriteBytes(Marshaler *m, const struct Bytes *v);
int marshalerWriteBytes32(Marshaler *m, const struct Bytes32 *v);
int marshalerWriteBytes64(Marshaler *m, const struct Bytes64 *v);
int marshalerWriteBigInt(Marshaler *m, const struct BigInt *v);
int marshalerWriteString(Marshaler *m, const struct String *v);
int marshalerWriteUrl(Marshaler *m, const struct Url *v);
int marshalerWriteRawJson(Marshaler *m, const struct RawJson *v);

// mempool will provide space for the objects will be "dynamically" allocated using the mempool
// buffer, use sparingly.
Unmarshaler NewUnmarshaler(buffer_t *inBuffer, buffer_t *mempool);

// will return null if not enough space in the pool is available, use sparingly.
void *unmarshalerAlloc(Unmarshaler *m, size_t n);
Bytes *unmarshalerNewByteBuffer(Unmarshaler *m, size_t n);

int unmarshalerReadInt(Unmarshaler *m, int64_t *n);
int unmarshalerReadUInt(Unmarshaler *m, uint64_t *n);
int unmarshalerPeekField(Unmarshaler *m, uint64_t *field);
int unmarshalerReadField(Unmarshaler *m, uint64_t *field);
int unmarshalerReadVarInt(Unmarshaler *m, struct VarInt *v);
int unmarshalerReadUVarInt(Unmarshaler *m, struct UVarInt *v);
int unmarshalerReadBytes(Unmarshaler *m, struct Bytes *v);
int unmarshalerReadBytesRaw(Unmarshaler *m, struct Bytes *v, size_t size);
int unmarshalerReadBytes32(Unmarshaler *m, struct Bytes32 *v);
int unmarshalerReadBytes64(Unmarshaler *m, struct Bytes64 *v);
int unmarshalerReadBigInt(Unmarshaler *m, struct BigInt *v);
int unmarshalerReadString(Unmarshaler *m, struct String *v);
int unmarshalerReadRawJson(Unmarshaler *m, struct RawJson *v);
int unmarshalerReadUrl(Unmarshaler *m, struct Url *v);
int unmarshalerReadByte(Unmarshaler *m, uint8_t *v);
