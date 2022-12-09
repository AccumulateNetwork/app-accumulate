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

#include <stdint.h>  // uint*_t
#include <stddef.h>  // size_t

#include <common/varint.h>

uint8_t varint_size(int64_t value) {
    uint64_t ux = ((uint64_t) value) << 1;
    if (value < 0) {
        ux = ~ux;
    }
    return uvarint_size(ux);
}

int varint_read(const uint8_t *in, size_t in_len, int64_t *value) {
    uint64_t ux = 0;
    int n = uvarint_read(in, in_len, &ux);  // ok to continue in presence of error
    *value = (int64_t) (ux >> 1);
    if ((ux & 1) != 0) {
        *value = (int64_t) (~ux);
    }
    return n;
}

int varint_write(uint8_t *out, size_t offset, int64_t value) {
    uint64_t ux = ((uint64_t) value) << 1;
    if (value < 0) {
        ux = ~ux;
    }
    return uvarint_write(out, offset, ux);
}
