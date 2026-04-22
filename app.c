/***************************************************************************/ /**
 * @file app.c
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "app.h"

#include <huffman.h>
#include <stdio.h>

#include "uink_thread.h"
#include "uink_button.h"
#include "uink_eink.h"
#include "uink_led.h"
#include "uink_aw9523b.h"
#include "uink_gd25wq64e.h"
#include "uink_pwr.h"
#include "uink_ssd2683.h"
#include "uink_gpio.h"
#include "uink_i2c.h"
#include "uink_spi.h"

extern const uint8_t pic_4color_2bit_data[];
extern volatile uint32_t recv_done;

uint8_t temp1[30000];
uint8_t temp2[30000];

/*******************************************************************************
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
	//int size;
	//uint16_t i;
	//uint8_t data_w[258] = {0xC7, 0x94, 0xA6, 0x3E};
	//uint8_t data_r[258] = {0};
	//uint8_t sr1 = 0;
	//uint8_t sr2 = 0;

	gpio_init();
	aw9523b_init();

	i2c_init();
	pwr_init();

	gspi_init();

	led_init();
	ssd2683_init();
	//gd25wq64e_init();

	eink_init();
	button_init();

	//test();

//	size = rle_2bit_compress(pic_4color_2bit_data, temp1);
//
//	printf("%d\r\n", size);
//	printf("%d\r\n", rle_2bit_decompress(temp1, size, temp2));
//
//	ssd2683_display_image(temp2);

	//gd25wq64e_read_sr1(&sr1);
	//DEBUGOUT("sr1:%02X\r\n", sr1);

	//gd25wq64e_read_sr2(&sr2);
	//DEBUGOUT("sr2:%02X\r\n", sr2);

//	for (i = 0; i < 258; i++) {
//		data_w[i] = i;
//	}

	//gd25wq64e_erase_block_32k(0x00020000);

	//gd25wq64e_write_page(0x00020000, data_w, 256);
	//gd25wq64e_read_page(0x00020000, data_r, 256);

//	for (i = 0; i < 256; i++) {
//		DEBUGOUT("%02X ", data_r[i]);
//	}

	//gd25wq64e_write_page((4<<15)+255, data_w, 1);

	//gd25wq64e_read_page((4<<15)+255, data_r, 1);

//	for (i = 0; i < 258; i++) {
//		printf("%d ", data_r[i]);
//	}

	//huffman_set_bit(pic_4color_2bit_data, 30000);

	printf("%ld\r\n", huffman_code(temp1, pic_4color_2bit_data, 30000));

	printf("\r\nHello World!\r\n");

	thread_init();
}

/*******************************************************************************
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
