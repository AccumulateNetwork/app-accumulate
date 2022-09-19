#pragma once

#include <types.h>

Error sha256(const uint8_t *in, unsigned int len,  uint8_t *out, unsigned int out_len);
Error sha256d(const uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len);
