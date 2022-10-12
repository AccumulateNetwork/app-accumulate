
#include "common/protocol/enum.h"
#include "common/protocol/unions.h"
#include "common/protocol/transaction.h"

#define _ACCUMULATE_TRANSACTION_SOURCE_



#ifdef _ACCUMULATE_TRANSACTION_SOURCE_

/// JSON Marshaling



#if _WANT_AddCredits_

TransactionType AddCredits_type(void) { return TransactionTypeAddCredits; }


/// Comparisons
bool AddCredits_equal(const AddCredits *v, const AddCredits *u) {
    {
        const TransactionType *a = &v->Type;
        const TransactionType *b = &u->Type;
        if ( !TransactionType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Recipient;
        const Url* b = &u->Recipient;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const BigInt *a = &v->Amount;
        const BigInt *b = &u->Amount;
        if ( !BigInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->Oracle;
        const UVarInt *b = &u->Oracle;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the add credits from bytes as a unsigned varint.
ACME_API int unmarshalerReadAddCredits(Unmarshaler *m, AddCredits *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = TransactionTypeAddCredits;
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        TransactionType *a = &v->Type;


        //ensure we are the correct union type
        uint64_t type = 0;
        b = unmarshalerReadUInt(m,&type);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        if ( type != unionType ) {
            return ErrorInvalidObject;
        }
        n += b;

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 2 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Recipient;


        b = unmarshalerReadUrl(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        BigInt *a = &v->Amount;


        b = unmarshalerReadBigInt(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->Oracle;


        b = unmarshalerReadUVarInt(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteAddCredits(Marshaler *m,const AddCredits*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != TransactionTypeAddCredits ) {
        return ErrorInvalidObject;
    }

    {
        const TransactionType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteTransactionType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Url* a = &v->Recipient;

        b = marshalerWriteField(m, 2);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUrl(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const BigInt *a = &v->Amount;

        b = marshalerWriteField(m, 3);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBigInt(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const UVarInt *a = &v->Oracle;

        b = marshalerWriteField(m, 4);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUVarInt(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


AddCredits AddCredits_init(AddCredits *v) {
    AddCredits init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = AddCredits_type;
    //    init.BinarySize = AddCredits_binarySize;
    //    init.Equal = AddCredits_equal;
    //init.Copy = AddCredits_copy;
    //    init.MarshalBinary = AddCredits_marshalBinary;
    //    init.UnmarshalBinary = AddCredits_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_AddCredits_ */

#if _WANT_Envelope_


/// Comparisons
bool Envelope_equal(const Envelope *v, const Envelope *u) {
    if ( v->Signatures_length == u->Signatures_length ) {
        for ( size_t i = 0; i < v->Signatures_length; ++i ) {
            const Signature* a = &v->Signatures[i];
            const Signature* b = &u->Signatures[i];
            if ( !Signature_equal(a, b) ) {
                return false;
            }
        }
    } else {
        return false;
    }
    {
        const Bytes *a = &v->TxHash;
        const Bytes *b = &u->TxHash;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    if ( v->Transaction_length == u->Transaction_length ) {
        for ( size_t i = 0; i < v->Transaction_length; ++i ) {
            const Transaction* a = &v->Transaction[i];
            const Transaction* b = &u->Transaction[i];
            if ( !Transaction_equal(a, b) ) {
                return false;
            }
        }
    } else {
        return false;
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the envelope from bytes as a unsigned varint.
ACME_API int unmarshalerReadEnvelope(Unmarshaler *m, Envelope *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;


    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 1 )
    {

        Unmarshaler m2 = NewUnmarshaler(&m->buffer,m->mempool);
        v->Signatures_length = 0;
        while ( field == 1 ) {
            b = unmarshalerReadField(&m2, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            uint64_t size = 0;
            b = unmarshalerReadUInt(&m2,&size);
            if ( IsError(ErrorCode(b)) ) {
                return b;
            }
            //skip the object
            buffer_seek_cur(&m2.buffer, size);

            v->Signatures_length++;
            field = 0;
            unmarshalerPeekField(&m2, &field);
        }
        //now unmarshal for real...
        v->Signatures = (Signature*)unmarshalerAlloc(m, v->Signatures_length*sizeof(Signature));
        for ( size_t i = 0; i < v->Signatures_length; ++i ) {
            Signature* a = &v->Signatures[i];

            b = unmarshalerReadField(m, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            if ( field != 1 ) {
                return ErrorInvalidField;
            }
            n += b;
            uint64_t size = 0;
            b = unmarshalerReadUInt(m,&size);
            if ( IsError(ErrorCode(b)) ) {
                return b;
            }
            n += b;
            Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                              .mempool = m->mempool};
            b = unmarshalerReadSignature(&m3, a);
            if ( IsError(ErrorCode(b))) {
                return b;
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
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 2 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes *a = &v->TxHash;


        b = unmarshalerReadBytes(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 3 )
    {

        Unmarshaler m2 = NewUnmarshaler(&m->buffer,m->mempool);
        v->Transaction_length = 0;
        while ( field == 3 ) {
            b = unmarshalerReadField(&m2, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            uint64_t size = 0;
            b = unmarshalerReadUInt(&m2,&size);
            if ( IsError(ErrorCode(b)) ) {
                return b;
            }
            //skip the object
            buffer_seek_cur(&m2.buffer, size);

            v->Transaction_length++;
            field = 0;
            unmarshalerPeekField(&m2, &field);
        }
        //now unmarshal for real...
        v->Transaction = (Transaction*)unmarshalerAlloc(m, v->Transaction_length*sizeof(Transaction));
        for ( size_t i = 0; i < v->Transaction_length; ++i ) {
            Transaction* a = &v->Transaction[i];

            b = unmarshalerReadField(m, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            if ( field != 3 ) {
                return ErrorInvalidField;
            }
            n += b;
            uint64_t size = 0;
            b = unmarshalerReadUInt(m,&size);
            if ( IsError(ErrorCode(b)) ) {
                return b;
            }
            n += b;
            Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                              .mempool = m->mempool};
            b = unmarshalerReadTransaction(&m3, a);
            if ( IsError(ErrorCode(b))) {
                return b;
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


ACME_API int marshalerWriteEnvelope(Marshaler *m,const Envelope*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    for ( size_t i = 0; i < v->Signatures_length; ++i ) {
        const Signature *a = &v->Signatures[i];
        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteSignature(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }

        n += b;
    }
    {
        const Bytes *a = &v->TxHash;

        b = marshalerWriteField(m, 2);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBytes(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    for ( size_t i = 0; i < v->Transaction_length; ++i ) {
        const Transaction *a = &v->Transaction[i];
        b = marshalerWriteField(m, 3);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteTransaction(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }

        n += b;
    }


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


Envelope Envelope_init(Envelope *v) {
    Envelope init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = Envelope_type;
    //    init.BinarySize = Envelope_binarySize;
    //    init.Equal = Envelope_equal;
    //init.Copy = Envelope_copy;
    //    init.MarshalBinary = Envelope_marshalBinary;
    //    init.UnmarshalBinary = Envelope_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_Envelope_ */

#if _WANT_SendTokens_

TransactionType SendTokens_type(void) { return TransactionTypeSendTokens; }


/// Comparisons
bool SendTokens_equal(const SendTokens *v, const SendTokens *u) {
    {
        const TransactionType *a = &v->Type;
        const TransactionType *b = &u->Type;
        if ( !TransactionType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->Hash;
        const Bytes32 *b = &u->Hash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }
    {
        const RawJson *a = &v->Meta;
        const RawJson *b = &u->Meta;
        if ( !RawJson_equal(a,b) ) {
            return false;
        }
    }
    if ( v->To_length == u->To_length ) {
        for ( size_t i = 0; i < v->To_length; ++i ) {
            const TokenRecipient* a = &v->To[i];
            const TokenRecipient* b = &u->To[i];
            if ( !TokenRecipient_equal(a, b) ) {
                return false;
            }
        }
    } else {
        return false;
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the send tokens from bytes as a unsigned varint.
ACME_API int unmarshalerReadSendTokens(Unmarshaler *m, SendTokens *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;
    v->Type = TransactionTypeSendTokens;
#if 0
    while ( b != m->buffer.size - m->buffer.offset ) {
        if ( m->buffer.offset == m->buffer.size ) {
            return n;
        }
        b = unmarshalerPeekField(m,&field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        switch ( field ) {
            case 1: {
                if ( !buffer_seek_cur(&m->buffer,1) ) {
                    return ErrorBufferTooSmall;
                }
                n += 1;

                uint64_t type = 0;
                b = uvarint_read(m->buffer.ptr+m->buffer.offset, m->buffer.size - m->buffer.offset, &type);
                if ( !buffer_seek_cur(&m->buffer,b) ) {
                    return ErrorBufferTooSmall;
                }
                if ( type != v->Type ) {
                    return ErrorInvalidObject;
                }
                n += b;

                break;
            }
            case 2: {
                if ( !buffer_seek_cur(&m->buffer,1) ) {
                    return ErrorBufferTooSmall;
                }
                n += 1;

                if ( !buffer_seek_cur(&m->buffer,32) ) {
                    return ErrorBufferTooSmall;
                }
                n += 32;
                break;
            }
            case 3: {
                if ( !buffer_seek_cur(&m->buffer,1) ) {
                    return ErrorBufferTooSmall;
                }
                n += 1;
                uint64_t size = 0;
                b = uvarint_read(m->buffer.ptr+m->buffer.offset, m->buffer.size - m->buffer.offset, &size);
                if ( !buffer_seek_cur(&m->buffer,b) ) {
                    return ErrorBufferTooSmall;
                }
                n += b;

                if ( !buffer_seek_cur(&m->buffer,size) ) {
                    return ErrorBufferTooSmall;
                }
                n += b;

                break;
            }
            case 4: {
                //Unmarshaler m2 = NewUnmarshaler(&m->buffer,m->mempool);
                while ( field == 4 ) {
                    b = unmarshalerReadField(m, &field);
                    if ( IsError(ErrorCode(b))) {
                        return b;
                    }
                    n += 1;

                    uint64_t size = 0;
                    b = uvarint_read(m->buffer.ptr+m->buffer.offset, m->buffer.size - m->buffer.offset, &size);
                    if ( !buffer_seek_cur(&m->buffer,b) ) {
                        return ErrorBufferTooSmall;
                    }
                    n += b;

                    //skip the object
                    buffer_seek_cur(&m->buffer, size);
                    n += size;
                    field = 0;
                    unmarshalerPeekField(m, &field);
                }
                return n;
                //break;
            }
            default:
                return n;
        }
    }
#endif
#if 1
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        TransactionType *a = &v->Type;


        //ensure we are the correct union type
        uint64_t type = 0;
        b = unmarshalerReadUInt(m,&type);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        if ( type != v->Type ) {
            return ErrorInvalidObject;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 2 )
    {
    //    buffer_seek_cur(&m->buffer,33);
    //    n += 33;
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->Hash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        RawJson *a = &v->Meta;


        b = unmarshalerReadRawJson(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 4 )
    {
        Unmarshaler m2 = NewUnmarshaler(&m->buffer,m->mempool);
        v->To_length = 0;
        while ( field == 4 ) {
            b = unmarshalerReadField(&m2, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            uint64_t size = 0;
            b = unmarshalerReadUInt(&m2,&size);
            if ( IsError(ErrorCode(b)) ) {
                return b;
            }
            //skip the object
            buffer_seek_cur(&m2.buffer, size);

            v->To_length++;
            field = 0;
            unmarshalerPeekField(&m2, &field);
        }
        //now unmarshal for real...
        v->To = (TokenRecipient*)unmarshalerAlloc(m, v->To_length*sizeof(TokenRecipient));
        for ( size_t i = 0; i < v->To_length; ++i ) {
            TokenRecipient* a = &v->To[i];

            b = unmarshalerReadField(m, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            if ( field != 4 ) {
                return ErrorInvalidField;
            }
            n += b;
            uint64_t size = 0;
            b = unmarshalerReadUInt(m,&size);
            if ( IsError(ErrorCode(b)) ) {
                return b;
            }
            n += b;
            Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                              .mempool = m->mempool};
            b = unmarshalerReadTokenRecipient(&m3, a);
            if ( IsError(ErrorCode(b))) {
                return b;
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
#endif
    return n;
}


ACME_API int marshalerWriteSendTokens(Marshaler *m,const SendTokens*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != TransactionTypeSendTokens ) {
        return ErrorInvalidObject;
    }

    {
        const TransactionType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteTransactionType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->Hash;

        b = marshalerWriteField(m, 2);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBytes32(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const RawJson *a = &v->Meta;

        b = marshalerWriteField(m, 3);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteRawJson(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    for ( size_t i = 0; i < v->To_length; ++i ) {
        const TokenRecipient *a = &v->To[i];
        b = marshalerWriteField(m, 4);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteTokenRecipient(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }

        n += b;
    }


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


SendTokens SendTokens_init(SendTokens *v) {
    SendTokens init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = SendTokens_type;
    //    init.BinarySize = SendTokens_binarySize;
    //    init.Equal = SendTokens_equal;
    //init.Copy = SendTokens_copy;
    //    init.MarshalBinary = SendTokens_marshalBinary;
    //    init.UnmarshalBinary = SendTokens_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_SendTokens_ */

#if _WANT_TokenRecipient_


/// Comparisons
bool TokenRecipient_equal(const TokenRecipient *v, const TokenRecipient *u) {
    {
        const Url* a = &v->Url;
        const Url* b = &u->Url;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const BigInt *a = &v->Amount;
        const BigInt *b = &u->Amount;
        if ( !BigInt_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the token recipient from bytes as a unsigned varint.
ACME_API int unmarshalerReadTokenRecipient(Unmarshaler *m, TokenRecipient *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;


    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Url;


        b = unmarshalerReadUrl(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 2 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        BigInt *a = &v->Amount;


        b = unmarshalerReadBigInt(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteTokenRecipient(Marshaler *m,const TokenRecipient*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    {
        const Url* a = &v->Url;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUrl(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const BigInt *a = &v->Amount;

        b = marshalerWriteField(m, 2);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBigInt(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


TokenRecipient TokenRecipient_init(TokenRecipient *v) {
    TokenRecipient init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = TokenRecipient_type;
    //    init.BinarySize = TokenRecipient_binarySize;
    //    init.Equal = TokenRecipient_equal;
    //init.Copy = TokenRecipient_copy;
    //    init.MarshalBinary = TokenRecipient_marshalBinary;
    //    init.UnmarshalBinary = TokenRecipient_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_TokenRecipient_ */

#if _WANT_Transaction_


/// Comparisons
bool Transaction_equal(const Transaction *v, const Transaction *u) {
    {
        const TransactionHeader *a = &v->Header;
        const TransactionHeader *b = &u->Header;
        if ( !TransactionHeader_equal(a,b) ) {
            return false;
        }
    }
    {
        const TransactionBody *a = &v->Body;
        const TransactionBody *b = &u->Body;
        if ( !TransactionBody_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the transaction from bytes as a unsigned varint.
ACME_API int unmarshalerReadTransaction(volatile Unmarshaler *m, Transaction *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;


    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        TransactionHeader *a = &v->Header;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }

        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadTransactionHeader(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        buffer_seek_cur(&m->buffer, b);


        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 2 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        TransactionBody *a = &v->Body;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadTransactionBody(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        buffer_seek_cur(&m->buffer, b);

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteTransaction(Marshaler *m,const Transaction*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    {
        const TransactionHeader *a = &v->Header;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteTransactionHeader(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const TransactionBody *a = &v->Body;

        b = marshalerWriteField(m, 2);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteTransactionBody(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


Transaction Transaction_init(Transaction *v) {
    Transaction init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = Transaction_type;
    //    init.BinarySize = Transaction_binarySize;
    //    init.Equal = Transaction_equal;
    //init.Copy = Transaction_copy;
    //    init.MarshalBinary = Transaction_marshalBinary;
    //    init.UnmarshalBinary = Transaction_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_Transaction_ */

#if _WANT_TransactionHeader_


/// Comparisons
bool TransactionHeader_equal(const TransactionHeader *v, const TransactionHeader *u) {
    {
        const Url* a = &v->Principal;
        const Url* b = &u->Principal;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->Initiator;
        const Bytes32 *b = &u->Initiator;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }
    {
        const String *a = &v->Memo;
        const String *b = &u->Memo;
        if ( !String_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->Metadata;
        const Bytes *b = &u->Metadata;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the transaction header from bytes as a unsigned varint.
ACME_API int unmarshalerReadTransactionHeader(Unmarshaler *m, TransactionHeader *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;


    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Principal;


        b = unmarshalerReadUrl(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 2 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->Initiator;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        String *a = &v->Memo;


        b = unmarshalerReadString(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes *a = &v->Metadata;


        b = unmarshalerReadBytes(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteTransactionHeader(Marshaler *m,const TransactionHeader*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    {
        const Url* a = &v->Principal;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUrl(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->Initiator;

        b = marshalerWriteField(m, 2);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBytes32(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const String *a = &v->Memo;

        b = marshalerWriteField(m, 3);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteString(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes *a = &v->Metadata;

        b = marshalerWriteField(m, 4);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBytes(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


TransactionHeader TransactionHeader_init(TransactionHeader *v) {
    TransactionHeader init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = TransactionHeader_type;
    //    init.BinarySize = TransactionHeader_binarySize;
    //    init.Equal = TransactionHeader_equal;
    //init.Copy = TransactionHeader_copy;
    //    init.MarshalBinary = TransactionHeader_marshalBinary;
    //    init.UnmarshalBinary = TransactionHeader_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_TransactionHeader_ */

#if _WANT_TransactionStatus_


/// Comparisons
bool TransactionStatus_equal(const TransactionStatus *v, const TransactionStatus *u) {
    {
        const Bytes32* a = &v->TxID;
        const Bytes32* b = &u->TxID;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }
    {
        const Status *a = &v->Code;
        const Status *b = &u->Code;
        if ( !Status_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bool *a = &v->Remote;
        const Bool *b = &u->Remote;
        if ( !Bool_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bool *a = &v->Delivered;
        const Bool *b = &u->Delivered;
        if ( !Bool_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bool *a = &v->Pending;
        const Bool *b = &u->Pending;
        if ( !Bool_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bool *a = &v->Failed;
        const Bool *b = &u->Failed;
        if ( !Bool_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->CodeNum;
        const UVarInt *b = &u->CodeNum;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const Error* a = &v->Error;
        const Error* b = &u->Error;
        if ( !Error_equal(a,b) ) {
            return false;
        }
    }
    {
        const TransactionResult *a = &v->Result;
        const TransactionResult *b = &u->Result;
        if ( !TransactionResult_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->Received;
        const UVarInt *b = &u->Received;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Initiator;
        const Url* b = &u->Initiator;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    if ( v->Signers_length == u->Signers_length ) {
        for ( size_t i = 0; i < v->Signers_length; ++i ) {
            const Signer* a = &v->Signers[i];
            const Signer* b = &u->Signers[i];
            if ( !Signer_equal(a, b) ) {
                return false;
            }
        }
    } else {
        return false;
    }
    if ( v->AnchorSigners_length == u->AnchorSigners_length ) {
        for ( size_t i = 0; i < v->AnchorSigners_length; ++i ) {
            const Bytes* a = &v->AnchorSigners[i];
            const Bytes* b = &u->AnchorSigners[i];
            if ( !Bytes_equal(a, b) ) {
                return false;
            }
        }
    } else {
        return false;
    }
    {
        const Url* a = &v->SourceNetwork;
        const Url* b = &u->SourceNetwork;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->DestinationNetwork;
        const Url* b = &u->DestinationNetwork;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->SequenceNumber;
        const UVarInt *b = &u->SequenceNumber;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bool *a = &v->GotDirectoryReceipt;
        const Bool *b = &u->GotDirectoryReceipt;
        if ( !Bool_equal(a,b) ) {
            return false;
        }
    }
    {
        const Receipt* a = &v->Proof;
        const Receipt* b = &u->Proof;
        if ( !Receipt_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the transaction status from bytes as a unsigned varint.
ACME_API int unmarshalerReadTransactionStatus(Unmarshaler *m, TransactionStatus *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;


    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 1 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32* a = &v->TxID;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 2 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Status *a = &v->Code;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadStatus(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        buffer_seek_cur(&m->buffer, b);

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 0 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bool *a = &v->Remote;


        b = unmarshalerReadBool(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 0 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bool *a = &v->Delivered;


        b = unmarshalerReadBool(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 0 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bool *a = &v->Pending;


        b = unmarshalerReadBool(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 0 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bool *a = &v->Failed;


        b = unmarshalerReadBool(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 0 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->CodeNum;


        b = unmarshalerReadUVarInt(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Error* a = &v->Error;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadError(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        buffer_seek_cur(&m->buffer, b);

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        TransactionResult *a = &v->Result;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadTransactionResult(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        buffer_seek_cur(&m->buffer, b);

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 5 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->Received;


        b = unmarshalerReadUVarInt(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 6 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Initiator;


        b = unmarshalerReadUrl(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 7 )
    {

        Unmarshaler m2 = NewUnmarshaler(&m->buffer,m->mempool);
        v->Signers_length = 0;
        while ( field == 7 ) {
            b = unmarshalerReadField(&m2, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            uint64_t size = 0;
            b = unmarshalerReadUInt(&m2,&size);
            if ( IsError(ErrorCode(b)) ) {
                return b;
            }
            //skip the object
            buffer_seek_cur(&m2.buffer, size);

            v->Signers_length++;
            field = 0;
            unmarshalerPeekField(&m2, &field);
        }
        //now unmarshal for real...
        v->Signers = (Signer*)unmarshalerAlloc(m, v->Signers_length*sizeof(Signer));
        for ( size_t i = 0; i < v->Signers_length; ++i ) {
            Signer* a = &v->Signers[i];

            b = unmarshalerReadField(m, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            if ( field != 7 ) {
                return ErrorInvalidField;
            }
            n += b;
            uint64_t size = 0;
            b = unmarshalerReadUInt(m,&size);
            if ( IsError(ErrorCode(b)) ) {
                return b;
            }
            n += b;
            Unmarshaler m3 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                              .mempool = m->mempool};
            b = unmarshalerReadSigner(&m3, a);
            if ( IsError(ErrorCode(b))) {
                return b;
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
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 8 )
    {

        Unmarshaler m2 = NewUnmarshaler(&m->buffer,m->mempool);
        v->AnchorSigners_length = 0;
        while ( field == 8 ) {
            b = unmarshalerReadField(&m2, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            //need to read the known type
            Bytes a;
            b = unmarshalerReadBytes(&m2, &a);
            if ( IsError(ErrorCode(b))) {
                return b;
            }

            v->AnchorSigners_length++;
            field = 0;
            unmarshalerPeekField(&m2, &field);
        }
        //now unmarshal for real...
        v->AnchorSigners = (Bytes*)unmarshalerAlloc(m, v->AnchorSigners_length*sizeof(Bytes));
        for ( size_t i = 0; i < v->AnchorSigners_length; ++i ) {
            Bytes* a = &v->AnchorSigners[i];

            b = unmarshalerReadField(m, &field);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            if ( field != 8 ) {
                return ErrorInvalidField;
            }
            n += b;
            b = unmarshalerReadBytes(m, a);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
        }

    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 9 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->SourceNetwork;


        b = unmarshalerReadUrl(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 10 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->DestinationNetwork;


        b = unmarshalerReadUrl(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 11 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->SequenceNumber;


        b = unmarshalerReadUVarInt(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 12 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bool *a = &v->GotDirectoryReceipt;


        b = unmarshalerReadBool(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    if ( field == 13 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Receipt* a = &v->Proof;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadReceipt(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        buffer_seek_cur(&m->buffer, b);

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteTransactionStatus(Marshaler *m,const TransactionStatus*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    {
        const Bytes32* a = &v->TxID;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBytes32(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Status *a = &v->Code;

        b = marshalerWriteField(m, 2);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteStatus(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bool *a = &v->Remote;

        b = marshalerWriteField(m, 0);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBool(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bool *a = &v->Delivered;

        b = marshalerWriteField(m, 0);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBool(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bool *a = &v->Pending;

        b = marshalerWriteField(m, 0);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBool(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bool *a = &v->Failed;

        b = marshalerWriteField(m, 0);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBool(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const UVarInt *a = &v->CodeNum;

        b = marshalerWriteField(m, 0);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUVarInt(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Error* a = &v->Error;

        b = marshalerWriteField(m, 3);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteError(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const TransactionResult *a = &v->Result;

        b = marshalerWriteField(m, 4);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteTransactionResult(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const UVarInt *a = &v->Received;

        b = marshalerWriteField(m, 5);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUVarInt(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Url* a = &v->Initiator;

        b = marshalerWriteField(m, 6);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUrl(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    for ( size_t i = 0; i < v->Signers_length; ++i ) {
        const Signer *a = &v->Signers[i];
        b = marshalerWriteField(m, 7);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteSigner(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }

        n += b;
    }
    for ( size_t i = 0; i < v->AnchorSigners_length; ++i ) {
        const Bytes *a = &v->AnchorSigners[i];
        b = marshalerWriteField(m, 8);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBytes(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }

        n += b;
    }
    {
        const Url* a = &v->SourceNetwork;

        b = marshalerWriteField(m, 9);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUrl(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Url* a = &v->DestinationNetwork;

        b = marshalerWriteField(m, 10);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUrl(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const UVarInt *a = &v->SequenceNumber;

        b = marshalerWriteField(m, 11);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteUVarInt(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bool *a = &v->GotDirectoryReceipt;

        b = marshalerWriteField(m, 12);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteBool(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Receipt* a = &v->Proof;

        b = marshalerWriteField(m, 13);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        buffer_t offsetBuffer = m->buffer;
        if ( !buffer_seek_cur(&offsetBuffer, sizeof(size_t))) {
            return ErrorBufferTooSmall;
        }
        Marshaler m2 = NewMarshaler(&offsetBuffer);//create a temporary marshaler that will compute size
        //need to identify what the size of the following will be and write those bytes.
        int size = marshalerWriteReceipt(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //write size of what is to follow
        b = marshalerWriteUInt(m, (uint64_t)size);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        //now copy the contents into the marshal buffer to prevent having to remarshal
        if (!buffer_move(&m->buffer, offsetBuffer.ptr + offsetBuffer.offset, size)) {
            return ErrorBadCopy;
        }
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


TransactionStatus TransactionStatus_init(TransactionStatus *v) {
    TransactionStatus init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = TransactionStatus_type;
    //    init.BinarySize = TransactionStatus_binarySize;
    //    init.Equal = TransactionStatus_equal;
    //init.Copy = TransactionStatus_copy;
    //    init.MarshalBinary = TransactionStatus_marshalBinary;
    //    init.UnmarshalBinary = TransactionStatus_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_TransactionStatus_ */

#endif /* _ACCUMULATE_TRANSACTION_SOURCE_ */