#include <common/error.h>

Error Error_init(Error *e) {
    Error err = ErrorCode(ErrorNone);
    if ( e ) {
        *e = err;
    }
    return err;
}

Error ErrorCode(ErrorEnum e) {
    static errors[] = {
    {ErrorNone, {0}},
    {ErrorUnknown, "unknown"},
    {ErrorInvalidEnum,"invalid enum"},
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
    if ( (int)(e) > sizeof(errors) ) {
        return Error[ErrorInvalidEnum];
    }
    return errors[e];
}

