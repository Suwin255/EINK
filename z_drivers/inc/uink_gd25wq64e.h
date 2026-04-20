#ifndef UINK_GD25WQ64E_H
#define UINK_GD25WQ64E_H

#include "rsi_debug.h"

void gd25wq64e_init(void);

void gd25wq64e_write_enable(void);

void gd25wq64e_erase_block_32k(uint32_t addr);

void gd25wq64e_write(uint32_t addr, const uint8_t *data, uint32_t len);
void gd25wq64e_read(uint32_t addr, uint8_t *data, uint32_t len);

void gd25wq64e_read_sr1(uint8_t *data);
void gd25wq64e_read_sr2(uint8_t *data);

#endif
