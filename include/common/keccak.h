#pragma once

#include <common/error.h>
#include <types.h>

Error keccak(const uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len);
