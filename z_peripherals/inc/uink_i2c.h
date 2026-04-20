/***************************************************************************/ /**
 * @file i2c_leader_example.h
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
#ifndef UINK_I2C_H
#define UINK_I2C_H

#include "rsi_debug.h"
#include "sl_si91x_i2c.h"

// -----------------------------------------------------------------------------
// Prototypes
/***************************************************************************/ /**
 * It is an initialization function, it initializes the clock, pin configuration
 * init_para for I2C communication.
 * 
 * @param none
 * @return none
 ******************************************************************************/
sl_i2c_status_t i2c_init(void);
sl_i2c_status_t i2c_send(uint16_t addr, uint8_t *buffer, uint32_t len);

#endif /* I2C_H */
