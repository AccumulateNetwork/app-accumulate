#include "utils.h"
#include <common/hasher.h>
#include <protocol/unions.h>

int initiatorHash(Signature *s, uint8_t initiator[static 32]) {
    CHECK_ERROR_INT(s)
    CHECK_ERROR_INT(s->_u)
    if (s->_u->PublicKey.buffer.size == 0 || s->_u->PublicKey.buffer.ptr == 0) {
        return ErrorInvalidObject;
    }
    uint64_t var = 0;
    Error e = UVarInt_get(&s->_u->SignerVersion, &var);
    if (IsError(e) || var == 0) {
        return ErrorInvalidObject;
    }
    e = UVarInt_get(&s->_u->Timestamp, &var);
    if (IsError(e) || var == 0) {
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

bool isMetadataField(int field, SignatureType type) {
    switch (field) {
        case SigTypeMarshalFieldTransactionHash:
            if (type == SignatureTypeDelegated) {
                return true;
            }
            break;
        case SigTypeMarshalFieldSignature:
            switch (type) {
                case SignatureTypeReceipt:
                case SignatureTypeInternal:
                case SignatureTypePartition:
                    return true;
                default:
                    return false;
            }
            break;
        default:
            return true;
    }
    return false;
}

int metadataHash(Signature *s,
                 uint8_t txHash[static 32],
                 uint8_t hash[static 32],
                 uint8_t metadataHash[static 32]) {
    CHECK_ERROR_INT(s)
    CHECK_ERROR_INT(s->_u)
    if (s->_u->PublicKey.buffer.size == 0 || s->_u->PublicKey.buffer.ptr == 0) {
        return ErrorInvalidObject;
    }
    int byteArrayLen = 0;
    Bytes *byteArray;
    byteArray = s->_u->extraData;
    byteArrayLen = (int) sizeof(s->_u->extraData) / sizeof(Bytes);

    // hash marshaled fields PublicKey, Signer, SignerVersion, Timestamp
    HashContext ctx;
    crypto_hash_init(&ctx);
    for (int i = 0; i < byteArrayLen; i++) {
        if (byteArray[i].buffer.ptr && isMetadataField(i + 1, s->_u->Type)) {
            buffer_t *buff = &byteArray[i].buffer;
            crypto_hash_update(&ctx, buff->ptr + buff->offset, buff->size - buff->offset);
        }
    }
    crypto_hash_final(&ctx, hash, 32);

    // combine hashes for metadata signing hash
    crypto_hash_init(&ctx);
    crypto_hash_update(&ctx, hash, 32);
    memmove(metadataHash, hash, 32);
    crypto_hash_update(&ctx, txHash, 32);
    crypto_hash_final(&ctx, hash, 32);
    return ErrorNone;
}

int readSignature(Unmarshaler *m, Signature *v) {
    int n = 0;
    uint64_t field = 0;
    uint64_t type = 0;

    buffer_t sigMark = {m->buffer.ptr + m->buffer.offset, 0, 0};

    int b = unmarshalerReadField(m, &field);
    CHECK_ERROR_CODE(b);

    if (field != 1) {
        return ErrorInvalidField;
    }
    n += b;
    sigMark.size += b;

    b = unmarshalerReadUInt(m, &type);
    CHECK_ERROR_CODE(b);
    n += b;
    sigMark.size += b;

    switch (type) {
        case SignatureTypeRCD1:
        case SignatureTypeETH:
        case SignatureTypeBTC:
        case SignatureTypeED25519:
            v->_u = (SignatureTypeUnion *) unmarshalerAlloc(m, sizeof(SignatureTypeUnion));
            explicit_bzero(v->_u->extraData, sizeof(v->_u->extraData));
            CHECK_ERROR_INT(v->_u);
            PRINTF("Signature Type %d\n", type);
            v->_u->Type = type;
            b = readSignatureTypeUnion(m, v->_u);
            v->_u->extraData[0].buffer = sigMark;

            CHECK_ERROR_CODE(b);
            n += b;
            sigMark.size += b;
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

    explicit_bzero(v->extraData, sizeof(v->extraData));
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    int b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);

    if (field == 1) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;

        // ensure we are the correct union type
        uint64_t type = 0;
        b = unmarshalerReadUInt(m, &type);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;

        if (type != v->Type) {
            return ErrorInvalidObject;
        }
    }

    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    if (field == 2) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;

        b = unmarshalerReadBytes(m, &v->PublicKey);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);

    if (field == 3) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;

        b = unmarshalerReadBytes(m, &v->Signature);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    PRINTF("pre signer parse %d\n", field);
    if (field == 4) {
        PRINTF("pre siigner field 4\n");
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        PRINTF("read signerurl\n");
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;

        b = unmarshalerReadUrl(m, &v->Signer);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);

    if (field == 5) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;

        b = unmarshalerReadUVarInt(m, &v->SignerVersion);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    if (field == 6) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;

        b = unmarshalerReadUVarInt(m, &v->Timestamp);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    if (field == 7) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;
        {
            uint64_t size = 0;
            b = unmarshalerReadUInt(m, &size);
            CHECK_ERROR_CODE(b);
            v->extraData[field - 1].buffer.size += b;
            n += b;

            Unmarshaler m2 = {.buffer.ptr = m->buffer.ptr + m->buffer.offset,
                              .buffer.size = size,
                              .buffer.offset = 0,
                              .mempool = m->mempool};
            b = unmarshalerReadVoteType(&m2, &v->Vote);
            CHECK_ERROR_CODE(b);
        }
        buffer_seek_cur(&m->buffer, b);
        v->extraData[field - 1].buffer.size += b;
        n += b;
    }
    if (m->buffer.offset == m->buffer.size) {
        return n;
    }
    b = unmarshalerPeekField(m, &field);
    CHECK_ERROR_CODE(b);
    if (field == 8) {
        v->extraData[field - 1].buffer.ptr = m->buffer.ptr + m->buffer.offset;
        b = unmarshalerReadField(m, &field);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;

        b = unmarshalerReadBytes32(m, &v->TransactionHash);
        CHECK_ERROR_CODE(b);
        v->extraData[field - 1].buffer.size += b;
        n += b;
    }
    return n;
}
