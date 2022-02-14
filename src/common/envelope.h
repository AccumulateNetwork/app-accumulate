#pragma once

#include <common/encoding.h>
#include <common/ed25519sig.h>

typedef struct Transaction {
    VarInt type;
    Bytes *payload;
    Error (*MarshalBinary)(const struct Transaction* t, struct Marshaler *outData);
    Error (*UnmarshalBinary)(struct Transaction* t, struct Marshaler *inData);
    int (*BinarySize)(const struct Transaction *self);
} Transaction; //encoder

typedef struct Envelope {
    VarInt       _numSignatures;  //stores the number of signatures.
    ED25519Sig  *_signatures;     //`json:"signatures,omitempty" form:"signatures" query:"signatures" validate:"required"`
    Bytes        _txHash;         //  `json:"txHash,omitempty" form:"txHash" query:"txHash" validate:"required"`
    Transaction *_transaction;    //  `json:"transaction,omitempty" form:"transaction" query:"transaction" validate:"required"`
} Envelope; //encoder

typedef Envelope Envelope_fields;

typedef struct {
    uint64_t       _NumSignatures;   // stores the number of signatures to follow
    ED25519Sig_t * _Signatures;      // `json:"signatures,omitempty" form:"signatures" query:"signatures" validate:"required"`
    Bytes32_t      _TxHash;      //  `json:"txHash,omitempty" form:"txHash" query:"txHash" validate:"required"`
    VarInt_t       _TransactionType;
    void *         _Transaction;     //  `json:"transaction,omitempty" form:"transaction" query:"transaction" validate:"required"`
} Envelope_t; //actual type
