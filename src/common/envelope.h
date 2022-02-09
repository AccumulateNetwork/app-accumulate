#pragma once

#include <common/encoding.h>
#include <common/ed25519sig.h>

typedef struct Transaction {
    VarInt type;
    Bytes *payload;
    Error MarshalBinary(const struct Transaction* t, struct Marshaler *outData);
    Error UnmarshalBinary(struct Transaction* t, struct Marshaler *inData);
} Transaction; //encoder

typedef struct {
    VarInt   numSignatures;//stores the number of signatures.
    ED25519Sig *Signatures;   //`json:"signatures,omitempty" form:"signatures" query:"signatures" validate:"required"`
    Bytes TxHash;         //  `json:"txHash,omitempty" form:"txHash" query:"txHash" validate:"required"`
    Transaction *transaction;          //  `json:"transaction,omitempty" form:"transaction" query:"transaction" validate:"required"`
} Envelope; //encoder


typedef struct {
    uint64_t       NumSignatures;//stores the number of signatures.
    ED25519Sig_t *Signatures;   //`json:"signatures,omitempty" form:"signatures" query:"signatures" validate:"required"`
    uint8_t TxHash[32];         //  `json:"txHash,omitempty" form:"txHash" query:"txHash" validate:"required"`
    uint64_t TransactionType;
    void *Transaction;          //  `json:"transaction,omitempty" form:"transaction" query:"transaction" validate:"required"`
} Envelope_t;
