/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ist8310_i2c.h"

uint8_t IST8310_I2C_Write_Reg(uint8_t addr, uint8_t data) {
	uint8_t flag = 0;

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_ADDR,
			0x7f & IST8310_ADDRESS);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_REG, addr);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_DO, data);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_CTRL, 0x80 | 0x01);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	return flag;
}

uint8_t IST8310_I2C_Read_Reg(uint8_t addr, uint8_t* data) {
	uint8_t flag = 0;

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV4_ADDR,
			0x80 | IST8310_ADDRESS);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);
	
	IST8310_I2C_DELAY(10);
	
	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV4_REG, addr);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV4_CTRL, 0x80);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_MASTER_READ(MPU6500_I2C_SLV4_DI, data);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV4_CTRL, 0x00);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);
	
	IST8310_I2C_DELAY(10);
	
	return flag;
}


