#pragma once

#include <encoding/bytes.h>

typedef buffer_t Url_t;
typedef struct Url {
    Bytes data;
} Url;

Url Url_new(buffer_t *b, size_t n);
Url Url_init(Url_t *v);
int    Url_binarySize(const Url *v);
Error  Url_valid(const Bytes *v);
bool   Url_equal(const Url *v, const Url *u);
int    Url_copy(Url *dst, const Url *src);
Error  Url_marshalBinary(const Url *self, struct Marshaler *outData);
Error  Url_unmarshalBinary(Url * self, struct Unmarshaler *inData);
int    Url_binarySize(const Url *v);
Error  Url_set(Url *v, const char *s);
Error  Url_get(const Url *v, char *s, size_t slen);
