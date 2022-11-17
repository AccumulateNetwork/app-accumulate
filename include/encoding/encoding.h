#ifndef ENCODING_H
#define ENCODING_H

//The structures in this file use buffered encoding that requires an external buffer be provided
//This is used in support of the Accumulate types generator.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <encoding/bytes.h>
#include <encoding/bytes32.h>
#include <encoding/bytes64.h>
#include <encoding/varint.h>
#include <encoding/string.h>
#include <encoding/uvarint.h>
#include <encoding/bigint.h>
#include <encoding/url.h>
#include <encoding/marshaler.h>
#include <encoding/rawjson.h>
#include <encoding/bool.h>

#define JSMN_HEADER
#include <common/jsmn.h>
#include <common/varint.h>

typedef int (*BinarySize)(const struct Bytes *);
typedef bool (*Equal)(const struct Bytes*, const struct Bytes*);
typedef int (*Copy)(struct Bytes*, const struct Bytes*);
typedef Error (*MarshalBinary)(const struct Bytes*, struct Marshaler *outData);
typedef Error (*UnmarshalBinary)(struct Bytes*,struct Unmarshaler *data);
typedef Error (*MarshalJSON)(const struct Bytes*, struct Marshaler *outData);
typedef Error (*UnmarshalJSON)(struct Bytes*,struct Marshaler *data);

#define ENCODE_DECLARE(T)                 \
T T##_new(buffer_t *b, size_t n);         \
T T##_init(T##_t *v);                     \
Error T##_valid(const Bytes *v);          \
Error T##_marshalBinary(const Bytes *self, struct Marshaler *outData);\
Error T##_unmarshalBinary(Bytes * self, const Unmarshaler *inData); \
Error T##_get(const struct T *v, Bytes *out); \
Error T##_set(struct T *v, const Bytes *in);

Bytes Bytes_init(Byte_t *v, size_t n);

#define ENCODE_BINARY_SIZE_STATIC(T) int T##_binarySize(const T *v) { \
    CHECK_ERROR_INT(v)                                                       \
    return Bytes_binarySizeStatic(&v->data);                                 \
}

#define ENCODE_BINARY_SIZE_DYNAMIC(T) int T##_binarySize(const T *v) { \
    CHECK_ERROR_INT(v)                                                        \
    return Bytes_binarySizeDynamic(&v->data);                                 \
}

#define ENCODE_MARSHAL_BINARY_STATIC(T) Error T##_marshalBinary(const T *v,struct Marshaler *m) { \
    CHECK_ERROR(v)                                                                   \
    CHECK_ERROR(m)                                                                   \
    Error e = T##_valid(&v->data);                                                   \
    if ( IsError(e) ) {                                                              \
        return e;                                                                    \
    }                                                                                \
    return Bytes_marshalBinaryStatic(&v->data,m);                                    \
}

#define ENCODE_UNMARSHAL_BINARY_STATIC(T) Error T##_unmarshalBinary(T *v, struct Unmarshaler *m) {\
    CHECK_ERROR(v)                                                                      \
    CHECK_ERROR(m)                                                                      \
    Error e = T##_valid(&v->data);                                                      \
    if ( IsError(e) ) {                                                                 \
        return e;                                                                       \
    }                                                                                   \
    return Bytes_unmarshalBinaryStatic(&v->data,m);                                     \
}

#define ENCODE_MARSHAL_BINARY_DYNAMIC(T) Error T##_marshalBinary(const T *v, struct Marshaler *m) { \
    CHECK_ERROR(v)                                                           \
    CHECK_ERROR(m)                                                           \
    Error e = T##_valid(&v->data);                                           \
    if ( IsError(e) ) {                                                      \
        return e;                                                            \
    }                                                                        \
    return Bytes_marshalBinaryDynamic(&v->data, m);                          \
}

#define ENCODE_UNMARSHAL_BINARY_DYNAMIC(T) Error T##_unmarshalBinary(T *v, struct Unmarshaler *m) { \
    CHECK_ERROR(v)                                                           \
    CHECK_ERROR(m)                                                           \
    Error e = T##_valid(&v->data);                                           \
    if ( IsError(e) ) {                                                      \
        return e;                                                            \
    }                                                                        \
    return Bytes_unmarshalBinaryDynamic(&v->data, m);                        \
}

#define ENCODE_COPY(T) \
int T##_copy(T*v, const T*u) {        \
    CHECK_ERROR_INT(v)                              \
    CHECK_ERROR_INT(u)                              \
    Error e = T##_valid(&v->data);                  \
    if ( IsError(e) ) {                             \
        return e.code;                              \
    }                                               \
    e = T##_valid(&u->data);                        \
    if ( IsError(e) ) {                             \
        return e.code;                              \
    }                                               \
    return Bytes_copy(&v->data, &u->data);          \
}

#define ENCODE_EQUAL(T) \
bool T##_equal(const T* v, const T* u) {            \
    CHECK_ERROR_BOOL(v)                             \
    CHECK_ERROR_INT(u)                              \
    Error e = T##_valid(&v->data);                  \
    if ( IsError(e) ) {                             \
        return false;                               \
    }                                               \
    e = T##_valid(&u->data);                        \
    if ( IsError(e) ) {                             \
        return false;                               \
    }                                               \
    return Bytes_equal(&v->data, &u->data);         \
}

#endif
