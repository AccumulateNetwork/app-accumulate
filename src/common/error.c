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

Error ErrorCode(ErrorEnum e) {
    static Error errors[] = {
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
    };
    //if we have an error code greater than zero that makes it in here, then it is not indended as an error
    if ( (int)(e) >= 0 ) {
        return errors[ErrorNone];
    }

    //if we have an enum error that wasn't included in the list, then we have an error
    if ( abs(e) > sizeof(errors) ) {
        return errors[abs(ErrorInvalidEnum)];
    }

    return errors[abs(e)];
}

