#pragma once

#include <common/encoding/bytes.h>

typedef struct Marshaler {
    //Bytes data;
    buffer_t buffer;
} Marshaler;


typedef struct Unmarshaler {
    buffer_t buffer;
    //buffer_t mempool;
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

//mempool is optional, if it is defined, the objects will be "dynamically" allocated using the mempool buffer
Unmarshaler NewUnmarshaler(buffer_t *inBuffer, buffer_t *mempool);

//int UnmarshalerReadInt(Marshaler *m, int64_t *n);
//int unmarshalerReadUInt(Marshaler *m, uint64_t *n);
int unmarshalerReadField(Marshaler *m, uint64_t *field);
int unmarshalerReadVarInt(Marshaler *m, struct VarInt *v);
int unmarshalerReadUVarInt(Marshaler *m, struct UVarInt *v);
int unmarshalerReadBytes(Marshaler *m, struct Bytes *v);
int unmarshalerReadBytesRaw(Marshaler *m, struct Bytes *v);
int unmarshalerReadBytes32(Marshaler *m, struct Bytes32 *v);
int unmarshalerReadBytes64(Marshaler *m, struct Bytes64 *v);
int unmarshalerReadBigInt(Marshaler *m, struct BigInt *v);
int unmarshalerReadString(Marshaler *m, struct String *v);



