#include "../../applications/inc/uink_led.h"

#include "cmsis_os2.h"
#include "../../applications/inc/uink_button.h"
#include "../../drivers/inc/uink_aw9523b.h"

extern button_event_t button_event;

extern osSemaphoreId_t button_to_led_semaphore;

osSemaphoreId_t led_to_button_semaphore;

static void led_red_config(void)
{
	aw9523b_gpioConfig_t aw9523b_gpioConfig;

	aw9523b_gpioConfig.direction = AW9523B_DIRECTION_OUTPUT;
	aw9523b_gpioConfig.inten = AW9523B_INTEN_DISABLE;
	aw9523b_gpioConfig.mode = AW9523B_MODE_LED;
	aw9523b_gpioConfig.pin = LED_RED_PIN;
	aw9523b_gpioConfig.port = LED_RED_PORT;
	aw9523b_gpioConfig.strength = 0;

	aw9523b_gpio_config(&aw9523b_gpioConfig);
}

static void led_green_config(void)
{
	aw9523b_gpioConfig_t aw9523b_gpioConfig;

	aw9523b_gpioConfig.direction = AW9523B_DIRECTION_OUTPUT;
	aw9523b_gpioConfig.inten = AW9523B_INTEN_DISABLE;
	aw9523b_gpioConfig.mode = AW9523B_MODE_LED;
	aw9523b_gpioConfig.pin = LED_GREEN_PIN;
	aw9523b_gpioConfig.port = LED_GREEN_PORT;
	aw9523b_gpioConfig.strength = 0;

	aw9523b_gpio_config(&aw9523b_gpioConfig);
}

void led_init(void)
{
	led_red_config();
	led_green_config();

	led_to_button_semaphore = osSemaphoreNew(1, 1, NULL);
}

void led_red_on(void)
{	
	aw9523b_gpio_pin_setStrength(LED_RED_PORT, LED_RED_PIN, 255);
}

void led_red_off(void)
{	
	aw9523b_gpio_pin_setStrength(LED_RED_PORT, LED_RED_PIN, 0);
}

void led_red_breathe(void)
{
	static uint8_t dir = 1;
	static uint8_t strength = 0;

	aw9523b_gpio_pin_setStrength(LED_RED_PORT, LED_RED_PIN, strength);

	if(dir){
		strength++;
		if(strength >= 255){
			dir = !dir;
		}
	}else{
		strength--;
		if(strength <= 0){
			dir = !dir;
		}
	}
}

void led_green_on(void)
{
	aw9523b_gpio_pin_setStrength(LED_GREEN_PORT, LED_GREEN_PIN, 255);
}

void led_green_off(void)
{
	aw9523b_gpio_pin_setStrength(LED_GREEN_PORT, LED_GREEN_PIN, 0);
}

void led_green_breathe(void)
{
	static uint8_t dir = 1;
	static uint8_t strength = 0;

	aw9523b_gpio_pin_setStrength(LED_GREEN_PORT, LED_GREEN_PIN, strength);

	if(dir){
		strength++;
		if(strength >= 255){
			dir = !dir;
		}
	}else{
		strength--;
		if(strength <= 0){
			dir = !dir;
		}
	}
}

void led_thread(void *argument)
{
	(void)argument;

	while(1){
		osSemaphoreAcquire(button_to_led_semaphore, osWaitForever);

		switch (button_event) {
			case BUTTON_EVENT_SHORT_PRESS_1:
				led_green_on();
				break;
			case BUTTON_EVENT_SHORT_PRESS_2:
				led_green_off();
				break;
			case BUTTON_EVENT_LONG_PRESS_3S:
				led_red_on();
				break;
			case BUTTON_EVENT_LONG_PRESS_5S:
				led_red_off();
				break;
			default:
				break;
		}
	}
}
