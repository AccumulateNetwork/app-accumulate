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
#include <common/read.h>
#include <common/uint256.h>
#include <stdio.h>
#include <string.h>

static const char HEXDIGITS[] = "0123456789abcdef";

int buffer_readu256BE(const buffer_t *b, uint256_t *target) {
    uint8_t fillBytes[32] = {};
    int bsize = (int) (b->size - b->offset);
    if (bsize > (int) sizeof(fillBytes)) {
        return -1;
    }
    for (int i = bsize - 1, j = 0; i >= 0; i--, j++) {
        fillBytes[i] = b->ptr[b->offset + j];
    }
    readu256BE(fillBytes, target);
    return bsize;
}

static uint64_t readUint64BE(const uint8_t *buffer) {
    return (((uint64_t) buffer[0]) << 56) | (((uint64_t) buffer[1]) << 48) |
           (((uint64_t) buffer[2]) << 40) | (((uint64_t) buffer[3]) << 32) |
           (((uint64_t) buffer[4]) << 24) | (((uint64_t) buffer[5]) << 16) |
           (((uint64_t) buffer[6]) << 8) | (((uint64_t) buffer[7]));
}

void writeu64BE(uint64_t r, uint8_t *buffer) {
    buffer[0] = (uint8_t) (r >> 56);
    buffer[1] = (uint8_t) (r >> 48);
    buffer[2] = (uint8_t) (r >> 40);
    buffer[3] = (uint8_t) (r >> 32);
    buffer[4] = (uint8_t) (r >> 24);
    buffer[5] = (uint8_t) (r >> 16);
    buffer[6] = (uint8_t) (r >> 8);
    buffer[7] = (uint8_t) (r);
}

void readu128LE(const uint8_t *buffer, uint128_t *target) {
    UPPER_P(target) = read_u64_le(buffer, 0);
    LOWER_P(target) = read_u64_le(buffer, 8);
}

void readu128BE(const uint8_t *buffer, uint128_t *target) {
    UPPER_P(target) = readUint64BE(buffer);
    LOWER_P(target) = readUint64BE(buffer + 8);
}

void readu256LE(const uint8_t *buffer, uint256_t *target) {
    readu128LE(buffer, &UPPER_P(target));
    readu128LE(buffer + 16, &LOWER_P(target));
}

void readu256BE(const uint8_t *buffer, uint256_t *target) {
    readu128BE(buffer, &UPPER_P(target));
    readu128BE(buffer + 16, &LOWER_P(target));
}

void writeu128BE(const uint128_t *source, uint8_t *buffer) {
    writeu64BE(UPPER_P(source), buffer);
    writeu64BE(LOWER_P(source), buffer + 8);
}

void writeu256BE(const uint256_t *source, uint8_t *buffer) {
    writeu128BE(&UPPER_P(source), buffer);
    writeu128BE(&LOWER_P(source), buffer + 16);
}

bool zero128(const uint128_t *number) {
    return ((LOWER_P(number) == 0) && (UPPER_P(number) == 0));
}

bool zero256(const uint256_t *number) {
    return (zero128(&LOWER_P(number)) && zero128(&UPPER_P(number)));
}

void copy128(uint128_t *target, const uint128_t *number) {
    UPPER_P(target) = UPPER_P(number);
    LOWER_P(target) = LOWER_P(number);
}

void copy256(uint256_t *target, const uint256_t *number) {
    copy128(&UPPER_P(target), &UPPER_P(number));
    copy128(&LOWER_P(target), &LOWER_P(number));
}

void clear128(uint128_t *target) {
    UPPER_P(target) = 0;
    LOWER_P(target) = 0;
}

void clear256(uint256_t *target) {
    clear128(&UPPER_P(target));
    clear128(&LOWER_P(target));
}

void shiftl128(const uint128_t *number, uint32_t value, uint128_t *target) {
    if (value >= 128) {
        clear128(target);
    } else if (value == 64) {
        UPPER_P(target) = LOWER_P(number);
        LOWER_P(target) = 0;
    } else if (value == 0) {
        copy128(target, number);
    } else if (value < 64) {
        UPPER_P(target) = (UPPER_P(number) << value) + (LOWER_P(number) >> (64 - value));
        LOWER_P(target) = (LOWER_P(number) << value);
    } else if ((128 > value) && (value > 64)) {
        UPPER_P(target) = LOWER_P(number) << (value - 64);
        LOWER_P(target) = 0;
    } else {
        clear128(target);
    }
}

void shiftl256(const uint256_t *number, uint32_t value, uint256_t *target) {
    if (value >= 256) {
        clear256(target);
    } else if (value == 128) {
        copy128(&UPPER_P(target), &LOWER_P(number));
        clear128(&LOWER_P(target));
    } else if (value == 0) {
        copy256(target, number);
    } else if (value < 128) {
        uint128_t tmp1;
        uint128_t tmp2;
        uint256_t result;
        shiftl128(&UPPER_P(number), value, &tmp1);
        shiftr128(&LOWER_P(number), (128 - value), &tmp2);
        add128(&tmp1, &tmp2, &UPPER(result));
        shiftl128(&LOWER_P(number), value, &LOWER(result));
        copy256(target, &result);
    } else if ((256 > value) && (value > 128)) {
        shiftl128(&LOWER_P(number), (value - 128), &UPPER_P(target));
        clear128(&LOWER_P(target));
    } else {
        clear256(target);
    }
}

void shiftr128(const uint128_t *number, uint32_t value, uint128_t *target) {
    if (value >= 128) {
        clear128(target);
    } else if (value == 64) {
        UPPER_P(target) = 0;
        LOWER_P(target) = UPPER_P(number);
    } else if (value == 0) {
        copy128(target, number);
    } else if (value < 64) {
        uint128_t result;
        UPPER(result) = UPPER_P(number) >> value;
        LOWER(result) = (UPPER_P(number) << (64 - value)) + (LOWER_P(number) >> value);
        copy128(target, &result);
    } else if ((128 > value) && (value > 64)) {
        LOWER_P(target) = UPPER_P(number) >> (value - 64);
        UPPER_P(target) = 0;
    } else {
        clear128(target);
    }
}

void shiftr256(const uint256_t *number, uint32_t value, uint256_t *target) {
    if (value >= 256) {
        clear256(target);
    } else if (value == 128) {
        copy128(&LOWER_P(target), &UPPER_P(number));
        clear128(&UPPER_P(target));
    } else if (value == 0) {
        copy256(target, number);
    } else if (value < 128) {
        uint128_t tmp1;
        uint128_t tmp2;
        uint256_t result;
        shiftr128(&UPPER_P(number), value, &UPPER(result));
        shiftr128(&LOWER_P(number), value, &tmp1);
        shiftl128(&UPPER_P(number), (128 - value), &tmp2);
        add128(&tmp1, &tmp2, &LOWER(result));
        copy256(target, &result);
    } else if ((256 > value) && (value > 128)) {
        shiftr128(&UPPER_P(number), (value - 128), &LOWER_P(target));
        clear128(&UPPER_P(target));
    } else {
        clear256(target);
    }
}

uint32_t bits128(const uint128_t *number) {
    uint32_t result = 0;
    if (UPPER_P(number)) {
        uint64_t up = UPPER_P(number);
        result = 64;
        while (up) {
            up >>= 1;
            result++;
        }
    } else {
        uint64_t low = LOWER_P(number);
        while (low) {
            low >>= 1;
            result++;
        }
    }
    return result;
}

uint32_t bits256(const uint256_t *number) {
    uint32_t result = 0;
    if (!zero128(&UPPER_P(number))) {
        uint128_t up;
        result = 128;
        copy128(&up, &UPPER_P(number));
        while (!zero128(&up)) {
            shiftr128(&up, 1, &up);
            result++;
        }
    } else {
        uint128_t low;
        copy128(&low, &LOWER_P(number));
        while (!zero128(&low)) {
            shiftr128(&low, 1, &low);
            result++;
        }
    }
    return result;
}

bool equal128(const uint128_t *number1, const uint128_t *number2) {
    return (UPPER_P(number1) == UPPER_P(number2)) && (LOWER_P(number1) == LOWER_P(number2));
}

bool equal256(const uint256_t *number1, const uint256_t *number2) {
    return (equal128(&UPPER_P(number1), &UPPER_P(number2)) &&
            equal128(&LOWER_P(number1), &LOWER_P(number2)));
}

bool gt128(const uint128_t *number1, const uint128_t *number2) {
    if (UPPER_P(number1) == UPPER_P(number2)) {
        return (LOWER_P(number1) > LOWER_P(number2));
    }
    return (UPPER_P(number1) > UPPER_P(number2));
}

bool gt256(const uint256_t *number1, const uint256_t *number2) {
    if (equal128(&UPPER_P(number1), &UPPER_P(number2))) {
        return gt128(&LOWER_P(number1), &LOWER_P(number2));
    }
    return gt128(&UPPER_P(number1), &UPPER_P(number2));
}

bool gte128(const uint128_t *number1, const uint128_t *number2) {
    return gt128(number1, number2) || equal128(number1, number2);
}

bool gte256(const uint256_t *number1, const uint256_t *number2) {
    return gt256(number1, number2) || equal256(number1, number2);
}

void add128(const uint128_t *number1, const uint128_t *number2, uint128_t *target) {
    UPPER_P(target) = UPPER_P(number1) + UPPER_P(number2) +
                      ((LOWER_P(number1) + LOWER_P(number2)) < LOWER_P(number1));
    LOWER_P(target) = LOWER_P(number1) + LOWER_P(number2);
}

void add256(const uint256_t *number1, const uint256_t *number2, uint256_t *target) {
    uint128_t tmp;
    add128(&UPPER_P(number1), &UPPER_P(number2), &UPPER_P(target));
    add128(&LOWER_P(number1), &LOWER_P(number2), &tmp);
    if (gt128(&LOWER_P(number1), &tmp)) {
        uint128_t one;
        UPPER(one) = 0;
        LOWER(one) = 1;
        add128(&UPPER_P(target), &one, &UPPER_P(target));
    }
    add128(&LOWER_P(number1), &LOWER_P(number2), &LOWER_P(target));
}

void minus128(const uint128_t *number1, const uint128_t *number2, uint128_t *target) {
    UPPER_P(target) = UPPER_P(number1) - UPPER_P(number2) -
                      ((LOWER_P(number1) - LOWER_P(number2)) > LOWER_P(number1));
    LOWER_P(target) = LOWER_P(number1) - LOWER_P(number2);
}

void minus256(const uint256_t *number1, const uint256_t *number2, uint256_t *target) {
    uint128_t tmp;
    minus128(&UPPER_P(number1), &UPPER_P(number2), &UPPER_P(target));
    minus128(&LOWER_P(number1), &LOWER_P(number2), &tmp);
    if (gt128(&tmp, &LOWER_P(number1))) {
        uint128_t one;
        UPPER(one) = 0;
        LOWER(one) = 1;
        minus128(&UPPER_P(target), &one, &UPPER_P(target));
    }
    minus128(&LOWER_P(number1), &LOWER_P(number2), &LOWER_P(target));
}

void or128(const uint128_t *number1, const uint128_t *number2, uint128_t *target) {
    UPPER_P(target) = UPPER_P(number1) | UPPER_P(number2);
    LOWER_P(target) = LOWER_P(number1) | LOWER_P(number2);
}

void or256(const uint256_t *number1, const uint256_t *number2, uint256_t *target) {
    or128(&UPPER_P(number1), &UPPER_P(number2), &UPPER_P(target));
    or128(&LOWER_P(number1), &LOWER_P(number2), &LOWER_P(target));
}

void mul128(const uint128_t *number1, const uint128_t *number2, uint128_t *target) {
    uint64_t top[4];
    uint64_t bottom[4];
    uint64_t products[4][4];
    uint128_t tmp, tmp2;
    uint64_t fourth32, third32, second32, first32;
    int y = 0;

    top[0] = UPPER_P(number1) >> 32;
    top[1] = UPPER_P(number1) & 0xffffffff;
    top[2] = LOWER_P(number1) >> 32;
    top[3] = LOWER_P(number1) & 0xffffffff;
    bottom[0] = UPPER_P(number2) >> 32;
    bottom[1] = UPPER_P(number2) & 0xffffffff;
    bottom[2] = LOWER_P(number2) >> 32;
    bottom[3] = LOWER_P(number2) & 0xffffffff;

    for (y = 3; y > -1; y--) {
        int x = 0;
        for (x = 3; x > -1; x--) {
            products[3 - x][y] = top[x] * bottom[y];
        }
    }
    {
        fourth32 = products[0][3] & 0xffffffff;
        third32 = (products[0][2] & 0xffffffff) + (products[0][3] >> 32);
        second32 = (products[0][1] & 0xffffffff) + (products[0][2] >> 32);
        first32 = (products[0][0] & 0xffffffff) + (products[0][1] >> 32);

        third32 += products[1][3] & 0xffffffff;
        second32 += (products[1][2] & 0xffffffff) + (products[1][3] >> 32);
        first32 += (products[1][1] & 0xffffffff) + (products[1][2] >> 32);

        second32 += products[2][3] & 0xffffffff;
        first32 += (products[2][2] & 0xffffffff) + (products[2][3] >> 32);

        first32 += products[3][3] & 0xffffffff;

        UPPER(tmp) = first32 << 32;
        LOWER(tmp) = 0;
        UPPER(tmp2) = third32 >> 32;
        LOWER(tmp2) = third32 << 32;
        add128(&tmp, &tmp2, target);
        UPPER(tmp) = second32;
        LOWER(tmp) = 0;
        add128(&tmp, target, &tmp2);
        UPPER(tmp) = 0;
        LOWER(tmp) = fourth32;
        add128(&tmp, &tmp2, target);
    }
}

void mul256(const uint256_t *number1, const uint256_t *number2, uint256_t *target) {
    uint128_t top[4];
    uint128_t bottom[4];
    uint128_t products[4][4];
    uint128_t tmp, tmp2, fourth64, third64, second64, first64;
    uint256_t target1, target2;
    int y = 0;
    int x = 0;
    UPPER(top[0]) = 0;
    LOWER(top[0]) = UPPER(UPPER_P(number1));
    UPPER(top[1]) = 0;
    LOWER(top[1]) = LOWER(UPPER_P(number1));
    UPPER(top[2]) = 0;
    LOWER(top[2]) = UPPER(LOWER_P(number1));
    UPPER(top[3]) = 0;
    LOWER(top[3]) = LOWER(LOWER_P(number1));
    UPPER(bottom[0]) = 0;
    LOWER(bottom[0]) = UPPER(UPPER_P(number2));
    UPPER(bottom[1]) = 0;
    LOWER(bottom[1]) = LOWER(UPPER_P(number2));
    UPPER(bottom[2]) = 0;
    LOWER(bottom[2]) = UPPER(LOWER_P(number2));
    UPPER(bottom[3]) = 0;
    LOWER(bottom[3]) = LOWER(LOWER_P(number2));

    for (y = 3; y > -1; y--) {
        for (x = 3; x > -1; x--) {
            mul128(&top[x], &bottom[y], &products[3 - x][y]);
        }
    }

    UPPER(fourth64) = 0;
    LOWER(fourth64) = LOWER(products[0][3]);
    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[0][2]);
    UPPER(tmp2) = 0;
    LOWER(tmp2) = UPPER(products[0][3]);
    add128(&tmp, &tmp2, &third64);
    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[0][1]);
    UPPER(tmp2) = 0;
    LOWER(tmp2) = UPPER(products[0][2]);
    add128(&tmp, &tmp2, &second64);
    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[0][0]);
    UPPER(tmp2) = 0;
    LOWER(tmp2) = UPPER(products[0][1]);
    add128(&tmp, &tmp2, &first64);

    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[1][3]);
    add128(&tmp, &third64, &tmp2);
    copy128(&third64, &tmp2);
    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[1][2]);
    add128(&tmp, &second64, &tmp2);
    UPPER(tmp) = 0;
    LOWER(tmp) = UPPER(products[1][3]);
    add128(&tmp, &tmp2, &second64);
    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[1][1]);
    add128(&tmp, &first64, &tmp2);
    UPPER(tmp) = 0;
    LOWER(tmp) = UPPER(products[1][2]);
    add128(&tmp, &tmp2, &first64);

    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[2][3]);
    add128(&tmp, &second64, &tmp2);
    copy128(&second64, &tmp2);
    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[2][2]);
    add128(&tmp, &first64, &tmp2);
    UPPER(tmp) = 0;
    LOWER(tmp) = UPPER(products[2][3]);
    add128(&tmp, &tmp2, &first64);

    UPPER(tmp) = 0;
    LOWER(tmp) = LOWER(products[3][3]);
    add128(&tmp, &first64, &tmp2);
    copy128(&first64, &tmp2);

    clear256(&target1);
    shiftl128(&first64, 64, &UPPER(target1));
    clear256(&target2);
    UPPER(UPPER(target2)) = UPPER(third64);
    shiftl128(&third64, 64, &LOWER(target2));
    add256(&target1, &target2, target);
    clear256(&target1);
    copy128(&UPPER(target1), &second64);
    add256(&target1, target, &target2);
    clear256(&target1);
    copy128(&LOWER(target1), &fourth64);
    add256(&target1, &target2, target);
}

void divmod128(const uint128_t *l, const uint128_t *r, uint128_t *retDiv, uint128_t *retMod) {
    uint128_t copyd, adder, resDiv, resMod;
    uint128_t one;
    uint32_t diffBits = 0;
    UPPER(one) = 0;
    LOWER(one) = 1;
    diffBits = bits128(l) - bits128(r);
    clear128(&resDiv);
    copy128(&resMod, l);
    if (gt128(r, l)) {
        copy128(retMod, l);
        clear128(retDiv);
    } else {
        shiftl128(r, diffBits, &copyd);
        shiftl128(&one, diffBits, &adder);
        if (gt128(&copyd, &resMod)) {
            shiftr128(&copyd, 1, &copyd);
            shiftr128(&adder, 1, &adder);
        }
        while (gte128(&resMod, r)) {
            if (gte128(&resMod, &copyd)) {
                minus128(&resMod, &copyd, &resMod);
                or128(&resDiv, &adder, &resDiv);
            }
            shiftr128(&copyd, 1, &copyd);
            shiftr128(&adder, 1, &adder);
        }
        copy128(retDiv, &resDiv);
        copy128(retMod, &resMod);
    }
}

void divmod256(const uint256_t *l, const uint256_t *r, uint256_t *retDiv, uint256_t *retMod) {
    uint256_t copyd, adder, resDiv, resMod;
    uint32_t diffBits = 0;
    uint256_t one;
    clear256(&one);
    UPPER(LOWER(one)) = 0;
    LOWER(LOWER(one)) = 1;
    diffBits = bits256(l) - bits256(r);
    clear256(&resDiv);
    copy256(&resMod, l);
    if (gt256(r, l)) {
        copy256(retMod, l);
        clear256(retDiv);
    } else {
        shiftl256(r, diffBits, &copyd);
        shiftl256(&one, diffBits, &adder);
        if (gt256(&copyd, &resMod)) {
            shiftr256(&copyd, 1, &copyd);
            shiftr256(&adder, 1, &adder);
        }
        while (gte256(&resMod, r)) {
            if (gte256(&resMod, &copyd)) {
                minus256(&resMod, &copyd, &resMod);
                or256(&resDiv, &adder, &resDiv);
            }
            shiftr256(&copyd, 1, &copyd);
            shiftr256(&adder, 1, &adder);
        }
        copy256(retDiv, &resDiv);
        copy256(retMod, &resMod);
    }
}

static void reverseString(char *str, uint32_t length) {
    uint32_t i, j;
    for (i = 0, j = length - 1; i < j; i++, j--) {
        uint8_t c;
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

bool tostring128(const uint128_t *number, uint32_t baseParam, char *out, uint32_t outLength) {
    uint128_t rDiv;
    uint128_t rMod;
    uint128_t base;
    uint32_t offset = 0;
    copy128(&rDiv, number);
    clear128(&rMod);
    clear128(&base);
    LOWER(base) = baseParam;
    if ((baseParam < 2) || (baseParam > 16)) {
        return false;
    }
    do {
        if (offset > (outLength - 1)) {
            return false;
        }
        divmod128(&rDiv, &base, &rDiv, &rMod);
        out[offset++] = HEXDIGITS[(uint8_t) LOWER(rMod)];
    } while (!zero128(&rDiv));
    out[offset] = '\0';
    reverseString(out, offset);
    return true;
}

bool tostring256(const uint256_t *number, uint32_t baseParam, char *out, uint32_t outLength) {
    uint256_t rDiv;
    uint256_t rMod;
    uint256_t base;
    uint32_t offset = 0;
    copy256(&rDiv, number);
    clear256(&rMod);
    clear256(&base);
    UPPER(LOWER(base)) = 0;
    LOWER(LOWER(base)) = baseParam;
    if ((baseParam < 2) || (baseParam > 16)) {
        return false;
    }
    do {
        if (offset > (outLength - 1)) {
            return false;
        }
        divmod256(&rDiv, &base, &rDiv, &rMod);
        out[offset++] = HEXDIGITS[(uint8_t) LOWER(LOWER(rMod))];
    } while (!zero256(&rDiv));
    out[offset] = '\0';
    reverseString(out, offset);
    return true;
}

int tobytes256(const uint256_t *number, uint8_t *out, uint32_t outLength) {
    // convert to hex
    char hexBuffer[65] = {0};

    if (!tostring256(number, 16, hexBuffer, 64)) {
        return -1;
    }

    // now convert the hex to binary.
    int n = hextobin(hexBuffer, (int) strlen(hexBuffer), out, (int) outLength);

    return n;
}

int fromstring256(const char *in, size_t inLen, uint256_t *number) {
    size_t bytesConsumed = 0;
    clear256(number);

    uint256_t number2;
    clear256(&number2);

    const char *str = in;
    if (*str == '-') {
        // don't support negative number
        return -1;
    }
    if (*str == '+' && bytesConsumed < inLen) {
        ++bytesConsumed;
        ++str;
    }
    while ((*str >= '0') && (*str <= '9') && bytesConsumed < inLen) {
        uint256_t number1;
        copy256(&number1, number);
        clear256(&number2);
        number2.elements[1].elements[1] = 10;
        mul256(&number1, &number2, number);
        clear256(&number2);
        number2.elements[1].elements[1] = (*str) - '0';
        copy256(&number1, number);
        add256(&number1, &number2, number);
        ++str;
        ++bytesConsumed;
    }

    return (int) bytesConsumed;
}

int frombytes256(const uint8_t *in, size_t inLen, uint256_t *number) {
    uint8_t buffer[32] = {0};

    int offset = (int) (sizeof(buffer)) - (int) (inLen);
    if (offset < 0) {
        return -1;
    }

    // align the buffer to 32 byte boundary
    memmove(&buffer[offset], in, inLen);
    readu256BE(buffer, number);
    return (int) (inLen);
}

int fromhex256(const char *in, size_t inLen, uint256_t *number) {
    // convert hex to binary
    // pad binary to 32 bytes.
    uint8_t buffer[32] = {0};
    char inbuffer[65] = {0};
    memset(inbuffer, '0', sizeof(inbuffer) - 1);
    int offset = (int) (sizeof(inbuffer)) - (int) (inLen);
    if (offset < 0) {
        return -1;
    }

    memmove(inbuffer, in, inLen);
    int n = hextobin(in, (int) inLen, buffer, (int) sizeof(buffer));
    if (n < 0) {
        return -1;
    }

    return frombytes256(buffer, n, number);
}
