#pragma once

#include <common/encoding.h>

Error sha256(uint8_t *in, unsigned int len,  uint8_t *out, unsigned int out_len); 
Error sha256d(uint8_t *in, unsigned int len, uint8_t *out, unsigned int out_len);
