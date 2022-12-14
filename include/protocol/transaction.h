#pragma once

/// GENERATED BY go run ./tools/cmd/genmarshal. DO NOT EDIT.

#include <encoding/encoding.h>
#include <protocol/enum.h>
#include <protocol/unions.h>
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ACME_STATIC
#define ACME_API static
#else
#define ACME_API extern
#endif

#define _WANT_AddCredits_        1
#define _WANT_Envelope_          1
#define _WANT_SendTokens_        1
#define _WANT_TokenRecipient_    1
#define _WANT_Transaction_       1
#define _WANT_TransactionHeader_ 1
#define _WANT_TransactionStatus_ 0

/// Forward Declarations

struct AddCredits;

struct Envelope;

struct SendTokens;

struct TokenRecipient;

struct Transaction;

struct TransactionHeader;

struct TransactionStatus;

/// Data Structures

#if _WANT_AddCredits_
typedef struct AddCredits {
    TransactionType Type;

    //

    // bool fieldsSet[4];
    Url Recipient;   //`json:"recipient,omitempty" form:"recipient" query:"recipient"
                     // validate:"required"`
    BigInt Amount;   //`json:"amount,omitempty" form:"amount" query:"amount" validate:"required"`
    UVarInt Oracle;  //`json:"oracle,omitempty" form:"oracle" query:"oracle"`
    Bytes extraData[4];

} AddCredits;
#endif /* _WANT_AddCredits_ */

#if _WANT_TokenRecipient_
typedef struct TokenRecipient {
    //

    // bool fieldsSet[2];
    Url Url;        //`json:"url,omitempty" form:"url" query:"url" validate:"required"`
    BigInt Amount;  //`json:"amount,omitempty" form:"amount" query:"amount" validate:"required"`
    Bytes extraData[2];

} TokenRecipient;
#endif /* _WANT_TokenRecipient_ */

#if _WANT_SendTokens_
typedef struct SendTokens {
    TransactionType Type;

    //

    // bool fieldsSet[4];
    Bytes32 Hash;  //`json:"hash,omitempty" form:"hash" query:"hash"`
    RawJson Meta;  //`json:"meta,omitempty" form:"meta" query:"meta"`
    size_t To_length;
    TokenRecipient *To;  //`json:"to,omitempty" form:"to" query:"to" validate:"required"`
    Bytes extraData[4];

} SendTokens;
#endif /* _WANT_SendTokens_ */

#if _WANT_TransactionHeader_
typedef struct TransactionHeader {
    //

    // uint8_t fieldsSet[4];
    Url Principal;      //`json:"principal,omitempty" form:"principal" query:"principal"
                        // validate:"required"`
    Bytes32 Initiator;  //`json:"initiator,omitempty" form:"initiator" query:"initiator"
                        // validate:"required"`
    String Memo;        //`json:"memo,omitempty" form:"memo" query:"memo"`
    Bytes Metadata;     //`json:"metadata,omitempty" form:"metadata" query:"metadata"`
    Bytes extraData[4];

} TransactionHeader;
#endif /* _WANT_TransactionHeader_ */

#if _WANT_Transaction_
typedef struct Transaction {
    //

    // uint8_t fieldsSet[3];
    TransactionHeader
        Header;  //`json:"header,omitempty" form:"header" query:"header" validate:"required"`
    TransactionBody Body;  //`json:"body,omitempty" form:"body" query:"body" validate:"required"`
    Bytes hash;
    Bytes extraData[3];
} Transaction;
#endif /* _WANT_Transaction_ */

#if _WANT_Envelope_
typedef struct Envelope {
    //

    // uint8_t fieldsSet[3];
    size_t Signatures_length;
    Signature *Signatures;  //`json:"signatures,omitempty" form:"signatures" query:"signatures"
                            // validate:"required"`
    Bytes TxHash;           //`json:"txHash,omitempty" form:"txHash" query:"txHash"`
    size_t Transaction_length;
    Transaction
        *Transaction;  //`json:"transaction,omitempty" form:"transaction" query:"transaction"`
    Bytes extraData[3];

} Envelope;
#endif /* _WANT_Envelope_ */

#if _WANT_TransactionStatus_
typedef struct TransactionStatus {
    //

    // uint8_t fieldsSet[18];
    Bytes32 TxID;  //`json:"txID,omitempty" form:"txID" query:"txID" validate:"required"`
    Status Code;   //`json:"code,omitempty" form:"code" query:"code" validate:"required"`
    Error Error;   //`json:"error,omitempty" form:"error" query:"error" validate:"required"`
    TransactionResult
        Result;  //`json:"result,omitempty" form:"result" query:"result" validate:"required"`
    /// Received is the block when the transaction was first received.
    UVarInt Received;  //`json:"received,omitempty" form:"received" query:"received"
                       // validate:"required"`
    /// Initiator is the signer that initiated the transaction.
    Url Initiator;  //`json:"initiator,omitempty" form:"initiator" query:"initiator"
                    // validate:"required"`
                    /// Signers lists accounts that have signed the transaction.
    size_t Signers_length;
    Signer
        *Signers;  //`json:"signers,omitempty" form:"signers" query:"signers" validate:"required"`
                   /// AnchorSigners is the list of validators that have signed the anchor.
    size_t AnchorSigners_length;
    Bytes *AnchorSigners;  //`json:"anchorSigners,omitempty" form:"anchorSigners"
                           // query:"anchorSigners" validate:"required"`
    /// SourceNetwork is the network that produced the transaction.
    Url SourceNetwork;  //`json:"sourceNetwork,omitempty" form:"sourceNetwork" query:"sourceNetwork"
                        // validate:"required"`
    /// DestinationNetwork is the network that the transaction is sent to.
    Url DestinationNetwork;  //`json:"destinationNetwork,omitempty" form:"destinationNetwork"
                             // query:"destinationNetwork" validate:"required"`
    /// SequenceNumber is the sequence number of the transaction.
    UVarInt SequenceNumber;  //`json:"sequenceNumber,omitempty" form:"sequenceNumber"
                             // query:"sequenceNumber" validate:"required"`
    /// GotDirectoryReceipt indicates if a receipt has been received from the DN.
    Bool GotDirectoryReceipt;  //`json:"gotDirectoryReceipt,omitempty" form:"gotDirectoryReceipt"
                               // query:"gotDirectoryReceipt" validate:"required"`
    /// Proof is the proof of the transaction.
    Receipt Proof;  //`json:"proof,omitempty" form:"proof" query:"proof" validate:"required"`
                    // Bytes extraData[18];

} TransactionStatus;
#endif /* _WANT_TransactionStatus_ */

#if _WANT_AddCredits_
ACME_API TransactionType AddCredits_type(void);
ACME_API bool AddCredits_equal(const AddCredits *v, const AddCredits *u);
ACME_API int unmarshalerReadAddCredits(Unmarshaler *m, AddCredits *v);
ACME_API int marshalerWriteAddCredits(Marshaler *m, const AddCredits *v);
ACME_API int AddCredits_binarySize(const AddCredits *v);

#endif /* _WANT_AddCredits_ */

#if _WANT_Envelope_

ACME_API bool Envelope_equal(const Envelope *v, const Envelope *u);
ACME_API int unmarshalerReadEnvelope(Unmarshaler *m, Envelope *v);
ACME_API int marshalerWriteEnvelope(Marshaler *m, const Envelope *v);
ACME_API int Envelope_binarySize(const Envelope *v);

#endif /* _WANT_Envelope_ */

#if _WANT_SendTokens_
ACME_API TransactionType SendTokens_type(void);
ACME_API bool SendTokens_equal(const SendTokens *v, const SendTokens *u);
ACME_API int unmarshalerReadSendTokens(Unmarshaler *m, SendTokens *v);
ACME_API int marshalerWriteSendTokens(Marshaler *m, const SendTokens *v);
ACME_API int SendTokens_binarySize(const SendTokens *v);

#endif /* _WANT_SendTokens_ */

#if _WANT_TokenRecipient_

ACME_API bool TokenRecipient_equal(const TokenRecipient *v, const TokenRecipient *u);
ACME_API int unmarshalerReadTokenRecipient(Unmarshaler *m, TokenRecipient *v);
ACME_API int marshalerWriteTokenRecipient(Marshaler *m, const TokenRecipient *v);
ACME_API int TokenRecipient_binarySize(const TokenRecipient *v);

#endif /* _WANT_TokenRecipient_ */

#if _WANT_Transaction_

ACME_API bool Transaction_equal(const Transaction *v, const Transaction *u);
ACME_API int unmarshalerReadTransaction(volatile Unmarshaler *m, Transaction *v);
ACME_API int marshalerWriteTransaction(Marshaler *m, const Transaction *v);
ACME_API int Transaction_binarySize(const Transaction *v);

#endif /* _WANT_Transaction_ */

#if _WANT_TransactionHeader_

ACME_API bool TransactionHeader_equal(const TransactionHeader *v, const TransactionHeader *u);
ACME_API int unmarshalerReadTransactionHeader(Unmarshaler *m, TransactionHeader *v);
ACME_API int marshalerWriteTransactionHeader(Marshaler *m, const TransactionHeader *v);
ACME_API int TransactionHeader_binarySize(const TransactionHeader *v);

#endif /* _WANT_TransactionHeader_ */

#if _WANT_TransactionStatus_

ACME_API bool TransactionStatus_equal(const TransactionStatus *v, const TransactionStatus *u);
ACME_API int unmarshalerReadTransactionStatus(Unmarshaler *m, TransactionStatus *v);
ACME_API int marshalerWriteTransactionStatus(Marshaler *m, const TransactionStatus *v);
ACME_API int TransactionStatus_binarySize(const TransactionStatus *v);

#endif /* _WANT_TransactionStatus_ */

#ifdef __cplusplus
}
#endif
