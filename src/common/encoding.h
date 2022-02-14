#ifndef ENCODING_H
#define ENCODING_H

//The structures in this file use buffered encoding that requires an external buffer be provided
//This is used in support of the Accumulate types generator.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define JSMN_HEADER
#include <common/jsmn.h>

#include <common/uint256.h>
#include <common/varint.h>
#include <common/buffer.h>
#include <common/error.h>

struct Marshaler;

typedef struct Bytes {
   buffer_t buffer;

   int (*BinarySize)(const struct Bytes *);
   bool (*Equal)(const struct Bytes*, const struct Bytes*);
   int (*Copy)(struct Bytes*, const struct Bytes*);
   Error (*MarshalBinary)(const struct Bytes*, struct Marshaler *outData);
   Error (*UnmarshalBinary)(struct Bytes*,const struct Marshaler *data);
   Error (*MarshalJSON)(const struct Bytes*, struct Marshaler *outData);
   Error (*UnmarshalJSON)(struct Bytes*,const struct Marshaler *data);
} Bytes;

typedef buffer_t Bytes_t;

typedef struct Marshaler {
    Bytes data;
    buffer_t cache;
} Marshaler;

typedef int (*BinarySize)(const struct Bytes *);
typedef bool (*Equal)(const struct Bytes*, const struct Bytes*);
typedef int (*Copy)(struct Bytes*, const struct Bytes*);
typedef Error (*MarshalBinary)(const struct Bytes*, struct Marshaler *outData);
typedef Error (*UnmarshalBinary)(struct Bytes*,const struct Marshaler *data);
typedef Error (*MarshalJSON)(const struct Bytes*, struct Marshaler *outData);
typedef Error (*UnmarshalJSON)(struct Bytes*,const struct Marshaler *data);

typedef uint8_t Bytes32_t[32];
typedef struct Bytes32 {
    Bytes data;
    Error (*get)(const struct Bytes *, Bytes32_t *out);
    Error (*set)(struct Bytes *, const Bytes32_t *in);
    Error (*MarshalBinary)(const struct Bytes32 *, struct Marshaler *outData);
    Error (*UnmarshalBinary)(struct Bytes32 *,const struct Marshaler *data);
} Bytes32;


typedef uint8_t Bytes64_t[64];

typedef struct Bytes64 {
    Bytes data;
    Error (*get)(const struct Bytes *, Bytes64_t *out);
    Error (*set)(struct Bytes *, const Bytes64_t *in);

    Error (*MarshalBinary)(const struct Bytes64 *, struct Marshaler *outData);
    Error (*UnmarshalBinary)(struct Bytes64 *,const struct Marshaler *data);
} Bytes64;


typedef buffer_t String_t;
typedef struct String {
    Bytes data;
    Error (*get)(const struct String *, String_t *out);
    Error (*set)(struct String *, const String_t *in);

    Error (*MarshalBinary)(const struct String *, struct Marshaler *outData);
    Error (*UnmarshalBinary)(struct String *,const struct Marshaler *data);

} String;

typedef uint256_t BigInt_t;
typedef struct BigInt {
    Bytes data;
    Error (*get)(const struct Bytes*, uint256_t *out);
    Error (*set)(struct Bytes*, const uint256_t *in);

    Error (*MarshalBinary)(const struct BigInt *, struct Marshaler *outData);
    Error (*UnmarshalBinary)(struct BigInt *,const struct Marshaler *data);
} BigInt;

typedef uint64_t VarInt_t;
typedef struct VarInt {
    Bytes data;
    Error (*get)(const struct Bytes *, VarInt_t *out);
    Error (*set)(struct Bytes *, VarInt_t in);

    Error (*MarshalBinary)(const struct VarInt *, struct Marshaler *outData);
    Error (*UnmarshalBinary)(struct VarInt *,const struct Marshaler *data);
} VarInt;

//Bytes Bytes_init(Bytes *b, buffer_t *buffer, int size);
//VarInt VarInit_init(VarInt *v, buffer_t *buffer);
//BigInt BigInit_init(BigInt *v, buffer_t *buffer);
//Bytes32 Bytes32_init(Bytes32 *v, buffer_t *buffer);
//Bytes64 Bytes64_init(Bytes64 *v, buffer_t *buffer);
//String String_init(String *s, buffer_t *buffer, int size);

Bytes Bytes_init(const Bytes_t *b);
VarInt VarInt_init(const VarInt_t *v);
BigInt BigInit_init(const BigInt_t *v);
Bytes32 Bytes32_init(const Bytes32_t *v);
Bytes64 Bytes64_init(const Bytes64_t *v);
String String_init(const String_t *s);

Marshaler Marshaler_init(Marshaler *v, buffer_t *buffer );

int Bytes_binarySizeStatic(const struct Bytes *self);
int Bytes_binarySizeDynamic(const struct Bytes *self);
Error Bytes_marshalBinaryDynamic(const struct Bytes*self, struct Marshaler *outData);
Error Bytes_unmarshalBinaryDynamic(Bytes* self, const Marshaler *inData);
Error Bytes_marshalBinaryStatic(const struct Bytes*self, struct Marshaler *outData);
Error Bytes_unmarshalBinaryStatic(Bytes* self, const Marshaler *inData);
bool Bytes_equal(const Bytes *b1,const Bytes *b2);
int Bytes_copy(Bytes *b1, const Bytes *b2);
Error Bytes_marshalJSON(const struct Bytes* self, struct Marshaler *outData);
Error Bytes_unmarshalJSON(struct Bytes* self, const struct Marshaler *data);

Error Bytes32_valid(const Bytes*v);
Error Bytes32_get(const struct Bytes *v, Bytes *out);
Error Bytes32_set(struct Bytes *v, const Bytes *in);
Error Bytes64_valid(const Bytes*v);
Error Bytes64_get(const struct Bytes *v, Bytes *out);
Error Bytes64_set(struct Bytes *v, const Bytes *in);

Error VarInt_valid(const VarInt *v);
Error VarInt_set(Bytes *v, uint64_t n);
Error VarInt_get(const Bytes *v, uint64_t *n);
int VarInt_binarySize(const Bytes *v);
Error VarInt_marshalBinary(const Bytes *self, struct Marshaler *outData);
Error VarInt_unmarshalBinary(Bytes* self, const Marshaler *inData);
VarInt VarInt_init(VarInt *v, buffer_t *buffer);
//#define DECLARE_ENCODERS(TYPE) \
//Error TYPE##Valid(const TYPE *v) { \
//    if (!v) return ErrorCode(ErrorParameterNil); \
//    Type##_valid(&v.data)                        \
//}

Error BigInt_valid(const Bytes *s);
Error BigInt_get(const struct Bytes*s, uint256_t *v);
Error BigInt_set(struct Bytes*s, const uint256_t *v);

Error String_valid(const Bytes *s);
Error String_get(const struct Bytes*s, char *v, int vlen);
Error String_set(struct Bytes*s, const char *v);



#endif
