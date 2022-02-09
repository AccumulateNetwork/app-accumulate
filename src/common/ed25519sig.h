#pragma once

#include <common/encoding.h>

#pragma pack(1)

typedef struct {
    uint64_t Nonce; // Nonce of Signature
    uint8_t PublicKey[32]; // 32 byte public key
    uint8_t Signature[64]; // a set of 64 byte signatures
} ED25519Sig_t;

//#pragma pop()


typedef struct ED25519Sig {
    VarInt nonce;
    Bytes32 PublicKey;
    Bytes64 Signature;
    Error MarshalBinary(const struct ED25519Sig* t, struct Marshaler *outData);
    Error UnmarshalBinary(struct ED25519Sig* t, struct Marshaler *inData);
} ED25519Sig;

