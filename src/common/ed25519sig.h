#pragma once

#include <common/encoding.h>

#pragma pack(1)

typedef struct {
    uint64_t _Nonce; // Nonce of Signature
    uint8_t  _PublicKey[32]; // 32 byte public key
    uint8_t  _Signature[64]; // a set of 64 byte signatures
} ED25519Sig_t;

//#pragma pop()


typedef struct ED25519Sig {
    VarInt    _Nonce;
    Bytes32   _PublicKey;
    Bytes64   _Signature;
    Error MarshalBinary(const struct ED25519Sig* t, struct Marshaler *outData);
    Error UnmarshalBinary(struct ED25519Sig* t, struct Marshaler *inData);
} ED25519Sig;

