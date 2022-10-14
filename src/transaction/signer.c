#include "utils.h"
#include "common/hasher.h"

int initiatorHash(Signature *s, uint8_t initiator[static 32]) {
    CHECK_ERROR_INT(s)
    CHECK_ERROR_INT(s->_u)
    if (s->_u->PublicKey.buffer.size == 0 || s->_u->PublicKey.buffer.ptr == 0 ) {
        return ErrorInvalidObject;
    }
    uint64_t var = 0;
    Error e = UVarInt_get(&s->_u->SignerVersion, &var);
    if ( IsError(e) || var == 0 ) {
        return ErrorInvalidObject;
    }
    e = UVarInt_get(&s->_u->Timestamp, &var);
    if ( IsError(e) || var == 0 ) {
        return ErrorInvalidObject;
    }

    MerkleState hasher;
    MerkleStateInit(&hasher);
    CHECK_ERROR_CODE(hasherAddBytes(&hasher, &s->_u->PublicKey));
    CHECK_ERROR_CODE(hasherAddUrl(&hasher, &s->_u->Signer));
    CHECK_ERROR_CODE(hasherAddUVarInt(&hasher, &s->_u->SignerVersion));
    CHECK_ERROR_CODE(hasherAddUVarInt(&hasher, &s->_u->Timestamp));

    CHECK_ERROR_CODE(MerkleDAGRoot(&hasher, initiator).code);
    return ErrorNone;
}

int readSignature(Unmarshaler *m, Signature *v) {
    int n = 0;
    uint64_t field = 0;
    uint64_t type = 0;

    PRINTF("readSignature Begin\n");
    int b = unmarshalerReadField(m, &field);
    CHECK_ERROR_CODE(b);

    if ( field != 1 ) {
        return ErrorInvalidField;
    }
    n += b;
    b = unmarshalerReadUInt(m, &type);
    CHECK_ERROR_CODE(b);
    n += b;

    switch ( type ) {
        case SignatureTypeRCD1:
        case SignatureTypeETH:
        case SignatureTypeBTC:
        case SignatureTypeED25519:
            v->_u = (SignatureTypeUnion*)unmarshalerAlloc(m, sizeof(SignatureTypeUnion));
            CHECK_ERROR_INT(v->_u);
            PRINTF("Signature Type %d\n", type);
            v->_u->Type = type;
            b = readSignatureTypeUnion(m, v->_u);
            CHECK_ERROR_CODE(b);
            n += b;
            break;
        default:
            n = ErrorNotImplemented;
    }
    PRINTF("readSignature End %d\n", n);

    return n;
}

// UnmarshalBinary unmarshals the signature info from bytes
int readSignatureTypeUnion(Unmarshaler *m, SignatureTypeUnion *v) {
    int n = 0;
    uint64_t field = 0;

    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    int b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);

        PRINTF("pre signer parse %d\n", field);
    if ( field == 1 )
    {
        PRINTF("read type\n");
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        //ensure we are the correct union type
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
    PRINTF("pre signer parse %d\n", field);
    if ( field == 2 )
    {
        PRINTF("read public key\n");;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadBytes(m,&v->PublicKey);
        CHECK_ERROR_CODE(b);
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    PRINTF("pre signer parse %d\n", field);
    if ( field == 3 )
    {
        PRINTF("read signature\n");
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadBytes(m,&v->Signature);
        CHECK_ERROR_CODE(b);
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    PRINTF("pre signer parse %d\n", field);
    if ( field == 4 )
    {
        PRINTF("read signerurl\n");
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadUrl(m,&v->Signer);
        CHECK_ERROR_CODE(b);
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    PRINTF("pre signer parse %d\n", field);
    if ( field == 5 )
    {
        PRINTF("read version\n");
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadUVarInt(m,&v->SignerVersion);
        CHECK_ERROR_CODE(b);
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    PRINTF("pre signer parse %d\n", field);
    if ( field == 6 )
    {
        PRINTF("read timestamp\n");
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;

        b = unmarshalerReadUVarInt(m,&v->Timestamp);
        CHECK_ERROR_CODE(b);

        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    PRINTF("pre signer parse %d\n", field);
    if ( field == 7 )
    {
        PRINTF("read VoteType\n");
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        n += b;
        {
            uint64_t size = 0;
            b = unmarshalerReadUInt(m,&size);
            CHECK_ERROR_CODE(b);
            n += b;

            Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset, .buffer.size = size, .buffer.offset = 0,
                              .mempool = m->mempool};
            b = unmarshalerReadVoteType(&m2, &v->Vote);
            CHECK_ERROR_CODE(b);
        }
        buffer_seek_cur(&m->buffer, b);
        n += b;
    }
    if ( m->buffer.offset == m->buffer.size ) {
        return n;
    }
    b = unmarshalerPeekField(m,&field);
    CHECK_ERROR_CODE(b);
    PRINTF("pre signer parse %d\n", field);
    if ( field == 8 )
    {
        PRINTF("read bytes32\n");
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        PRINTF("read field %d\n", field);
        n += b;

        b = unmarshalerReadBytes32(m,&v->TransactionHash);
        PRINTF("read transaction hash %d",b);
        CHECK_ERROR_CODE(b);
        PRINTF("read transaction hash %d\n",b);
        n += b;
    }

        PRINTF("finsh signature union read %d\n",n);
    return n;
}
