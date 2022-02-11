#pragma once

typedef struct Error {
   int code;
   char err[64];
} Error;

enum ErrorEnum {
    ErrorNone = 0,
    ErrorUnknown,
    ErrorInvalidEnum,
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

Error ErrorCode(ErrorEnum e); 

Error Error_init(Error *e); 

