#pragma once

#include <common/encoding.h>
#include <common/ed25519sig.h>


typedef struct {
    uint8_t       NumSignatures;//stores the number of signatures.
    ED25519Sig_t *Signatures;   //`json:"signatures,omitempty" form:"signatures" query:"signatures" validate:"required"`
    uint8_t TxHash[32];         //  `json:"txHash,omitempty" form:"txHash" query:"txHash" validate:"required"`
    uint64_t TransactionType;
    void *Transaction;          //  `json:"transaction,omitempty" form:"transaction" query:"transaction" validate:"required"`
}  Envelope;

