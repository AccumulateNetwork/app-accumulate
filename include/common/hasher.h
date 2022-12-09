#pragma once

#include "common/buffer.h"
#include "common/sha256.h"

struct Bytes32;
struct Bytes;
struct BigInt;
struct VarInt;
struct UVarInt;
struct Url;
struct String;

#define MAX_PENDING 8
typedef struct MerkleState {
    buffer_t pending[MAX_PENDING];
    int pendingLen;
    int count;
    buffer_t arena;
    uint8_t hashes[MAX_PENDING * 32];
} MerkleState;

void MerkleStateInit(MerkleState *m);

Error MerkleDAGRoot(MerkleState *m, uint8_t mdroot[static 32]);

int AddToMerkleTree(MerkleState *m, uint8_t hash_[static 32]);

int hasherAddHash(MerkleState *m, struct Bytes32 *v);
int hasherAddInt(MerkleState *m, int64_t v);
int hasherAddUint(MerkleState *m, uint64_t v);
int hasherAddBool(MerkleState *m, bool v);
int hasherAddBytes(MerkleState *m, struct Bytes *v);
int hasherAddString(MerkleState *m, struct String *v);
int hasherAddBigInt(MerkleState *m, struct BigInt *v);
int hasherAddVarInt(MerkleState *m, struct VarInt *v);
int hasherAddUVarInt(MerkleState *m, struct UVarInt *v);
int hasherAddUrl(MerkleState *m, struct Url *v);
int hasherAddEnum(MerkleState *m, int n);
