/***************************************************************************//**
 * @file sl_si91x_ulp_uart_common_config.h
 * @brief SL SI91X ULP UART Common Config.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_SI91X_ULP_UART_COMMON_CONFIG_H
#define SL_SI91X_ULP_UART_COMMON_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h>DMA Configuration

// <q SL_ULPUART_DMA_CONFIG_ENABLE> ULP UART DMA
// <i> Default: 1
#define SL_ULPUART_DMA_CONFIG_ENABLE 1

// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <ulp_uart signal=TX,RX> SL_ULP_UART
// $[ULP_UART_SL_ULP_UART]
#ifndef SL_ULP_UART_PERIPHERAL                  
#define SL_ULP_UART_PERIPHERAL                   ULP_UART
#endif

// ULP_UART TX on ULP_GPIO_7/GPIO_71
#ifndef SL_ULP_UART_TX_PORT                     
#define SL_ULP_UART_TX_PORT                      ULP
#endif
#ifndef SL_ULP_UART_TX_PIN                      
#define SL_ULP_UART_TX_PIN                       7
#endif
#ifndef SL_ULP_UART_TX_LOC                      
#define SL_ULP_UART_TX_LOC                       0
#endif

// ULP_UART RX on ULP_GPIO_6/GPIO_70
#ifndef SL_ULP_UART_RX_PORT                     
#define SL_ULP_UART_RX_PORT                      ULP
#endif
#ifndef SL_ULP_UART_RX_PIN                      
#define SL_ULP_UART_RX_PIN                       6
#endif
#ifndef SL_ULP_UART_RX_LOC                      
#define SL_ULP_UART_RX_LOC                       2
#endif
// [ULP_UART_SL_ULP_UART]$
// <<< sl:end pin_tool >>>

#endif // SL_SI91X_ULP_UART_COMMON_CONFIG_H
