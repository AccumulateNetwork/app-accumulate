#pragma once

// GENERATED BY go run ./tools/cmd/gen-types. DO NOT EDIT.
#include <common/protocol/enum.h>
#include <common/encoding/encoding.h>
#include <common/encoding/marshaler.h>

typedef struct {
        TransactionType Type;
        Bytes data;
} TransactionTypeUnion;

typedef union {
        TransactionTypeUnion *_u;
        struct AcmeFaucet *_AcmeFaucet;
        struct AddCredits *_AddCredits;
        struct BurnTokens *_BurnTokens;
        struct CreateDataAccount *_CreateDataAccount;
        struct CreateIdentity *_CreateIdentity;
        struct CreateKeyBook *_CreateKeyBook;
        struct CreateKeyPage *_CreateKeyPage;
        struct CreateLiteTokenAccount *_CreateLiteTokenAccount;
        struct CreateToken *_CreateToken;
        struct CreateTokenAccount *_CreateTokenAccount;
        struct IssueTokens *_IssueTokens;
        struct LockAccount *_LockAccount;
        struct RemoteTransaction *_RemoteTransaction;
        struct SendTokens *_SendTokens;
        struct UpdateAccountAuth *_UpdateAccountAuth;
        struct UpdateKey *_UpdateKey;
        struct UpdateKeyPage *_UpdateKeyPage;
        struct WriteData *_WriteData;
        struct WriteDataTo *_WriteDataTo;
} TransactionBody;


typedef struct {
        KeyPageOperationType Type;
        Bytes data;
} KeyPageOperationTypeUnion;

typedef union {
        KeyPageOperationTypeUnion *_u;
        struct AddKeyOperation *_AddKeyOperation;
        struct RemoveKeyOperation *_RemoveKeyOperation;
        struct SetThresholdKeyPageOperation *_SetThresholdKeyPageOperation;
        struct UpdateAllowedKeyPageOperation *_UpdateAllowedKeyPageOperation;
        struct UpdateKeyOperation *_UpdateKeyOperation;
} KeyPageOperation;


typedef struct {
        SignatureType Type;
        Bytes data;
} SignatureTypeUnion;

typedef union {
        SignatureTypeUnion *_u;
        struct BTCLegacySignature *_BTCLegacySignature;
        struct BTCSignature *_BTCSignature;
        struct DelegatedSignature *_DelegatedSignature;
        struct ED25519Signature *_ED25519Signature;
        struct ETHSignature *_ETHSignature;
        struct InternalSignature *_InternalSignature;
        struct LegacyED25519Signature *_LegacyED25519Signature;
        struct PartitionSignature *_PartitionSignature;
        struct RCD1Signature *_RCD1Signature;
        struct ReceiptSignature *_ReceiptSignature;
        struct RemoteSignature *_RemoteSignature;
        struct SignatureSet *_SignatureSet;
} Signature;

bool TransactionBody_equal(const TransactionBody *a,const TransactionBody *b);
//bool TransactionType_equal(const TransactionType *a, const TransactionType *b);

int unmarshalerReadTransactionBody(Unmarshaler *m, TransactionBody *v);
int marshalerWriteTransactionBody(Marshaler *m, const TransactionBody *v);


bool KeyPageOperation_equal(const KeyPageOperation *a,const KeyPageOperation *b);
//bool KeyPageOperationType_equal(const KeyPageOperationType *a, const KeyPageOperationType *b);

int unmarshalerReadKeyPageOperation(Unmarshaler *m, KeyPageOperation *v);
int marshalerWriteKeyPageOperation(Marshaler *m, const KeyPageOperation *v);


bool Signature_equal(const Signature *a,const Signature *b);
//bool SignatureType_equal(const SignatureType *a, const SignatureType *b);

int unmarshalerReadSignature(Unmarshaler *m, Signature *v);
int marshalerWriteSignature(Marshaler *m, const Signature *v);




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
	#if _WANT_AcmeFaucet_
    case TransactionTypeAcmeFaucet:
        return AcmeFaucet_equal(a->_AcmeFaucet, b->_AcmeFaucet);
	#endif
	#if _WANT_AddCredits_
    case TransactionTypeAddCredits:
        return AddCredits_equal(a->_AddCredits, b->_AddCredits);
	#endif
	#if _WANT_BurnTokens_
    case TransactionTypeBurnTokens:
        return BurnTokens_equal(a->_BurnTokens, b->_BurnTokens);
	#endif
	#if _WANT_CreateDataAccount_
    case TransactionTypeCreateDataAccount:
        return CreateDataAccount_equal(a->_CreateDataAccount, b->_CreateDataAccount);
	#endif
	#if _WANT_CreateIdentity_
    case TransactionTypeCreateIdentity:
        return CreateIdentity_equal(a->_CreateIdentity, b->_CreateIdentity);
	#endif
	#if _WANT_CreateKeyBook_
    case TransactionTypeCreateKeyBook:
        return CreateKeyBook_equal(a->_CreateKeyBook, b->_CreateKeyBook);
	#endif
	#if _WANT_CreateKeyPage_
    case TransactionTypeCreateKeyPage:
        return CreateKeyPage_equal(a->_CreateKeyPage, b->_CreateKeyPage);
	#endif
	#if _WANT_CreateLiteTokenAccount_
    case TransactionTypeCreateLiteTokenAccount:
        return CreateLiteTokenAccount_equal(a->_CreateLiteTokenAccount, b->_CreateLiteTokenAccount);
	#endif
	#if _WANT_CreateToken_
    case TransactionTypeCreateToken:
        return CreateToken_equal(a->_CreateToken, b->_CreateToken);
	#endif
	#if _WANT_CreateTokenAccount_
    case TransactionTypeCreateTokenAccount:
        return CreateTokenAccount_equal(a->_CreateTokenAccount, b->_CreateTokenAccount);
	#endif
	#if _WANT_IssueTokens_
    case TransactionTypeIssueTokens:
        return IssueTokens_equal(a->_IssueTokens, b->_IssueTokens);
	#endif
	#if _WANT_LockAccount_
    case TransactionTypeLockAccount:
        return LockAccount_equal(a->_LockAccount, b->_LockAccount);
	#endif
	#if _WANT_Remote_
    case TransactionTypeRemote:
        return RemoteTransaction_equal(a->_RemoteTransaction, b->_RemoteTransaction);
	#endif
	#if _WANT_SendTokens_
    case TransactionTypeSendTokens:
        return SendTokens_equal(a->_SendTokens, b->_SendTokens);
	#endif
	#if _WANT_UpdateAccountAuth_
    case TransactionTypeUpdateAccountAuth:
        return UpdateAccountAuth_equal(a->_UpdateAccountAuth, b->_UpdateAccountAuth);
	#endif
	#if _WANT_UpdateKey_
    case TransactionTypeUpdateKey:
        return UpdateKey_equal(a->_UpdateKey, b->_UpdateKey);
	#endif
	#if _WANT_UpdateKeyPage_
    case TransactionTypeUpdateKeyPage:
        return UpdateKeyPage_equal(a->_UpdateKeyPage, b->_UpdateKeyPage);
	#endif
	#if _WANT_WriteData_
    case TransactionTypeWriteData:
        return WriteData_equal(a->_WriteData, b->_WriteData);
	#endif
	#if _WANT_WriteDataTo_
    case TransactionTypeWriteDataTo:
        return WriteDataTo_equal(a->_WriteDataTo, b->_WriteDataTo);
	#endif
    default:
        return false;
    };
}

#if _WANT_AcmeFaucet_
int newAcmeFaucet(Unmarshaler *m, TransactionBody *v) {
    v->_AcmeFaucet = (AcmeFaucet*)unmarshalerAlloc(m, sizeof(AcmeFaucet));
    CHECK_ERROR_INT(v->_AcmeFaucet)
    return ErrorNone;
}
#endif

#if _WANT_AddCredits_
int newAddCredits(Unmarshaler *m, TransactionBody *v) {
    v->_AddCredits = (AddCredits*)unmarshalerAlloc(m, sizeof(AddCredits));
    CHECK_ERROR_INT(v->_AddCredits)
    return ErrorNone;
}
#endif

#if _WANT_BurnTokens_
int newBurnTokens(Unmarshaler *m, TransactionBody *v) {
    v->_BurnTokens = (BurnTokens*)unmarshalerAlloc(m, sizeof(BurnTokens));
    CHECK_ERROR_INT(v->_BurnTokens)
    return ErrorNone;
}
#endif

#if _WANT_CreateDataAccount_
int newCreateDataAccount(Unmarshaler *m, TransactionBody *v) {
    v->_CreateDataAccount = (CreateDataAccount*)unmarshalerAlloc(m, sizeof(CreateDataAccount));
    CHECK_ERROR_INT(v->_CreateDataAccount)
    return ErrorNone;
}
#endif

#if _WANT_CreateIdentity_
int newCreateIdentity(Unmarshaler *m, TransactionBody *v) {
    v->_CreateIdentity = (CreateIdentity*)unmarshalerAlloc(m, sizeof(CreateIdentity));
    CHECK_ERROR_INT(v->_CreateIdentity)
    return ErrorNone;
}
#endif

#if _WANT_CreateKeyBook_
int newCreateKeyBook(Unmarshaler *m, TransactionBody *v) {
    v->_CreateKeyBook = (CreateKeyBook*)unmarshalerAlloc(m, sizeof(CreateKeyBook));
    CHECK_ERROR_INT(v->_CreateKeyBook)
    return ErrorNone;
}
#endif

#if _WANT_CreateKeyPage_
int newCreateKeyPage(Unmarshaler *m, TransactionBody *v) {
    v->_CreateKeyPage = (CreateKeyPage*)unmarshalerAlloc(m, sizeof(CreateKeyPage));
    CHECK_ERROR_INT(v->_CreateKeyPage)
    return ErrorNone;
}
#endif

#if _WANT_CreateLiteTokenAccount_
int newCreateLiteTokenAccount(Unmarshaler *m, TransactionBody *v) {
    v->_CreateLiteTokenAccount = (CreateLiteTokenAccount*)unmarshalerAlloc(m, sizeof(CreateLiteTokenAccount));
    CHECK_ERROR_INT(v->_CreateLiteTokenAccount)
    return ErrorNone;
}
#endif

#if _WANT_CreateToken_
int newCreateToken(Unmarshaler *m, TransactionBody *v) {
    v->_CreateToken = (CreateToken*)unmarshalerAlloc(m, sizeof(CreateToken));
    CHECK_ERROR_INT(v->_CreateToken)
    return ErrorNone;
}
#endif

#if _WANT_CreateTokenAccount_
int newCreateTokenAccount(Unmarshaler *m, TransactionBody *v) {
    v->_CreateTokenAccount = (CreateTokenAccount*)unmarshalerAlloc(m, sizeof(CreateTokenAccount));
    CHECK_ERROR_INT(v->_CreateTokenAccount)
    return ErrorNone;
}
#endif

#if _WANT_IssueTokens_
int newIssueTokens(Unmarshaler *m, TransactionBody *v) {
    v->_IssueTokens = (IssueTokens*)unmarshalerAlloc(m, sizeof(IssueTokens));
    CHECK_ERROR_INT(v->_IssueTokens)
    return ErrorNone;
}
#endif

#if _WANT_LockAccount_
int newLockAccount(Unmarshaler *m, TransactionBody *v) {
    v->_LockAccount = (LockAccount*)unmarshalerAlloc(m, sizeof(LockAccount));
    CHECK_ERROR_INT(v->_LockAccount)
    return ErrorNone;
}
#endif

#if _WANT_RemoteTransaction_
int newRemoteTransaction(Unmarshaler *m, TransactionBody *v) {
    v->_RemoteTransaction = (RemoteTransaction*)unmarshalerAlloc(m, sizeof(RemoteTransaction));
    CHECK_ERROR_INT(v->_RemoteTransaction)
    return ErrorNone;
}
#endif

#if _WANT_SendTokens_
int newSendTokens(Unmarshaler *m, TransactionBody *v) {
    v->_SendTokens = (SendTokens*)unmarshalerAlloc(m, sizeof(SendTokens));
    CHECK_ERROR_INT(v->_SendTokens)
    return ErrorNone;
}
#endif

#if _WANT_UpdateAccountAuth_
int newUpdateAccountAuth(Unmarshaler *m, TransactionBody *v) {
    v->_UpdateAccountAuth = (UpdateAccountAuth*)unmarshalerAlloc(m, sizeof(UpdateAccountAuth));
    CHECK_ERROR_INT(v->_UpdateAccountAuth)
    return ErrorNone;
}
#endif

#if _WANT_UpdateKey_
int newUpdateKey(Unmarshaler *m, TransactionBody *v) {
    v->_UpdateKey = (UpdateKey*)unmarshalerAlloc(m, sizeof(UpdateKey));
    CHECK_ERROR_INT(v->_UpdateKey)
    return ErrorNone;
}
#endif

#if _WANT_UpdateKeyPage_
int newUpdateKeyPage(Unmarshaler *m, TransactionBody *v) {
    v->_UpdateKeyPage = (UpdateKeyPage*)unmarshalerAlloc(m, sizeof(UpdateKeyPage));
    CHECK_ERROR_INT(v->_UpdateKeyPage)
    return ErrorNone;
}
#endif

#if _WANT_WriteData_
int newWriteData(Unmarshaler *m, TransactionBody *v) {
    v->_WriteData = (WriteData*)unmarshalerAlloc(m, sizeof(WriteData));
    CHECK_ERROR_INT(v->_WriteData)
    return ErrorNone;
}
#endif

#if _WANT_WriteDataTo_
int newWriteDataTo(Unmarshaler *m, TransactionBody *v) {
    v->_WriteDataTo = (WriteDataTo*)unmarshalerAlloc(m, sizeof(WriteDataTo));
    CHECK_ERROR_INT(v->_WriteDataTo)
    return ErrorNone;
}
#endif

int unmarshalerReadTransactionBody(Unmarshaler *m, TransactionBody *v) {
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
	#if _WANT_AcmeFaucet_
    case TransactionTypeAcmeFaucet:
        b = newAcmeFaucet(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadAcmeFaucet(m, v->_AcmeFaucet);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
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
	#if _WANT_BurnTokens_
    case TransactionTypeBurnTokens:
        b = newBurnTokens(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadBurnTokens(m, v->_BurnTokens);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_CreateDataAccount_
    case TransactionTypeCreateDataAccount:
        b = newCreateDataAccount(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadCreateDataAccount(m, v->_CreateDataAccount);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_CreateIdentity_
    case TransactionTypeCreateIdentity:
        b = newCreateIdentity(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadCreateIdentity(m, v->_CreateIdentity);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_CreateKeyBook_
    case TransactionTypeCreateKeyBook:
        b = newCreateKeyBook(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadCreateKeyBook(m, v->_CreateKeyBook);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_CreateKeyPage_
    case TransactionTypeCreateKeyPage:
        b = newCreateKeyPage(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadCreateKeyPage(m, v->_CreateKeyPage);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_CreateLiteTokenAccount_
    case TransactionTypeCreateLiteTokenAccount:
        b = newCreateLiteTokenAccount(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadCreateLiteTokenAccount(m, v->_CreateLiteTokenAccount);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_CreateToken_
    case TransactionTypeCreateToken:
        b = newCreateToken(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadCreateToken(m, v->_CreateToken);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_CreateTokenAccount_
    case TransactionTypeCreateTokenAccount:
        b = newCreateTokenAccount(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadCreateTokenAccount(m, v->_CreateTokenAccount);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_IssueTokens_
    case TransactionTypeIssueTokens:
        b = newIssueTokens(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadIssueTokens(m, v->_IssueTokens);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_LockAccount_
    case TransactionTypeLockAccount:
        b = newLockAccount(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadLockAccount(m, v->_LockAccount);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_RemoteTransaction_
    case TransactionTypeRemote:
        b = newRemoteTransaction(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadRemoteTransaction(m, v->_RemoteTransaction);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_SendTokens_
    case TransactionTypeSendTokens:
        b = newSendTokens(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadSendTokens(m, v->_SendTokens);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_UpdateAccountAuth_
    case TransactionTypeUpdateAccountAuth:
        b = newUpdateAccountAuth(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadUpdateAccountAuth(m, v->_UpdateAccountAuth);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_UpdateKey_
    case TransactionTypeUpdateKey:
        b = newUpdateKey(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadUpdateKey(m, v->_UpdateKey);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_UpdateKeyPage_
    case TransactionTypeUpdateKeyPage:
        b = newUpdateKeyPage(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadUpdateKeyPage(m, v->_UpdateKeyPage);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_WriteData_
    case TransactionTypeWriteData:
        b = newWriteData(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadWriteData(m, v->_WriteData);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_WriteDataTo_
    case TransactionTypeWriteDataTo:
        b = newWriteDataTo(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadWriteDataTo(m, v->_WriteDataTo);
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
	#if _WANT_AcmeFaucet_
    case TransactionTypeAcmeFaucet:
		return marshalerWriteAcmeFaucet(m, v->_AcmeFaucet);
	#endif
	#if _WANT_AddCredits_
    case TransactionTypeAddCredits:
		return marshalerWriteAddCredits(m, v->_AddCredits);
	#endif
	#if _WANT_BurnTokens_
    case TransactionTypeBurnTokens:
		return marshalerWriteBurnTokens(m, v->_BurnTokens);
	#endif
	#if _WANT_CreateDataAccount_
    case TransactionTypeCreateDataAccount:
		return marshalerWriteCreateDataAccount(m, v->_CreateDataAccount);
	#endif
	#if _WANT_CreateIdentity_
    case TransactionTypeCreateIdentity:
		return marshalerWriteCreateIdentity(m, v->_CreateIdentity);
	#endif
	#if _WANT_CreateKeyBook_
    case TransactionTypeCreateKeyBook:
		return marshalerWriteCreateKeyBook(m, v->_CreateKeyBook);
	#endif
	#if _WANT_CreateKeyPage_
    case TransactionTypeCreateKeyPage:
		return marshalerWriteCreateKeyPage(m, v->_CreateKeyPage);
	#endif
	#if _WANT_CreateLiteTokenAccount_
    case TransactionTypeCreateLiteTokenAccount:
		return marshalerWriteCreateLiteTokenAccount(m, v->_CreateLiteTokenAccount);
	#endif
	#if _WANT_CreateToken_
    case TransactionTypeCreateToken:
		return marshalerWriteCreateToken(m, v->_CreateToken);
	#endif
	#if _WANT_CreateTokenAccount_
    case TransactionTypeCreateTokenAccount:
		return marshalerWriteCreateTokenAccount(m, v->_CreateTokenAccount);
	#endif
	#if _WANT_IssueTokens_
    case TransactionTypeIssueTokens:
		return marshalerWriteIssueTokens(m, v->_IssueTokens);
	#endif
	#if _WANT_LockAccount_
    case TransactionTypeLockAccount:
		return marshalerWriteLockAccount(m, v->_LockAccount);
	#endif
	#if _WANT_Remote_
    case TransactionTypeRemote:
		return marshalerWriteRemoteTransaction(m, v->_RemoteTransaction);
	#endif
	#if _WANT_SendTokens_
    case TransactionTypeSendTokens:
		return marshalerWriteSendTokens(m, v->_SendTokens);
	#endif
	#if _WANT_UpdateAccountAuth_
    case TransactionTypeUpdateAccountAuth:
		return marshalerWriteUpdateAccountAuth(m, v->_UpdateAccountAuth);
	#endif
	#if _WANT_UpdateKey_
    case TransactionTypeUpdateKey:
		return marshalerWriteUpdateKey(m, v->_UpdateKey);
	#endif
	#if _WANT_UpdateKeyPage_
    case TransactionTypeUpdateKeyPage:
		return marshalerWriteUpdateKeyPage(m, v->_UpdateKeyPage);
	#endif
	#if _WANT_WriteData_
    case TransactionTypeWriteData:
		return marshalerWriteWriteData(m, v->_WriteData);
	#endif
	#if _WANT_WriteDataTo_
    case TransactionTypeWriteDataTo:
		return marshalerWriteWriteDataTo(m, v->_WriteDataTo);
	#endif
	default:
        return ErrorNotImplemented;
    };
}




//EqualKeyPageOperation is used to compare the values of the union
bool KeyPageOperation_equal(const KeyPageOperation *a, const KeyPageOperation *b) {
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
	#if _WANT_Add_
    case KeyPageOperationTypeAdd:
        return AddKeyOperation_equal(a->_AddKeyOperation, b->_AddKeyOperation);
	#endif
	#if _WANT_Remove_
    case KeyPageOperationTypeRemove:
        return RemoveKeyOperation_equal(a->_RemoveKeyOperation, b->_RemoveKeyOperation);
	#endif
	#if _WANT_SetThreshold_
    case KeyPageOperationTypeSetThreshold:
        return SetThresholdKeyPageOperation_equal(a->_SetThresholdKeyPageOperation, b->_SetThresholdKeyPageOperation);
	#endif
	#if _WANT_UpdateAllowed_
    case KeyPageOperationTypeUpdateAllowed:
        return UpdateAllowedKeyPageOperation_equal(a->_UpdateAllowedKeyPageOperation, b->_UpdateAllowedKeyPageOperation);
	#endif
	#if _WANT_Update_
    case KeyPageOperationTypeUpdate:
        return UpdateKeyOperation_equal(a->_UpdateKeyOperation, b->_UpdateKeyOperation);
	#endif
    default:
        return false;
    };
}

#if _WANT_AddKeyOperation_
int newAddKeyOperation(Unmarshaler *m, KeyPageOperation *v) {
    v->_AddKeyOperation = (AddKeyOperation*)unmarshalerAlloc(m, sizeof(AddKeyOperation));
    CHECK_ERROR_INT(v->_AddKeyOperation)
    return ErrorNone;
}
#endif

#if _WANT_RemoveKeyOperation_
int newRemoveKeyOperation(Unmarshaler *m, KeyPageOperation *v) {
    v->_RemoveKeyOperation = (RemoveKeyOperation*)unmarshalerAlloc(m, sizeof(RemoveKeyOperation));
    CHECK_ERROR_INT(v->_RemoveKeyOperation)
    return ErrorNone;
}
#endif

#if _WANT_SetThresholdKeyPageOperation_
int newSetThresholdKeyPageOperation(Unmarshaler *m, KeyPageOperation *v) {
    v->_SetThresholdKeyPageOperation = (SetThresholdKeyPageOperation*)unmarshalerAlloc(m, sizeof(SetThresholdKeyPageOperation));
    CHECK_ERROR_INT(v->_SetThresholdKeyPageOperation)
    return ErrorNone;
}
#endif

#if _WANT_UpdateAllowedKeyPageOperation_
int newUpdateAllowedKeyPageOperation(Unmarshaler *m, KeyPageOperation *v) {
    v->_UpdateAllowedKeyPageOperation = (UpdateAllowedKeyPageOperation*)unmarshalerAlloc(m, sizeof(UpdateAllowedKeyPageOperation));
    CHECK_ERROR_INT(v->_UpdateAllowedKeyPageOperation)
    return ErrorNone;
}
#endif

#if _WANT_UpdateKeyOperation_
int newUpdateKeyOperation(Unmarshaler *m, KeyPageOperation *v) {
    v->_UpdateKeyOperation = (UpdateKeyOperation*)unmarshalerAlloc(m, sizeof(UpdateKeyOperation));
    CHECK_ERROR_INT(v->_UpdateKeyOperation)
    return ErrorNone;
}
#endif

int unmarshalerReadKeyPageOperation(Unmarshaler *m, KeyPageOperation *v) {
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
	#if _WANT_AddKeyOperation_
    case KeyPageOperationTypeAdd:
        b = newAddKeyOperation(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadAddKeyOperation(m, v->_AddKeyOperation);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_RemoveKeyOperation_
    case KeyPageOperationTypeRemove:
        b = newRemoveKeyOperation(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadRemoveKeyOperation(m, v->_RemoveKeyOperation);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_SetThresholdKeyPageOperation_
    case KeyPageOperationTypeSetThreshold:
        b = newSetThresholdKeyPageOperation(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadSetThresholdKeyPageOperation(m, v->_SetThresholdKeyPageOperation);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_UpdateAllowedKeyPageOperation_
    case KeyPageOperationTypeUpdateAllowed:
        b = newUpdateAllowedKeyPageOperation(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadUpdateAllowedKeyPageOperation(m, v->_UpdateAllowedKeyPageOperation);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_UpdateKeyOperation_
    case KeyPageOperationTypeUpdate:
        b = newUpdateKeyOperation(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
		b = unmarshalerReadUpdateKeyOperation(m, v->_UpdateKeyOperation);
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

int marshalerWriteKeyPageOperation(Marshaler *m, const KeyPageOperation *v) {
    CHECK_ERROR_INT(m)
    CHECK_ERROR_INT(v)

    switch ( v->_u->Type ) {
	#if _WANT_Add_
    case KeyPageOperationTypeAdd:
		return marshalerWriteAddKeyOperation(m, v->_AddKeyOperation);
	#endif
	#if _WANT_Remove_
    case KeyPageOperationTypeRemove:
		return marshalerWriteRemoveKeyOperation(m, v->_RemoveKeyOperation);
	#endif
	#if _WANT_SetThreshold_
    case KeyPageOperationTypeSetThreshold:
		return marshalerWriteSetThresholdKeyPageOperation(m, v->_SetThresholdKeyPageOperation);
	#endif
	#if _WANT_UpdateAllowed_
    case KeyPageOperationTypeUpdateAllowed:
		return marshalerWriteUpdateAllowedKeyPageOperation(m, v->_UpdateAllowedKeyPageOperation);
	#endif
	#if _WANT_Update_
    case KeyPageOperationTypeUpdate:
		return marshalerWriteUpdateKeyOperation(m, v->_UpdateKeyOperation);
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
        b = newBTCSignature(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
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
		b = unmarshalerReadED25519Signature(m, v->_ED25519Signature);
		if ( IsError(ErrorCode(b))) {
		    return b;
		}
		n += b;
		break;
	#endif
	#if _WANT_ETHSignature_
    case SignatureTypeETH:
        b = newETHSignature(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
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
        b = newRCD1Signature(m, v);
        if ( IsError(ErrorCode(b))) {
            return b;
        }
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
