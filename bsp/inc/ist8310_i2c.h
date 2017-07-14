#ifndef __IST8310_I2C_H__
#define __IST8310_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "mpu6500_drv.h"
#include "delay.h"

#define IST8310_I2C_MASTER_READ(ADDR, DATA) MPU6500_SPI_Read_Reg(ADDR, DATA)
#define IST8310_I2C_MASTER_WRITE(ADDR, DATA) MPU6500_SPI_Write_Reg(ADDR, DATA)

#define IST8310_I2C_DELAY(TICK) Delay_Ms(TICK)

uint8_t IST8310_I2C_Write_Reg(uint8_t addr, uint8_t data);
uint8_t IST8310_I2C_Read_Reg(uint8_t addr, uint8_t* data);

#ifdef __cplusplus
}
#endif

#endif
