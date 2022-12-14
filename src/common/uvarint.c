/*****************************************************************************
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

#include <common/uvarint.h>
#include <stddef.h>  // size_t
#include <stdint.h>  // uint*_t

uint8_t uvarint_size(uint64_t value) {
    uint8_t b[MaxVarintLen64] = {0};
    return uvarint_write(b, 0, value);
}

int uvarint_read(const uint8_t *in, size_t in_len, uint64_t *value) {
    uint64_t s = 0;
    *value = 0;
    for (size_t i = 0; i < in_len; ++i) {
        if (i == MaxVarintLen64) {
            // Catch byte reads past MaxVarintLen64.
            // See issue https://golang.org/issues/41185
            *value = 0;
            return -(int) (i + 1);  // overflow
        }
        if (in[i] < 0x80) {
            if (i == MaxVarintLen64 - 1 && in[i] > 1) {
                *value = 0;
                return -(int) (i + 1);  // overflow
            }
            *value |= ((uint64_t) in[i]) << s;
            return (int) i + 1;
        }
        *value |= (uint64_t) (in[i] & 0x7f) << s;
        s += 7;
    }
    *value = 0;
    return 0;
}

int uvarint_write(uint8_t *out, size_t offset, uint64_t value) {
    size_t i = offset;
    while (value >= 0x80) {
        out[offset++] = ((uint8_t) value) | 0x80;
        value >>= 7;
    }
    out[offset++] = (uint8_t) value;
    return (int) (offset - i);
}
