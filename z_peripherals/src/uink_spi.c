/***************************************************************************/ /**
 * @file gspi_example.c
 * @brief GSPI examples functions
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#include "uink_spi.h"
#include "uink_debug.h"
#include "sl_si91x_gspi.h"
#include "sl_si91x_gspi_common_config.h"
/*******************************************************************************
 ***************************  Defines / Macros  ********************************
 ******************************************************************************/

/*******************************************************************************
 *************************** LOCAL VARIABLES   *******************************
 ******************************************************************************/
static sl_gspi_handle_t gspi_driver_handle = NULL;

/* 字库IC片选引脚 */
static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_gt_cs = {{SL_SI91X_GPIO_27_PORT, SL_SI91X_GPIO_27_PIN}, GPIO_OUTPUT};
/* 墨水屏片选引脚 */
static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_gspi_cs0 = {{SL_SI91X_GPIO_53_PORT, SL_SI91X_GPIO_53_PIN}, GPIO_OUTPUT};
/* LORA片选引脚 */
static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_gspi_cs1 = {{SL_SI91X_GPIO_54_PORT, SL_SI91X_GPIO_54_PIN}, GPIO_OUTPUT};
/* FLASH片选引脚 */
static sl_si91x_gpio_pin_config_t sl_gpio_pin_config_ext_flash_cs = {{SL_SI91X_GPIO_26_PORT, SL_SI91X_GPIO_26_PIN}, GPIO_OUTPUT};
/* GSPI所有片选引脚数组 */
static sl_si91x_gpio_pin_config_t *sl_gpio_pin_config_gspi_cs_array[GSPI_CS_NUM] = {&sl_gpio_pin_config_gspi_cs0,
																					&sl_gpio_pin_config_gspi_cs1,
																					&sl_gpio_pin_config_gt_cs,
																   	   	 	 	 	&sl_gpio_pin_config_ext_flash_cs};

/*******************************************************************************
 **********************  Local Function prototypes   ***************************
 ******************************************************************************/
static void callback_event(uint32_t event);
volatile boolean_t transfer_complete  = true;

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/
/*******************************************************************************
 * GSPI example initialization function
 ******************************************************************************/
static sl_status_t gspi_pin_init(void)
{
	uint8_t i;
	sl_status_t status;

	for (i = 0 ; i < GSPI_CS_NUM; i++) {
		status = gpio_pin_config(sl_gpio_pin_config_gspi_cs_array[i], GPIO_HZ, GPIO_TWO_MILLI_AMPS);
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
	}

	return status;
}

sl_status_t gspi_cs_low(uint8_t cs_index)
{
	sl_status_t status;

	status = gpio_reset_pin(sl_gpio_pin_config_gspi_cs_array[cs_index]);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_reset_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_reset_pin\r\n");
	}
#endif

	return status;
}

sl_status_t gspi_cs_high(uint8_t cs_index)
{
	sl_status_t status;

	status = gpio_set_pin(sl_gpio_pin_config_gspi_cs_array[cs_index]);
#if DEBUG_PPH_GPIO
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gpio_set_pin\r\n", status);
	} else {
		DEBUGOUT("Success:gpio_set_pin\r\n");
	}
#endif

	return status;
}

sl_status_t gspi_init(void)
{
	uint8_t i;
	sl_status_t status;

	status = gspi_pin_init();
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_pin_init\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_pin_init\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	for(i = 0; i < GSPI_CS_NUM; i++){
		status = gspi_cs_high(i);
#if DEBUG_PPH_GSPI
		if (status != SL_STATUS_OK) {
			DEBUGOUT("Error%lu:gspi_cs_high\r\n", status);
		} else {
			DEBUGOUT("Success:gspi_cs_high\r\n");
		}
#endif
		if (status != SL_STATUS_OK) {
			return status;
		}
	}

    status = sl_si91x_gspi_init(SL_GSPI_MASTER, &gspi_driver_handle);
#if DEBUG_SDK_GSPI
    if (status != SL_STATUS_OK) {
    	DEBUGOUT("Error%lu:sl_si91x_gspi_init\r\n", status);
    } else {
    	DEBUGOUT("Success:sl_si91x_gspi_init\r\n");
    }
#endif
    if (status != SL_STATUS_OK) {
    	return status;
    }

    status = sl_si91x_gspi_set_configuration(gspi_driver_handle, NULL);
#if DEBUG_SDK_GSPI
    if (status != SL_STATUS_OK) {
        DEBUGOUT("Error%lu:sl_si91x_gspi_set_configuration\r\n", status);
    } else {
        DEBUGOUT("Success:sl_si91x_gspi_set_configuration\r\n");
    }
#endif
    if (status != SL_STATUS_OK) {
    	return status;
    }

    status = sl_si91x_gspi_register_event_callback(gspi_driver_handle, callback_event);
#if DEBUG_SDK_GSPI
    if (status != SL_STATUS_OK) {
        DEBUGOUT("Error%lu:sl_si91x_gspi_register_event_callback\r\n", status);
    } else {
        DEBUGOUT("Success:sl_si91x_gspi_register_event_callback\r\n");
    }
#endif
    if (status != SL_STATUS_OK) {
    	return status;
    }

    status = sl_si91x_gspi_set_slave_number(GSPI_SLAVE_2);
#if DEBUG_SDK_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_si91x_gspi_set_slave_number\r\n", status);
	} else {
		DEBUGOUT("Success:sl_si91x_gspi_set_slave_number\r\n");
	}
#endif

	return status;
}

sl_status_t gspi_readWrite(uint8_t cs_index, uint8_t *data_out, uint8_t *data_in, uint32_t len)
{
	sl_status_t status;

	(void)cs_index;

	/*status = gspi_cs_low(cs_index);
#if DEBUG_PPH_GSPI
    if (status != SL_STATUS_OK) {
        DEBUGOUT("Error%lu:sl_si91x_gspi_register_event_callback\r\n", status);
    } else {
        DEBUGOUT("Success:sl_si91x_gspi_register_event_callback\r\n");
    }
#endif
    if (status != SL_STATUS_OK) {
    	return status;
    }*/

	status = sl_si91x_gspi_transfer_data(gspi_driver_handle, data_out, data_in, len);
#if DEBUG_SDK_GSPI
    if (status != SL_STATUS_OK) {
        DEBUGOUT("Error%lu:sl_si91x_gspi_register_event_callback\r\n", status);
    } else {
        DEBUGOUT("Success:sl_si91x_gspi_register_event_callback\r\n");
    }
#endif
    if (status != SL_STATUS_OK) {
    	return status;
    }

	/*status = gspi_cs_high(cs_index);
#if DEBUG_PPH_GSPI
    if (status != SL_STATUS_OK) {
        DEBUGOUT("Error%lu:sl_si91x_gspi_register_event_callback\r\n", status);
    } else {
        DEBUGOUT("Success:sl_si91x_gspi_register_event_callback\r\n");
    }
#endif*/

    return status;
}

sl_status_t gspi_write(uint8_t cs_index, const uint8_t *data_out, uint32_t len)
{
	sl_status_t status;

	(void)cs_index;

	//while(!transfer_complete);
	//transfer_complete = false;

	/*status = gspi_cs_low(cs_index);
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_cs_low\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_cs_low\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}*/

	status = sl_si91x_gspi_send_data(gspi_driver_handle, data_out, len);
#if DEBUG_SDK_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_si91x_gspi_send_data\r\n", status);
	} else {
		DEBUGOUT("Success:sl_si91x_gspi_send_data\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	/*status = gspi_cs_high(cs_index);
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_cs_high\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_cs_high\r\n");
	}
#endif*/

	return status;
}

sl_status_t gspi_read(uint8_t cs_index, uint8_t *data_in, uint32_t len)
{
	sl_status_t status;

	(void)cs_index;

	/*status = gspi_cs_low(cs_index);
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_cs_low\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_cs_low\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}*/

	status = sl_si91x_gspi_receive_data(gspi_driver_handle, data_in, len);
#if DEBUG_SDK_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:sl_si91x_gspi_receive_data\r\n", status);
	} else {
		DEBUGOUT("Success:sl_si91x_gspi_receive_data\r\n");
	}
#endif
	if (status != SL_STATUS_OK) {
		return status;
	}

	/*status = gspi_cs_high(cs_index);
#if DEBUG_PPH_GSPI
	if (status != SL_STATUS_OK) {
		DEBUGOUT("Error%lu:gspi_cs_high\r\n", status);
	} else {
		DEBUGOUT("Success:gspi_cs_high\r\n");
	}
#endif*/

	return status;
}

/*******************************************************************************
 * Callback event function
 * It is responsible for the event which are triggered by GSPI interface
 * It updates the respective member of the structure as the event is triggered.
 ******************************************************************************/
static void callback_event(uint32_t event)
{
  switch (event) {
    case SL_GSPI_TRANSFER_COMPLETE:
    	transfer_complete = true;
      break;
    case SL_GSPI_DATA_LOST:
      break;
    case SL_GSPI_MODE_FAULT:
      break;
  }
}


