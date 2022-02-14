#include <common/encoding.h>
#include <common/envelope.h>

int Envelope_binarySize(const Envelope* v) {
    if ( !v ) {
        return 0;
    }
    int ret = 0;
    uint64_t numSignatures = 0;
    Error e = VarInt_get(&v->_numSignatures.data,&numSignatures);
    if ( e.code != ErrorNone ) {
        return 0;
    }

    ret += VarInt_binarySize(&v->_numSignatures.data);

    for ( int i = 0; i < numSignatures ; ++i ) {
        ret += v->_Signatures->BinarySize(v->_Signatures);
    }

    ret += v->_TxHash.BinarySize(&v->_TxHash);

    ret += v->_Transaction->BinarySize(v->_Transaction);

    return ret;
}

Error Envelope_marshalBinary2(const Envelope_t *self, Marshaler *outData) {
    if ( !self || !outData ) {
        return ErrorCode(ErrorParameterNil);
    }

    int size = Envelope_binarySize(self);
    if ( size > outData->cache.size - outData->cache.offset) {
        return ErrorCode(ErrorBufferTooSmall);
    }

}

Error Envelope_copy(Envelope_t *dst, const Envelope *src) {
    //copy the buffer into the object.
}

Error Envelope_marshalBinary(const struct Envelope* self, struct Marshaler *outData) {
    if ( !self || !outData ) {
        return ErrorCode(ErrorParameterNil);
    }

    int n = Envelope_binarySize(self);
    if ( n + outData->cache.offset < outData->cache.size) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    Error e = VarInt_marshalBinary(&self->_numSignatures.data,outData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    uint64_t numSignatures = 0;
    e = VarInt_get(&self->_numSignatures.data,&numSignatures);
    if ( e.code != ErrorNone ) {
        return e;
    }

    for ( int i = 0; i < numSignatures; ++i ) {
        e = self->_Signatures->MarshalBinary(&self->_Signatures[i],outData);
        if ( e.code != ErrorNone ) {
            return e;
        }
    }

    e = self->_TxHash.MarshalBinary(&self->_TxHash,outData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    e = self->_Transaction->MarshalBinary(self->_Transaction,outData);

    return e;
}


// Marshal process
// data_t -> data byte field -> marshaler
// unmarshal process
// marshaler -> data byte field -> data_t
// initialize real message
// create a memory backed stream and assign it to marshaler
// unmarshal stream and assign it to real message

// Envelope_unmarshalBinary assign pointers to the envelop that reside in the bytestream
Error Envelope_unmarshalBinary(Envelope* self, Marshaler *inData) {
    if (!self || !inData) {
        return ErrorCode(ErrorParameterNil);
    }

    self->_numSignatures.UnmarshalBinary(&self->_numSignatures, inData);

    uint64_t numSignatures = 0;
    Error e = VarInt_get(&self->_numSignatures.data,&numSignatures);
    if (e.code != ErrorNone) {
        return e;
    }

    for (int i = 0; i < numSignatures; ++i ) {
        e = self->_signatures[i].UnmarshalBinary(&self->_signatures[i],inData);
        if ( e.code != ErrorNone ) {
            return e;
        }
    }

    e = self->_txHash.UnmarshalBinary(&self->_txHash, inData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    return self->_transaction->UnmarshalBinary(self->_transaction, inData);
}

//// GetTxHash returns the hash of the transaction.
////
//// GetTxHash will panic if Transaction is nil and TxHash is nil or not a valid
//// hash.
//Error GetTxHash(e *Envelope, Bytes *bytes ) {

//    if len(e.TxHash) == sha256.Size {
//                return e.TxHash
//        }

//        if e.Transaction != nil {
//                return e.Transaction.calculateHash()
//        }

//        if len(e.TxHash) == 0 {
//                panic("both Transaction and TxHash are unspecified")
//        }
//        panic("invalid TxHash")
//}

// EnvHash calculates the hash of the envelope as H(H(sig₀) + H(sig₁) + ... +
// H(txn)).
//
// EnvHash will panic if any of the signatures are not well formed or if
// Transaction is nil and TxHash is nil or not a valid hash.
Error EnvHash(Envelope_t *e, Bytes32_t *hash) {

}
//func (e *Envelope) EnvHash() []byte {
//        // Already computed?
//        if e.hash != nil {
//                return e.hash
//        }

//        // Marshal and hash the signatures
//        hashes := make([]byte, 0, (len(e.Signatures)+1)*sha256.Size)
//        for _, sig := range e.Signatures {
//                data, err := sig.MarshalBinary()
//                if err != nil {
//                        // Warn the user
//                        panic(err)
//                }
//                h := sha256.Sum256(data)
//                hashes = append(hashes, h[:]...)
//        }

//        // Append the transaction hash
//        hashes = append(hashes, e.GetTxHash()...)

//        // Hash!
//        h := sha256.Sum256(hashes)
//        e.hash = h[:]
//        return h[:]
//}

// VerifyTxHash verifies that TxHash matches the hash of the transaction.
//Error VerifyTxHash(Envelope_t *e)  {
//    if ( e-> == nil {
//                return true
//        }
//        return bytes.Equal(e.TxHash, e.Transaction.calculateHash())
//}

// Hash calculates the hash of the transaction as H(H(header) + H(body)).
Error CalculateTransactionHash(Transaction *t, Bytes32_t *hash) {
    uint64_t type = 0;

    Error e = t->type.get(&t->type.data, &type);
    if ( e.code != ErrorNone ) {
        return e;
    }

    if ( type == TransactionTypeSignPending ) {
        // Do not use the hash for a signature transaction
        return ErrorCode(ErrorInvalidObject);
    }

    // Marshal the header
    e = t.TransactionHeader.MarshalBinary();
    if ( e.code != ErrorNone ) {
            // TransactionHeader.MarshalBinary will never return an error, but better safe than sorry.
            return e
    }

    // Calculate the hash
    uint8_t h[32] = {0};
    e = sha256(data, datalen, h, 32);
    if ( e.code != ErrorNone ) {
        return e;
    }

    h2 := sha256.Sum256(t.Body)
    data = make([]byte, sha256.Size*2)
    copy(data, h1[:])
    copy(data[sha256.Size:], h2[:])
    h := sha256.Sum256(data)
    t.hash = h[:]
    return h[:]
}

// Type decodes the transaction type from the body.
func (t *Transaction) Type() TransactionType {
        typ := TransactionTypeUnknown
        _ = typ.UnmarshalBinary(t.Body)
        return typ
}

// Verify verifies that the signatures are valid.
func (e *Envelope) Verify() bool {
        // Compute the transaction hash
        txid := e.GetTxHash()

        // Check each signature
        for _, v := range e.Signatures {
                if !v.Verify(txid) {
                        return false
                }
        }

        return true
}

// As unmarshals the transaction payload as the given sub transaction type.
func (e *Envelope) As(subTx encoding.BinaryUnmarshaler) error {
        return subTx.UnmarshalBinary(e.Transaction.Body)
}
