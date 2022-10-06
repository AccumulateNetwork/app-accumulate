#pragma once

#include <stdbool.h>

typedef struct Error {
   int code;
   char err[64];
} Error;

typedef enum {
    ErrorNone = 0,
    ErrorUnknown = -1,
    ErrorInvalidEnum = -2,
    ErrorInvalidObject = -3,
    ErrorNotImplemented = -4,
    ErrorTypeNotFound = -5,
    ErrorParameterNil = -6,
    ErrorParameterInsufficientData = -7,
    ErrorBadCopy = -8,
    ErrorBufferTooSmall = -9,
    ErrorVarIntRead = -10,
    ErrorVarIntWrite = -11,
    ErrorResizeRequred = -12,
    ErrorInvalidBigInt = -13,
    ErrorInvalidString = -14,
    ErrorInvalidHashParameters = -15,
    ErrorUVarIntRead = -16,
    ErrorUVarIntWrite = -17,
    ErrorMempoolFull = -18,
    ErrorInvalidOffset = -19,
    ErrorInvalidData = -20,
    ErrorBadKey = -21,
    ErrorInvalidField = -22,
    ErrorExpectingType = -23,
} ErrorEnum;

Error ErrorCode(ErrorEnum e); 
Error Error_init(Error *e);
bool IsError(Error e);
bool IsErrorCode(int e);

#define CHECK_ERROR(v) if (!v) { return ErrorCode(ErrorParameterNil); }
#define CHECK_ERROR_INT(v) if (!v) { return ErrorCode(ErrorParameterNil).code; }
#define CHECK_ERROR_BOOL(v) if (!v) { return false; }

#define CHECK_ERROR_CODE(v) if (IsErrorCode(v)) { return v; }
