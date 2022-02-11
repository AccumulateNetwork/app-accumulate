#pragma once

typedef struct Error {
   int code;
   char err[64];
} Error;

typedef enum {
    ErrorNone = 0,
    ErrorUnknown,
    ErrorInvalidEnum,
    ErrorInvalidObject,
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
} ErrorEnum;

Error ErrorCode(ErrorEnum e); 
Error Error_init(Error *e);

