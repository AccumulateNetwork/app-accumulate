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
#include <stddef.h>   // size_t
#include <stdbool.h>  // bool
#include <string.h>   // memmove

#include "os.h"
#include "cx.h"

#include "address.h"
#include "transaction/types.h"
#include "common/base58.h"
#include "common/sha256.h"
#include "common/keccak.h"


bool lite_address_from_pubkey(CoinType t,
                              pubkey_ctx_t *publicKey,
                              uint8_t *publicKeyOut, size_t *publicKeyLenInOut,
                              uint8_t *keyHashOut, size_t keyHashLen,
                              int8_t *keyNameOut, size_t keyNameLen,
                              int8_t *liteIdOut, size_t liteIdLen) {
    uint8_t address[32] = {0};
    Error e = resolvePublicKey(t, publicKey,
                     publicKeyOut, publicKeyLenInOut);
    if (IsError(e)) {
        return false;
    }
    switch (t) {
        case CoinTypeAcme:
            if ( *publicKeyLenInOut < 32 ) {
                return false;
            }

            sha256(publicKeyOut,*publicKeyLenInOut, keyHashOut, keyHashLen);
            if (!getLiteIdentityUrl(keyHashOut,keyHashLen,liteIdOut, liteIdLen)) {
                return false;
            }
            break;
        case CoinTypeFct:
            if ( *publicKeyLenInOut < 32 ) {
                return false;
            }

            getFctLiteAddress(publicKeyOut, publicKeyLenInOut,
                               keyHashOut, keyHashLen,
                               keyNameOut, keyNameLen,
                               liteIdOut, liteIdLen);
            break;
        case CoinTypeBtc: {
            if ( *publicKeyLenInOut < 32 ) {
                return false;
            }
            getBtcLiteIdentity(publicKeyOut, publicKeyLenInOut,
                               keyHashOut, keyHashLen,
                               keyNameOut, keyNameLen,
                               liteIdOut, liteIdLen);
        }   break;
        case CoinTypeEth:{
            if ( *publicKeyLenInOut < 64 ) {
                return false;
            }

            getEthLiteIdentity(publicKeyOut, publicKeyLenInOut,
                               keyHashOut, keyHashLen,
                               keyNameOut, keyNameLen,
                               liteIdOut,  liteIdLen);
        }   break;
        default:
            return false;
    };
    return true;
}

bool getEthLiteIdentity(uint8_t *publicKey, size_t *publicKeyLen,
        uint8_t *keyHash, size_t keyHashLen,
        int8_t *keyName, size_t keyNameLen,
        int8_t *liteId, size_t liteIdLen) {

    if (keyNameLen < ADDRESS_LEN) {
        return false;
    }

    if (liteIdLen < LITE_ADDRESS_LEN) {
        return false;
    }

    if (keyHashLen != 32) {
        return false;
    }

    if ( *publicKeyLen != 64 ) {
        return false;
    }

    //1) generate eth hash
    Error e = keccak(publicKey,64, keyHash, keyHashLen);
    if (IsError(e) ) {
        return false;
    }

    //2) encode the name address
    int offset = 0;
    for ( int i = 0; i < ADDRESS_LEN; ++i ) {
        snprintf((char*)&keyName[offset], keyNameLen - offset, "%02x", keyHash[i]);
        offset += 2;
    }

    //3) compute lite identity url.
    getLiteIdentityUrl(keyHash, keyNameLen - offset, liteId,liteIdLen);

    return true;
}

bool getBtcLiteIdentity(uint8_t *publicKey, size_t *publicKeyLen,
                        uint8_t *keyHash, size_t keyHashLen,
                        int8_t *keyName, size_t keyNameLen,
                        int8_t *liteId, size_t liteIdLen) {
    return true;
}


bool getAccLiteIdentity(uint8_t *publicKey, size_t *publicKeyLen,
                        uint8_t *keyHash, size_t keyHashLen,
                        int8_t *keyName, size_t keyNameLen,
                        int8_t *liteId, size_t liteIdLen) {
    return true;
}

bool getAcmeLiteAccountUrl(int8_t *liteIdUrl, uint8_t liteIdUrlLen) {

    if ( liteIdUrlLen < LITE_ADDRESS_LEN + strlen("/ACME")) {
        return false;
    }
    if ( strlen((char*)liteIdUrl) > ACME_LITE_ADDRESS_LEN ) {
        return false;
    }

    strncat((char*)liteIdUrl, "/ACME", liteIdUrlLen);
    return true;
}

bool getLiteIdentityUrl(const uint8_t *keyHash, uint8_t keyHashLen, int8_t *urlOut, size_t urlOutLen) {

    if ( keyHashLen < 20 ) {
        return false;
    }
    if ( urlOutLen < 54 ) {
        return false;
    }
    uint8_t checksum[32] = {0};
    //1) compute checksum
    sha256d(keyHash, 20, checksum, sizeof(checksum));

    //2) make url
    int offset = 6;
    strncpy((char*)urlOut, "acc://", offset);
    for ( int i = 0; i < 20; ++i ) {
        snprintf((char*)&urlOut[offset], urlOutLen - offset, "%02x", keyHash[i]);
        offset += 2;
    }
    snprintf((char*)&urlOut[offset], urlOutLen - offset, "%02x%02x%02x%02x", checksum[0], checksum[1],checksum[2],checksum[3]);

    return true;
}

bool getLiteTokenAccount(const int8_t *liteIdentity, size_t liteIdentityLen,
                         const int8_t *tokenUrl, size_t tokenUrlLen,
                         int8_t *urlOut, size_t urlOutLen) {

    return true;
}

Error resolvePublicKey( CoinType type, pubkey_ctx_t *publicKey,
        uint8_t *out, size_t *inoutlen)
{
    if ( *inoutlen < (type==CoinTypeEth?64:32) )
    {
        return ErrorCode(ErrorBufferTooSmall);
    }
    *inoutlen = type==CoinTypeEth?64:32;
    if ( publicKey->curve == CX_CURVE_256K1 )
    {
        memmove(out + 1, publicKey->W + 1, *inoutlen);
    }
    else if (publicKey->curve == CX_CURVE_Ed25519 && publicKey->W[0] != 0xED)
    {
        for (uint8_t i = 0; i < *inoutlen; i++)
        {
            out[i] = publicKey->W[64 - i];
        }
        if ((publicKey->W[32] & 1) != 0)
        {
            out[31] |= 0x80;
        }
    }
    else
    {
        return ErrorCode(ErrorInvalidObject);
    }

    return ErrorCode(ErrorNone);
}


//the key prefix code is byte swapped
const uint16_t g_factom_key_prefix[] = { 0xb15f, 0x7864, 0x2a59, 0xb65d };


void getFctAddressStringFromRCDHash(uint8_t *rcdhash,int8_t *out, keyType_t keytype)
{
    uint8_t address[38];

    if ( keytype < 0 || keytype > 3 )
    {
        THROW(BTCHIP_SW_INVALID_OFFSET);
    }

    *(uint16_t*)address = g_factom_key_prefix[keytype];

    memmove(address+2, rcdhash, 32);

    uint8_t checksum[32];
    sha256d(address, 34, checksum,sizeof(checksum));
    memmove(address+34, checksum, 4);

    base58_encode(address,38, out, 52);

}

void getFctAddressStringFromKey(cx_ecfp_public_key_t *publicKey, uint8_t *out,
                                keyType_t keytype) {
    uint8_t address[41];//FCT: prefix(2 bytes) + RCD_hash(32 bytes) + checksum(4 bytes)
    // EC: prefix(2 bytes) + Pub Key (32 bytes) + checksum(4 bytes)
    // ID: prefix(5 bytes) + Pub Key (32 bytes) + checksum(4 bytes)
    uint8_t checksum[32];

    uint8_t key_offset = (keytype == PUBLIC_OFFSET_ID) ? 5: 2;

    //https://github.com/FactomProject/FactomDocs/blob/master/factomDataStructureDetails.md

    //1) Concatenate 0x5fb1 and the RCD Hash bytewise
    if ( keytype == PUBLIC_OFFSET_FCT )
    {
        *(uint16_t*)address = g_factom_key_prefix[keytype];
        sha256d(publicKey->W, publicKey->W_len, &address[2],32);
    }
    else
    {
        if (keytype == PUBLIC_OFFSET_ID)
        {
            const uint8_t factom_id_prefix[] = { 0x03, 0x45, 0xef, 0x9d, 0xe0 };
            os_memmove(address, factom_id_prefix, key_offset);
        }
        else //LEDGER-REVIEW: check that keytype is not going out of bound when used as an index in g_factom_key_prefix
        {
            //ensure keytype doesn't go out of bounds for g_factom_key_prefix
            if ( keytype < 0 || keytype > 3 )
            {

                //THROW(INVALID_PARAMETER)
                THROW(BTCHIP_SW_INVALID_OFFSET);
            }
            *(uint16_t*)address = g_factom_key_prefix[keytype];
        }

        memmove(&address[key_offset], publicKey->W, publicKey->W_len);
    }


    //2) Take the SHA256d of the above data. Append the first 4 bytes of
    //   this SHA256d to the end of the above value bytewise
    sha256d(address, 32 + key_offset, checksum, sizeof(checksum));

    memmove(address + 32 + key_offset, checksum, 4);

    //3) Convert the above value from base 256 to base 58. Use standard
    //   Bitcoin base58 encoding to display the number
    base(address, 32 + 4 + key_offset, out, 50 + key_offset);
}

bool getFctLiteAddress(const uint8_t uncompressedPubKey[static 64],
                       uint8_t *pubKey, size_t *inoutPubKeyLen,
                       uint8_t *keyHash, size_t keyHashLen,
                       uint8_t *keyName, size_t keyNameLen,
                       int8_t *liteId, size_t liteIdLen) {
    if ( *inoutPubKeyLen < 32 || keyHashLen != 32 || keyNameLen < 52 ) {
        return false;
    }

    if ( *inoutPubKeyLen == 64 ) {
        //compress the key

    }
    *inoutPubKeyLen = 32;

    //2) compute rcd
    uint8_t rcd[33] = {0};
    rcd[0] = 0x01;
    memmove(&rcd[1], pubKey, *inoutPubKeyLen);

    //3) Hash rcd
    Error e = sha256(rcd,sizeof(rcd),keyHash, keyHashLen);
    if ( IsError(e) ) {
        return false;
    }

    //4) get fct label
    getFctAddressStringFromRCDHash(keyHash, keyName, keyNameLen);

    //5) compute lite identity url.
    getLiteIdentity(keyHash,liteId,liteIdLen);

    return true;
}

bool adjustDecimals(char *src, uint32_t srcLength, char *target,
                    uint32_t targetLength, uint8_t decimals)
{
    uint32_t startOffset;
    uint32_t lastZeroOffset = 0;
    uint32_t offset = 0;
    if ((srcLength == 1) && (*src == '0'))
    {
        if (targetLength < 2)
        {
            return false;
        }
        target[0] = '0';
        target[1] = '\0';
        return true;
    }
    if (srcLength <= decimals)
    {
        uint32_t delta = decimals - srcLength;
        if (targetLength < srcLength + 1 + 2 + delta)
        {
            return false;
        }
        target[offset++] = '0';
        target[offset++] = '.';
        for (uint32_t i = 0; i < delta; i++)
        {
            target[offset++] = '0';
        }
        startOffset = offset;
        for (uint32_t i = 0; i < srcLength; i++)
        {
            target[offset++] = src[i];
        }
        target[offset] = '\0';
    }
    else
    {
        uint32_t sourceOffset = 0;
        uint32_t delta = srcLength - decimals;
        if (targetLength < srcLength + 1 + 1)
        {
            return false;
        }
        while (offset < delta)
        {
            target[offset++] = src[sourceOffset++];
        }
        if (decimals != 0)
        {
            target[offset++] = '.';
        }
        startOffset = offset;
        while (sourceOffset < srcLength)
        {
            target[offset++] = src[sourceOffset++];
        }
        target[offset] = '\0';
    }
    for (uint32_t i = startOffset; i < offset; i++)
    {
        if (target[i] == '0')
        {
            if (lastZeroOffset == 0)
            {
                lastZeroOffset = i;
            }
        }
        else
        {
            lastZeroOffset = 0;
        }
    }
    if (lastZeroOffset != 0)
    {
        target[lastZeroOffset] = '\0';
        if (target[lastZeroOffset - 1] == '.')
        {
            target[lastZeroOffset - 1] = '\0';
        }
    }
    return true;
}

unsigned short fct_print_amount(uint64_t amount, int8_t *out,
                                uint32_t outlen)
{
    char tmp[20];
    char tmp2[25];
    uint32_t numDigits = 0, i;
    uint64_t base = 1;
    while (base <= amount)
    {
        base *= 10;
        numDigits++;
    }
    if (numDigits > sizeof(tmp) - 1)
    {
        THROW(EXCEPTION);
    }
    base /= 10;
    for (i = 0; i < numDigits; i++)
    {
        tmp[i] = '0' + ((amount / base) % 10);
        base /= 10;
    }
    tmp[i] = '\0';

    memmove(tmp2, "FCT ", 4); //"ғ"
    adjustDecimals(tmp, i, tmp2 + 4, 25, 8);
    if (strlen(tmp2) < outlen - 1)
    {
        strcpy(out, tmp2);
    }
    else
    {
        out[0] = '\0';
    }
    return strlen(out);
}

