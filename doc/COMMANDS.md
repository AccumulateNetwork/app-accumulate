# Accumulate commands

## Overview

| Command name | INS | Description |
| --- | --- | --- |
| `GET_VERSION` | 0x03 | Get application version as `MAJOR`, `MINOR`, `PATCH` |
| `GET_APP_NAME` | 0x04 | Get ASCII encoded application name |
| `GET_PUBLIC_KEY` | 0x05 | Get public key given BIP32 path |
| `SIGN_TX` | 0x06 | Sign transaction given BIP32 path and raw transaction |

## GET_VERSION

### Command

| CLA | INS | P1 | P2 | Lc | CData |
| --- | --- | --- | --- | --- | --- |
| 0xE0 | 0x03 | 0x00 | 0x00 | 0x00 | - |

### Response

| Response length (bytes) | SW | RData                                         |
| --- | --- |-----------------------------------------------|
| 3 | 0x9000 | `MAJOR` (1) <br> `MINOR` (1) <br> `PATCH` (1) |

## GET_APP_NAME

### Command

| CLA | INS | P1 | P2 | Lc | CData |
| --- | --- | --- | --- | --- | --- |
| 0xE0 | 0x04 | 0x00 | 0x00 | 0x00 | - |

### Response

| Response length (bytes) | SW | RData               |
| --- | --- |---------------------|
| var | 0x9000 | `APPNAME` (variable) |

## GET_PUBLIC_KEY

### Command

| CLA | INS | P1 | P2 | Lc | CData                                            |
| --- | --- | --- | --- | --- |--------------------------------------------------|
| 0xE0 | 0x05 | 0x00 (no display) <br> 0x01 (display) | 0x00 | 1 + 4n | `len(bip32_path)` (1) <br> `bip32_path{1}` (4) <br>`...` <br>`bip32_path{n}` (4) |

### Response

| Response length (bytes) | SW | RData                                                                                                                         |
|-------------------------| --- |-------------------------------------------------------------------------------------------------------------------------------|
| variable                | 0x9000 | `len(public_key)` (1) <br> `public_key` (variable) <br> `len(chain code)` (1) <br> `chain code` (32 bytes) <br> `len(derived key name)` (1) <br> `derived key name` (variable string) |

## SIGN_TX

### Command

| CLA  | INS | P1                                        | P2 | Lc | CData                                                                                                                                                                                                                                                                                            |
|------| --- |-------------------------------------------| --- | --- |--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0xE0 | 0x06 | 0x00 (first tx) <br> (0x01) (continue tx) | 0x00 (more) <br> 0x80 (last) | 1 + 4n | `len(bip32_path)` (1) <br> `bip32_path{1}` (4) <br>`...` <br>`bip32_path{n}` (4) <br> `serialized accumulate transaction envelope` (variable) |

The transaction envelope must contain one unsigned Signature structure and one corresponding Transaction structure. The firmware will compute the initiator hash and the transaction hash. If the intitator hash and transaction hash are provided, the computed hashes will be verified with what is provided. Additionally, if public key is provided, it will be compared with the key derived from the bip32 path as added verification. 
### Response

| Response length (bytes) | SW | RData                                                                            |
|-------------------------| --- |----------------------------------------------------------------------------------|
| variable                | 0x9000 | `len(signature)` (1) <br> `signature` (variable) <br> `v` (1) <br> `tx hash` (32) |

## GET_BLIND_SIGNING_TOKEN

### Command

| CLA | INS  | P1 | P2 | Lc   | CData |
| --- |------| --- | --- |------|-------|
| 0xE0 | 0x08 | 0x00 | 0x00 | 0x00 | -     |

### Response

| Response length (bytes) | SW | RData                                              |
|-------------------------| --- |----------------------------------------------------|
| 33                      | 0x9000 | `len(signing_token)` (1) <br> `signing_token` (32) |


## BLIND_SIGN_TX
### Command

| CLA  | INS  | P1                                        | P2 | Lc | CData                                                                                                                                                                   |
|------|------|-------------------------------------------| --- | --- |-------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0xE0 | 0x09 | 0x00 (first tx) <br> (0x01) (continue tx) | 0x00 (more) <br> 0x80 (last) | 1 + 4n | `len(bip32_path)` (1) <br> `bip32_path{1}` (4) <br>`...` <br>`bip32_path{n}` (4) <br> `signing_token` (32) <br> `serialized accumulate transaction envelope` (variable) |

This is the same as **SIGN_TX** however it will not prompt the user to confirm the transaction on the device if `siging_token` is valid. A `signing_token` can be obtained from **GET_BLIND_SIGNING_TOKEN**

### Response

| Response length (bytes) | SW | RData                                                                            |
|-------------------------| --- |----------------------------------------------------------------------------------|
| variable                | 0x9000 | `len(signature)` (1) <br> `signature` (variable) <br> `v` (1) <br> `tx hash` (32) |


## CLEAR_BLIND_SIGNING_TOKEN

### Command

| CLA | INS | P1 | P2 | Lc   | CData |
|------|------|------|------|------|-------|
| 0xE0 | 0x10 | 0x00 | 0x00 | 0x00 | -     |

### Response

| Response length (bytes) | SW | RData |
|-------------------------| --- |-------|
| variable                | 0x9000 | -     |


## Status Words

| SW     | SW name                       | Description                                                               |
|--------|-------------------------------|---------------------------------------------------------------------------|
| 0x6985 | `SW_DENY`                     | Rejected by user                                                          |
| 0x6A86 | `SW_WRONG_P1P2`               | Either `P1` or `P2` is incorrect                                          |
| 0x6A87 | `SW_WRONG_DATA_LENGTH`        | `Lc` or minimum APDU length is incorrect                                  |
| 0x6D00 | `SW_INS_NOT_SUPPORTED`        | No command exists with `INS`                                              |
| 0x6E00 | `SW_CLA_NOT_SUPPORTED`        | Bad `CLA` used for this application                                       |
| 0xAC01 | `ACC_REPLY_UNKNOWN`           | Unknown error from parsing accumulate transaction                         |
| 0xAC02 | `ACC_INVALID_ENUM`            | Incorrect enumeration while parsing transaction                           |
| 0xAC03 | `ACC_INVALID_OBJECT`          | Malformed transaction object                                              |
| 0xAC04 | `ACC_NOT_IMPLEMENTED`         | Accumulate transaction type currently not supported                       |
| 0xAC05 | `ACC_TYPE_NOT_FOUND`          | Transaction type is not a valid Accumulate type                           | 
| 0xAC06 | `ACC_PARAMETER_NIL`           | Unexpected empty parameter while parsing transaction                      |
| 0xAC07 | `ACC_INSUFFICIENT_DATA`       | Incomplete data for transaction                                           |
| 0xAC08 | `ACC_BAD_COPY`                | Cannot copy data from transaction                                         |
| 0xAC09 | `ACC_BUFFER_TOO_SMALL`        | Transaction size too large to fit in buffer                               |
| 0xAC0A | `ACC_BAD_VARINT_READ`         | Error processing variable sized integer in transaction                    |
| 0xAC0B | `ACC_BAD_VARINT_WRITE`        | Error converting integer to variable integer                              |
| 0xAC0C | `ACC_RESIZE_REQUIRED`         | Allocated buffer too small and requires resize                            |
| 0xAC0D | `ACC_INVALID_BIG_INT`         | Error converting transaction amount to big integer                        |
| 0xAC0E | `ACC_INVALID_STRING`          | Error parsing string in transaction                                       |
| 0xAC0F | `ACC_INVALID_HASH_PARAMETERS` | Invalid hash parameters provided to hash algorithm                        |
| 0xAC10 | `ACC_BAD_UVARINT_READ`        | Error processing variable sized unsigned integer                          |
| 0xAC11 | `ACC_BAD_UVARINT_WRITE`       | Error converting unsigned integer to variable unsigned integer            |
| 0xAC12 | `ACC_MEMPOOL_FULL`            | Internal pool for memory allocation is out of memory                      |
| 0xAC13 | `ACC_INVALID_OFFSET`          | Offset into buffer is invalid while processing transaction                |
| 0xAC14 | `ACC_INVALID_DATA`            | Data encountered while processing transaction is invalid                  |
| 0xAC15 | `ACC_BAD_KEY`                 | Parsed key is invalid or does not match what is expected                  |
| 0xAC16 | `ACC_INVALID_FIELD`           | Unexpected field type encountered by transaction parser                   |
| 0xAC17 | `ACC_EXPECTING_TYPE`          | Expecting type but received something else while processing transaction   |
| 0xAC18 | `ACC_RNG_FAIL`                | Failed obtaining random number for blind signing token |
| 0xB000 | `SW_WRONG_RESPONSE_LENGTH`    | Wrong response length (buffer size problem)                               |
| 0xB001 | `SW_DISPLAY_BIP32_PATH_FAIL`  | BIP32 path conversion to string failed                                    |
| 0xB002 | `SW_DISPLAY_ADDRESS_FAIL`     | Address conversion to string failed                                       |
| 0xB003 | `SW_DISPLAY_AMOUNT_FAIL`      | Amount conversion to string failed                                        |
| 0xB004 | `SW_WRONG_TX_LENGTH`          | Wrong raw transaction length                                              |
| 0xB005 | `SW_TX_PARSING_FAIL`          | Failed to parse raw transaction                                           |
| 0xB006 | `SW_TX_HASH_FAIL`             | Failed to compute hash digest of raw transaction                          |
| 0xB007 | `SW_BAD_STATE`                | Security issue with bad state                                             |
| 0xB008 | `SW_SIGNATURE_FAIL`           | Signature of raw transaction failed                                       |
| 0x9000 | `OK`                          | Success                                                                   |

