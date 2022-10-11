#include <common/error.h>
#include <stdlib.h>

Error Error_init(Error *e) {
    Error err = ErrorCode(ErrorNone);
    if ( e ) {
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

    static Error errors[] = {
#ifdef WANT_TEXT
    {ErrorNone, {0}},
    {ErrorUnknown, "unknown"},
    {ErrorInvalidEnum,"invalid enum"},
    {ErrorInvalidObject,"invalid object"},
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
    {ErrorInvalidHashParameters, "invalid hash params"},
    {ErrorUVarIntRead, "uvarint read failed"},
    {ErrorUVarIntWrite,"uvarint write failed"},
    {ErrorMempoolFull, "mempool full"},
    {ErrorInvalidOffset, "invalid offset"},
    {ErrorInvalidData, "invalid data"},
    {ErrorBadKey, "bad key"},
    {ErrorInvalidField, "invalid field"},
    {ErrorExpectingType, "expecting type"},
#else
        {ErrorNone, {0}},
        {ErrorUnknown, {0}},
        {ErrorInvalidEnum,{0}},
        {ErrorInvalidObject,{0}},
        {ErrorNotImplemented, {0}},
        {ErrorTypeNotFound, {0}},
        {ErrorParameterNil, {0}},
        {ErrorParameterInsufficientData,{0}},
        {ErrorBadCopy,{0}},
        {ErrorBufferTooSmall,{0}},
        {ErrorVarIntRead, {0}},
        {ErrorVarIntWrite,{0}},
        {ErrorResizeRequred,{0}},
        {ErrorInvalidBigInt,{0}},
        {ErrorInvalidString,{0}},
        {ErrorInvalidHashParameters, {0}},
        {ErrorUVarIntRead, {0}},
        {ErrorUVarIntWrite,{0}},
        {ErrorMempoolFull, {0}},
        {ErrorInvalidOffset, {0}},
        {ErrorInvalidData, {0}},
        {ErrorBadKey, {0}},
        {ErrorInvalidField, {0}},
        {ErrorExpectingType, {0}},
#endif
    };
    //if we have an error code greater than zero that makes it in here, then it is not intended as an error
    if ( (int)(e) >= 0 ) {
        return errors[ErrorNone];
    }

    //if we have an enum error that wasn't included in the list, then we have an error
    if ( abs((int)e) >= (int)abs(ErrorMaxError) ) {
        return errors[abs(ErrorInvalidEnum)];
    }

    return errors[abs((int)e)];
}

