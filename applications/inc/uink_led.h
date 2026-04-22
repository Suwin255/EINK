#ifndef UINK_LED_H
#define UINK_LED_H

#define LED_RED_PIN		3
#define LED_RED_PORT	AW9523B_PORT_1

#define LED_GREEN_PIN	1
#define LED_GREEN_PORT	AW9523B_PORT_1

void led_init(void);
void led_red_on(void);
void led_red_off(void);
void led_green_on(void);
void led_green_off(void);

void led_red_breathe(void);
void led_green_breathe(void);

void led_thread(void *argument);

#endif
