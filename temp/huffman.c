#include "huffman.h"

uint8_t code_bit_len[4];

void huffman_set_bit(const uint8_t *src, uint32_t src_len)
{	
	uint32_t i, j;
	uint32_t code_cnt[4][2] = { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 3, 0 } };
	uint32_t code_cnt_tmp[2];

	for (i = 0; i < src_len; i++) {
		for (j = 0; j <= 3; j++) {
			code_cnt[(src[i] >> (2 * (3 -j))) & 0x03][1]++;
		}
	}

	for (i = 0; i < 3; i++) {
		for (j = 3; j > i ; j--) {
			if (code_cnt[j][1] > code_cnt[i][1]) {
				code_cnt_tmp[0] = code_cnt[j][0];
				code_cnt_tmp[1] = code_cnt[j][1];

				code_cnt[j][0] = code_cnt[i][0];
				code_cnt[j][1] = code_cnt[i][1];

				code_cnt[i][0] = code_cnt_tmp[0];
				code_cnt[i][1] = code_cnt_tmp[1];
			}
		}
	}

	code_bit_len[code_cnt[0][0]] = 1;
	code_bit_len[code_cnt[1][0]] = 2;
	code_bit_len[code_cnt[2][0]] = 3;
	code_bit_len[code_cnt[3][0]] = 4;

//	for (i = 0; i < 4; i++) {
//		printf("%d ", code_bit_len[i]);
//	}
}

uint32_t huffman_code(uint8_t *dst, const uint8_t *src, uint32_t src_len)
{
	uint8_t code = 0, index;
	
	uint32_t i, j;
	uint32_t a = 0;
	uint32_t b = 0;		

	huffman_set_bit(src, src_len);
	
	for (i = 0; i < src_len; i++) {
		for (j = 0; j <= 3; j++) {
			index = (src[i] >> (2 * (3 - j))) & 0x03;
			
			switch (code_bit_len[index]) {
				case 1:
					b++;
					if (b > 7) {
						dst[a] = code;
						code = 0;						
						a++;
						b %= 8;						
					}
					break;
				case 2:
					code |= 1 << (7 - b);
					
					b += 2;
					if (b > 7) {
						dst[a] = code;
						code = 0;						
						a++;
						b %= 8;
					}
					break;
				case 3:
					code |= 1 << (7 - b);

					b++;
					if (b > 7) {
						dst[a] = code;
						code = 0;						
						a++;
						b %= 8;
					}

					code |= 1 << (7 - b);
					
					b += 2;
					if (b > 7) {
						dst[a] = code;
						code = 0;						
						a++;
						b %= 8;
					}
					break;
				case 4:
					code |= 1 << (7 - b);

					b++;
					if (b > 7) {
						dst[a] = code;
						code = 0;						
						a++;
						b %= 8;
					}

					code |= 1 << (7 - b);

					b++;
					if (b > 7) {
						dst[a] = code;
						code = 0;						
						a++;
						b %= 8;
					}

					code |= 1 << (7 - b);

					b++;
					if (b > 7) {
						dst[a] = code;
						code = 0;						
						a++;
						b %= 8;
					}
					break;
				default:
					break;
			}
		}
	}

	return a;
}
