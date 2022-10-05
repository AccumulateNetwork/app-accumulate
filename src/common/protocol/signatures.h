#pragma once


/// GENERATED BY go run ./tools/cmd/genmarshal. DO NOT EDIT.

#include <common/encoding/encoding.h>
#include <common/protocol/enum.h>
#include <common/protocol/unions.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef ACME_STATIC
#define ACME_API static
#else
#define ACME_API extern
#endif

#define _WANT_BTCLegacySignature_    1
#define _WANT_BTCSignature_    1
#define _WANT_DelegatedSignature_    0
#define _WANT_ED25519Signature_    1
#define _WANT_ETHSignature_    1
#define _WANT_InternalSignature_    1
#define _WANT_LegacyED25519Signature_    1
#define _WANT_PartitionSignature_    1
#define _WANT_RCD1Signature_    1
#define _WANT_ReceiptSignature_    0
#define _WANT_RemoteSignature_    0
#define _WANT_SignatureSet_    0

/// Forward Declarations

struct BTCLegacySignature;

struct BTCSignature;

struct DelegatedSignature;

struct ED25519Signature;

struct ETHSignature;

struct InternalSignature;

struct LegacyED25519Signature;

struct PartitionSignature;

struct RCD1Signature;

struct ReceiptSignature;

struct RemoteSignature;

struct SignatureSet;


/// Data Structures

#if _WANT_BTCLegacySignature_
typedef struct BTCLegacySignature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[8];
	Bytes PublicKey;  //`json:"publicKey,omitempty" form:"publicKey" query:"publicKey" validate:"required"`
	Bytes Signature;  //`json:"signature,omitempty" form:"signature" query:"signature" validate:"required"`
	Url Signer;  //`json:"signer,omitempty" form:"signer" query:"signer" validate:"required"`
	UVarInt SignerVersion;  //`json:"signerVersion,omitempty" form:"signerVersion" query:"signerVersion" validate:"required"`
	UVarInt Timestamp;  //`json:"timestamp,omitempty" form:"timestamp" query:"timestamp"`
	VoteType Vote;  //`json:"vote,omitempty" form:"vote" query:"vote"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
	//Bytes extraData[8];

} BTCLegacySignature;
#endif /* _WANT_BTCLegacySignature_ */

#if _WANT_BTCSignature_
typedef struct BTCSignature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[8];
	Bytes PublicKey;  //`json:"publicKey,omitempty" form:"publicKey" query:"publicKey" validate:"required"`
	Bytes Signature;  //`json:"signature,omitempty" form:"signature" query:"signature" validate:"required"`
	Url Signer;  //`json:"signer,omitempty" form:"signer" query:"signer" validate:"required"`
	UVarInt SignerVersion;  //`json:"signerVersion,omitempty" form:"signerVersion" query:"signerVersion" validate:"required"`
	UVarInt Timestamp;  //`json:"timestamp,omitempty" form:"timestamp" query:"timestamp"`
	VoteType Vote;  //`json:"vote,omitempty" form:"vote" query:"vote"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
	//Bytes extraData[8];

} BTCSignature;
#endif /* _WANT_BTCSignature_ */

#if _WANT_DelegatedSignature_
typedef struct DelegatedSignature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[3];
	Signature Signature;  //`json:"signature,omitempty" form:"signature" query:"signature" validate:"required"`
	/// Delegator is the authority that delegated its authority to the signer.
	Url Delegator;  //`json:"delegator,omitempty" form:"delegator" query:"delegator" validate:"required"`
	//Bytes extraData[3];

} DelegatedSignature;
#endif /* _WANT_DelegatedSignature_ */

#if _WANT_ED25519Signature_
typedef struct ED25519Signature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[8];
	Bytes PublicKey;  //`json:"publicKey,omitempty" form:"publicKey" query:"publicKey" validate:"required"`
	Bytes Signature;  //`json:"signature,omitempty" form:"signature" query:"signature" validate:"required"`
	Url Signer;  //`json:"signer,omitempty" form:"signer" query:"signer" validate:"required"`
	UVarInt SignerVersion;  //`json:"signerVersion,omitempty" form:"signerVersion" query:"signerVersion" validate:"required"`
	UVarInt Timestamp;  //`json:"timestamp,omitempty" form:"timestamp" query:"timestamp"`
	VoteType Vote;  //`json:"vote,omitempty" form:"vote" query:"vote"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
	//Bytes extraData[8];

} ED25519Signature;
#endif /* _WANT_ED25519Signature_ */

#if _WANT_ETHSignature_
typedef struct ETHSignature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[8];
	Bytes PublicKey;  //`json:"publicKey,omitempty" form:"publicKey" query:"publicKey" validate:"required"`
	Bytes Signature;  //`json:"signature,omitempty" form:"signature" query:"signature" validate:"required"`
	Url Signer;  //`json:"signer,omitempty" form:"signer" query:"signer" validate:"required"`
	UVarInt SignerVersion;  //`json:"signerVersion,omitempty" form:"signerVersion" query:"signerVersion" validate:"required"`
	UVarInt Timestamp;  //`json:"timestamp,omitempty" form:"timestamp" query:"timestamp"`
	VoteType Vote;  //`json:"vote,omitempty" form:"vote" query:"vote"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
	//Bytes extraData[8];

} ETHSignature;
#endif /* _WANT_ETHSignature_ */

#if _WANT_InternalSignature_
typedef struct InternalSignature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[3];
	/// Cause is the hash of the transaction that produced the signed transaction.
	Bytes32 Cause;  //`json:"cause,omitempty" form:"cause" query:"cause" validate:"required"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash" validate:"required"`
	//Bytes extraData[3];

} InternalSignature;
#endif /* _WANT_InternalSignature_ */

#if _WANT_LegacyED25519Signature_
typedef struct LegacyED25519Signature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[8];
	UVarInt Timestamp;  //`json:"timestamp,omitempty" form:"timestamp" query:"timestamp" validate:"required"`
	Bytes PublicKey;  //`json:"publicKey,omitempty" form:"publicKey" query:"publicKey" validate:"required"`
	Bytes Signature;  //`json:"signature,omitempty" form:"signature" query:"signature" validate:"required"`
	Url Signer;  //`json:"signer,omitempty" form:"signer" query:"signer" validate:"required"`
	UVarInt SignerVersion;  //`json:"signerVersion,omitempty" form:"signerVersion" query:"signerVersion" validate:"required"`
	VoteType Vote;  //`json:"vote,omitempty" form:"vote" query:"vote"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
	//Bytes extraData[8];

} LegacyED25519Signature;
#endif /* _WANT_LegacyED25519Signature_ */

#if _WANT_PartitionSignature_
typedef struct PartitionSignature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[5];
	/// SourceNetwork is the network that produced the transaction.
	Url SourceNetwork;  //`json:"sourceNetwork,omitempty" form:"sourceNetwork" query:"sourceNetwork" validate:"required"`
	/// DestinationNetwork is the network that the transaction is sent to.
	Url DestinationNetwork;  //`json:"destinationNetwork,omitempty" form:"destinationNetwork" query:"destinationNetwork" validate:"required"`
	/// SequenceNumber is the sequence number of the transaction.
	UVarInt SequenceNumber;  //`json:"sequenceNumber,omitempty" form:"sequenceNumber" query:"sequenceNumber" validate:"required"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
	//Bytes extraData[5];

} PartitionSignature;
#endif /* _WANT_PartitionSignature_ */

#if _WANT_RCD1Signature_
typedef struct RCD1Signature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[8];
	Bytes PublicKey;  //`json:"publicKey,omitempty" form:"publicKey" query:"publicKey" validate:"required"`
	Bytes Signature;  //`json:"signature,omitempty" form:"signature" query:"signature" validate:"required"`
	Url Signer;  //`json:"signer,omitempty" form:"signer" query:"signer" validate:"required"`
	UVarInt SignerVersion;  //`json:"signerVersion,omitempty" form:"signerVersion" query:"signerVersion" validate:"required"`
	UVarInt Timestamp;  //`json:"timestamp,omitempty" form:"timestamp" query:"timestamp"`
	VoteType Vote;  //`json:"vote,omitempty" form:"vote" query:"vote"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
	//Bytes extraData[8];

} RCD1Signature;
#endif /* _WANT_RCD1Signature_ */

#if _WANT_ReceiptSignature_
typedef struct ReceiptSignature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[4];
	/// SourceNetwork is the network that produced the transaction.
	Url SourceNetwork;  //`json:"sourceNetwork,omitempty" form:"sourceNetwork" query:"sourceNetwork" validate:"required"`
	Receipt Proof;  //`json:"proof,omitempty" form:"proof" query:"proof" validate:"required"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
	//Bytes extraData[4];

} ReceiptSignature;
#endif /* _WANT_ReceiptSignature_ */

#if _WANT_RemoteSignature_
typedef struct RemoteSignature {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[3];
	Url Destination;  //`json:"destination,omitempty" form:"destination" query:"destination" validate:"required"`
	Signature Signature;  //`json:"signature,omitempty" form:"signature" query:"signature" validate:"required"`
	//Bytes extraData[3];

} RemoteSignature;
#endif /* _WANT_RemoteSignature_ */

#if _WANT_SignatureSet_
typedef struct SignatureSet {
    
    SignatureType Type;
    
    //

	//uint8_t fieldsSet[5];
	VoteType Vote;  //`json:"vote,omitempty" form:"vote" query:"vote"`
	Url Signer;  //`json:"signer,omitempty" form:"signer" query:"signer" validate:"required"`
	Bytes32 TransactionHash;  //`json:"transactionHash,omitempty" form:"transactionHash" query:"transactionHash"`
    size_t Signatures_length;
	Signature* Signatures;  //`json:"signatures,omitempty" form:"signatures" query:"signatures" validate:"required"`
	//Bytes extraData[5];

} SignatureSet;
#endif /* _WANT_SignatureSet_ */





#if _WANT_BTCLegacySignature_
ACME_API SignatureType BTCLegacy_type(void);
ACME_API bool BTCLegacySignature_equal(const BTCLegacySignature *v, const BTCLegacySignature *u);
ACME_API int unmarshalerReadBTCLegacySignature(Unmarshaler *m, BTCLegacySignature *v);
ACME_API int marshalerWriteBTCLegacySignature(Marshaler *m, const BTCLegacySignature*v);
ACME_API int BTCLegacySignature_binarySize(const BTCLegacySignature *v);

#endif /* _WANT_BTCLegacySignature_ */

#if _WANT_BTCSignature_
ACME_API SignatureType BTC_type(void);
ACME_API bool BTCSignature_equal(const BTCSignature *v, const BTCSignature *u);
ACME_API int unmarshalerReadBTCSignature(Unmarshaler *m, BTCSignature *v);
ACME_API int marshalerWriteBTCSignature(Marshaler *m, const BTCSignature*v);
ACME_API int BTCSignature_binarySize(const BTCSignature *v);

#endif /* _WANT_BTCSignature_ */

#if _WANT_DelegatedSignature_
ACME_API SignatureType Delegated_type(void);
ACME_API bool DelegatedSignature_equal(const DelegatedSignature *v, const DelegatedSignature *u);
ACME_API int unmarshalerReadDelegatedSignature(Unmarshaler *m, DelegatedSignature *v);
ACME_API int marshalerWriteDelegatedSignature(Marshaler *m, const DelegatedSignature*v);
ACME_API int DelegatedSignature_binarySize(const DelegatedSignature *v);

#endif /* _WANT_DelegatedSignature_ */

#if _WANT_ED25519Signature_
ACME_API SignatureType ED25519_type(void);
ACME_API bool ED25519Signature_equal(const ED25519Signature *v, const ED25519Signature *u);
ACME_API int unmarshalerReadED25519Signature(Unmarshaler *m, ED25519Signature *v);
ACME_API int marshalerWriteED25519Signature(Marshaler *m, const ED25519Signature*v);
ACME_API int ED25519Signature_binarySize(const ED25519Signature *v);

#endif /* _WANT_ED25519Signature_ */

#if _WANT_ETHSignature_
ACME_API SignatureType ETH_type(void);
ACME_API bool ETHSignature_equal(const ETHSignature *v, const ETHSignature *u);
ACME_API int unmarshalerReadETHSignature(Unmarshaler *m, ETHSignature *v);
ACME_API int marshalerWriteETHSignature(Marshaler *m, const ETHSignature*v);
ACME_API int ETHSignature_binarySize(const ETHSignature *v);

#endif /* _WANT_ETHSignature_ */

#if _WANT_InternalSignature_
ACME_API SignatureType Internal_type(void);
ACME_API bool InternalSignature_equal(const InternalSignature *v, const InternalSignature *u);
ACME_API int unmarshalerReadInternalSignature(Unmarshaler *m, InternalSignature *v);
ACME_API int marshalerWriteInternalSignature(Marshaler *m, const InternalSignature*v);
ACME_API int InternalSignature_binarySize(const InternalSignature *v);

#endif /* _WANT_InternalSignature_ */

#if _WANT_LegacyED25519Signature_
ACME_API SignatureType LegacyED25519_type(void);
ACME_API bool LegacyED25519Signature_equal(const LegacyED25519Signature *v, const LegacyED25519Signature *u);
ACME_API int unmarshalerReadLegacyED25519Signature(Unmarshaler *m, LegacyED25519Signature *v);
ACME_API int marshalerWriteLegacyED25519Signature(Marshaler *m, const LegacyED25519Signature*v);
ACME_API int LegacyED25519Signature_binarySize(const LegacyED25519Signature *v);

#endif /* _WANT_LegacyED25519Signature_ */

#if _WANT_PartitionSignature_
ACME_API SignatureType Partition_type(void);
ACME_API bool PartitionSignature_equal(const PartitionSignature *v, const PartitionSignature *u);
ACME_API int unmarshalerReadPartitionSignature(Unmarshaler *m, PartitionSignature *v);
ACME_API int marshalerWritePartitionSignature(Marshaler *m, const PartitionSignature*v);
ACME_API int PartitionSignature_binarySize(const PartitionSignature *v);

#endif /* _WANT_PartitionSignature_ */

#if _WANT_RCD1Signature_
ACME_API SignatureType RCD1_type(void);
ACME_API bool RCD1Signature_equal(const RCD1Signature *v, const RCD1Signature *u);
ACME_API int unmarshalerReadRCD1Signature(Unmarshaler *m, RCD1Signature *v);
ACME_API int marshalerWriteRCD1Signature(Marshaler *m, const RCD1Signature*v);
ACME_API int RCD1Signature_binarySize(const RCD1Signature *v);

#endif /* _WANT_RCD1Signature_ */

#if _WANT_ReceiptSignature_
ACME_API SignatureType Receipt_type(void);
ACME_API bool ReceiptSignature_equal(const ReceiptSignature *v, const ReceiptSignature *u);
ACME_API int unmarshalerReadReceiptSignature(Unmarshaler *m, ReceiptSignature *v);
ACME_API int marshalerWriteReceiptSignature(Marshaler *m, const ReceiptSignature*v);
ACME_API int ReceiptSignature_binarySize(const ReceiptSignature *v);

#endif /* _WANT_ReceiptSignature_ */

#if _WANT_RemoteSignature_
ACME_API SignatureType Remote_type(void);
ACME_API bool RemoteSignature_equal(const RemoteSignature *v, const RemoteSignature *u);
ACME_API int unmarshalerReadRemoteSignature(Unmarshaler *m, RemoteSignature *v);
ACME_API int marshalerWriteRemoteSignature(Marshaler *m, const RemoteSignature*v);
ACME_API int RemoteSignature_binarySize(const RemoteSignature *v);

#endif /* _WANT_RemoteSignature_ */

#if _WANT_SignatureSet_
ACME_API SignatureType Set_type(void);
ACME_API bool SignatureSet_equal(const SignatureSet *v, const SignatureSet *u);
ACME_API int unmarshalerReadSignatureSet(Unmarshaler *m, SignatureSet *v);
ACME_API int marshalerWriteSignatureSet(Marshaler *m, const SignatureSet*v);
ACME_API int SignatureSet_binarySize(const SignatureSet *v);

#endif /* _WANT_SignatureSet_ */


#ifdef __cplusplus
}
#endif


