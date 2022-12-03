#pragma once

#include <encoding/bytes.h>

typedef buffer_t RawJson_t;
typedef struct RawJson {
    Bytes data;
} RawJson;

RawJson RawJson_new(buffer_t *b, size_t n);
RawJson RawJson_init(RawJson_t *v);
int RawJson_binarySize(const RawJson *v);
Error RawJson_valid(const Bytes *v);
bool RawJson_equal(const RawJson *v, const RawJson *u);
int RawJson_copy(RawJson *dst, const RawJson *src);
Error RawJson_marshalBinary(const RawJson *self, struct Marshaler *outData);
Error RawJson_unmarshalBinary(RawJson *self, struct Unmarshaler *inData);
int RawJson_binarySize(const RawJson *v);
Error RawJson_set(RawJson *v, const char *s);
Error RawJson_get(const RawJson *v, char *s, size_t slen);
