/***************************************************************************/ /**
* @file i2c_leader_example.c
* @brief I2C Leader Blocking example functions
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
#include "../../peripherals/inc/uink_i2c.h"

#include "sl_i2c_instances.h"
#include "sl_si91x_peripheral_i2c.h"

/*******************************************************************************
 ***************************  Defines / Macros  ********************************
 ******************************************************************************/
#define INSTANCE_ZERO 0 // For instance 0
#define INSTANCE_ONE  1 // For instance 1
#define INSTANCE_TWO  2 // For ulp instance (instance 2)

#define I2C_TX_FIFO_THRESHOLD    0     // FIFO threshold
#define I2C_RX_FIFO_THRESHOLD    0     // FIFO threshold
/*******************************************************************************
 ******************************  Data Types  ***********************************
 ******************************************************************************/

/*******************************************************************************
 *************************** LOCAL VARIABLES   *******************************
 ******************************************************************************/
static sl_i2c_instance_t i2c_instance = INSTANCE_ZERO;

/*******************************************************************************
 **********************  Local Function prototypes   ***************************
 ******************************************************************************/

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/*******************************************************************************
 * I2C initialization function
 ******************************************************************************/
sl_i2c_status_t i2c_init(void)
{
	sl_i2c_status_t i2c_status;

	i2c_status = sl_i2c_driver_init(i2c_instance, &sl_i2c_i2c0_config);
#if DEBUG_SDK_I2C
	if (i2c_status != SL_I2C_SUCCESS) {
		DEBUGOUT("Error%u:sl_i2c_driver_init\r\n", i2c_status);
	} else {
		DEBUGOUT("Success:sl_i2c_driver_init\r\n");
	}
#endif
	if (i2c_status != SL_I2C_SUCCESS) {
		return i2c_status;
	}

	i2c_status = sl_i2c_driver_configure_fifo_threshold(i2c_instance, I2C_TX_FIFO_THRESHOLD, I2C_RX_FIFO_THRESHOLD);
#if DEBUG_SDK_I2C
	if (i2c_status != SL_I2C_SUCCESS) {
		DEBUGOUT("Error%u:sl_i2c_driver_configure_fifo_threshold\r\n", i2c_status);
	} else {
		DEBUGOUT("Success:sl_i2c_driver_configure_fifo_threshold\r\n");
	}
#endif
	if (i2c_status != SL_I2C_SUCCESS) {
		return i2c_status;
	}

	i2c_status = sl_i2c_driver_enable_repeated_start(i2c_instance, false);
#if DEBUG_SDK_I2C
	if (i2c_status != SL_I2C_SUCCESS) {
		DEBUGOUT("Error%u:sl_i2c_driver_enable_repeated_start\r\n", i2c_status);
	} else {
		DEBUGOUT("Success:sl_i2c_driver_enable_repeated_start\r\n");
	}
#endif

	return i2c_status;
}

sl_i2c_status_t i2c_send(uint16_t addr, uint8_t *buffer, uint32_t len)
{
	sl_i2c_status_t i2c_status;

	i2c_status = sl_i2c_driver_send_data_blocking(i2c_instance, addr, buffer, len);
#if DEBUG_SDK_I2C
	if (i2c_status != SL_I2C_SUCCESS) {
		DEBUGOUT("Error%u:sl_i2c_driver_send_data_blocking\r\n", i2c_status);
	} else {
		DEBUGOUT("Success:sl_i2c_driver_send_data_blocking\r\n");
	}
#endif

	return i2c_status;
}










