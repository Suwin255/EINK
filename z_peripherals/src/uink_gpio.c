#include "uink_gpio.h"
#include "uink_debug.h"

void gpio_int_config(sl_gpio_t *gpio,
        	  	  	 uint32_t int_no,
					 sl_gpio_interrupt_flag_t flags,
					 sl_gpio_irq_callback_t gpio_callback)
{
	sl_gpio_driver_configure_interrupt(gpio, int_no, flags, gpio_callback, NULL);
}

sl_status_t gpio_pin_config(sl_si91x_gpio_pin_config_t *sl_si91x_gpio_pin_config,
					 	 	sl_si91x_gpio_driver_disable_state_t sl_si91x_gpio_driver_disable_state,
							sl_si91x_gpio_driver_strength_select_t sl_si91x_gpio_driver_strength_select)
{
	sl_status_t status;

	status = sl_gpio_set_configuration(*sl_si91x_gpio_pin_config);
#if DEBUG_SDK_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_gpio_set_configuration\r\n", status);
	} else {
		DEBUGOUT("Success:sl_gpio_set_configuration\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	sl_si91x_gpio_driver_select_pad_driver_strength(sl_si91x_gpio_pin_config->port_pin.pin, sl_si91x_gpio_driver_strength_select);
#if DEBUG_SDK_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_si91x_gpio_driver_select_pad_driver_strength\r\n", status);
	} else {
		DEBUGOUT("Success:sl_si91x_gpio_driver_select_pad_driver_strength\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = sl_si91x_gpio_driver_select_pad_driver_disable_state(sl_si91x_gpio_pin_config->port_pin.pin, sl_si91x_gpio_driver_disable_state);
#if DEBUG_SDK_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_si91x_gpio_driver_select_pad_driver_disable_state\r\n", status);
	} else {
		DEBUGOUT("Success:sl_si91x_gpio_driver_select_pad_driver_disable_state\r\n");
	}
#endif

	return status;
}

sl_status_t gpio_reset_pin(sl_si91x_gpio_pin_config_t *sl_si91x_gpio_pin_config)
{
	sl_status_t status;

	status = sl_gpio_driver_clear_pin(&sl_si91x_gpio_pin_config->port_pin);
#if DEBUG_SDK_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_gpio_driver_clear_pin\r\n", status);
	} else {
		DEBUGOUT("Success:sl_gpio_driver_clear_pin\r\n");
	}
#endif

	return status;
}

sl_status_t gpio_set_pin(sl_si91x_gpio_pin_config_t *sl_si91x_gpio_pin_config)
{
	sl_status_t status;

	status = sl_gpio_driver_set_pin(&sl_si91x_gpio_pin_config->port_pin);
#if DEBUG_SDK_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_gpio_driver_set_pin\r\n", status);
	} else {
		DEBUGOUT("Success:sl_gpio_driver_set_pin\r\n");
	}
#endif

	return status;
}

sl_status_t gpio_read_pin(sl_si91x_gpio_pin_config_t *sl_si91x_gpio_pin_config, uint8_t *pin_value)
{
	sl_status_t status;

	status = sl_gpio_driver_get_pin(&sl_si91x_gpio_pin_config->port_pin, pin_value);
#if DEBUG_SDK_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_gpio_driver_get_pin\r\n", status);
	} else {
		DEBUGOUT("Success:sl_gpio_driver_get_pin\r\n");
	}
#endif

	return status;
}

sl_status_t gpio_init(void)
{
	sl_status_t status;

	status = sl_gpio_driver_init();
#if DEBUG_SDK_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_gpio_driver_init\r\n", status);
	} else {
		DEBUGOUT("Success:sl_gpio_driver_init\r\n");
	}
#endif

	return status;
}


