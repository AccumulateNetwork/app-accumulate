#pragma once

#include <common/encoding/bytes.h>

typedef buffer_t String_t;
typedef struct String {
    Bytes data;
//    Error (*get)(const struct String *, String_t *out);
//    Error (*set)(struct String *, String_t in);
//
//    int (*BinarySize)(const struct String *);
//    bool (*Equal)(const struct String*, const struct String*);
//    int (*Copy)(struct String*, const struct String*);
//    Error (*MarshalBinary)(const struct String *, struct Marshaler *outData);
//    Error (*UnmarshalBinary)(struct String *,const struct Marshaler *data);
} String;

String String_new(buffer_t *b, size_t n);
String String_init(String_t *v);
int    String_binarySize(const String *v);
Error  String_valid(const Bytes *v);
bool   String_equal(const String *a, const String *b);
Error  String_marshalBinary(const String *self, struct Marshaler *outData);
Error  String_unmarshalBinary(String * self, struct Unmarshaler *inData);
int    String_binarySize(const String *v);
Error  String_set(String *v, const char *s);
Error  String_get(const String *v, char *s, size_t slen);
