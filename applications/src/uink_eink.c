#include "uink_eink.h"

#include "rsi_debug.h"
#include "cmsis_os2.h"

#include "uink_gd25wq64e.h"
#include "uink_ssd2683.h"

#define PIC_SIZE	30000
#define PIC_BLOCK_INDEX	4

uint8_t pic[PIC_SIZE];

extern const uint8_t pic_4color_2bit_data[30000];

uint8_t pic_num = 0;
uint8_t pic_index;

osSemaphoreId_t eink_thread_semaphore;

volatile osMessageQueueId_t eink_msgQueue;

void eink_init(void)
{
	//ssd2683_display_clear(SSD2683_BLACK);

	//eink_thread_semaphore = osSemaphoreNew(1, 0, NULL);

	eink_msgQueue = osMessageQueueNew (10, 1, NULL);
}

void eink_thread(void *argument)
{
	(void)argument;

	uint8_t msg;

	while (1) {
		osMessageQueueGet(eink_msgQueue, &msg, NULL, osWaitForever);

		switch (msg) {
			case 0:
				if (pic_num) {
					pic_index++;
					if (pic_index >= pic_num) {
						pic_index = 0;
					}

					printf("pic_index:%d\r\n", pic_index);

					gd25wq64e_read((PIC_BLOCK_INDEX + pic_index) << 15, pic, PIC_SIZE);
					osDelay(200);
					ssd2683_display_image(pic);
				}
				break;
			case 1:
				ssd2683_display_clear(SSD2683_WHITE);
				break;
			case 2:
				ssd2683_display_image(pic);

				gd25wq64e_erase_block_32k((PIC_BLOCK_INDEX + pic_num) << 15);
				gd25wq64e_write((PIC_BLOCK_INDEX + pic_num) << 15, pic, PIC_SIZE);

				pic_num++;
				pic_index = pic_num - 1;
				break;
			default:
				break;
		}
	}
}
