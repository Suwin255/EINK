/***********************************************************************************
 * @file config_timer_ocu_non_dma_example.c
 * @brief Config Timer Basic features and Output Compare feature without DMA example
 ***********************************************************************************
 * # License
 * <b>Copyright 2025 Silicon Laboratories Inc. www.silabs.com</b>
 ****************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 *****************************************************************************/

/*==============================================================================
 * @brief : This files contains example describing usage of Configurable Timer
            APIs.
 * @section Description :
 * Counter mode Use-case :
 * One as free running timer. The timer instance is configured to generate peak 
 * reached console message.
 * The counter-0 is set to expire at 1-millisecond (1KHz) intervals.
 * PWM output mode Use-case :
 * Here it will generate 2 PWM outputs, Counter-1 will generate square wave
 * output (50%-duty cycle) and counter-0 will generates PWM output whose duty
 * cycle continuously varies from 100% to 0% then 0% to 100%.
 =============================================================================*/

/* Includes ------------------------------------------------------------------*/
#include "../../peripherals/inc/uink_timer.h"

/*******************************************************************************
 ***************************  Defines / Macros  ********************************
 ******************************************************************************/
#define CT_COUNTER_USED   SL_COUNTER_0 // counter number used for normal counter application
#define TIME_PERIOD_VALUE 1000         // Time period in microseconds

/*******************************************************************************
 **********************  GLOBAL variables   ***************************
 ******************************************************************************/

/*******************************************************************************
 **********************  Local Function prototypes   ***************************
 ******************************************************************************/
static void config_timer_callback(void *callback_flag);

/*******************************************************************************
 **********************  Local variables   ***************************
 ******************************************************************************/
static void *callback_flag_data;
volatile boolean_t interrupt_flag = false;

/*******************************************************************************
**************************   GLOBAL FUNCTIONS   *******************************
******************************************************************************/

/*******************************************************************************
 * Config-Timer example initialization function
 ******************************************************************************/
sl_status_t timer_init(void)
{
	sl_status_t status;
	uint32_t match_value;
	sl_config_timer_config_t ct_config;
	sl_config_timer_interrupt_flags_t ct_interrupt_flags;

	ct_config.is_counter_mode_32bit_enabled    = SL_COUNTER_16BIT;
	ct_config.counter0_direction               = SL_COUNTER0_UP;
	ct_config.is_counter0_periodic_enabled     = true;
	ct_config.is_counter0_sync_trigger_enabled = true;
	ct_config.counter1_direction               = SL_COUNTER0_UP;
	ct_config.is_counter1_periodic_enabled     = true;
	ct_config.is_counter1_sync_trigger_enabled = true;

	if (CT_COUNTER_USED == SL_COUNTER_0) {
		ct_interrupt_flags.is_counter0_hit_peak_interrupt_enabled = true;
	} else {
		ct_interrupt_flags.is_counter1_hit_peak_interrupt_enabled = true;
	}

    sl_si91x_config_timer_init();
    DEBUGOUT("Success:sl_si91x_config_timer_init\r\n");

    status = sl_si91x_config_timer_set_configuration(&ct_config);
#if DEBUG_SDK_TIMER
    if (status != SL_STATUS_OK) {
    	DEBUGOUT("Error%lu:sl_si91x_config_timer_set_configuration\r\n", status);
    }
    DEBUGOUT("Success:sl_si91x_config_timer_set_configuration\r\n");
#endif
    if (status != SL_STATUS_OK) {
    	return status;
    }

    status = sl_si91x_config_timer_get_match_value(TIME_PERIOD_VALUE, &match_value);
#if DEBUG_SDK_TIMER
    if (status != SL_STATUS_OK) {
    	DEBUGOUT("Error%lu:sl_si91x_config_timer_get_match_value\r\n", status);
    }
    DEBUGOUT("Success:sl_si91x_config_timer_get_match_value\r\n");
#endif
    if (status != SL_STATUS_OK) {
        return status;
    }

    status = sl_si91x_config_timer_register_callback(config_timer_callback, callback_flag_data, &ct_interrupt_flags);
#if DEBUG_SDK_TIMER
    if (status != SL_STATUS_OK) {
    	DEBUGOUT("Error%lu:sl_si91x_config_timer_register_callback\r\n", status);
    }
    DEBUGOUT("Success:sl_si91x_config_timer_register_callback\r\n");
#endif
    if (status != SL_STATUS_OK) {
        return status;
    }

    status = sl_si91x_config_timer_set_match_count(SL_COUNTER_16BIT, CT_COUNTER_USED, match_value);
#if DEBUG_SDK_TIMER
    if (status != SL_STATUS_OK) {
    	DEBUGOUT("Error%lu:sl_si91x_config_timer_set_match_count\r\n", status);
    }
    DEBUGOUT("Success:sl_si91x_config_timer_set_match_count\r\n");
#endif
    if (status != SL_STATUS_OK) {
        return status;
    }

    status = sl_si91x_config_timer_start_on_software_trigger(CT_COUNTER_USED);
#if DEBUG_SDK_TIMER
    if (status != SL_STATUS_OK) {
    	DEBUGOUT("Error%lu:sl_si91x_config_timer_start_on_software_trigger\r\n", status);
    }
    DEBUGOUT("Success:sl_si91x_config_timer_start_on_software_trigger\r\n");
#endif

    return status;
}

/*******************************************************************************
 * @brief         Config-Timer callback function
 * @return        none
 ******************************************************************************/
static void config_timer_callback(void *callback_flag)
{
	uint32_t interrupt_flag_value = 0;

	if (CT_COUNTER_USED == SL_COUNTER_0) {
		interrupt_flag_value = SL_CT_COUNTER_0_IS_PEAK_FLAG;
	} else {
		interrupt_flag_value = SL_CT_COUNTER_1_IS_PEAK_FLAG;
	}

	if (*(uint32_t *)callback_flag == interrupt_flag_value) {
		interrupt_flag = true;
	}
}
