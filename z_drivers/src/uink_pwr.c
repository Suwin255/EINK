#include "uink_aw9523b.h"
#include "uink_gpio.h"
#include "uink_pwr.h"

static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_pwr_ctrl_gt = {{SL_SI91X_GPIO_29_PORT, SL_SI91X_GPIO_29_PIN}, GPIO_OUTPUT};

static sl_i2c_status_t pwr_ctrl_eink_config(void)
{
	sl_i2c_status_t i2c_status;
	aw9523b_gpioConfig_t aw9523b_gpioConfig;

	aw9523b_gpioConfig.direction = AW9523B_DIRECTION_OUTPUT;
	aw9523b_gpioConfig.inten = AW9523B_INTEN_DISABLE;
	aw9523b_gpioConfig.mode = AW9523B_MODE_GPIO;
	aw9523b_gpioConfig.pin = PWR_CTRL_EINK_PIN;
	aw9523b_gpioConfig.port = PWR_CTRL_EINK_PORT;
	aw9523b_gpioConfig.strength = 0;

	i2c_status = aw9523b_gpio_config(&aw9523b_gpioConfig);
#if DEBUG_DRV_AW9523B
    if (i2c_status != SL_I2C_SUCCESS) {
        DEBUGOUT("Error%u:aw9523b_gpio_config\r\n", i2c_status);
    } else {
        DEBUGOUT("Success:aw9523b_gpio_config\r\n");
    }
#endif

    return i2c_status;
}

sl_i2c_status_t pwr_ctrl_eink_on(void)
{
	sl_i2c_status_t i2c_status;

	i2c_status = aw9523b_gpio_pin_setOutput(PWR_CTRL_EINK_PORT, PWR_CTRL_EINK_PIN);
#if DEBUG_DRV_AW9523B
    if (i2c_status != SL_I2C_SUCCESS) {
        DEBUGOUT("Error%u:aw9523b_gpio_pin_setOutput\r\n", i2c_status);
    } else {
        DEBUGOUT("Success:aw9523b_gpio_pin_setOutput\r\n");
    }
#endif

    return i2c_status;
}

sl_i2c_status_t pwr_ctrl_eink_off(void)
{
	sl_i2c_status_t i2c_status;

	i2c_status = aw9523b_gpio_pin_resetOutput(PWR_CTRL_EINK_PORT, PWR_CTRL_EINK_PIN);
#if DEBUG_DRV_AW9523B
    if (i2c_status != SL_I2C_SUCCESS) {
        DEBUGOUT("Error%u:aw9523b_gpio_pin_resetOutput\r\n", i2c_status);
    } else {
        DEBUGOUT("Success:aw9523b_gpio_pin_resetOutput\r\n");
    }
#endif

    return i2c_status;
}

static sl_status_t pwr_ctrl_gt_config(void)
{
	sl_status_t status;

	status = gpio_pin_config(&sl_gpio_pin_config_pwr_ctrl_gt, GPIO_HZ, GPIO_TWO_MILLI_AMPS);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_pin_config\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_pin_config\r\n");
	}
#endif

	return status;
}

sl_status_t pwr_ctrl_gt_on(void)
{
	sl_status_t status;

	status = gpio_set_pin(&sl_gpio_pin_config_pwr_ctrl_gt);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_set_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_set_pin\r\n");
	}
#endif

	return status;
}

sl_status_t pwr_ctrl_gt_off(void)
{
	sl_status_t status;

	status = gpio_reset_pin(&sl_gpio_pin_config_pwr_ctrl_gt);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_reset_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_reset_pin\r\n");
	}
#endif

	return status;
}

sl_status_t pwr_init(void)
{
	sl_status_t status;
	sl_i2c_status_t i2c_status;

	status = pwr_ctrl_gt_config();
#if DEBUG_DRV_PWR
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:pwr_ctrl_gt_config\r\n", status);
	} else {
		DEBUGOUT("Success:pwr_ctrl_gt_config\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	status = pwr_ctrl_gt_on();
#if DEBUG_DRV_PWR
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:pwr_ctrl_gt_on\r\n", status);
	} else {
		DEBUGOUT("Success:pwr_ctrl_gt_on\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	i2c_status = pwr_ctrl_eink_config();
#if DEBUG_DRV_PWR
	if (i2c_status != SL_I2C_SUCCESS) {
		DEBUGOUT("Error%u:pwr_ctrl_eink_config\r\n", i2c_status);
	} else {
		DEBUGOUT("Success:pwr_ctrl_eink_config\r\n");
	}
#endif
	if (i2c_status != SL_I2C_SUCCESS) {
		return i2c_status;
	}

	i2c_status = pwr_ctrl_eink_on();
#if DEBUG_DRV_PWR
	if (i2c_status != SL_I2C_SUCCESS) {
		DEBUGOUT("Error%u:pwr_ctrl_eink_on\r\n", i2c_status);
	} else {
		DEBUGOUT("Success:pwr_ctrl_eink_on\r\n");
	}
#endif

	return i2c_status;
}
