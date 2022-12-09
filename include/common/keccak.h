#pragma once

#include <types.h>
#include <common/error.h>

Error keccak(const uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len);
