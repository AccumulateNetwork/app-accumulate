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

Error Envelope_marshalBinary(const struct Envelope* self, struct Marshaler *outData) {
    if ( !self || !outData ) {
        return ErrorCode(ErrorParameterNil);
    }

    int n = Envelope_binarySize(self);
    if ( n + outData->cache.offset < outData->cache.size) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    Error e = self->_numSignatures.MarshalBinary(&self->_numSignatures,outData);
    if ( e.code != ErrorNone ) {
        return e;
    }

    uint64_t numSignatures = 0;
    e = VarInt_get(&self->_numSignatures.data,&numSignatures);
    if ( e.code != ErrorNone ) {
        return e;
    }

    for ( int i = 0; i < numSignatures; ++i ) {
        e = self->_Signatures->MarshalBinary(self->_Signatures,outData);
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
func (e *Envelope) VerifyTxHash() bool {
        if e.TxHash == nil {
                return true
        }
        return bytes.Equal(e.TxHash, e.Transaction.calculateHash())
}

// Hash calculates the hash of the transaction as H(H(header) + H(body)).
func (t *Transaction) calculateHash() []byte {
        // Already computed?
        if t.hash != nil {
                return t.hash
        }

        if t.Type() == TransactionTypeSignPending {
                // Do not use the hash for a signature transaction
                return nil
        }

        // Marshal the header
        data, err := t.TransactionHeader.MarshalBinary()
        if err != nil {
                // TransactionHeader.MarshalBinary will never return an error, but better safe than sorry.
                panic(err)
        }

        // Calculate the hash
        h1 := sha256.Sum256(data)
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
