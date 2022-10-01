#pragma once

#include <common/encoding/bytes.h>

typedef struct Bool_t { uint8_t x[64]; } Bool_t;

typedef struct Bool {
    Bytes data;
//    Error (*get)(const struct Bytes *, Bool_t *out);
//    Error (*set)(struct Bytes *, const Bool_t *in);
//    int (*BinarySize)(const struct Bool *);
//    bool (*Equal)(const struct Bool*, const struct Bool*);
//    int (*Copy)(struct Bool*, const struct Bool*);
//    Error (*MarshalBinary)(const struct Bool *, struct Marshaler *outData);
//    Error (*UnmarshalBinary)(struct Bool *,struct Marshaler *data);
} Bool;

Bool Bool_new(buffer_t *b, size_t n);
Bool Bool_init(Bool_t *v);
bool  Bool_equal(const Bool *v, const Bool *u);
int   Bool_copy(Bool *dst, const Bool *src);
int   Bool_binarySize(const Bool *v);
Error Bool_valid(const Bytes* v);
Error Bool_get(const Bool *v, Bytes *out);
Error Bool_set(Bool *v, const Bytes *in);
Error Bool_valid(const Bytes*v);
Error Bool_marshalBinary(const Bool *self, struct Marshaler *outData);
Error Bool_unmarshalBinary(Bool * self, struct Unmarshaler *inData);
