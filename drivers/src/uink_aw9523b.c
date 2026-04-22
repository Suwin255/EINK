#include "../../drivers/inc/uink_aw9523b.h"

uint8_t DIM_Array[2][8] = {{AW9523B_REG_DIM4, AW9523B_REG_DIM5, AW9523B_REG_DIM6, AW9523B_REG_DIM7, AW9523B_REG_DIM8, AW9523B_REG_DIM9, AW9523B_REG_DIM10, AW9523B_REG_DIM11},
                           {AW9523B_REG_DIM0, AW9523B_REG_DIM1, AW9523B_REG_DIM2, AW9523B_REG_DIM3, AW9523B_REG_DIM12, AW9523B_REG_DIM13, AW9523B_REG_DIM14, AW9523B_REG_DIM15}};

aw9523b_reg_t g_aw9523b_reg;

void aw9523b_init(void)
{
	g_aw9523b_reg.aw9523b_output_p0 = 0x00;
	g_aw9523b_reg.aw9523b_output_p1 = 0x0F;

	g_aw9523b_reg.aw9523b_config_p0 = 0x00;
	g_aw9523b_reg.aw9523b_config_p1 = 0x00;

	g_aw9523b_reg.aw9523b_int_p0 = 0x00;
	g_aw9523b_reg.aw9523b_int_p1 = 0x00;

	g_aw9523b_reg.aw9523b_ledModeSwitch_p0 = 0xFF;
	g_aw9523b_reg.aw9523b_ledModeSwitch_p1 = 0xFF;
}

sl_i2c_status_t aw9523b_gpio_config(aw9523b_gpioConfig_t *aw9523b_gpioConfig)
{
	sl_i2c_status_t i2c_status;
	uint8_t buffer[2];
    uint8_t mask = ((uint8_t)1)<<aw9523b_gpioConfig->pin;

    if(aw9523b_gpioConfig->port == AW9523B_PORT_0)
    {
        //配置方向
        if(aw9523b_gpioConfig->direction == AW9523B_DIRECTION_INPUT) {
        	g_aw9523b_reg.aw9523b_config_p0 |= mask;
        } else if (aw9523b_gpioConfig->direction == AW9523B_DIRECTION_OUTPUT) {
        	g_aw9523b_reg.aw9523b_config_p0 &= ~mask;
        }

        buffer[0] = AW9523B_REG_CONFIG_P0;
        buffer[1] = g_aw9523b_reg.aw9523b_config_p0;

        i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
        if (i2c_status != SL_I2C_SUCCESS) {
        	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
        } else {
        	DEBUGOUT("Success:i2c_send\r\n");
        }
#endif
        if (i2c_status != SL_I2C_SUCCESS) {
        	return i2c_status;
        }
        
        //配置模式
        if(aw9523b_gpioConfig->mode == AW9523B_MODE_GPIO) {
        	g_aw9523b_reg.aw9523b_ledModeSwitch_p0 |= mask;
        } else if (aw9523b_gpioConfig->mode == AW9523B_MODE_LED) {
        	g_aw9523b_reg.aw9523b_ledModeSwitch_p0 &= ~mask;
        }

        buffer[0] = AW9523B_REG_LEDMODESWITCH_P0;
        buffer[1] = g_aw9523b_reg.aw9523b_ledModeSwitch_p0;

        i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
        if (i2c_status != SL_I2C_SUCCESS) {
        	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
        } else {
        	DEBUGOUT("Success:i2c_send\r\n");
        }
#endif
        if (i2c_status != SL_I2C_SUCCESS) {
        	return i2c_status;
        }
        
        //配置中断
        if(aw9523b_gpioConfig->inten == AW9523B_INTEN_DISABLE) {
        	g_aw9523b_reg.aw9523b_int_p0 |= mask;
        } else if (aw9523b_gpioConfig->inten == AW9523B_INTEN_ENABLE) {
        	g_aw9523b_reg.aw9523b_int_p0 &= ~mask;
        }

        buffer[0] = AW9523B_REG_INT_P0;
        buffer[1] = g_aw9523b_reg.aw9523b_int_p0;

        i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
        if (i2c_status != SL_I2C_SUCCESS) {
        	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
        } else {
        	DEBUGOUT("Success:i2c_send\r\n");
        }
#endif
        if (i2c_status != SL_I2C_SUCCESS) {
        	return i2c_status;
        }
    }
    else if(aw9523b_gpioConfig->port == AW9523B_PORT_1)
    {
        //配置方向
        if(aw9523b_gpioConfig->direction == AW9523B_DIRECTION_INPUT) {
        	g_aw9523b_reg.aw9523b_config_p1 |= mask;
        } else if (aw9523b_gpioConfig->direction == AW9523B_DIRECTION_OUTPUT) {
        	g_aw9523b_reg.aw9523b_config_p1 &= ~mask;
        }

        buffer[0] = AW9523B_REG_CONFIG_P1;
        buffer[1] = g_aw9523b_reg.aw9523b_config_p1;

        i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
        if (i2c_status != SL_I2C_SUCCESS) {
        	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
        } else {
        	DEBUGOUT("Success:i2c_send\r\n");
        }
#endif
        if (i2c_status != SL_I2C_SUCCESS) {
        	return i2c_status;
        }

        //配置模式
        if(aw9523b_gpioConfig->mode == AW9523B_MODE_GPIO) {
        	g_aw9523b_reg.aw9523b_ledModeSwitch_p1 |= mask;
        } else if (aw9523b_gpioConfig->mode == AW9523B_MODE_LED) {
        	g_aw9523b_reg.aw9523b_ledModeSwitch_p1 &= ~mask;
        }

        buffer[0] = AW9523B_REG_LEDMODESWITCH_P1;
        buffer[1] = g_aw9523b_reg.aw9523b_ledModeSwitch_p1;

        i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
        if (i2c_status != SL_I2C_SUCCESS) {
        	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
        } else {
        	DEBUGOUT("Success:i2c_send\r\n");
        }
#endif
        if (i2c_status != SL_I2C_SUCCESS) {
        	return i2c_status;
        }

        //配置中断
        if(aw9523b_gpioConfig->inten == AW9523B_INTEN_DISABLE) {
        	g_aw9523b_reg.aw9523b_int_p1 |= mask;
        } else if (aw9523b_gpioConfig->inten == AW9523B_INTEN_ENABLE) {
        	g_aw9523b_reg.aw9523b_int_p1 &= ~mask;
        }

        buffer[0] = AW9523B_REG_INT_P1;
        buffer[1] = g_aw9523b_reg.aw9523b_int_p1;

        i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
        if (i2c_status != SL_I2C_SUCCESS) {
        	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
        } else {
        	DEBUGOUT("Success:i2c_send\r\n");
        }
#endif
        if (i2c_status != SL_I2C_SUCCESS) {
        	return i2c_status;
        }
    }

    //配置强度        
    buffer[0] = DIM_Array[aw9523b_gpioConfig->port][aw9523b_gpioConfig->pin];
    buffer[1] = aw9523b_gpioConfig->strength;

    i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
    if (i2c_status != SL_I2C_SUCCESS) {
    	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
    } else {
    	DEBUGOUT("Success:i2c_send\r\n");
    }
#endif

    return i2c_status;
}

sl_i2c_status_t aw9523b_gpio_pin_setOutput(aw9523b_port_t port, uint8_t pin)
{
	sl_i2c_status_t i2c_status;
	uint8_t buffer[2];
    uint8_t mask = ((uint8_t)1)<<pin;

    if(port == AW9523B_PORT_0)
    {
    	g_aw9523b_reg.aw9523b_output_p0 |= mask;
        
        buffer[0] = AW9523B_REG_OUTPUT_P0;
        buffer[1] = g_aw9523b_reg.aw9523b_output_p0;
    }           
    else if(port == AW9523B_PORT_1)
    {
    	g_aw9523b_reg.aw9523b_output_p1 |= mask;
        
        buffer[0] = AW9523B_REG_OUTPUT_P1;
        buffer[1] = g_aw9523b_reg.aw9523b_output_p1;
    } 

    i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
    if (i2c_status != SL_I2C_SUCCESS) {
    	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
    } else {
    	DEBUGOUT("Success:i2c_send\r\n");
    }
#endif

    return i2c_status;
}

sl_i2c_status_t aw9523b_gpio_pin_resetOutput(aw9523b_port_t port, uint8_t pin)
{
	sl_i2c_status_t i2c_status;
	uint8_t buffer[2];
    uint8_t mask = ((uint8_t)1)<<pin;

    if(port == AW9523B_PORT_0)
    {
    	g_aw9523b_reg.aw9523b_output_p0 &= ~mask;
        
        buffer[0] = AW9523B_REG_OUTPUT_P0;
        buffer[1] = g_aw9523b_reg.aw9523b_output_p0;
    }           
    else if(port == AW9523B_PORT_1)
    {
    	printf("mask:%d\n", mask);
    	printf("AW9523B_Output_P1:%d\n", g_aw9523b_reg.aw9523b_output_p1);
    	g_aw9523b_reg.aw9523b_output_p1 &= ~mask;
        
        buffer[0] = AW9523B_REG_OUTPUT_P1;
        buffer[1] = g_aw9523b_reg.aw9523b_output_p1;

        printf("AW9523B_Output_P1:%d\n", g_aw9523b_reg.aw9523b_output_p1);
    } 

    i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
    if (i2c_status != SL_I2C_SUCCESS) {
    	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
    } else {
    	DEBUGOUT("Success:i2c_send\r\n");
    }
#endif

    return i2c_status;
}

sl_i2c_status_t aw9523b_gpio_pin_setStrength(aw9523b_port_t port, uint8_t pin, uint8_t strength)
{
	sl_i2c_status_t i2c_status;
	uint8_t buffer[2];

    buffer[0] = DIM_Array[port][pin];
    buffer[1] = strength; 

    i2c_status = i2c_send(AW9523B_I2C_ADDR, buffer, 2);
#if DEBUG_PPH_I2C
    if (i2c_status != SL_I2C_SUCCESS) {
    	DEBUGOUT("Error%u:i2c_send\r\n", i2c_status);
    } else {
    	DEBUGOUT("Success:i2c_send\r\n");
    }
#endif

    return i2c_status;
}
