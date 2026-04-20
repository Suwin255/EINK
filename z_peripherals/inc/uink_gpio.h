#ifndef UINK_GPIO_H
#define UINK_GPIO_H

#include "rsi_debug.h"

#include "sl_si91x_driver_gpio.h"
#include "sl_gpio_board.h"

sl_status_t gpio_init(void);
void gpio_int_config(sl_gpio_t *gpio,
        	  	  	 uint32_t int_no,
					 sl_gpio_interrupt_flag_t flags,
					 sl_gpio_irq_callback_t gpio_callback);
sl_status_t gpio_pin_config(sl_si91x_gpio_pin_config_t *sl_si91x_gpio_pin_config,
					 	 	sl_si91x_gpio_driver_disable_state_t sl_si91x_gpio_driver_disable_state,
							sl_si91x_gpio_driver_strength_select_t sl_si91x_gpio_driver_strength_select);
sl_status_t gpio_set_pin(sl_si91x_gpio_pin_config_t *sl_si91x_gpio_pin_config);
sl_status_t gpio_reset_pin(sl_si91x_gpio_pin_config_t *sl_si91x_gpio_pin_config);
sl_status_t gpio_read_pin(sl_si91x_gpio_pin_config_t *sl_si91x_gpio_pin_config, uint8_t *pin_value);

#endif
