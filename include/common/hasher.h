#pragma once

#include "common/buffer.h"
#include "common/sha256.h"

#define MAX_PENDING 8
typedef struct MerkleState {
    buffer_t pending[MAX_PENDING];
    int pendingLen;
    int count;
    buffer_t arena;
    uint8_t hashes[MAX_PENDING*32];
} MerkleState;

void MerkleStateInit(MerkleState *m);

Error MerkleDAGRoot(MerkleState *m, uint8_t mdroot[static 32]);

int AddToMerkleTree(MerkleState *m, uint8_t hash_[static 32]);

int hasherAddHash(MerkleState *m, Bytes32 *v);
int hasherAddInt(MerkleState *m, int64_t v);
int hasherAddUint(MerkleState *m, uint64_t v);
int hasherAddBool(MerkleState *m, bool v);
int hasherAddBytes(MerkleState *m, Bytes *v);
int hasherAddString(MerkleState *m, String *v);
int hasherAddBigInt(MerkleState *m, BigInt *v);
int hasherAddVarInt(MerkleState *m, VarInt *v);
int hasherAddUVarInt(MerkleState *m, UVarInt *v);
int hasherAddUrl(MerkleState *m, Url *v);
int hasherAddEnum(MerkleState *m, int n);
