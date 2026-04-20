#include "uink_button.h"
#include "rsi_debug.h"
#include "uink_gpio.h"
#include "cmsis_os2.h"

static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_power_key_det = {{SL_SI91X_UULP_GPIO_2_PORT, SL_SI91X_UULP_GPIO_2_PIN}, GPIO_INPUT};

extern osSemaphoreId_t led_to_button_semaphore;

extern osMessageQueueId_t eink_msgQueue;

osSemaphoreId_t button_to_led_semaphore;

button_event_t button_event;

/*
static void gpio_uulp_pin_interrupt_callback(uint32_t flag)
{
	if (flag == UULP_GPIO_INTERRUPT_2) {
		tick = osKernelGetTickCount();
		osSemaphoreRelease(button_thread_semaphore);
	}
}*/

void button_init(void)
{
	gpio_pin_config(&sl_gpio_pin_config_power_key_det, GPIO_HZ, GPIO_TWO_MILLI_AMPS);

	//gpio_int_config(&sl_gpio_pin_config_power_key_det.port_pin,
					//UULP_GPIO_INTERRUPT_2,
					//SL_GPIO_INTERRUPT_RISE_FALL_EDGE,
					//gpio_uulp_pin_interrupt_callback);

	button_to_led_semaphore = osSemaphoreNew(1, 0, NULL);
}

void button_scan(void)
{
	static uint8_t pin_value;
	static uint8_t state = 1;
	static uint8_t short_press_cnt = 0;

	static uint32_t tick;
	static uint32_t time;

	state = 1;
	short_press_cnt = 0;

	while (1) {
		gpio_read_pin(&sl_gpio_pin_config_power_key_det, &pin_value);

		if (state == 1) {//检测按下
			if (!pin_value) {//按键按下，开始消抖
				tick = osKernelGetTickCount();

				state = 2;
			}
		} else if (state == 2) {//按下消抖
			if (pin_value) {//按键松开，判定抖动
				state = 1;
			} else {//按键按下，判定成功
				state = 3;
			}
		} else if (state == 3) {//检测松开
			if (pin_value) {//按键松开，开始消抖
				state = 4;
			}
		} else if (state == 4) {//松开消抖
			if (pin_value) {//按键松开，判定成功
				time = osKernelGetTickCount() - tick;
				tick += time;

				if (short_press_cnt) {//连按情况
					if (time < BUTTON_SINGLE_PRESS_TIME_3S) {//短按，符合连按要求
						short_press_cnt++;
						if (short_press_cnt >= BUTTON_EVENT_SHORT_PRESS_MAX) {//达到最大连按次数
							break;
						}

						state = 5;
					} else {//长按，不符合连按要求，重新开始检测
						short_press_cnt = 0;

						state = 1;
					}
				} else {//首次按下
					if (time >= BUTTON_SINGLE_PRESS_TIME_3S) {//长按
						break;
					} else {//短按
						short_press_cnt++;
						if (short_press_cnt >= BUTTON_EVENT_SHORT_PRESS_MAX) {//达到最大连按次数
							break;
						}

						state = 5;
					}
				}
			} else {//按键按下，判定抖动
				state = 3;
			}
		} else if (state == 5) {//检测连按
			if (!pin_value) {
				state = 2;
			} else if (osKernelGetTickCount() >= (tick + BUTTON_CONTINUOUS_PRESS_INTERVAL)) {
				break;
			}
		}

		osDelay(20);
	}

	if (short_press_cnt) {
		switch (short_press_cnt) {
			case 1:
				button_event = BUTTON_EVENT_SHORT_PRESS_1;
				break;
			case 2:
				button_event = BUTTON_EVENT_SHORT_PRESS_2;
				break;
			default:
				break;
		}
	} else {
		if (time >= BUTTON_SINGLE_PRESS_TIME_10S) {
			button_event = BUTTON_EVENT_LONG_PRESS_10S;
		} else if (time >= BUTTON_SINGLE_PRESS_TIME_5S) {
			button_event = BUTTON_EVENT_LONG_PRESS_5S;
		} else {
			button_event = BUTTON_EVENT_LONG_PRESS_3S;
		}
	}
}

void button_thread(void *argument)
{
	(void)argument;

	uint8_t msg;

	while (1) {
		//osSemaphoreAcquire(led_to_button_semaphore, osWaitForever);

		button_scan();

		//osSemaphoreRelease(button_to_led_semaphore);

		msg = button_event;

		osMessageQueuePut(eink_msgQueue, &msg, 0, 0);
	}
}

