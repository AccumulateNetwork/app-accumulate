
#include "common/protocol/unions.h"
#include "common/protocol/signatures.h"
#include "common/protocol/transaction.h"

#define _ACCUMULATE_TRANSACTION_SOURCE_


#ifdef _ACCUMULATE_TRANSACTION_SOURCE_

/// JSON Marshaling



#if _WANT_BTCLegacySignature_

SignatureType BTCLegacy_type(void) { return SignatureTypeBTCLegacy; }


/// Comparisons
bool BTCLegacySignature_equal(const BTCLegacySignature *v, const BTCLegacySignature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->PublicKey;
        const Bytes *b = &u->PublicKey;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->Signature;
        const Bytes *b = &u->Signature;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Signer;
        const Url* b = &u->Signer;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->SignerVersion;
        const UVarInt *b = &u->SignerVersion;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->Timestamp;
        const UVarInt *b = &u->Timestamp;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const VoteType *a = &v->Vote;
        const VoteType *b = &u->Vote;
        if ( !VoteType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the btclegacy signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadBTCLegacySignature(Unmarshaler *m, BTCLegacySignature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeBTCLegacy;
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
        SignatureType *a = &v->Type;


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
        Bytes *a = &v->PublicKey;


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
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes *a = &v->Signature;


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
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Signer;


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
    if ( field == 5 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->SignerVersion;


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
        UVarInt *a = &v->Timestamp;


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
    if ( field == 7 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        VoteType *a = &v->Vote;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadVoteType(&m2, a);
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
    if ( field == 8 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteBTCLegacySignature(Marshaler *m,const BTCLegacySignature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeBTCLegacy ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes *a = &v->PublicKey;

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
    {
        const Bytes *a = &v->Signature;

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
    {
        const Url* a = &v->Signer;

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
        const UVarInt *a = &v->SignerVersion;

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
        const UVarInt *a = &v->Timestamp;

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
        const VoteType *a = &v->Vote;

        b = marshalerWriteField(m, 7);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteVoteType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static BTCLegacySignature BTCLegacySignature_init(BTCLegacySignature *v) {
    BTCLegacySignature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = BTCLegacySignature_type;
    //    init.BinarySize = BTCLegacySignature_binarySize;
    //    init.Equal = BTCLegacySignature_equal;
    //init.Copy = BTCLegacySignature_copy;
    //    init.MarshalBinary = BTCLegacySignature_marshalBinary;
    //    init.UnmarshalBinary = BTCLegacySignature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_BTCLegacySignature_ */

#if _WANT_BTCSignature_

SignatureType BTC_type(void) { return SignatureTypeBTC; }


/// Comparisons
bool BTCSignature_equal(const BTCSignature *v, const BTCSignature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->PublicKey;
        const Bytes *b = &u->PublicKey;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->Signature;
        const Bytes *b = &u->Signature;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Signer;
        const Url* b = &u->Signer;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->SignerVersion;
        const UVarInt *b = &u->SignerVersion;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->Timestamp;
        const UVarInt *b = &u->Timestamp;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const VoteType *a = &v->Vote;
        const VoteType *b = &u->Vote;
        if ( !VoteType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the btcsignature from bytes as a unsigned varint.
ACME_API int unmarshalerReadBTCSignature(Unmarshaler *m, BTCSignature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeBTC;
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
        SignatureType *a = &v->Type;


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
        Bytes *a = &v->PublicKey;


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
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes *a = &v->Signature;


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
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Signer;


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
    if ( field == 5 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->SignerVersion;


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
        UVarInt *a = &v->Timestamp;


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
    if ( field == 7 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        VoteType *a = &v->Vote;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadVoteType(&m2, a);
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
    if ( field == 8 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteBTCSignature(Marshaler *m,const BTCSignature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeBTC ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes *a = &v->PublicKey;

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
    {
        const Bytes *a = &v->Signature;

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
    {
        const Url* a = &v->Signer;

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
        const UVarInt *a = &v->SignerVersion;

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
        const UVarInt *a = &v->Timestamp;

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
        const VoteType *a = &v->Vote;

        b = marshalerWriteField(m, 7);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteVoteType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static BTCSignature BTCSignature_init(BTCSignature *v) {
    BTCSignature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = BTCSignature_type;
    //    init.BinarySize = BTCSignature_binarySize;
    //    init.Equal = BTCSignature_equal;
    //init.Copy = BTCSignature_copy;
    //    init.MarshalBinary = BTCSignature_marshalBinary;
    //    init.UnmarshalBinary = BTCSignature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_BTCSignature_ */

#if _WANT_DelegatedSignature_

SignatureType Delegated_type(void) { return SignatureTypeDelegated; }


/// Comparisons
bool DelegatedSignature_equal(const DelegatedSignature *v, const DelegatedSignature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Signature *a = &v->Signature;
        const Signature *b = &u->Signature;
        if ( !Signature_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Delegator;
        const Url* b = &u->Delegator;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the delegated signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadDelegatedSignature(Unmarshaler *m, DelegatedSignature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeDelegated;
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
        SignatureType *a = &v->Type;


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
        Signature *a = &v->Signature;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadSignature(&m2, a);
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
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Delegator;


        b = unmarshalerReadUrl(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteDelegatedSignature(Marshaler *m,const DelegatedSignature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeDelegated ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Signature *a = &v->Signature;

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
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Url* a = &v->Delegator;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static DelegatedSignature DelegatedSignature_init(DelegatedSignature *v) {
    DelegatedSignature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = DelegatedSignature_type;
    //    init.BinarySize = DelegatedSignature_binarySize;
    //    init.Equal = DelegatedSignature_equal;
    //init.Copy = DelegatedSignature_copy;
    //    init.MarshalBinary = DelegatedSignature_marshalBinary;
    //    init.UnmarshalBinary = DelegatedSignature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_DelegatedSignature_ */

#if _WANT_ED25519Signature_

SignatureType ED25519_type(void) { return SignatureTypeED25519; }


/// Comparisons
bool ED25519Signature_equal(const ED25519Signature *v, const ED25519Signature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->PublicKey;
        const Bytes *b = &u->PublicKey;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->Signature;
        const Bytes *b = &u->Signature;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Signer;
        const Url* b = &u->Signer;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->SignerVersion;
        const UVarInt *b = &u->SignerVersion;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->Timestamp;
        const UVarInt *b = &u->Timestamp;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const VoteType *a = &v->Vote;
        const VoteType *b = &u->Vote;
        if ( !VoteType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the ed25519signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadED25519Signature(Unmarshaler *m, ED25519Signature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeED25519;
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
        SignatureType *a = &v->Type;


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
        Bytes *a = &v->PublicKey;


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
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes *a = &v->Signature;


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
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Signer;


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
    if ( field == 5 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->SignerVersion;


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
        UVarInt *a = &v->Timestamp;


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
    if ( field == 7 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        VoteType *a = &v->Vote;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadVoteType(&m2, a);
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
    if ( field == 8 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteED25519Signature(Marshaler *m,const ED25519Signature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeED25519 ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes *a = &v->PublicKey;

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
    {
        const Bytes *a = &v->Signature;

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
    {
        const Url* a = &v->Signer;

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
        const UVarInt *a = &v->SignerVersion;

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
        const UVarInt *a = &v->Timestamp;

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
        const VoteType *a = &v->Vote;

        b = marshalerWriteField(m, 7);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteVoteType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static ED25519Signature ED25519Signature_init(ED25519Signature *v) {
    ED25519Signature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = ED25519Signature_type;
    //    init.BinarySize = ED25519Signature_binarySize;
    //    init.Equal = ED25519Signature_equal;
    //init.Copy = ED25519Signature_copy;
    //    init.MarshalBinary = ED25519Signature_marshalBinary;
    //    init.UnmarshalBinary = ED25519Signature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_ED25519Signature_ */

#if _WANT_ETHSignature_

SignatureType ETH_type(void) { return SignatureTypeETH; }


/// Comparisons
bool ETHSignature_equal(const ETHSignature *v, const ETHSignature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->PublicKey;
        const Bytes *b = &u->PublicKey;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->Signature;
        const Bytes *b = &u->Signature;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Signer;
        const Url* b = &u->Signer;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->SignerVersion;
        const UVarInt *b = &u->SignerVersion;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->Timestamp;
        const UVarInt *b = &u->Timestamp;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const VoteType *a = &v->Vote;
        const VoteType *b = &u->Vote;
        if ( !VoteType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the ethsignature from bytes as a unsigned varint.
ACME_API int unmarshalerReadETHSignature(Unmarshaler *m, ETHSignature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeETH;
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
        SignatureType *a = &v->Type;


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
        Bytes *a = &v->PublicKey;


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
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes *a = &v->Signature;


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
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Signer;


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
    if ( field == 5 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->SignerVersion;


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
        UVarInt *a = &v->Timestamp;


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
    if ( field == 7 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        VoteType *a = &v->Vote;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadVoteType(&m2, a);
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
    if ( field == 8 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteETHSignature(Marshaler *m,const ETHSignature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeETH ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes *a = &v->PublicKey;

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
    {
        const Bytes *a = &v->Signature;

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
    {
        const Url* a = &v->Signer;

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
        const UVarInt *a = &v->SignerVersion;

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
        const UVarInt *a = &v->Timestamp;

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
        const VoteType *a = &v->Vote;

        b = marshalerWriteField(m, 7);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteVoteType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static ETHSignature ETHSignature_init(ETHSignature *v) {
    ETHSignature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = ETHSignature_type;
    //    init.BinarySize = ETHSignature_binarySize;
    //    init.Equal = ETHSignature_equal;
    //init.Copy = ETHSignature_copy;
    //    init.MarshalBinary = ETHSignature_marshalBinary;
    //    init.UnmarshalBinary = ETHSignature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_ETHSignature_ */

#if _WANT_InternalSignature_

SignatureType Internal_type(void) { return SignatureTypeInternal; }


/// Comparisons
bool InternalSignature_equal(const InternalSignature *v, const InternalSignature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->Cause;
        const Bytes32 *b = &u->Cause;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the internal signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadInternalSignature(Unmarshaler *m, InternalSignature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeInternal;
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
        SignatureType *a = &v->Type;


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
        Bytes32 *a = &v->Cause;


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
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteInternalSignature(Marshaler *m,const InternalSignature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeInternal ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->Cause;

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
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static InternalSignature InternalSignature_init(InternalSignature *v) {
    InternalSignature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = InternalSignature_type;
    //    init.BinarySize = InternalSignature_binarySize;
    //    init.Equal = InternalSignature_equal;
    //init.Copy = InternalSignature_copy;
    //    init.MarshalBinary = InternalSignature_marshalBinary;
    //    init.UnmarshalBinary = InternalSignature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_InternalSignature_ */

#if _WANT_LegacyED25519Signature_

SignatureType LegacyED25519_type(void) { return SignatureTypeLegacyED25519; }


/// Comparisons
bool LegacyED25519Signature_equal(const LegacyED25519Signature *v, const LegacyED25519Signature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->Timestamp;
        const UVarInt *b = &u->Timestamp;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->PublicKey;
        const Bytes *b = &u->PublicKey;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->Signature;
        const Bytes *b = &u->Signature;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Signer;
        const Url* b = &u->Signer;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->SignerVersion;
        const UVarInt *b = &u->SignerVersion;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const VoteType *a = &v->Vote;
        const VoteType *b = &u->Vote;
        if ( !VoteType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the legacy ed25519signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadLegacyED25519Signature(Unmarshaler *m, LegacyED25519Signature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeLegacyED25519;
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
        SignatureType *a = &v->Type;


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
        UVarInt *a = &v->Timestamp;


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
        Bytes *a = &v->PublicKey;


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
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes *a = &v->Signature;


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
    if ( field == 5 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Signer;


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
    if ( field == 6 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->SignerVersion;


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
    if ( field == 7 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        VoteType *a = &v->Vote;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadVoteType(&m2, a);
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
    if ( field == 8 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteLegacyED25519Signature(Marshaler *m,const LegacyED25519Signature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeLegacyED25519 ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const UVarInt *a = &v->Timestamp;

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
        const Bytes *a = &v->PublicKey;

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
    {
        const Bytes *a = &v->Signature;

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
    {
        const Url* a = &v->Signer;

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
        const UVarInt *a = &v->SignerVersion;

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
        const VoteType *a = &v->Vote;

        b = marshalerWriteField(m, 7);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteVoteType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static LegacyED25519Signature LegacyED25519Signature_init(LegacyED25519Signature *v) {
    LegacyED25519Signature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = LegacyED25519Signature_type;
    //    init.BinarySize = LegacyED25519Signature_binarySize;
    //    init.Equal = LegacyED25519Signature_equal;
    //init.Copy = LegacyED25519Signature_copy;
    //    init.MarshalBinary = LegacyED25519Signature_marshalBinary;
    //    init.UnmarshalBinary = LegacyED25519Signature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_LegacyED25519Signature_ */

#if _WANT_PartitionSignature_

SignatureType Partition_type(void) { return SignatureTypePartition; }


/// Comparisons
bool PartitionSignature_equal(const PartitionSignature *v, const PartitionSignature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
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
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the partition signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadPartitionSignature(Unmarshaler *m, PartitionSignature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypePartition;
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
        SignatureType *a = &v->Type;


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
    if ( field == 3 )
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
    if ( field == 4 )
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
    if ( field == 5 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWritePartitionSignature(Marshaler *m,const PartitionSignature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypePartition ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Url* a = &v->SourceNetwork;

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
        const Url* a = &v->DestinationNetwork;

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
    {
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static PartitionSignature PartitionSignature_init(PartitionSignature *v) {
    PartitionSignature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = PartitionSignature_type;
    //    init.BinarySize = PartitionSignature_binarySize;
    //    init.Equal = PartitionSignature_equal;
    //init.Copy = PartitionSignature_copy;
    //    init.MarshalBinary = PartitionSignature_marshalBinary;
    //    init.UnmarshalBinary = PartitionSignature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_PartitionSignature_ */

#if _WANT_RCD1Signature_

SignatureType RCD1_type(void) { return SignatureTypeRCD1; }


/// Comparisons
bool RCD1Signature_equal(const RCD1Signature *v, const RCD1Signature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->PublicKey;
        const Bytes *b = &u->PublicKey;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes *a = &v->Signature;
        const Bytes *b = &u->Signature;
        if ( !Bytes_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Signer;
        const Url* b = &u->Signer;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->SignerVersion;
        const UVarInt *b = &u->SignerVersion;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const UVarInt *a = &v->Timestamp;
        const UVarInt *b = &u->Timestamp;
        if ( !UVarInt_equal(a,b) ) {
            return false;
        }
    }
    {
        const VoteType *a = &v->Vote;
        const VoteType *b = &u->Vote;
        if ( !VoteType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the rcd1signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadRCD1Signature(Unmarshaler *m, RCD1Signature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeRCD1;
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
        SignatureType *a = &v->Type;


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
        Bytes *a = &v->PublicKey;


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
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes *a = &v->Signature;


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
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Signer;


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
    if ( field == 5 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        UVarInt *a = &v->SignerVersion;


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
        UVarInt *a = &v->Timestamp;


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
    if ( field == 7 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        VoteType *a = &v->Vote;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadVoteType(&m2, a);
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
    if ( field == 8 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteRCD1Signature(Marshaler *m,const RCD1Signature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeRCD1 ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes *a = &v->PublicKey;

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
    {
        const Bytes *a = &v->Signature;

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
    {
        const Url* a = &v->Signer;

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
        const UVarInt *a = &v->SignerVersion;

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
        const UVarInt *a = &v->Timestamp;

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
        const VoteType *a = &v->Vote;

        b = marshalerWriteField(m, 7);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteVoteType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static RCD1Signature RCD1Signature_init(RCD1Signature *v) {
    RCD1Signature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = RCD1Signature_type;
    //    init.BinarySize = RCD1Signature_binarySize;
    //    init.Equal = RCD1Signature_equal;
    //init.Copy = RCD1Signature_copy;
    //    init.MarshalBinary = RCD1Signature_marshalBinary;
    //    init.UnmarshalBinary = RCD1Signature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_RCD1Signature_ */

#if _WANT_ReceiptSignature_

SignatureType Receipt_type(void) { return SignatureTypeReceipt; }


/// Comparisons
bool ReceiptSignature_equal(const ReceiptSignature *v, const ReceiptSignature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->SourceNetwork;
        const Url* b = &u->SourceNetwork;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const Receipt *a = &v->Proof;
        const Receipt *b = &u->Proof;
        if ( !Receipt_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the receipt signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadReceiptSignature(Unmarshaler *m, ReceiptSignature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeReceipt;
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
        SignatureType *a = &v->Type;


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
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Receipt *a = &v->Proof;


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
        Bytes32 *a = &v->TransactionHash;


        b = unmarshalerReadBytes32(m,a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteReceiptSignature(Marshaler *m,const ReceiptSignature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeReceipt ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Url* a = &v->SourceNetwork;

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
        const Receipt *a = &v->Proof;

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
    {
        const Bytes32 *a = &v->TransactionHash;

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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static ReceiptSignature ReceiptSignature_init(ReceiptSignature *v) {
    ReceiptSignature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = ReceiptSignature_type;
    //    init.BinarySize = ReceiptSignature_binarySize;
    //    init.Equal = ReceiptSignature_equal;
    //init.Copy = ReceiptSignature_copy;
    //    init.MarshalBinary = ReceiptSignature_marshalBinary;
    //    init.UnmarshalBinary = ReceiptSignature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_ReceiptSignature_ */

#if _WANT_RemoteSignature_

SignatureType Remote_type(void) { return SignatureTypeRemote; }


/// Comparisons
bool RemoteSignature_equal(const RemoteSignature *v, const RemoteSignature *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Destination;
        const Url* b = &u->Destination;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const Signature *a = &v->Signature;
        const Signature *b = &u->Signature;
        if ( !Signature_equal(a,b) ) {
            return false;
        }
    }

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the remote signature from bytes as a unsigned varint.
ACME_API int unmarshalerReadRemoteSignature(Unmarshaler *m, RemoteSignature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeRemote;
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
        SignatureType *a = &v->Type;


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
        Url* a = &v->Destination;


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
        Signature *a = &v->Signature;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadSignature(&m2, a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        buffer_seek_cur(&m->buffer, b);

        n += b;
    }

    return n;
}


ACME_API int marshalerWriteRemoteSignature(Marshaler *m,const RemoteSignature*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeRemote ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Url* a = &v->Destination;

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
        const Signature *a = &v->Signature;

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
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static RemoteSignature RemoteSignature_init(RemoteSignature *v) {
    RemoteSignature init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = RemoteSignature_type;
    //    init.BinarySize = RemoteSignature_binarySize;
    //    init.Equal = RemoteSignature_equal;
    //init.Copy = RemoteSignature_copy;
    //    init.MarshalBinary = RemoteSignature_marshalBinary;
    //    init.UnmarshalBinary = RemoteSignature_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_RemoteSignature_ */

#if _WANT_SignatureSet_

SignatureType Set_type(void) { return SignatureTypeSet; }


/// Comparisons
bool SignatureSet_equal(const SignatureSet *v, const SignatureSet *u) {
    {
        const SignatureType *a = &v->Type;
        const SignatureType *b = &u->Type;
        if ( !SignatureType_equal(a,b) ) {
            return false;
        }
    }
    {
        const VoteType *a = &v->Vote;
        const VoteType *b = &u->Vote;
        if ( !VoteType_equal(a,b) ) {
            return false;
        }
    }
    {
        const Url* a = &v->Signer;
        const Url* b = &u->Signer;
        if ( !Url_equal(a,b) ) {
            return false;
        }
    }
    {
        const Bytes32 *a = &v->TransactionHash;
        const Bytes32 *b = &u->TransactionHash;
        if ( !Bytes32_equal(a,b) ) {
            return false;
        }
    }
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

    return true;
}



/// Binary Marshalers
/// Binary Unmarshalers
// UnmarshalBinary unmarshals the signature set from bytes as a unsigned varint.
ACME_API int unmarshalerReadSignatureSet(Unmarshaler *m, SignatureSet *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;
    uint64_t field = 0;

    uint64_t unionType = SignatureTypeSet;
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
        SignatureType *a = &v->Type;


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
        VoteType *a = &v->Vote;


        uint64_t size = 0;
        b = unmarshalerReadUInt(m,&size);
        if ( IsError(ErrorCode(b)) ) {
            return b;
        }
        n += b;
        Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                          .mempool = m->mempool};
        b = unmarshalerReadVoteType(&m2, a);
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
    if ( field == 3 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Url* a = &v->Signer;


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
    if ( field == 4 )
    {
        b = unmarshalerReadField(m, &field);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        n += b;
        Bytes32 *a = &v->TransactionHash;


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
    if ( field == 5 )
    {

        Unmarshaler m2 = NewUnmarshaler(&m->buffer,&m->mempool);
        v->Signatures_length = 0;
        while ( field == 5 ) {
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
            if ( field != 5 ) {
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

    return n;
}


ACME_API int marshalerWriteSignatureSet(Marshaler *m,const SignatureSet*v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    int b = 0;


    if ( v->Type != SignatureTypeSet ) {
        return ErrorInvalidObject;
    }

    {
        const SignatureType *a = &v->Type;

        b = marshalerWriteField(m, 1);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteSignatureType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const VoteType *a = &v->Vote;

        b = marshalerWriteField(m, 2);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
        b = marshalerWriteVoteType(m,*a);
        if ( IsError(ErrorCode(b))) {
            return b;
        }

        n += b;
    }
    {
        const Url* a = &v->Signer;

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
        const Bytes32 *a = &v->TransactionHash;

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
    for ( size_t i = 0; i < v->Signatures_length; ++i ) {
        const Signature *a = &v->Signatures[i];
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


    return n;
}


/// JSON Marshaling


/// JSON Unmarshaling


static SignatureSet SignatureSet_init(SignatureSet *v) {
    SignatureSet init;
    memset((void*)&init, 0, sizeof(init));

    //    init.GetType = SignatureSet_type;
    //    init.BinarySize = SignatureSet_binarySize;
    //    init.Equal = SignatureSet_equal;
    //init.Copy = SignatureSet_copy;
    //    init.MarshalBinary = SignatureSet_marshalBinary;
    //    init.UnmarshalBinary = SignatureSet_unmarshalBinary;
    //

    if ( v ) {
        *v = init;
    }
    return init;
}
#endif /* _WANT_SignatureSet_ */

#endif /* _ACCUMULATE_TRANSACTION_SOURCE_ */
