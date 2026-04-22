/***************************************************************************/ /**
* @file  config_timer_ocu_non_dma_example.h
* @brief Config Timer Basic features and Output Compare feature without DMA example
*******************************************************************************
* # License
* <b>Copyright 2025 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef UINK_TIMER_H
#define UINK_TIMER_H

#include "rsi_debug.h"
#include "sl_si91x_config_timer.h"

// -----------------------------------------------------------------------------
// Prototypes
/***************************************************************************/ /**
* Config-timer example initialization function
* Clock and Timer Configurations, timeout callback registration
* First use-case: At the configured timeout of timer, we generate peak reached message 
* in console. 
* Second use-case: counter0 produces PWM output with varying duty cycle and counter1
* produces square wave output
*
* @param none
* @return none
******************************************************************************/
sl_status_t timer_init(void);

#endif /* TIMER_H */
