#include <common/protocol/enum.h>

#ifdef ACME_API
#undef ACME_API
#define ACME_API
#endif
#define _ACME_ENUM_SOURCE_



#ifdef _ACME_ENUM_SOURCE_




ACME_API Error AccountAuthOperationType_set(VarInt *v, AccountAuthOperationType n) {
    return VarInt_set(v,n);
}

ACME_API Error AccountAuthOperationType_get(const VarInt *v, AccountAuthOperationType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Account Auth Operation Type
ACME_API uint64_t AccountAuthOperationType_ID(AccountAuthOperationType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Account Auth Operation Type
static enum_t AccountAuthOperationType_l[] = {
    { "unknown", AccountAuthOperationTypeUnknown },
    { "enable", AccountAuthOperationTypeEnable },
    { "disable", AccountAuthOperationTypeDisable },
    { "addauthority", AccountAuthOperationTypeAddAuthority },
    { "removeauthority", AccountAuthOperationTypeRemoveAuthority },
    { 0,0 },
};

ACME_API Error AccountAuthOperationType_asString(const AccountAuthOperationType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( AccountAuthOperationType_l[i].name == 0 ) {
            break;
        }
        if ( AccountAuthOperationType_l[i].e == v ) {
            String_set(out, AccountAuthOperationType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// AccountAuthOperationTypeByName returns the named Account Auth Operation Type.
ACME_API Error AccountAuthOperationType_fromString(AccountAuthOperationType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( AccountAuthOperationType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(AccountAuthOperationType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = AccountAuthOperationType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool AccountAuthOperationType_equal(const AccountAuthOperationType *a, const AccountAuthOperationType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Account Auth Operation Type to bytes as an unsigned varint.
ACME_API int marshalerWriteAccountAuthOperationType(Marshaler *m, AccountAuthOperationType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Account Auth Operation Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadAccountAuthOperationType(Unmarshaler *m, AccountAuthOperationType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (AccountAuthOperationType)n;
    return b;
}



ACME_API Error AccountType_set(VarInt *v, AccountType n) {
    return VarInt_set(v,n);
}

ACME_API Error AccountType_get(const VarInt *v, AccountType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Account Type
ACME_API uint64_t AccountType_ID(AccountType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Account Type
static enum_t AccountType_l[] = {
    { "unknown", AccountTypeUnknown },
    { "anchorledger", AccountTypeAnchorLedger },
    { "identity", AccountTypeIdentity },
    { "tokenissuer", AccountTypeTokenIssuer },
    { "tokenaccount", AccountTypeTokenAccount },
    { "litetokenaccount", AccountTypeLiteTokenAccount },
    { "blockledger", AccountTypeBlockLedger },
    { "keypage", AccountTypeKeyPage },
    { "keybook", AccountTypeKeyBook },
    { "dataaccount", AccountTypeDataAccount },
    { "litedataaccount", AccountTypeLiteDataAccount },
    { "unknownsigner", AccountTypeUnknownSigner },
    { "systemledger", AccountTypeSystemLedger },
    { "liteidentity", AccountTypeLiteIdentity },
    { "syntheticledger", AccountTypeSyntheticLedger },
    { 0,0 },
};

ACME_API Error AccountType_asString(const AccountType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( AccountType_l[i].name == 0 ) {
            break;
        }
        if ( AccountType_l[i].e == v ) {
            String_set(out, AccountType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// AccountTypeByName returns the named Account Type.
ACME_API Error AccountType_fromString(AccountType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( AccountType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(AccountType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = AccountType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool AccountType_equal(const AccountType *a, const AccountType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Account Type to bytes as an unsigned varint.
ACME_API int marshalerWriteAccountType(Marshaler *m, AccountType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Account Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadAccountType(Unmarshaler *m, AccountType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (AccountType)n;
    return b;
}



ACME_API Error AllowedTransactionBit_set(VarInt *v, AllowedTransactionBit n) {
    return VarInt_set(v,n);
}

ACME_API Error AllowedTransactionBit_get(const VarInt *v, AllowedTransactionBit *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Allowed Transaction Bit
ACME_API uint64_t AllowedTransactionBit_ID(AllowedTransactionBit v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Allowed Transaction Bit
static enum_t AllowedTransactionBit_l[] = {
    { "updatekeypage", AllowedTransactionBitUpdateKeyPage },
    { "updateaccountauth", AllowedTransactionBitUpdateAccountAuth },
    { 0,0 },
};

ACME_API Error AllowedTransactionBit_asString(const AllowedTransactionBit v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( AllowedTransactionBit_l[i].name == 0 ) {
            break;
        }
        if ( AllowedTransactionBit_l[i].e == v ) {
            String_set(out, AllowedTransactionBit_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// AllowedTransactionBitByName returns the named Allowed Transaction Bit.
ACME_API Error AllowedTransactionBit_fromString(AllowedTransactionBit *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( AllowedTransactionBit_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(AllowedTransactionBit_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = AllowedTransactionBit_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool AllowedTransactionBit_equal(const AllowedTransactionBit *a, const AllowedTransactionBit *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Allowed Transaction Bit to bytes as an unsigned varint.
ACME_API int marshalerWriteAllowedTransactionBit(Marshaler *m, AllowedTransactionBit v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Allowed Transaction Bit from bytes as an unsigned varint.
ACME_API int unmarshalerReadAllowedTransactionBit(Unmarshaler *m, AllowedTransactionBit *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (AllowedTransactionBit)n;
    return b;
}



ACME_API Error BookType_set(VarInt *v, BookType n) {
    return VarInt_set(v,n);
}

ACME_API Error BookType_get(const VarInt *v, BookType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Book Type
ACME_API uint64_t BookType_ID(BookType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Book Type
static enum_t BookType_l[] = {
    { "normal", BookTypeNormal },
    { "validator", BookTypeValidator },
    { "operator", BookTypeOperator },
    { 0,0 },
};

ACME_API Error BookType_asString(const BookType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( BookType_l[i].name == 0 ) {
            break;
        }
        if ( BookType_l[i].e == v ) {
            String_set(out, BookType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// BookTypeByName returns the named Book Type.
ACME_API Error BookType_fromString(BookType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( BookType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(BookType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = BookType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool BookType_equal(const BookType *a, const BookType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Book Type to bytes as an unsigned varint.
ACME_API int marshalerWriteBookType(Marshaler *m, BookType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Book Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadBookType(Unmarshaler *m, BookType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (BookType)n;
    return b;
}



ACME_API Error DataEntryType_set(VarInt *v, DataEntryType n) {
    return VarInt_set(v,n);
}

ACME_API Error DataEntryType_get(const VarInt *v, DataEntryType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Data Entry Type
ACME_API uint64_t DataEntryType_ID(DataEntryType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Data Entry Type
static enum_t DataEntryType_l[] = {
    { "unknown", DataEntryTypeUnknown },
    { "factom", DataEntryTypeFactom },
    { "accumulate", DataEntryTypeAccumulate },
    { 0,0 },
};

ACME_API Error DataEntryType_asString(const DataEntryType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( DataEntryType_l[i].name == 0 ) {
            break;
        }
        if ( DataEntryType_l[i].e == v ) {
            String_set(out, DataEntryType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// DataEntryTypeByName returns the named Data Entry Type.
ACME_API Error DataEntryType_fromString(DataEntryType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( DataEntryType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(DataEntryType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = DataEntryType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool DataEntryType_equal(const DataEntryType *a, const DataEntryType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Data Entry Type to bytes as an unsigned varint.
ACME_API int marshalerWriteDataEntryType(Marshaler *m, DataEntryType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Data Entry Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadDataEntryType(Unmarshaler *m, DataEntryType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (DataEntryType)n;
    return b;
}



ACME_API Error KeyPageOperationType_set(VarInt *v, KeyPageOperationType n) {
    return VarInt_set(v,n);
}

ACME_API Error KeyPageOperationType_get(const VarInt *v, KeyPageOperationType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Key Page Operation Type
ACME_API uint64_t KeyPageOperationType_ID(KeyPageOperationType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Key Page Operation Type
static enum_t KeyPageOperationType_l[] = {
    { "unknown", KeyPageOperationTypeUnknown },
    { "update", KeyPageOperationTypeUpdate },
    { "remove", KeyPageOperationTypeRemove },
    { "add", KeyPageOperationTypeAdd },
    { "setthreshold", KeyPageOperationTypeSetThreshold },
    { "updateallowed", KeyPageOperationTypeUpdateAllowed },
    { 0,0 },
};

ACME_API Error KeyPageOperationType_asString(const KeyPageOperationType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( KeyPageOperationType_l[i].name == 0 ) {
            break;
        }
        if ( KeyPageOperationType_l[i].e == v ) {
            String_set(out, KeyPageOperationType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// KeyPageOperationTypeByName returns the named Key Page Operation Type.
ACME_API Error KeyPageOperationType_fromString(KeyPageOperationType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( KeyPageOperationType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(KeyPageOperationType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = KeyPageOperationType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool KeyPageOperationType_equal(const KeyPageOperationType *a, const KeyPageOperationType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Key Page Operation Type to bytes as an unsigned varint.
ACME_API int marshalerWriteKeyPageOperationType(Marshaler *m, KeyPageOperationType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Key Page Operation Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadKeyPageOperationType(Unmarshaler *m, KeyPageOperationType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (KeyPageOperationType)n;
    return b;
}



ACME_API Error ObjectType_set(VarInt *v, ObjectType n) {
    return VarInt_set(v,n);
}

ACME_API Error ObjectType_get(const VarInt *v, ObjectType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Object Type
ACME_API uint64_t ObjectType_ID(ObjectType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Object Type
static enum_t ObjectType_l[] = {
    { "unknown", ObjectTypeUnknown },
    { "account", ObjectTypeAccount },
    { "transaction", ObjectTypeTransaction },
    { 0,0 },
};

ACME_API Error ObjectType_asString(const ObjectType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( ObjectType_l[i].name == 0 ) {
            break;
        }
        if ( ObjectType_l[i].e == v ) {
            String_set(out, ObjectType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// ObjectTypeByName returns the named Object Type.
ACME_API Error ObjectType_fromString(ObjectType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( ObjectType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(ObjectType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = ObjectType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool ObjectType_equal(const ObjectType *a, const ObjectType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Object Type to bytes as an unsigned varint.
ACME_API int marshalerWriteObjectType(Marshaler *m, ObjectType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Object Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadObjectType(Unmarshaler *m, ObjectType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (ObjectType)n;
    return b;
}



ACME_API Error PartitionType_set(VarInt *v, PartitionType n) {
    return VarInt_set(v,n);
}

ACME_API Error PartitionType_get(const VarInt *v, PartitionType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Partition Type
ACME_API uint64_t PartitionType_ID(PartitionType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Partition Type
static enum_t PartitionType_l[] = {
    { "directory", PartitionTypeDirectory },
    { "blockvalidator", PartitionTypeBlockValidator },
    { 0,0 },
};

ACME_API Error PartitionType_asString(const PartitionType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( PartitionType_l[i].name == 0 ) {
            break;
        }
        if ( PartitionType_l[i].e == v ) {
            String_set(out, PartitionType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// PartitionTypeByName returns the named Partition Type.
ACME_API Error PartitionType_fromString(PartitionType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( PartitionType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(PartitionType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = PartitionType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool PartitionType_equal(const PartitionType *a, const PartitionType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Partition Type to bytes as an unsigned varint.
ACME_API int marshalerWritePartitionType(Marshaler *m, PartitionType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Partition Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadPartitionType(Unmarshaler *m, PartitionType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (PartitionType)n;
    return b;
}



ACME_API Error SignatureType_set(VarInt *v, SignatureType n) {
    return VarInt_set(v,n);
}

ACME_API Error SignatureType_get(const VarInt *v, SignatureType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Signature Type
ACME_API uint64_t SignatureType_ID(SignatureType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Signature Type
static enum_t SignatureType_l[] = {
    { "unknown", SignatureTypeUnknown },
    { "legacyed25519", SignatureTypeLegacyED25519 },
    { "ed25519", SignatureTypeED25519 },
    { "rcd1", SignatureTypeRCD1 },
    { "receipt", SignatureTypeReceipt },
    { "partition", SignatureTypePartition },
    { "set", SignatureTypeSet },
    { "remote", SignatureTypeRemote },
    { "btc", SignatureTypeBTC },
    { "btclegacy", SignatureTypeBTCLegacy },
    { "eth", SignatureTypeETH },
    { "delegated", SignatureTypeDelegated },
    { "internal", SignatureTypeInternal },
    { 0,0 },
};

ACME_API Error SignatureType_asString(const SignatureType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( SignatureType_l[i].name == 0 ) {
            break;
        }
        if ( SignatureType_l[i].e == v ) {
            String_set(out, SignatureType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// SignatureTypeByName returns the named Signature Type.
ACME_API Error SignatureType_fromString(SignatureType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( SignatureType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(SignatureType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = SignatureType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool SignatureType_equal(const SignatureType *a, const SignatureType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Signature Type to bytes as an unsigned varint.
ACME_API int marshalerWriteSignatureType(Marshaler *m, SignatureType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Signature Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadSignatureType(Unmarshaler *m, SignatureType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (SignatureType)n;
    return b;
}



ACME_API Error TransactionMax_set(VarInt *v, TransactionMax n) {
    return VarInt_set(v,n);
}

ACME_API Error TransactionMax_get(const VarInt *v, TransactionMax *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Transaction Max
ACME_API uint64_t TransactionMax_ID(TransactionMax v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Transaction Max
static enum_t TransactionMax_l[] = {
    { "user", TransactionMaxUser },
    { "synthetic", TransactionMaxSynthetic },
    { "system", TransactionMaxSystem },
    { 0,0 },
};

ACME_API Error TransactionMax_asString(const TransactionMax v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( TransactionMax_l[i].name == 0 ) {
            break;
        }
        if ( TransactionMax_l[i].e == v ) {
            String_set(out, TransactionMax_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// TransactionMaxByName returns the named Transaction Max.
ACME_API Error TransactionMax_fromString(TransactionMax *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( TransactionMax_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(TransactionMax_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = TransactionMax_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool TransactionMax_equal(const TransactionMax *a, const TransactionMax *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Transaction Max to bytes as an unsigned varint.
ACME_API int marshalerWriteTransactionMax(Marshaler *m, TransactionMax v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Transaction Max from bytes as an unsigned varint.
ACME_API int unmarshalerReadTransactionMax(Unmarshaler *m, TransactionMax *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (TransactionMax)n;
    return b;
}



ACME_API Error TransactionType_set(VarInt *v, TransactionType n) {
    return VarInt_set(v,n);
}

ACME_API Error TransactionType_get(const VarInt *v, TransactionType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Transaction Type
ACME_API uint64_t TransactionType_ID(TransactionType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Transaction Type
static enum_t TransactionType_l[] = {
    { "unknown", TransactionTypeUnknown },
    { "createidentity", TransactionTypeCreateIdentity },
    { "createtokenaccount", TransactionTypeCreateTokenAccount },
    { "sendtokens", TransactionTypeSendTokens },
    { "createdataaccount", TransactionTypeCreateDataAccount },
    { "writedata", TransactionTypeWriteData },
    { "writedatato", TransactionTypeWriteDataTo },
    { "acmefaucet", TransactionTypeAcmeFaucet },
    { "createtoken", TransactionTypeCreateToken },
    { "issuetokens", TransactionTypeIssueTokens },
    { "burntokens", TransactionTypeBurnTokens },
    { "createlitetokenaccount", TransactionTypeCreateLiteTokenAccount },
    { "createkeypage", TransactionTypeCreateKeyPage },
    { "createkeybook", TransactionTypeCreateKeyBook },
    { "addcredits", TransactionTypeAddCredits },
    { "updatekeypage", TransactionTypeUpdateKeyPage },
    { "lockaccount", TransactionTypeLockAccount },
    { "updateaccountauth", TransactionTypeUpdateAccountAuth },
    { "updatekey", TransactionTypeUpdateKey },
    { "remote", TransactionTypeRemote },
    { "syntheticcreateidentity", TransactionTypeSyntheticCreateIdentity },
    { "syntheticwritedata", TransactionTypeSyntheticWriteData },
    { "syntheticdeposittokens", TransactionTypeSyntheticDepositTokens },
    { "syntheticdepositcredits", TransactionTypeSyntheticDepositCredits },
    { "syntheticburntokens", TransactionTypeSyntheticBurnTokens },
    { "syntheticforwardtransaction", TransactionTypeSyntheticForwardTransaction },
    { "systemgenesis", TransactionTypeSystemGenesis },
    { "directoryanchor", TransactionTypeDirectoryAnchor },
    { "blockvalidatoranchor", TransactionTypeBlockValidatorAnchor },
    { "systemwritedata", TransactionTypeSystemWriteData },
    { 0,0 },
};

ACME_API Error TransactionType_asString(const TransactionType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( TransactionType_l[i].name == 0 ) {
            break;
        }
        if ( TransactionType_l[i].e == v ) {
            String_set(out, TransactionType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// TransactionTypeByName returns the named Transaction Type.
ACME_API Error TransactionType_fromString(TransactionType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( TransactionType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(TransactionType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = TransactionType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool TransactionType_equal(const TransactionType *a, const TransactionType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Transaction Type to bytes as an unsigned varint.
ACME_API int marshalerWriteTransactionType(Marshaler *m, TransactionType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Transaction Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadTransactionType(Unmarshaler *m, TransactionType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (TransactionType)n;
    return b;
}



ACME_API Error VoteType_set(VarInt *v, VoteType n) {
    return VarInt_set(v,n);
}

ACME_API Error VoteType_get(const VarInt *v, VoteType *n) {
    return VarInt_get(v,(int64_t*)n);
}


// ID returns the ID of the Vote Type
ACME_API uint64_t VoteType_ID(VoteType v) { return (uint64_t)(v); }
#if WANT_ENUM_STRING_CONVERSION
// String returns the name of the Vote Type
static enum_t VoteType_l[] = {
    { "accept", VoteTypeAccept },
    { "reject", VoteTypeReject },
    { "abstain", VoteTypeAbstain },
    { "suggest", VoteTypeSuggest },
    { 0,0 },
};

ACME_API Error VoteType_asString(const VoteType v, String *out) {
    CHECK_ERROR(out)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( VoteType_l[i].name == 0 ) {
            break;
        }
        if ( VoteType_l[i].e == v ) {
            String_set(out, VoteType_l[i].name);
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}

// VoteTypeByName returns the named Vote Type.
ACME_API Error VoteType_fromString(VoteType *v, String *name) {
    CHECK_ERROR(name)
    //since we are only dealing with a limited number of enumerations, we will do a linear search
    for ( uint64_t i = 0; ; ++i ) {
        if ( VoteType_l[i].name == 0 ) {
            break;
        }
        if ( strncmp(VoteType_l[i].name, (const char*)name->data.buffer.ptr+name->data.buffer.offset,name->data.buffer.size) == 0 ) {
            *v = VoteType_l[i].e;
            return ErrorCode(ErrorNone);
        }
    }
    return ErrorCode(ErrorTypeNotFound);
}
#endif

ACME_API bool VoteType_equal(const VoteType *a, const VoteType *b) {
    if (!a || !b) {
        return false;
    }
    return *a == *b;
}

// MarshalBinary marshals the Vote Type to bytes as an unsigned varint.
ACME_API int marshalerWriteVoteType(Marshaler *m, VoteType v) {
    return marshalerWriteUInt(m,(uint64_t) v);
}


// UnmarshalBinary unmarshals the Vote Type from bytes as an unsigned varint.
ACME_API int unmarshalerReadVoteType(Unmarshaler *m, VoteType *v) {
    uint64_t n = 0;
    int b = unmarshalerReadUInt(m, &n);
    *v = (VoteType)n;
    return b;
}



#endif /* _ACME_ENUM_SOURCE_ */
