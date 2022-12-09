#pragma once

#include <encoding/bytes.h>

typedef buffer_t String_t;
typedef struct String {
    Bytes data;
} String;

String String_new(buffer_t *b, size_t n);
String String_init(String_t *v);
int String_binarySize(const String *v);
Error String_valid(const Bytes *v);
bool String_equal(const String *a, const String *b);
Error String_marshalBinary(const String *self, struct Marshaler *outData);
Error String_unmarshalBinary(String *self, struct Unmarshaler *inData);
int String_binarySize(const String *v);
Error String_set(String *v, const char *s);
Error String_get(const String *v, char *s, size_t slen);
