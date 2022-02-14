#pragma once

#include <common/encoding.h>

#pragma pack(1)

typedef struct {
    VarInt_t _Nonce; // Nonce of Signature
    Bytes32_t _PublicKey; // 32 byte public key
    Bytes64_t _Signature; // a set of 64 byte signatures
} ED25519Sig_t;

int ED25519Sig_binarySize(const ED25519Sig_t *d) {
    if (!d) {
        return 0;
    }
    int n = 0;
    VarInt v = VarInt_init(&d->_Nonce);
    Bytes32 pk = Bytes32_init(&d->_PublicKey);
    Bytes64 sig = Bytes64_init( &d->_Signature);

    n += v.data.BinarySize(&v.data);
    n += pk.data.BinarySize(&pk.data);
    n += sig.data.BinarySize(&pk.data);
    return n;
}

Error ED25519Sig_marshalBinary(const ED25519Sig_t *d, Marshaler *outData) {
    if (!d || !outData) {
        return ErrorCode(ErrorParameterNil);
    }

    int size = ED25519Sig_binarySize(d);
    if ( size > outData->cache.size-outData->cache.offset) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    VarInt v = VarInt_init(&d->_Nonce);
    Error e = v.data.MarshalBinary(&v.data,outData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    Bytes32 pk = Bytes32_init(&d->_PublicKey);
    e = pk.data.MarshalBinary(&pk.data,outData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    Bytes64 sig = Bytes64_init( &d->_Signature);
    e = sig.data.MarshalBinary(&sig.data,outData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    return e;
}

Error ED25519Sig_unmarshalBinary(ED25519Sig_t *d, Marshaler *inData) {
    if (!d || !inData) {
        return ErrorCode(ErrorParameterNil);
    }

    VarInt v = VarInt_init(&d->_Nonce);
    Error e = v.data.UnmarshalBinary(&v.data,inData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    Bytes32 pk = Bytes32_init(&d->_PublicKey);
    e = pk.data.UnmarshalBinary(&pk.data,inData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    Bytes64 sig = Bytes64_init( &d->_Signature);
    e = sig.data.UnmarshalBinary(&sig.data,inData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    return e;

}

typedef struct ED25519Sig {
    VarInt    _nonce;
    Bytes32   _publicKey;
    Bytes64   _signature;
    Error (*MarshalBinary)(const struct ED25519Sig* t, struct Marshaler *outData);
    Error (*UnmarshalBinary)(struct ED25519Sig* t, struct Marshaler *inData);
    int (*BinarySize)(const struct ED25519Sig *self);
} ED25519Sig;


