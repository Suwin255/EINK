#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// $[USART0]
// [USART0]$

// $[UART1]
// [UART1]$

// $[ULP_UART]
// ULP_UART TX on ULP_GPIO_7/GPIO_71
#ifndef ULP_UART_TX_PORT                        
#define ULP_UART_TX_PORT                         ULP
#endif
#ifndef ULP_UART_TX_PIN                         
#define ULP_UART_TX_PIN                          7
#endif
#ifndef ULP_UART_TX_LOC                         
#define ULP_UART_TX_LOC                          0
#endif

// ULP_UART RX on ULP_GPIO_6/GPIO_70
#ifndef ULP_UART_RX_PORT                        
#define ULP_UART_RX_PORT                         ULP
#endif
#ifndef ULP_UART_RX_PIN                         
#define ULP_UART_RX_PIN                          6
#endif
#ifndef ULP_UART_RX_LOC                         
#define ULP_UART_RX_LOC                          2
#endif

// [ULP_UART]$

// $[I2C0]
// I2C0 SCL on GPIO_7
#ifndef I2C0_SCL_PORT                           
#define I2C0_SCL_PORT                            HP
#endif
#ifndef I2C0_SCL_PIN                            
#define I2C0_SCL_PIN                             7
#endif
#ifndef I2C0_SCL_LOC                            
#define I2C0_SCL_LOC                             0
#endif

// I2C0 SDA on GPIO_6
#ifndef I2C0_SDA_PORT                           
#define I2C0_SDA_PORT                            HP
#endif
#ifndef I2C0_SDA_PIN                            
#define I2C0_SDA_PIN                             6
#endif
#ifndef I2C0_SDA_LOC                            
#define I2C0_SDA_LOC                             3
#endif

// [I2C0]$

// $[I2C1]
// [I2C1]$

// $[ULP_I2C]
// [ULP_I2C]$

// $[SSI_MASTER]
// [SSI_MASTER]$

// $[SSI_SLAVE]
// [SSI_SLAVE]$

// $[ULP_SSI]
// [ULP_SSI]$

// $[GSPI_MASTER]
// GSPI_MASTER SCK_ on GPIO_52
#ifndef GSPI_MASTER_SCK__PORT                   
#define GSPI_MASTER_SCK__PORT                    HP
#endif
#ifndef GSPI_MASTER_SCK__PIN                    
#define GSPI_MASTER_SCK__PIN                     52
#endif
#ifndef GSPI_MASTER_SCK_LOC                     
#define GSPI_MASTER_SCK_LOC                      3
#endif

// GSPI_MASTER CS0_ on GPIO_28
#ifndef GSPI_MASTER_CS0__PORT                   
#define GSPI_MASTER_CS0__PORT                    HP
#endif
#ifndef GSPI_MASTER_CS0__PIN                    
#define GSPI_MASTER_CS0__PIN                     28
#endif
#ifndef GSPI_MASTER_CS0_LOC                     
#define GSPI_MASTER_CS0_LOC                      5
#endif

// GSPI_MASTER MOSI_ on GPIO_57
#ifndef GSPI_MASTER_MOSI__PORT                  
#define GSPI_MASTER_MOSI__PORT                   HP
#endif
#ifndef GSPI_MASTER_MOSI__PIN                   
#define GSPI_MASTER_MOSI__PIN                    57
#endif
#ifndef GSPI_MASTER_MOSI_LOC                    
#define GSPI_MASTER_MOSI_LOC                     19
#endif

// GSPI_MASTER MISO_ on GPIO_56
#ifndef GSPI_MASTER_MISO__PORT                  
#define GSPI_MASTER_MISO__PORT                   HP
#endif
#ifndef GSPI_MASTER_MISO__PIN                   
#define GSPI_MASTER_MISO__PIN                    56
#endif
#ifndef GSPI_MASTER_MISO_LOC                    
#define GSPI_MASTER_MISO_LOC                     24
#endif

// [GSPI_MASTER]$

// $[I2S0]
// [I2S0]$

// $[ULP_I2S]
// [ULP_I2S]$

// $[SCT]
// SCT IN0 on GPIO_25
#ifndef SCT_IN0_PORT                            
#define SCT_IN0_PORT                             HP
#endif
#ifndef SCT_IN0_PIN                             
#define SCT_IN0_PIN                              25
#endif
#ifndef SCT_IN0_LOC                             
#define SCT_IN0_LOC                              0
#endif

// SCT OUT0 on GPIO_29
#ifndef SCT_OUT0_PORT                           
#define SCT_OUT0_PORT                            HP
#endif
#ifndef SCT_OUT0_PIN                            
#define SCT_OUT0_PIN                             29
#endif
#ifndef SCT_OUT0_LOC                            
#define SCT_OUT0_LOC                             10
#endif

// SCT OUT1 on GPIO_30
#ifndef SCT_OUT1_PORT                           
#define SCT_OUT1_PORT                            HP
#endif
#ifndef SCT_OUT1_PIN                            
#define SCT_OUT1_PIN                             30
#endif
#ifndef SCT_OUT1_LOC                            
#define SCT_OUT1_LOC                             12
#endif

// [SCT]$

// $[SIO]
// [SIO]$

// $[PWM]
// [PWM]$

// $[PWM_CH0]
// [PWM_CH0]$

// $[PWM_CH1]
// [PWM_CH1]$

// $[PWM_CH2]
// [PWM_CH2]$

// $[PWM_CH3]
// [PWM_CH3]$

// $[ADC_CH1]
// [ADC_CH1]$

// $[ADC_CH2]
// [ADC_CH2]$

// $[ADC_CH3]
// [ADC_CH3]$

// $[ADC_CH4]
// [ADC_CH4]$

// $[ADC_CH5]
// [ADC_CH5]$

// $[ADC_CH6]
// [ADC_CH6]$

// $[ADC_CH7]
// [ADC_CH7]$

// $[ADC_CH8]
// [ADC_CH8]$

// $[ADC_CH9]
// [ADC_CH9]$

// $[ADC_CH10]
// [ADC_CH10]$

// $[ADC_CH11]
// [ADC_CH11]$

// $[ADC_CH12]
// [ADC_CH12]$

// $[ADC_CH13]
// [ADC_CH13]$

// $[ADC_CH14]
// [ADC_CH14]$

// $[ADC_CH15]
// [ADC_CH15]$

// $[ADC_CH16]
// [ADC_CH16]$

// $[ADC_CH17]
// [ADC_CH17]$

// $[ADC_CH18]
// [ADC_CH18]$

// $[ADC_CH19]
// [ADC_CH19]$

// $[COMP1]
// [COMP1]$

// $[COMP2]
// [COMP2]$

// $[DAC0]
// [DAC0]$

// $[DAC1]
// [DAC1]$

// $[SYSRTC]
// [SYSRTC]$

// $[UULP_VBAT_GPIO]
// [UULP_VBAT_GPIO]$

// $[GPIO]
// [GPIO]$

// $[QEI]
// [QEI]$

// $[HSPI_SECONDARY]
// [HSPI_SECONDARY]$

// $[OPAMP1]
// [OPAMP1]$

// $[OPAMP2]
// [OPAMP2]$

// $[OPAMP3]
// [OPAMP3]$

// $[SDC_CH1]
// [SDC_CH1]$

// $[SDC_CH2]
// [SDC_CH2]$

// $[SDC_CH3]
// [SDC_CH3]$

// $[SDC_CH4]
// [SDC_CH4]$

// $[CUSTOM_PIN_NAME]
#ifndef _PORT                                   
#define _PORT                                    HP
#endif
#ifndef _PIN                                    
#define _PIN                                     6
#endif

// [CUSTOM_PIN_NAME]$

#endif // PIN_CONFIG_H
