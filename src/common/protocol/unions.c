
//#undef _ACCUMULATE_UNION_HEADER_
#include <common/protocol/signatures.h>
#include <common/protocol/transaction.h>
#include <common/protocol/unions.h>

#define _ACCUMULATE_UNION_SOURCE_

//typedef union {
//    SignatureTypeUnion _u;
//    struct BTCSignature _BTCSignature;
//    struct ED25519Signature _ED25519Signature;
//    struct ETHSignature _ETHSignature;
//    struct RCD1Signature _RCD1Signature;
//} Signature_t;
//Signature_t gSignature;
#ifdef _ACCUMULATE_UNION_SOURCE_

//EqualTransactionBody is used to compare the values of the union
bool TransactionBody_equal(const TransactionBody *a, const TransactionBody *b) {
    if (!a || !b) {
        return false;
    }
    if (!a->_u || !b->_u) {
        return false;
    }
    if ( a == b ) {
        return true;
    }

    switch ( a->_u->Type ) {
#if _WANT_AddCredits_
        case TransactionTypeAddCredits:
            return AddCredits_equal(a->_AddCredits, b->_AddCredits);
#endif
#if _WANT_SendTokens_
        case TransactionTypeSendTokens:
            return SendTokens_equal(a->_SendTokens, b->_SendTokens);
#endif
        default:
            return false;
    };
}

#if _WANT_AddCredits_
int newAddCredits(Unmarshaler *m, TransactionBody *v) {
    v->_AddCredits = (AddCredits*)unmarshalerAlloc(m, sizeof(AddCredits));
    CHECK_ERROR_INT(v->_AddCredits)
    return ErrorNone;
}
#endif

#if _WANT_SendTokens_
int newSendTokens(Unmarshaler *m, TransactionBody *v) {
    v->_SendTokens = (SendTokens*)unmarshalerAlloc(m, sizeof(SendTokens));
    PRINTF("allocate SEND TOKENS %p size %d\n", v->_SendTokens, sizeof(SendTokens));
    CHECK_ERROR_INT(v->_SendTokens)
    return ErrorNone;
}
#endif

int unmarshalerReadTransactionBody(Unmarshaler *m, TransactionBody *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    uint64_t field = 0;
    uint64_t type = 0;
    PRINTF("ENTERING READ TRANSACTION BODY\n");
    int b = unmarshalerReadField(m, &field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }

    if ( field != 1 ) {
        return ErrorInvalidField;
    }
    n += b;

        PRINTF("DONE READ FIELD\n");
    b = unmarshalerReadUInt(m, &type);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    n += b;

    PRINTF("READ  TRANSACTION BODY type %d\n", type);
    switch ( type ) {
#if _WANT_AddCredits_
        case TransactionTypeAddCredits:
            b = newAddCredits(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadAddCredits(m, v->_AddCredits);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_SendTokens_
        case TransactionTypeSendTokens:

            PRINTF("Allocate Send Tokens\n");
            b = newSendTokens(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }

            PRINTF("Unmarshal Read Send TOkens\n");
            b = unmarshalerReadSendTokens(m, v->_SendTokens);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
        default:
            n = ErrorNotImplemented;
    };
    return n;
}

int marshalerWriteTransactionBody(Marshaler *m, const TransactionBody *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    switch ( v->_u->Type ) {
#if _WANT_AddCredits_
        case TransactionTypeAddCredits:
            return marshalerWriteAddCredits(m, v->_AddCredits);
#endif
#if _WANT_SendTokens_
        case TransactionTypeSendTokens:
            return marshalerWriteSendTokens(m, v->_SendTokens);
#endif
        default:
            return ErrorNotImplemented;
    };
}




//EqualSignature is used to compare the values of the union
bool Signature_equal(const Signature *a, const Signature *b) {
    if (!a || !b) {
        return false;
    }
    if (!a->_u || !b->_u) {
        return false;
    }
    if ( a == b ) {
        return true;
    }

    switch ( a->_u->Type ) {
#if _WANT_BTCLegacy_
        case SignatureTypeBTCLegacy:
            return BTCLegacySignature_equal(a->_BTCLegacySignature, b->_BTCLegacySignature);
#endif
#if _WANT_BTC_
        case SignatureTypeBTC:
            return BTCSignature_equal(a->_BTCSignature, b->_BTCSignature);
#endif
#if _WANT_Delegated_
        case SignatureTypeDelegated:
            return DelegatedSignature_equal(a->_DelegatedSignature, b->_DelegatedSignature);
#endif
#if _WANT_ED25519_
        case SignatureTypeED25519:
            return ED25519Signature_equal(a->_ED25519Signature, b->_ED25519Signature);
#endif
#if _WANT_ETH_
        case SignatureTypeETH:
            return ETHSignature_equal(a->_ETHSignature, b->_ETHSignature);
#endif
#if _WANT_Internal_
        case SignatureTypeInternal:
            return InternalSignature_equal(a->_InternalSignature, b->_InternalSignature);
#endif
#if _WANT_LegacyED25519_
        case SignatureTypeLegacyED25519:
            return LegacyED25519Signature_equal(a->_LegacyED25519Signature, b->_LegacyED25519Signature);
#endif
#if _WANT_Partition_
        case SignatureTypePartition:
            return PartitionSignature_equal(a->_PartitionSignature, b->_PartitionSignature);
#endif
#if _WANT_RCD1_
        case SignatureTypeRCD1:
            return RCD1Signature_equal(a->_RCD1Signature, b->_RCD1Signature);
#endif
#if _WANT_Receipt_
        case SignatureTypeReceipt:
            return ReceiptSignature_equal(a->_ReceiptSignature, b->_ReceiptSignature);
#endif
#if _WANT_Remote_
        case SignatureTypeRemote:
            return RemoteSignature_equal(a->_RemoteSignature, b->_RemoteSignature);
#endif
#if _WANT_Set_
        case SignatureTypeSet:
            return SignatureSet_equal(a->_SignatureSet, b->_SignatureSet);
#endif
        default:
            return false;
    };
}

#if _WANT_BTCLegacySignature_
int newBTCLegacySignature(Unmarshaler *m, Signature *v) {
    v->_BTCLegacySignature = (BTCLegacySignature*)unmarshalerAlloc(m, sizeof(BTCLegacySignature));
    CHECK_ERROR_INT(v->_BTCLegacySignature)
    return ErrorNone;
}
#endif

#if _WANT_BTCSignature_
int newBTCSignature(Unmarshaler *m, Signature *v) {
    v->_BTCSignature = (BTCSignature*)unmarshalerAlloc(m, sizeof(BTCSignature));
    CHECK_ERROR_INT(v->_BTCSignature)
    return ErrorNone;
}
#endif

#if _WANT_DelegatedSignature_
int newDelegatedSignature(Unmarshaler *m, Signature *v) {
    v->_DelegatedSignature = (DelegatedSignature*)unmarshalerAlloc(m, sizeof(DelegatedSignature));
    CHECK_ERROR_INT(v->_DelegatedSignature)
    return ErrorNone;
}
#endif

#if _WANT_ED25519Signature_
int newED25519Signature(Unmarshaler *m, Signature *v) {
    v->_ED25519Signature = (ED25519Signature*)unmarshalerAlloc(m, sizeof(ED25519Signature));
    CHECK_ERROR_INT(v->_ED25519Signature)
    return ErrorNone;
}
#endif

#if _WANT_ETHSignature_
int newETHSignature(Unmarshaler *m, Signature *v) {
    v->_ETHSignature = (ETHSignature*)unmarshalerAlloc(m, sizeof(ETHSignature));
    CHECK_ERROR_INT(v->_ETHSignature)
    return ErrorNone;
}
#endif

#if _WANT_InternalSignature_
int newInternalSignature(Unmarshaler *m, Signature *v) {
    v->_InternalSignature = (InternalSignature*)unmarshalerAlloc(m, sizeof(InternalSignature));
    CHECK_ERROR_INT(v->_InternalSignature)
    return ErrorNone;
}
#endif

#if _WANT_LegacyED25519Signature_
int newLegacyED25519Signature(Unmarshaler *m, Signature *v) {
    v->_LegacyED25519Signature = (LegacyED25519Signature*)unmarshalerAlloc(m, sizeof(LegacyED25519Signature));
    CHECK_ERROR_INT(v->_LegacyED25519Signature)
    return ErrorNone;
}
#endif

#if _WANT_PartitionSignature_
int newPartitionSignature(Unmarshaler *m, Signature *v) {
    v->_PartitionSignature = (PartitionSignature*)unmarshalerAlloc(m, sizeof(PartitionSignature));
    CHECK_ERROR_INT(v->_PartitionSignature)
    return ErrorNone;
}
#endif

#if _WANT_RCD1Signature_
int newRCD1Signature(Unmarshaler *m, Signature *v) {
    v->_RCD1Signature = (RCD1Signature*)unmarshalerAlloc(m, sizeof(RCD1Signature));
    CHECK_ERROR_INT(v->_RCD1Signature)
    return ErrorNone;
}
#endif

#if _WANT_ReceiptSignature_
int newReceiptSignature(Unmarshaler *m, Signature *v) {
    v->_ReceiptSignature = (ReceiptSignature*)unmarshalerAlloc(m, sizeof(ReceiptSignature));
    CHECK_ERROR_INT(v->_ReceiptSignature)
    return ErrorNone;
}
#endif

#if _WANT_RemoteSignature_
int newRemoteSignature(Unmarshaler *m, Signature *v) {
    v->_RemoteSignature = (RemoteSignature*)unmarshalerAlloc(m, sizeof(RemoteSignature));
    CHECK_ERROR_INT(v->_RemoteSignature)
    return ErrorNone;
}
#endif

#if _WANT_SignatureSet_
int newSignatureSet(Unmarshaler *m, Signature *v) {
    v->_SignatureSet = (SignatureSet*)unmarshalerAlloc(m, sizeof(SignatureSet));
    CHECK_ERROR_INT(v->_SignatureSet)
    return ErrorNone;
}
#endif

int unmarshalerReadSignature(Unmarshaler *m, Signature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)
    int n = 0;
    uint64_t field = 0;
    uint64_t type = 0;

    int b = unmarshalerReadField(m, &field);
    if ( IsError(ErrorCode(b))) {
        return b;
    }

    if ( field != 1 ) {
        return ErrorInvalidField;
    }
    n += b;

    b = unmarshalerReadUInt(m, &type);
    if ( IsError(ErrorCode(b))) {
        return b;
    }
    n += b;
    switch ( type ) {
#if _WANT_BTCLegacySignature_
        case SignatureTypeBTCLegacy:
            b = newBTCLegacySignature(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadBTCLegacySignature(m, v->_BTCLegacySignature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_BTCSignature_
        case SignatureTypeBTC:
//            b = newBTCSignature(m, v);
//            if ( IsError(ErrorCode(b))) {
//                return b;
//            }
            v->_BTCSignature = &gSignature._BTCSignature;
            b = unmarshalerReadBTCSignature(m, v->_BTCSignature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_DelegatedSignature_
        case SignatureTypeDelegated:
            b = newDelegatedSignature(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadDelegatedSignature(m, v->_DelegatedSignature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_ED25519Signature_
        case SignatureTypeED25519:
            b = newED25519Signature(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }

            //v->_ED25519Signature = &gSignature._ED25519Signature;
            b = unmarshalerReadED25519Signature(m, v->_ED25519Signature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_ETHSignature_
        case SignatureTypeETH:
//            b = newETHSignature(m, v);
//            if ( IsError(ErrorCode(b))) {
//                return b;
//            }
//
            v->_ETHSignature = &gSignature._ETHSignature;
            b = unmarshalerReadETHSignature(m, v->_ETHSignature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_InternalSignature_
        case SignatureTypeInternal:
            b = newInternalSignature(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadInternalSignature(m, v->_InternalSignature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_LegacyED25519Signature_
        case SignatureTypeLegacyED25519:
            b = newLegacyED25519Signature(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadLegacyED25519Signature(m, v->_LegacyED25519Signature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_PartitionSignature_
        case SignatureTypePartition:
            b = newPartitionSignature(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadPartitionSignature(m, v->_PartitionSignature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_RCD1Signature_
        case SignatureTypeRCD1:
//            b = newRCD1Signature(m, v);
//            if ( IsError(ErrorCode(b))) {
//                return b;
//            }
            v->_RCD1Signature = &gSignature._RCD1Signature;

            b = unmarshalerReadRCD1Signature(m, v->_RCD1Signature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_ReceiptSignature_
        case SignatureTypeReceipt:
            b = newReceiptSignature(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadReceiptSignature(m, v->_ReceiptSignature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_RemoteSignature_
        case SignatureTypeRemote:
            b = newRemoteSignature(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadRemoteSignature(m, v->_RemoteSignature);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
#if _WANT_SignatureSet_
        case SignatureTypeSet:
            b = newSignatureSet(m, v);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            b = unmarshalerReadSignatureSet(m, v->_SignatureSet);
            if ( IsError(ErrorCode(b))) {
                return b;
            }
            n += b;
            break;
#endif
        default:
            n = ErrorNotImplemented;
    };
    return n;
}

int marshalerWriteSignature(Marshaler *m, const Signature *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    switch ( v->_u->Type ) {
#if _WANT_BTCLegacy_
        case SignatureTypeBTCLegacy:
            return marshalerWriteBTCLegacySignature(m, v->_BTCLegacySignature);
#endif
#if _WANT_BTC_
        case SignatureTypeBTC:
            return marshalerWriteBTCSignature(m, v->_BTCSignature);
#endif
#if _WANT_Delegated_
        case SignatureTypeDelegated:
            return marshalerWriteDelegatedSignature(m, v->_DelegatedSignature);
#endif
#if _WANT_ED25519_
        case SignatureTypeED25519:
            return marshalerWriteED25519Signature(m, v->_ED25519Signature);
#endif
#if _WANT_ETH_
        case SignatureTypeETH:
            return marshalerWriteETHSignature(m, v->_ETHSignature);
#endif
#if _WANT_Internal_
        case SignatureTypeInternal:
            return marshalerWriteInternalSignature(m, v->_InternalSignature);
#endif
#if _WANT_LegacyED25519_
        case SignatureTypeLegacyED25519:
            return marshalerWriteLegacyED25519Signature(m, v->_LegacyED25519Signature);
#endif
#if _WANT_Partition_
        case SignatureTypePartition:
            return marshalerWritePartitionSignature(m, v->_PartitionSignature);
#endif
#if _WANT_RCD1_
        case SignatureTypeRCD1:
            return marshalerWriteRCD1Signature(m, v->_RCD1Signature);
#endif
#if _WANT_Receipt_
        case SignatureTypeReceipt:
            return marshalerWriteReceiptSignature(m, v->_ReceiptSignature);
#endif
#if _WANT_Remote_
        case SignatureTypeRemote:
            return marshalerWriteRemoteSignature(m, v->_RemoteSignature);
#endif
#if _WANT_Set_
        case SignatureTypeSet:
            return marshalerWriteSignatureSet(m, v->_SignatureSet);
#endif
        default:
            return ErrorNotImplemented;
    };
}



#endif /* _ACCUMULATE_UNION_SOURCE_ */
