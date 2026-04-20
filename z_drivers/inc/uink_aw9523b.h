#ifndef UINK_AW9523B_H
#define UINK_AW9523B_H

#include "rsi_debug.h"
#include "uink_i2c.h"

#define AW9523B_I2C_ADDR                0x59

#define AW9523B_REG_INPUT_P0            0x00
#define AW9523B_REG_INPUT_P1            0x01
#define AW9523B_REG_OUTPUT_P0           0x02
#define AW9523B_REG_OUTPUT_P1           0x03
#define AW9523B_REG_CONFIG_P0           0x04
#define AW9523B_REG_CONFIG_P1           0x05
#define AW9523B_REG_INT_P0              0x06
#define AW9523B_REG_INT_P1              0x07

#define AW9523B_REG_ID                  0x10
#define AW9523B_REG_CTL                 0x11
#define AW9523B_REG_LEDMODESWITCH_P0    0x12
#define AW9523B_REG_LEDMODESWITCH_P1    0x13

#define AW9523B_REG_DIM0                0x20
#define AW9523B_REG_DIM1                0x21
#define AW9523B_REG_DIM2                0x22
#define AW9523B_REG_DIM3                0x23
#define AW9523B_REG_DIM4                0x24
#define AW9523B_REG_DIM5                0x25
#define AW9523B_REG_DIM6                0x26
#define AW9523B_REG_DIM7                0x27
#define AW9523B_REG_DIM8                0x28
#define AW9523B_REG_DIM9                0x29
#define AW9523B_REG_DIM10               0x2A
#define AW9523B_REG_DIM11               0x2B
#define AW9523B_REG_DIM12               0x2C
#define AW9523B_REG_DIM13               0x2D
#define AW9523B_REG_DIM14               0x2E
#define AW9523B_REG_DIM15               0x2F

#define AW9523B_REG_SWRSTN              0x7F

typedef enum
{
    AW9523B_INTEN_ENABLE,
    AW9523B_INTEN_DISABLE,
}aw9523b_inten_t;

typedef enum
{
    AW9523B_PORT_0,
    AW9523B_PORT_1,
}aw9523b_port_t;

typedef enum
{
    AW9523B_MODE_LED,
    AW9523B_MODE_GPIO,
}aw9523b_mode_t;

typedef enum
{
    AW9523B_DIRECTION_OUTPUT,
    AW9523B_DIRECTION_INPUT,
}aw9523b_direction_t;

typedef struct
{
    uint8_t pin;    
    aw9523b_port_t port;
    aw9523b_mode_t mode;
    aw9523b_inten_t inten;
    aw9523b_direction_t direction;
    uint8_t strength;
}aw9523b_gpioConfig_t;

typedef struct
{
	uint8_t aw9523b_output_p0;
	uint8_t aw9523b_output_p1;

	uint8_t aw9523b_config_p0;
	uint8_t aw9523b_config_p1;

	uint8_t aw9523b_int_p0;
	uint8_t aw9523b_int_p1;

	uint8_t aw9523b_ledModeSwitch_p0;
	uint8_t aw9523b_ledModeSwitch_p1;
}aw9523b_reg_t;

void aw9523b_init(void);

sl_i2c_status_t aw9523b_gpio_config(aw9523b_gpioConfig_t *aw9523b_gpioConfig);

sl_i2c_status_t aw9523b_gpio_pin_setOutput(aw9523b_port_t port, uint8_t pin);
sl_i2c_status_t aw9523b_gpio_pin_resetOutput(aw9523b_port_t port, uint8_t pin);
sl_i2c_status_t aw9523b_gpio_pin_setStrength(aw9523b_port_t port, uint8_t pin, uint8_t strength);

#endif
