/*******************************************************************************
 *   Ledger Blue
 *   (c) 2016 Ledger
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
 ********************************************************************************/

// Adapted from https://github.com/calccrypto/uint256_t

#include <common/buffer.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct uint128_t {
    uint64_t elements[2];
} uint128_t;

typedef struct uint256_t {
    uint128_t elements[2];
} uint256_t;

#define UPPER_P(x) x->elements[0]
#define LOWER_P(x) x->elements[1]
#define UPPER(x)   x.elements[0]
#define LOWER(x)   x.elements[1]

void readu128BE(const uint8_t *buffer, uint128_t *target);
void readu256BE(const uint8_t *buffer, uint256_t *target);
void writeu256BE(const uint256_t *source, uint8_t *buffer);
void writeu128BE(const uint128_t *source, uint8_t *buffer);
bool zero128(const uint128_t *number);
bool zero256(const uint256_t *number);
void copy128(uint128_t *target, const uint128_t *number);
void copy256(uint256_t *target, const uint256_t *number);
void clear128(uint128_t *target);
void clear256(uint256_t *target);
void shiftl128(const uint128_t *number, uint32_t value, uint128_t *target);
void shiftr128(const uint128_t *number, uint32_t value, uint128_t *target);
void shiftl256(const uint256_t *number, uint32_t value, uint256_t *target);
void shiftr256(const uint256_t *number, uint32_t value, uint256_t *target);
uint32_t bits128(const uint128_t *number);
uint32_t bits256(const uint256_t *number);
bool equal128(const uint128_t *number1, const uint128_t *number2);
bool equal256(const uint256_t *number1, const uint256_t *number2);
bool gt128(const uint128_t *number1, const uint128_t *number2);
bool gt256(const uint256_t *number1, const uint256_t *number2);
bool gte128(const uint128_t *number1, const uint128_t *number2);
bool gte256(const uint256_t *number1, const uint256_t *number2);
void add128(const uint128_t *number1, const uint128_t *number2, uint128_t *target);
void add256(const uint256_t *number1, const uint256_t *number2, uint256_t *target);
void minus128(const uint128_t *number1, const uint128_t *number2, uint128_t *target);
void minus256(const uint256_t *number1, const uint256_t *number2, uint256_t *target);
void or128(const uint128_t *number1, const uint128_t *number2, uint128_t *target);
void or256(const uint256_t *number1, const uint256_t *number2, uint256_t *target);
void mul128(const uint128_t *number1, const uint128_t *number2, uint128_t *target);
void mul256(const uint256_t *number1, const uint256_t *number2, uint256_t *target);
void divmod128(const uint128_t *l, const uint128_t *r, uint128_t *div, uint128_t *mod);
void divmod256(const uint256_t *l, const uint256_t *r, uint256_t *div, uint256_t *mod);
bool tostring128(const uint128_t *number, uint32_t base, char *out, uint32_t outLength);
bool tostring256(const uint256_t *number, uint32_t base, char *out, uint32_t outLength);

/// returns the number of bytes populated in "out" or -1 on error.
int tobytes256(const uint256_t *number, uint8_t *out, uint32_t outLength);

void readu256LE(const uint8_t *buffer, uint256_t *target);
void readu128LE(const uint8_t *buffer, uint128_t *target);

int fromstring256(const char *in, size_t inLen, uint256_t *number);
int fromhex256(const char *in, size_t inLen, uint256_t *number);
int frombytes256(const uint8_t *in, size_t inLen, uint256_t *number);
int buffer_readu256BE(const buffer_t *b, uint256_t *target);
