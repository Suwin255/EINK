#ifndef UINK_SSD_H
#define UINK_SSD_H

#include "rsi_debug.h"

#include "../../peripherals/inc/uink_gpio.h"

sl_status_t ssd_init(void);

sl_status_t ssd_send_data(uint8_t data);
sl_status_t ssd_send_datas(const uint8_t *data, uint32_t len);
sl_status_t ssd_read_datas(uint8_t *data, uint32_t len);
sl_status_t ssd_send_command(uint8_t cmd);

sl_status_t ssd_wait_busy(void);
sl_status_t ssd_reset(void);

#endif
