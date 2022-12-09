#include <common/error.h>
#include <stdlib.h>

Error Error_init(Error *e) {
    Error err = ErrorCode(ErrorNone);
    if (e) {
        *e = err;
    }
    return err;
}

bool IsError(Error e) {
    return e.code != ErrorNone;
}
bool IsErrorCode(int e) {
    return ErrorCode(e).code != ErrorNone;
}

Error ErrorCode(int e) {
    // if we have an error code greater than zero that makes it in here, then it is not intended as
    // an error
    if ((int) (e) >= 0) {
        return (const Error){ErrorNone, {0}};
    }

#if WANT_TEXT
    switch (abs((int) e)) {
        case ErrorNone:
            return (const Error){ErrorNone, {0}};
        case ErrorUnknown:
            return (const Error){ErrorUnknown, "unknown"};
        case ErrorInvalidEnum:
            return (const Error){ErrorInvalidEnum, "invalid enum"};
        case ErrorInvalidObject:
            return (const Error){ErrorInvalidObject, "invalid object"};
        case ErrorNotImplemented:
            return (const Error){ErrorNotImplemented, "not implemented"};
        case ErrorTypeNotFound:
            return (const Error){ErrorTypeNotFound, "type not found"};
        case ErrorParameterNil:
            return (const Error){ErrorParameterNil, "parameter is nil"};
        case ErrorParameterInsufficientData:
            return (const Error){ErrorParameterInsufficientData, "insufficient buffer size"};
        case ErrorBadCopy:
            return (const Error){ErrorBadCopy, "cannot copy buffer"};
        case ErrorBufferTooSmall:
            return (const Error){ErrorBufferTooSmall, "buffer size too small"};
        case ErrorVarIntRead:
            return (const Error){ErrorVarIntRead, "varint read failed"};
        case ErrorVarIntWrite:
            return (const Error){ErrorVarIntWrite, "varint write failed"};
        case ErrorResizeRequred:
            return (const Error){ErrorResizeRequired, "resize required"};
        case ErrorInvalidBigInt:
            return (const Error){ErrorInvalidBigInt, "invalid big int"};
        case ErrorInvalidString:
            return (const Error){ErrorInvalidString, "invalid string"};
        case ErrorInvalidHashParameters:
            return (const Error){ErrorInvalidHashParameters, "invalid hash params"};
        case ErrorUVarIntRead:
            return (const Error){ErrorUVarIntRead, "uvarint read failed"};
        case ErrorUVarIntWrite:
            return (const Error){ErrorUVarIntWrite, "uvarint write failed"};
        case ErrorMempoolFull:
            return (const Error){ErrorMempoolFull, "mempool full"};
        case ErrorInvalidOffset:
            return (const Error){ErrorInvalidOffset, "invalid offset"};
        case ErrorInvalidData:
            return (const Error){ErrorInvalidData, "invalid data"};
        case ErrorBadKey:
            return (const Error){ErrorBadKey, "bad key"};
        case ErrorInvalidField:
            return (const Error){ErrorInvalidField, "invalid field"};
        case ErrorExpectingType:
            return (const Error){ErrorExpectingType, "expecting type"};
        default:
            return (const Error){ErrorInvalidEnum, "invalid enum"};
    }
#else
    return (const Error){e, {0}};
#endif
}
