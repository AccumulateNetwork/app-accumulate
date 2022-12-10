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

#include "address.h"

#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include <stdint.h>   // uint*_t
#include <stdlib.h>
#include <string.h>  // memmove

#include "common/base58.h"
#include "common/keccak.h"
#include "common/sha256.h"
#include "crypto.h"
#include "cx.h"
#include "lcx_ripemd160.h"
#include "os.h"
#include "transaction/types.h"

Error lite_address_from_pubkey(CoinType t, pubkey_ctx_t *publicKey) {
    Error ret;
    switch (t) {
        case CoinTypeAcme:
            ret = getLiteAcmeAddress(publicKey);
            break;
        case CoinTypeFct:
            ret = getFctLiteAddress(publicKey);
            break;
        case CoinTypeBtc: {
            ret = getBtcLiteIdentity(publicKey);
        } break;
        case CoinTypeEth: {
            ret = getEthLiteIdentity(publicKey);
        } break;
        default:
            ret = ErrorCode(ErrorUnknown);
    };
    return ret;
}

Error getEthLiteIdentity(pubkey_ctx_t *publicKey) {
    if (publicKey->public_key_length != 65) {
        return ErrorCode(ErrorBadKey);
    }

    // 1) generate eth hash
    uint8_t hash[32] = {0};
    Error e = keccak(publicKey->raw_public_key + 1, 64, hash, sizeof(hash));
    if (IsError(e)) {
        return e;
    }
    memmove(publicKey->hash, &hash[sizeof(hash) - ADDRESS_LEN], ADDRESS_LEN);
    publicKey->hashLength = ADDRESS_LEN;

    explicit_bzero(publicKey->address_name, sizeof(publicKey->address_name));
    // 2) encode the name address
    int offset = 2;
    publicKey->address_name[0] = '0';
    publicKey->address_name[1] = 'x';
    for (int i = 0; i < ADDRESS_LEN; ++i) {
        snprintf((char *) &publicKey->address_name[offset],
                 sizeof(publicKey->address_name) - offset,
                 "%02x",
                 publicKey->hash[i]);
        offset += 2;
    }

    // 3) compute lite identity url.
    e = getLiteIdentityUrl(publicKey->hash,
                           publicKey->hashLength,
                           publicKey->lite_account,
                           sizeof(publicKey->lite_account));
    return e;
}

Error getBtcLiteIdentity(pubkey_ctx_t *publicKey) {
    if (publicKey->public_key_length != 33) {
        return ErrorCode(ErrorBadKey);
    }
    explicit_bzero(publicKey->address_name, sizeof(publicKey->address_name));

    uint8_t hash[32] = {0};
    sha256(publicKey->raw_public_key, publicKey->public_key_length, hash, sizeof(hash));

    uint8_t pubRip[CX_RIPEMD160_SIZE + 1 + 4] = {
        0};  // 20 bytes for hash, 1 byte for version, 4 bytes for checksum
    // cx_hash_ripemd160(hash, sizeof(hash), pubRip+1, 20);
    crypto_ripemd160(hash, sizeof(hash), pubRip + 1);
    // create a legacy btc address
    sha256d(pubRip, CX_RIPEMD160_SIZE + 1, hash, sizeof(hash));
    for (int i = 0; i < 4; ++i) {
        pubRip[21 + i] = hash[i];
    }

    memmove(publicKey->hash, pubRip + 1, CX_RIPEMD160_SIZE);
    publicKey->hashLength = CX_RIPEMD160_SIZE;

    base58_encode(pubRip, sizeof(pubRip), publicKey->address_name, sizeof(publicKey->address_name));

    return getLiteIdentityUrl(pubRip + 1,
                              20,
                              publicKey->lite_account,
                              sizeof publicKey->lite_account);
}

bool getAcmeLiteAccountUrl(int8_t *liteIdUrl, uint8_t liteIdUrlLen) {
    if (liteIdUrlLen < LITE_ADDRESS_LEN + strlen("/ACME")) {
        return false;
    }
    if (strlen((char *) liteIdUrl) > ACME_LITE_ADDRESS_LEN) {
        return false;
    }

    strncat((char *) liteIdUrl, "/ACME", liteIdUrlLen);
    return true;
}

Error getLiteIdentityUrl(const uint8_t *keyHash,
                         uint8_t keyHashLen,
                         char *urlOut,
                         size_t urlOutLen) {
    if (keyHashLen < ADDRESS_LEN) {
        return ErrorCode(ErrorInvalidHashParameters);
    }
    if (urlOutLen < 54) {
        return ErrorCode(ErrorBufferTooSmall);
    }
    uint8_t checksum[32] = {0};

    // 2) make url
    const int schemeOffset = 6;
    int offset = schemeOffset;
    snprintf(urlOut, urlOutLen, "acc://");
    for (int i = 0; i < 20; ++i) {
        snprintf((char *) &urlOut[offset], urlOutLen - offset, "%02x", keyHash[i]);
        offset += 2;
    }
    // 1) compute checksum of identity
    sha256((uint8_t *) &urlOut[schemeOffset], offset - schemeOffset, checksum, sizeof(checksum));

    snprintf((char *) &urlOut[offset],
             urlOutLen - offset,
             "%02x%02x%02x%02x",
             checksum[28],
             checksum[29],
             checksum[30],
             checksum[31]);

    return ErrorCode(ErrorNone);
}

Error getFctAddressStringFromRCDHash(uint8_t *rcdhash, char *out, int8_t outLen) {
    uint8_t address[38];

    *(uint16_t *) address = 0xb15f;

    memmove(address + 2, rcdhash, 32);

    uint8_t checksum[32];
    sha256d(address, 34, checksum, sizeof(checksum));
    memmove(address + 34, checksum, 4);

    if (outLen < 52) {
        return ErrorCode(ErrorBufferTooSmall);
    }

    base58_encode(address, 38, (char *) out, 52);

    return ErrorCode(ErrorNone);
}

Error encodeMultihash(const uint8_t *hash, uint8_t hashLength, char *out, uint8_t outLength) {
    const uint64_t multihash_identity = 0;
    uint8_t multiHash[MAX_HASH_LENGTH + 16] = {0};
    int n = uvarint_write(multiHash, 0, multihash_identity);
    n += uvarint_write(multiHash, n, (uint64_t) hashLength);
    memmove(&multiHash[n], hash, hashLength);
    explicit_bzero(out, outLength);
    return getNamedAddress("MHz", 3, multiHash, n + hashLength, out, outLength);
}

Error getNamedAddress(const char *prefix,
                      uint8_t prefixLength,
                      const uint8_t *hash,
                      uint8_t hashLength,
                      char *out,
                      uint8_t outLength) {
    if (prefixLength > MAX_PREFIX_LENGTH) {
        return ErrorCode(ErrorInvalidString);
    }

    if (hashLength > MAX_HASH_LENGTH) {
        return ErrorCode(ErrorInvalidHashParameters);
    }

    // Prepare Checksum
    uint8_t ac1[MAX_PREFIX_LENGTH + MAX_HASH_LENGTH + CHECKSUM_LEN] = {0};

    memmove(ac1, prefix, prefixLength);
    memmove(&ac1[prefixLength], hash, hashLength);

    // compute checksum
    {
        uint8_t checksum[32];
        sha256d(ac1, prefixLength + hashLength, checksum, sizeof(checksum));
        memmove(ac1 + prefixLength + hashLength, checksum, CHECKSUM_LEN);
    }

    // encode address
    explicit_bzero(out, outLength);
    memmove(out, prefix, prefixLength);

    int ret = base58_encode(&ac1[prefixLength],
                            hashLength + CHECKSUM_LEN,
                            (char *) &out[prefixLength],
                            outLength);
    if (ret < 0) {
        return ErrorCode(ErrorInvalidObject);
    }

    return ErrorCode(ErrorNone);
}

Error getLiteAcmeAddress(pubkey_ctx_t *publicKey) {
    if (publicKey->public_key_length != 32) {
        return ErrorCode(ErrorBadKey);
    }

    // Compute Key Hash
    publicKey->hashLength = sizeof(publicKey->hash);
    Error e = sha256(publicKey->raw_public_key,
                     publicKey->public_key_length,
                     publicKey->hash,
                     sizeof(publicKey->hash));
    if (IsError(e)) {
        return e;
    }

    e = getNamedAddress("AC1",
                        3,
                        publicKey->hash,
                        sizeof(publicKey->hash),
                        publicKey->address_name,
                        sizeof(publicKey->address_name));
    if (IsError(e)) {
        return e;
    }

    e = getLiteIdentityUrl(publicKey->hash,
                           sizeof(publicKey->hash),
                           publicKey->lite_account,
                           sizeof(publicKey->lite_account));
    if (IsError(e)) {
        return e;
    }

    return ErrorCode(ErrorNone);
}

Error getFctLiteAddress(pubkey_ctx_t *publicKey) {
    if (publicKey->public_key_length != 32) {
        return ErrorCode(ErrorBadKey);
    }

    // 2) compute rcd
    uint8_t rcd[33] = {0};
    rcd[0] = 0x01;
    memmove(&rcd[1], publicKey->raw_public_key, publicKey->public_key_length);

    // 3) Hash rcd
    publicKey->hashLength = sizeof(publicKey->hash);
    Error e = sha256(rcd, sizeof(rcd), publicKey->hash, publicKey->hashLength);
    if (IsError(e)) {
        return e;
    }

    // 4) get fct label
    e = getFctAddressStringFromRCDHash(publicKey->hash,
                                       publicKey->address_name,
                                       sizeof(publicKey->address_name));
    if (IsError(e)) {
        return e;
    }
    // 5) compute lite identity url.
    e = getLiteIdentityUrl(publicKey->hash,
                           sizeof(publicKey->hash),
                           publicKey->lite_account,
                           sizeof publicKey->lite_account);
    if (IsError(e)) {
        return e;
    }

    return ErrorCode(ErrorNone);
}

bool adjustDecimals(const char *src,
                    uint32_t srcLength,
                    char *target,
                    uint32_t targetLength,
                    uint8_t decimals) {
    uint32_t startOffset;
    uint32_t lastZeroOffset = 0;
    uint32_t offset = 0;
    if ((srcLength == 1) && (*src == '0')) {
        if (targetLength < 2) {
            return false;
        }
        target[0] = '0';
        target[1] = '\0';
        return true;
    }
    if (srcLength <= decimals) {
        uint32_t delta = decimals - srcLength;
        if (targetLength < srcLength + 1 + 2 + delta) {
            return false;
        }
        target[offset++] = '0';
        target[offset++] = '.';
        for (uint32_t i = 0; i < delta; i++) {
            target[offset++] = '0';
        }
        startOffset = offset;
        for (uint32_t i = 0; i < srcLength; i++) {
            target[offset++] = src[i];
        }
        target[offset] = '\0';
    } else {
        uint32_t sourceOffset = 0;
        uint32_t delta = srcLength - decimals;
        if (targetLength < srcLength + 1 + 1) {
            return false;
        }
        while (offset < delta) {
            target[offset++] = src[sourceOffset++];
        }
        if (decimals != 0) {
            target[offset++] = '.';
        }
        startOffset = offset;
        while (sourceOffset < srcLength) {
            target[offset++] = src[sourceOffset++];
        }
        target[offset] = '\0';
    }
    for (uint32_t i = startOffset; i < offset; i++) {
        if (target[i] == '0') {
            if (lastZeroOffset == 0) {
                lastZeroOffset = i;
            }
        } else {
            lastZeroOffset = 0;
        }
    }
    if (lastZeroOffset != 0) {
        target[lastZeroOffset] = '\0';
        if (target[lastZeroOffset - 1] == '.') {
            target[lastZeroOffset - 1] = '\0';
        }
    }
    return true;
}
