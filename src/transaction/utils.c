/*****************************************************************************
 *   Accumulate Ledger Wallet
 *   (c) 2022 DefiDevs, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *****************************************************************************/

#include <stdint.h>   // uint*_t
#include <stdbool.h>  // bool
#include <string.h>   // memmove

#include "types.h"
#include "common/sha256.h"

bool transaction_utils_check_encoding(const uint8_t *memo, uint64_t memo_len) {
    for (uint64_t i = 0; i < memo_len; i++) {
        if (memo[i] > 0x7F) {
            return false;
        }
    }

    return true;
}

bool transaction_utils_format_memo(const uint8_t *memo,
                                   uint64_t memo_len,
                                   char *dst,
                                   uint64_t dst_len) {
    if (memo_len > MAX_MEMO_LEN || dst_len < memo_len + 1) {
        return false;
    }

    memmove(dst, memo, memo_len);
    dst[memo_len] = '\0';

    return true;
}

typedef struct MerkleState {
    buffer_t **hashlist[32];
    int hashlistlen;
    buffer_t **pending;
    int pendingLen;
    int pendingSize;
    int count;
} MerkleState;

Error MerkleState_DAGRoot(MerkleState *m, uint8_t mdroot[static 32]) {
    Error e = ErrorCode(ErrorNone);

    bool first = true;
    for (int i = 0; i < m->pendingLen; i++ ){ //_, v := range m.Pending {
        if (first) { // Pick up the first hash in m.MerkleState no matter what.
            first = false;
            memmove(mdroot, m->pending[i], 32);
            // = Hash(v).Copy() // If a nil is assigned over a nil, no harm no foul.  Fewer cases to test this way.
        } else if (m->pending[i] != 0 ) { // If MDRoot isn't nil and v isn't nil, combine them.
            // the pending hash is on the left, MDRoot candidate is on the right, for a new MDRoot
            uint8_t combine[64] = {0};
            memmove(combine, mdroot, 32);
            memmove(combine + 32, m->pending[i], 32 );
            e = sha256(combine, sizeof(combine), mdroot, 32);
            if (IsError(e) ) {
                return e;
            }
        }
    }
    return e;
}

Error MerkleState_PadPending(MerkleState *m) {
    int pendingLen = m->pendingLen;
    if ( pendingLen == 0 || m->pending[pendingLen-1] != 0) {
        //m.Pending = append(m.Pending, nil)
        m->pendingLen++;
    } else {
        return ErrorCode(ErrorInvalidHashParameters);
    }
    return ErrorCode(ErrorNone);
}

#if 0
void MerkleState_AddToMerkleTree(MerkleState *m, hash_ []byte) {
    //hash := Hash(hash_).Copy()
    //m.HashList = append(m.HashList, hash) // Add the new Hash to the Hash List
    m->count++;                             // Increment our total Hash Count
    MerkleState_PadPending(m);
    for (int i = 0; i < m->pendingLen; i++ ) {         // Adding the hash is like incrementing a variable
        if (m->pending[i] == 0) { //                     Look for an empty slot, and
           m->pending[i] = hash; //               And put the Hash there if one is found
           return;              //          Mission complete, so return
        }
        hash = Hash(v).Combine(Sha256, hash); // If this slot isn't empty, combine the hash with the slot
        m.Pending[i] = 0;                   //   and carry the result to the next (clearing this one)
        }




}

Error MerkleFieldHash(buffer_t **marshaledFieldBuffers, int numFieldBuffers) {
    uint8_t hash[32] = {0};
    Error e = ErrorCode(ErrorNone);
    for ( int i = 0; i < numFieldBuffers; i++ ) {
        e = sha256(marshaledFieldBuffers[i]->ptr+marshaledFieldBuffers[i]->offset,
               marshaledFieldBuffers[i]->size - marshaledFieldBuffers[i]->offset,
               hash, sizeof(hash));
        if (IsError(e)) {
            return e;
        }
    }
    bytes32 root = sha256(marshaledState);

    //compare the start of the proof and kick out if the hashes are not equal
    if ( root != start || entries.length > 64 ) {
        return false;
    }

    // Now apply all the path hashes to the root
    for (uint256 i = 0; i < entries.length; i++ )
    {
        if (lrBitfield & (1 << i) != 0) {
            // If this hash comes from the right, apply it that way
            root = sha256(abi.encodePacked(root,entries[i]));
            continue;
        }
        // If this hash comes from the left, apply it that way
        root = sha256(abi.encodePacked(entries[i],root));
    }


    return e;
}

#endif
