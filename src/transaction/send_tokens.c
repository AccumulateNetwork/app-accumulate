#include "utils.h"

int readSendTokens(Unmarshaler *m, SendTokens *v) {
    int n = 0;
    uint64_t field = 0;
    v->Type = TransactionTypeSendTokens;
//
//    int b = 0;
//    while ( b != (int)(m->buffer.size - m->buffer.offset) ) {
//        if ( m->buffer.offset == m->buffer.size ) {
//            return n;
//        }
//        b = unmarshalerPeekField(m,&field);
//        CHECK_ERROR_CODE(b);
//
//        switch ( field ) {
//            case 1: {
//                if ( !buffer_seek_cur(&m->buffer,1) ) {
//                    return ErrorBufferTooSmall;
//                }
//                n += 1;
//
//                uint64_t type = 0;
//                b = buffer_read_uvarint(&m->buffer, &type);
//                CHECK_ERROR_CODE(b);
//
//                if ( type != v->Type ) {
//                    return ErrorInvalidObject;
//                }
//                n += b;
//
//                break;
//            }
//            case 2: {
//                if ( !buffer_seek_cur(&m->buffer,1) ) {
//                    return ErrorBufferTooSmall;
//                }
//                n += 1;
//
//                if ( !buffer_seek_cur(&m->buffer,32) ) {
//                    return ErrorBufferTooSmall;
//                }
//                n += 32;
//                break;
//            }
//            case 3: {
//                if ( !buffer_seek_cur(&m->buffer,1) ) {
//                    return ErrorBufferTooSmall;
//                }
//                n += 1;
//                uint64_t size = 0;
//                b = buffer_read_uvarint(&m->buffer, &size);
//                CHECK_ERROR_CODE(b);
//                n += b;
//
//                //skip the buffer, don't need
//                if ( !buffer_seek_cur(&m->buffer,size) ) {
//                    return ErrorBufferTooSmall;
//                }
//                n += b;
//
//                break;
//            }
//            case 4: {
//                Unmarshaler m2 = {.buffer = m->buffer, .mempool = m->mempool};
//                v->To_length = 0;
//                while ( field == 4 ) {
//                    b = unmarshalerReadField(&m2, &field);
//                    CHECK_ERROR_CODE(b);
//
//                    uint64_t size = 0;
//                    b = unmarshalerReadUInt(&m2,&size);
//                    CHECK_ERROR_CODE(b);
//                    //skip the object
//                    buffer_seek_cur(&m2.buffer, size);
//
//                    v->To_length++;
//                    field = 0;
//                    unmarshalerPeekField(&m2, &field);
//                }
//                //now unmarshal for real...
//                v->To = (TokenRecipient*)unmarshalerAlloc(m, v->To_length*sizeof(TokenRecipient));
//                for ( size_t i = 0; i < v->To_length; ++i ) {
//                    TokenRecipient *a = &v->To[i];
//
//                    b = unmarshalerReadField(m, &field);
//                    if (IsError(ErrorCode(b))) {
//                        return b;
//                    }
//                    if (field != 4) {
//                        return ErrorInvalidField;
//                    }
//                    n += b;
//                    uint64_t size = 0;
//                    b = unmarshalerReadUInt(m, &size);
//                    CHECK_ERROR_CODE(b);
//
//                    n += b;
//                    {
//                        Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
//                                          .buffer.size = size,
//                                          .buffer.offset = 0,
//                                          .mempool = m->mempool};
//                        b = readTokenRecipient(&m3, &v->To[i]);
//                        CHECK_ERROR_CODE(b);
//                    }
//                    buffer_seek_cur(&m->buffer, b);
//                    if ( b > (int)size ) {
//                        return ErrorInvalidObject;
//                    }
//
//                    int skip = (int)size - b;
//                    if ( !buffer_seek_cur(&m->buffer, skip) ) {
//                        return ErrorInvalidObject;
//                    }
//                    b += (int)size-b;
//                    n += b;
//                }
//                return n;
//                //break;
//            }
//            default:
//                return n;
//        }
//    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    int b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        uint64_t type = 0;
        b = unmarshalerReadUInt(m,&type);
        CHECK_ERROR_CODE(b);
        n += b;

        if ( type != v->Type ) {
            return ErrorInvalidObject;
        }
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 2 )
    {
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadBytes32(m,&v->Hash);
        CHECK_ERROR_CODE(b);
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadRawJson(m,&v->Meta);
        CHECK_ERROR_CODE(b);
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    if ( field == 4 )
    {
        Unmarshaler m2 = NewUnmarshaler(&m->buffer,m->mempool);
        v->To_length = 0;
        while ( field == 4 ) {
            b = unmarshalerReadField(&m2, &field);
            CHECK_ERROR_CODE(b);
            uint64_t size = 0;
            b = unmarshalerReadUInt(&m2,&size);
            CHECK_ERROR_CODE(b);
            //skip the object
            buffer_seek_cur(&m2.buffer, size);
            v->To_length++;
            field = 0;
            unmarshalerPeekField(&m2, &field);
        }

        //now unmarshal for real...
        v->To = (TokenRecipient*)unmarshalerAlloc(m, v->To_length*sizeof(TokenRecipient));
        CHECK_ERROR_INT(v->To);
        for ( size_t i = 0; i < v->To_length; ++i ) {
            b = unmarshalerReadField(m, &field);
            CHECK_ERROR_CODE(b);
            n += b;
            if ( field != 4 ) {
                return ErrorInvalidField;
            }

            uint64_t size = 0;
            b = unmarshalerReadUInt(m,&size);
            CHECK_ERROR_CODE(b);
            n += b;

            {
                Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
                                  .buffer.size = size,
                                  .buffer.offset = 0,
                                  .mempool = m->mempool};
                b = readTokenRecipient(&m3, &v->To[i]);
                CHECK_ERROR_CODE(b);
            }
            buffer_seek_cur(&m->buffer, b);
            if ( b > (int)size ) {
                return ErrorInvalidObject;
            }

            int skip = (int)size - b;
            if ( !buffer_seek_cur(&m->buffer, skip) ) {
                return ErrorInvalidObject;
            }
            b += (int)size-b;
            n += b;
        }

    }
    return n;
}