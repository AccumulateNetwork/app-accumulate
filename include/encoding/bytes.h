#pragma once

#include <common/buffer.h>
#include <common/error.h>

struct Marshaler;
struct Unmarshaler;

typedef struct Bytes {
    buffer_t buffer;
} Bytes;

typedef uint8_t Byte_t;


Bytes Bytes_new(buffer_t *b, size_t n);
int Bytes_binarySizeStatic(const struct Bytes *self);
int Bytes_binarySizeDynamic(const struct Bytes *self);
int Bytes_binarySize(const struct Bytes *self);
Error Bytes_marshalBinaryDynamic(const struct Bytes*self, struct Marshaler *outData);
Error Bytes_unmarshalBinaryDynamic(Bytes* self, struct Unmarshaler *inData);
Error Bytes_marshalBinaryStatic(const struct Bytes*self, struct Marshaler *outData);
Error Bytes_unmarshalBinaryStatic(Bytes* self, struct Unmarshaler *inData);
bool Bytes_equal(const Bytes *b1,const Bytes *b2);
int Bytes_copy(Bytes *b1, const Bytes *b2);
Error Bytes_marshalJSON(const struct Bytes* self, struct Marshaler *outData);
Error Bytes_unmarshalJSON(struct Bytes* self, struct Marshaler *data);