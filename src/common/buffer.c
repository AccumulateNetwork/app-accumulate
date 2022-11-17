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

#include <stdint.h>   // uint*_t
#include <stddef.h>   // size_t
#include <stdbool.h>  // bool
#include <string.h>   // memmove

#include <common/buffer.h>
#include <common/read.h>
#include <common/varint.h>
#include <common/bip32.h>

bool buffer_can_read(const buffer_t *buffer, size_t n) {
    return buffer->size - buffer->offset >= n;
}

bool buffer_seek_set(buffer_t *buffer, size_t offset) {
    if (offset > buffer->size) {
        return false;
    }

    buffer->offset = offset;

    return true;
}

bool buffer_seek_cur(buffer_t *buffer, size_t offset) {
    if (buffer->offset + offset < buffer->offset ||  // overflow
        buffer->offset + offset > buffer->size) {    // exceed buffer size
        return false;
    }

    buffer->offset += offset;

    return true;
}

bool buffer_seek_end(buffer_t *buffer, size_t offset) {
    if (offset > buffer->size) {
        return false;
    }

    buffer->offset = buffer->size - offset;

    return true;
}

bool buffer_read_u8(buffer_t *buffer, uint8_t *value) {
    if (!buffer_can_read(buffer, 1)) {
        *value = 0;

        return false;
    }

    *value = buffer->ptr[buffer->offset];
    buffer_seek_cur(buffer, 1);

    return true;
}

bool buffer_read_u16(buffer_t *buffer, uint16_t *value, endianness_t endianness) {
    if (!buffer_can_read(buffer, 2)) {
        *value = 0;

        return false;
    }

    *value = ((endianness == BE) ? read_u16_be(buffer->ptr, buffer->offset)
                                 : read_u16_le(buffer->ptr, buffer->offset));

    buffer_seek_cur(buffer, 2);

    return true;
}

bool buffer_read_u32(buffer_t *buffer, uint32_t *value, endianness_t endianness) {
    if (!buffer_can_read(buffer, 4)) {
        *value = 0;

        return false;
    }

    *value = ((endianness == BE) ? read_u32_be(buffer->ptr, buffer->offset)
                                 : read_u32_le(buffer->ptr, buffer->offset));

    buffer_seek_cur(buffer, 4);

    return true;
}

int buffer_read_varint(buffer_t *buffer, int64_t *value) {
    int length = varint_read(buffer->ptr + buffer->offset, buffer->size - buffer->offset, value);

    if (length < 0) {
        *value = 0;

        return length;
    }

    buffer_seek_cur(buffer, (size_t) length);

    return length;
}

bool buffer_read_u64(buffer_t *buffer, uint64_t *value, endianness_t endianness) {
    if (!buffer_can_read(buffer, 8)) {
        *value = 0;

        return false;
    }

    *value = ((endianness == BE) ? read_u64_be(buffer->ptr, buffer->offset)
                                 : read_u64_le(buffer->ptr, buffer->offset));

    buffer_seek_cur(buffer, 8);

    return true;
}

int buffer_read_uvarint(buffer_t *buffer, uint64_t *value) {
    int length = uvarint_read(buffer->ptr + buffer->offset, buffer->size - buffer->offset, value);

    if (length < 0) {
        *value = 0;

        return length;
    }

    buffer_seek_cur(buffer, (size_t) length);

    return length;
}

bool buffer_read_bip32_path(buffer_t *buffer, uint32_t *out, size_t out_len) {
    if (!bip32_path_read(buffer->ptr + buffer->offset,
                         buffer->size - buffer->offset,
                         out,
                         out_len)) {
        return false;
    }

    buffer_seek_cur(buffer, sizeof(*out) * out_len);

    return true;
}

bool buffer_copy(const buffer_t *buffer, uint8_t *out, size_t out_len) {
    if (buffer->size - buffer->offset > out_len) {
        return false;
    }

    memmove(out, buffer->ptr + buffer->offset, buffer->size - buffer->offset);

    return true;
}

bool buffer_move(buffer_t *buffer, uint8_t *out, size_t out_len) {
    if (!buffer_copy(buffer, out, out_len)) {
        return false;
    }

    buffer_seek_cur(buffer, out_len);

    return true;
}

int hextobin(const char *hexStr, int hexLen, uint8_t *output, int outputLen) {
    size_t len = hexLen;
    if (len % 2 != 0) {
        return -1;
    }
    const char offset = 'a' - 'A';
    size_t finalLen = len / 2;
    if ( outputLen < (int) finalLen ) {
        return -1;
    }
    for (size_t inIdx = 0, outIdx = 0; outIdx < finalLen; inIdx += 2, outIdx++) {
        char h0 = (hexStr[inIdx] >= 'a' && hexStr[inIdx] <= 'z') ? hexStr[inIdx] - offset : hexStr[inIdx];
        char h1 = (hexStr[inIdx+1] >= 'a' && hexStr[inIdx+1] <= 'z') ? hexStr[inIdx+1] - offset : hexStr[inIdx+1];
        if ((h0 - 48) <= 9 && (h1 - 48) <= 9) {
            goto convert;
        } else {
            if ((h0 - 65) <= 5 && (h1 - 65) <= 5) {
                goto convert;
            } else {
                return -1;
            }
        }
        convert:
        output[outIdx] =
                (h0 % 32 + 9) % 25 * 16 + (h1 % 32 + 9) % 25;
    }
    return (int)finalLen;
}
