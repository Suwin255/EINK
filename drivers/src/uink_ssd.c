#include "uink_ssd.h"

#include "cmsis_os2.h"
#include "uink_spi.h"

static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_lcd_dc = {{SL_SI91X_ULP_GPIO_10_PORT, SL_SI91X_ULP_GPIO_10_PIN}, GPIO_OUTPUT};
static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_lcd_rst = {{SL_SI91X_ULP_GPIO_9_PORT, SL_SI91X_ULP_GPIO_9_PIN}, GPIO_OUTPUT};
static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_lcd_busy = {{SL_SI91X_ULP_GPIO_11_PORT, SL_SI91X_ULP_GPIO_11_PIN}, GPIO_INPUT};

sl_status_t ssd_init(void)
{
	sl_status_t status;

	status = gpio_pin_config(&sl_gpio_pin_config_lcd_dc, GPIO_HZ, GPIO_TWO_MILLI_AMPS);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_pin_config\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_pin_config\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = gpio_pin_config(&sl_gpio_pin_config_lcd_rst, GPIO_HZ, GPIO_TWO_MILLI_AMPS);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_pin_config\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_pin_config\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = gpio_pin_config(&sl_gpio_pin_config_lcd_busy, GPIO_HZ, GPIO_TWO_MILLI_AMPS);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_pin_config\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_pin_config\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = gpio_set_pin(&sl_gpio_pin_config_lcd_rst);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_set_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_set_pin\r\n");
	}
#endif

	return status;
}

sl_status_t ssd_reset(void)
{
	sl_status_t status;

	status = gpio_reset_pin(&sl_gpio_pin_config_lcd_rst);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_reset_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_reset_pin\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	osDelay(10);

	status = gpio_set_pin(&sl_gpio_pin_config_lcd_rst);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_set_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_set_pin\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = ssd_wait_busy();
#if DEBUG_DRV_SSD
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:ssd_wait_busy\r\n", status);
	} else {
		DEBUGOUT("Success:ssd_wait_busy\r\n");
	}
#endif

	return status;
}

sl_status_t ssd_wait_busy(void)
{
	sl_status_t status;
	uint8_t pin_value;

	while (1) {
		status = gpio_read_pin(&sl_gpio_pin_config_lcd_busy, &pin_value);
#if DEBUG_PPH_GPIO
		if (status != SL_STATUS_OK) {
			DEBUGOUT("Error%lu:gpio_read_pin\r\n", status);
		} else {
			DEBUGOUT("Success:gpio_read_pin\r\n");
		}
#endif
		if (status != SL_STATUS_OK) {
			return status;
		}

		if (pin_value) {
			break;
		}
	}

	return status;
}

sl_status_t ssd_send_command(uint8_t cmd)
{
	sl_status_t status;

	status = gpio_reset_pin(&sl_gpio_pin_config_lcd_dc);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_reset_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_reset_pin\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	gspi_cs_low(SSD_CS);

	status = gspi_write(SSD_CS, &cmd, 1);
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_write\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_write\r\n");
	}
#endif

	gspi_cs_high(SSD_CS);

	return status;
}

sl_status_t ssd_send_data(uint8_t data)
{
	sl_status_t status;

	status = gpio_set_pin(&sl_gpio_pin_config_lcd_dc);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_set_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_set_pin\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	gspi_cs_low(SSD_CS);

	status = gspi_write(SSD_CS, &data, 1);
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_write\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_write\r\n");
	}
#endif

	gspi_cs_high(SSD_CS);

	return status;
}

sl_status_t ssd_send_datas(const uint8_t *data, uint32_t len)
{
	sl_status_t status;

	status = gpio_set_pin(&sl_gpio_pin_config_lcd_dc);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_set_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_set_pin\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	gspi_cs_low(SSD_CS);

	status = gspi_write(SSD_CS, data, len);
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_write\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_write\r\n");
	}
#endif

	gspi_cs_high(SSD_CS);

	return status;
}

sl_status_t ssd_read_datas(uint8_t *data, uint32_t len)
{
	sl_status_t status;

	status = gpio_set_pin(&sl_gpio_pin_config_lcd_dc);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_set_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_set_pin\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	gspi_cs_low(SSD_CS);

	status = gspi_read(SSD_CS, data, len);
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_read\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_read\r\n");
	}
#endif

	gspi_cs_high(SSD_CS);

	return status;
}
