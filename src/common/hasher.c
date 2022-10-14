#include "common/sha256.h"
#include "common/hasher.h"
#include <common/encoding/encoding.h>

//16*32 <- 512
void MerkleStateInit(MerkleState *m) {
    explicit_bzero(m, sizeof(MerkleState));
    m->arena.ptr = m->hashes;
    m->arena.offset = 0;
    m->arena.size = sizeof(m->hashes);
}

Error MerkleDAGRoot(MerkleState *m, uint8_t mdroot[static 32]) {
    Error e = ErrorCode(ErrorNone);

    bool first = true;
    for (int i = 0; i < m->pendingLen; i++ ){ //_, v := range m.Pending {
        if (first && m->pending[i].size != 0) { // Pick up the first hash in m.MerkleState no matter what.
            first = false;
            memmove(mdroot, m->pending[i].ptr+m->pending[i].offset, m->pending[i].size);
            // = Hash(v).Copy() // If a nil is assigned over a nil, no harm no foul.  Fewer cases to test this way.
        } else if (!first && m->pending[i].size != 0) { // If MDRoot isn't nil and v isn't nil, combine them.
            // the pending hash is on the left, MDRoot candidate is on the right, for a new MDRoot
            uint8_t combine[64] = {0};
            memmove(combine, m->pending[i].ptr+m->pending[i].offset, 32 );
            memmove(combine+32, mdroot, 32);
            e = sha256(combine, sizeof(combine), mdroot, 32);
            if (IsError(e) ) {
                return e;
            }
        }
    }
    return e;
}

static int append_pending(MerkleState *m, uint8_t *append, uint8_t appendlen) {
    //appendLen must be either 0 or 32
    if ( appendlen != 32 ) {
        if ( appendlen != 0) {
            return ErrorInvalidOffset;
        }
    }
    if ( !buffer_can_read(&m->arena,32) ) {
        return ErrorBufferTooSmall;
    }

    m->pending[m->pendingLen].ptr = m->arena.ptr + m->arena.offset;
    m->pending[m->pendingLen].size = appendlen;
    memmove(m->pending[m->pendingLen].ptr+m->pending[m->pendingLen].offset, append, appendlen);
    m->arena.offset += 32;
    m->pendingLen++;
    return ErrorNone;
}

static int padPending(MerkleState *m) {
    if ( m->pendingLen == 0 || m->pending[m->pendingLen-1].size != 0) {
        return append_pending(m, NULL, 0);
    }
    return ErrorNone;
}

int AddToMerkleTree(MerkleState *m, uint8_t hash_[static 32]) {
    uint8_t hash[32];
    memmove(hash, hash_, 32);
    // Increment our total Hash Count
    m->count++;
    int e = padPending(m);
    if (IsErrorCode(e)) {
        return e;
    }
    for (int i = 0; i < m->pendingLen; i++ ) {
        // Adding the hash is like incrementing a variable
        if (m->pending[i].size == 0) {
            // Look for an empty slot, and
            m->pending[i].size = 32;
            //put the Hash there if one is found
            memmove(m->pending[i].ptr + m->pending[i].offset, hash, 32);
            // Mission complete, so return
            return ErrorNone;
        }
        uint8_t combine[64] = {0};
        memmove(combine, m->pending[i].ptr+m->pending[i].offset, 32);
        memmove(combine+32, hash, 32);
        sha256(combine,sizeof(combine), hash, 32);
        //   and carry the result to the next (clearing this one)
        m->pending[i].size = 0;
    }
    return 0;
}

static int hasherAppend(MerkleState *m, const Bytes *v) {
    uint8_t hash[32];
    sha256(v->buffer.ptr+v->buffer.offset, v->buffer.size- v->buffer.offset,
           hash, sizeof(hash));
    return AddToMerkleTree(m, hash);
}

int hasherAddHash(MerkleState *m, Bytes32 *v) {
    return hasherAppend(m,&v->data);
}

int hasherAddInt(MerkleState *m, int64_t v) {
    uint8_t b[10] = {0};
    int size = varint_write(b,0,v);
    if (size < 0 ) {
        return ErrorVarIntWrite;
    }
    return hasherAppend(m,&(const Bytes){.buffer.ptr = b, .buffer.offset = 0, .buffer.size = size });
}

int hasherAddUint(MerkleState *m, uint64_t v) {
    uint8_t b[10] = {0};
    int size = uvarint_write(b,0,v);
    if (size < 0 ) {
        return ErrorUVarIntWrite;
    }
    return hasherAppend(m,&(const Bytes){.buffer.ptr = b, .buffer.offset = 0, .buffer.size = size });
}

int hasherAddBool(MerkleState *m, bool v) {
    uint64_t u = v;
    return hasherAddUint(m,u);
}
//
//int hasherAddTime(v time.Time) {
//    h.AddInt(v.UTC().Unix())
//}

int hasherAddBytes(MerkleState *m, Bytes *v) {
    return hasherAppend(m, v);
}

int hasherAddVarInt(MerkleState *m, VarInt *v) {
    return hasherAppend(m, &v->data);
}

int hasherAddUVarInt(MerkleState *m, UVarInt *v) {
    return hasherAppend(m, &v->data);
}

int hasherAddString(MerkleState *m, String *v) {
    return hasherAppend(m,&v->data);
}
//
//func (h *Hasher) AddDuration(v time.Duration) {
//    sec, ns := encoding.SplitDuration(v)
//               var b [10]byte
//           n := binary.PutUvarint(b[:], sec)
//              var c [10]byte
//          m := binary.PutUvarint(c[:], ns)
//                  h.append(append(b[:n], c[:m]...))
//}

int hasherAddBigInt(MerkleState *m, BigInt *v) {
    return hasherAppend(m, &v->data);
}

int hasherAddUrl(MerkleState *m, Url *v) {
    return hasherAppend(m, &v->data);
}
//
//func (h *Hasher) AddValue(v interface{ MerkleHash() []byte }) {
//        *h = append(*h, v.MerkleHash())
//}

int hasherAddEnum(MerkleState *m, int n) {
    return hasherAddUint(m, (uint64_t)n);
}
