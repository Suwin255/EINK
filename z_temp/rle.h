#ifndef RLE_H
#define RLE_H

int rle_2bit_compress(const uint8_t *raw, uint8_t *out);
int rle_2bit_decompress(const uint8_t *comp, int comp_size, uint8_t *out);

#endif
