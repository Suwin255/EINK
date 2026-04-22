#include "uink_gd25wq64e.h"
#include "uink_spi.h"

void gd25wq64e_read_sr1(uint8_t *data)
{
	uint8_t code = 0x05;

	gspi_cs_low(FLASH_CS);
	gspi_write(FLASH_CS, &code, 1);
	gspi_read(FLASH_CS, data, 1);
	gspi_cs_high(FLASH_CS);
}

void gd25wq64e_read_sr2(uint8_t *data)
{
	uint8_t code = 0x35;

	gspi_cs_low(FLASH_CS);
	gspi_write(FLASH_CS, &code, 1);
	gspi_read(FLASH_CS, data, 1);
	gspi_cs_high(FLASH_CS);
}

void gd25wq64e_wait_busy(void)
{
	uint8_t sr1;

	do {
		gd25wq64e_read_sr1(&sr1);
	} while (sr1 & 0x01);
}

void gd25wq64e_write_enable(void)
{
	uint8_t code = 0x06;

	gspi_cs_low(FLASH_CS);
	gspi_write(FLASH_CS, &code, 1);
	gspi_cs_high(FLASH_CS);

	gd25wq64e_wait_busy();
}

void gd25wq64e_erase_block_32k(uint32_t addr)
{
	uint8_t code[4];

	code[0] = 0x52;
	code[1] = addr >> 16;
	code[2] = addr >> 8;
	code[3] = addr;

	gd25wq64e_write_enable();

	gspi_cs_low(FLASH_CS);
	gspi_write(FLASH_CS, code, 4);
	gspi_cs_high(FLASH_CS);

	gd25wq64e_wait_busy();
}

void gd25wq64e_write_page(uint32_t addr, const uint8_t *data, uint32_t len)
{
	uint8_t code[4];

	code[0] = 0x02;
	code[1] = addr >> 16;
	code[2] = addr >> 8;
	code[3] = addr;

	gd25wq64e_write_enable();

	gspi_cs_low(FLASH_CS);
	gspi_write(FLASH_CS, code, 4);
	gspi_write(FLASH_CS, data, len);
	gspi_cs_high(FLASH_CS);

	gd25wq64e_wait_busy();
}

void gd25wq64e_write(uint32_t addr, const uint8_t *data, uint32_t len)
{
	uint32_t i = 0;
	uint16_t left_size;

	while (len) {
		left_size = 256 - addr%256;

		if (len < left_size) {
			gd25wq64e_write_page(addr, &data[i], len);
			i += len;
			addr += len;
			len -= len;
		} else {
			gd25wq64e_write_page(addr, &data[i], left_size);
			i += left_size;
			addr += left_size;
			len -= left_size;
		}		
	}
}

void gd25wq64e_read_page(uint32_t addr, uint8_t *data, uint32_t len)
{
	uint8_t code[4];

	code[0] = 0x03;
	code[1] = addr >> 16;
	code[2] = addr >> 8;
	code[3] = addr;

	gspi_cs_low(FLASH_CS);
	gspi_write(FLASH_CS, code, 4);
	gspi_read(FLASH_CS, data, len);
	gspi_cs_high(FLASH_CS);
}

void gd25wq64e_read(uint32_t addr, uint8_t *data, uint32_t len)
{
	uint32_t i = 0;
	uint16_t left_size;

	while (len) {
		left_size = 256 - addr%256;

		if (len < left_size) {
			gd25wq64e_read_page(addr, &data[i], len);
			i += len;
			addr += len;
			len -= len;
		} else {
			gd25wq64e_read_page(addr, &data[i], left_size);
			i += left_size;
			addr += left_size;
			len -= left_size;
		}
	}
}

void gd25wq64e_init(void)
{
	gd25wq64e_write_enable();
}
