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

#include <stdio.h>

#include "uink_aw9523b.h"
#include "uink_gpio.h"
#include "uink_led.h"
#include "uink_pwr.h"
#include "uink_ssd2683.h"
#include "uink_i2c.h"
#include "uink_spi.h"
#include "uink_thread.h"
#include "uink_eink.h"
#include "uink_button.h"
#include "uink_gd25wq64e.h"

#include "rle.h"

extern const uint8_t pic_4color_2bit_data[];
extern volatile uint32_t recv_done;

uint8_t temp1[30000];
uint8_t temp2[30000];

/*******************************************************************************
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
	int size;
	//uint8_t i;
	//uint8_t data_w[4] = {0x01, 0x02, 0x03, 0x04};
	//uint8_t data_r[4] = {0};
	//uint8_t sr1 = 0;
	//uint8_t sr2 = 0;

	gpio_init();
	aw9523b_init();

	i2c_init();
	pwr_init();

	gspi_init();

	led_init();
	ssd2683_init();
	gd25wq64e_init();

	eink_init();
	button_init();

	//test();

	size = rle_2bit_compress(pic_4color_2bit_data, temp1);

	printf("%d\r\n", size);
	printf("%d\r\n", rle_2bit_decompress(temp1, size, temp2));

	ssd2683_display_image(temp2);

	//gd25wq64e_read_sr1(&sr1);
	//DEBUGOUT("sr1:%02X\r\n", sr1);

	//gd25wq64e_read_sr2(&sr2);
	//DEBUGOUT("sr2:%02X\r\n", sr2);

	//gd25wq64e_write_enable();

	//gd25wq64e_read_sr1(&sr1);
	//DEBUGOUT("%02X\r\n", sr1);

	//gd25wq64e_write(0x00020000, data_w, 4);
	//gd25wq64e_read(0x00020000, data_r, 4);

//	for (i = 0; i < 4; i++) {
//		DEBUGOUT("%02X ", data_r[i]);
//	}

	//while(1){
		printf("Hello World!\r\n");
	//}
	//printf("SystemCoreClock:%ld\r\n", SystemCoreClock);

	thread_init();
}

/*******************************************************************************
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
