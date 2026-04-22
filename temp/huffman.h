#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "rsi_debug.h"

void huffman_set_bit(const uint8_t *src, uint32_t src_len);

uint32_t huffman_code(uint8_t *dst, const uint8_t *src, uint32_t src_len);

#endif
