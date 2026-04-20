#ifndef UINK_SSD2683_H
#define UINK_SSD2683_H

#include "rsi_debug.h"
#include "uink_ssd.h"

#define SSD2683_DISPLAY_BYTE_SIZE 30000

typedef enum{
	SSD2683_BLACK,
	SSD2683_WHITE,
	SSD2683_YELLOW,
	SSD2683_RED,
}ssd2683_color_t;

sl_status_t ssd2683_init(void);

sl_status_t ssd2683_power_on(void);

void ssd2683_display_clear(ssd2683_color_t ssd2683_color);
void ssd2683_display_image(const uint8_t *img);

#endif
