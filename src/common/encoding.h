#ifndef ENCODING_H
#define ENCODING_H

//The structures in this file use buffered encoding that requires an external buffer be provided
//This is used in support of the Accumulate types generator.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <common/jsmn.h>
#include <common/uint256.h>
#include <common/varint.h>
#include <common/buffer.h>

typedef struct Error {
   int code;
   char err[64];
} Error;

enum ErrorEnum {
    ErrorNone = 0,
    ErrorUnknown,
    ErrorNotImplemented,
    ErrorTypeNotFound,
    ErrorParameterNil,
    ErrorParameterInsufficientData,
    ErrorBadCopy,
    ErrorBufferTooSmall,
    ErrorVarIntRead,
    ErrorVarIntWrite,
    ErrorResizeRequred,
    ErrorInvalidBigInt,
    ErrorInvalidString,
};

static Error ErrorCode[] = {
    {ErrorNone, {0}},
    {ErrorUnknown, "unknown"},
    {ErrorNotImplemented, "not implemented"},
    {ErrorTypeNotFound, "type not found"},
    {ErrorParameterNil, "parameter is nil"},
    {ErrorParameterInsufficientData,"insufficient buffer size"},
    {ErrorBadCopy,"cannot copy buffer"},
    {ErrorBufferTooSmall,"buffer size too small"},
    {ErrorVarIntRead, "varint read failed"},
    {ErrorVarIntWrite,"varint write failed"},
    {ErrorResizeRequred,"resize required"},
    {ErrorInvalidBigInt,"invalid big int"},
    {ErrorInvalidString,"invalid string"},
};

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

typedef struct Bytes32 {
    Bytes data;
    Error (*get)(const struct Bytes *, Bytes *out);
    Error (*set)(struct Bytes *, const Bytes *in);
} Bytes32;

typedef struct Bytes64 {
    Bytes data;
    Error (*get)(const struct Bytes *, Bytes *out);
    Error (*set)(struct Bytes *, const Bytes *in);
} Bytes64;

typedef struct String {
   Bytes data;
   Error (*get)(const struct Bytes *, char *out, int oulen);
   Error (*set)(struct Bytes *, const char *in);
} String;

typedef struct BigInt {
    Bytes data;
    Error (*get)(const struct Bytes*, uint256_t *out);
    Error (*set)(struct Bytes*, const uint256_t *in);
} BigInt;

typedef struct VarInt {
   Bytes data;
   Error (*get)(const struct Bytes *, uint64_t *out);
   Error (*set)(struct Bytes *, uint64_t in);
} VarInt;

Error Error_init(Error *e);
Bytes Bytes_init(Bytes *b, buffer_t *buffer, int size);
VarInt VarInit_init(VarInt *v, buffer_t *buffer);
BigInt BigInit_init(BigInt *v, buffer_t *buffer);
Bytes32 Bytes32_init(Bytes32 *v, buffer_t *buffer);
Bytes64 Bytes64_init(Bytes64 *v, buffer_t *buffer);
String String_init(String *s, buffer_t *buffer, int size);
Marshaler Marshaler_init(Marshaler *v, buffer_t *buffer );

#endif
