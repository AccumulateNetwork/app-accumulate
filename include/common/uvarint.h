#pragma once

#include <stdbool.h>  // bool
#include <stddef.h>   // size_t
#include <stdint.h>   // uint*_t

enum
{
    MaxVarintLen16 = 3,
    MaxVarintLen32 = 5,
    MaxVarintLen64 = 10,
};

int uvarint_write(uint8_t *out, size_t offset, uint64_t value);

uint8_t uvarint_size(uint64_t value);
int uvarint_read(const uint8_t *in, size_t in_len, uint64_t *value);