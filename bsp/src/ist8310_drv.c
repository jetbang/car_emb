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

#include "ist8310_drv.h"

uint8_t IST8310_AuxCfg(void) {
	uint8_t flag = 0;

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_ADDR, IST8310_ADDRESS);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_REG, IST8310_R_CONFA);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_DO, IST8310_ODR_MODE);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV0_ADDR,
			0x80 | IST8310_ADDRESS);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV0_REG, IST8310_R_XL);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV4_CTRL, 0x03);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	IST8310_I2C_MASTER_WRITE(MPU6500_I2C_MST_DELAY_CTRL, 0x01 | 0x02); // Enable slave0 delay and slave1 delay
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(2);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_CTRL, 0x80 | 0x01); // Enable slave1 with length 0x01
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(6);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV0_CTRL, 0x80 | 0x06); // Enable slave0 with length @data_num
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(7);

	return flag;
}

uint8_t IST8310_Init(void) {
	uint8_t flag = 0, data = 0;

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_USER_CTRL, 0x30);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_MST_CTRL, 0x0d);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_ADDR, IST8310_ADDRESS);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV4_ADDR,
			0x80 | IST8310_ADDRESS);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_Write_Reg(IST8310_R_CONFB, 0x01);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_Read_Reg(IST8310_WHO_AM_I, &data);
	flag &= (data == IST8310_DEVICE_ID_A);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_Write_Reg(IST8310_R_CONFA, 0x00);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	flag = IST8310_I2C_Read_Reg(IST8310_R_CONFA, &data);
	flag &= (data == 0x00);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_Write_Reg(IST8310_R_CONFB, 0x00);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	flag = IST8310_I2C_Read_Reg(IST8310_R_CONFB, &data);
	flag &= (data == 0x00);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_Write_Reg(IST8310_AVGCNTL, 0x24);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	flag = IST8310_I2C_Read_Reg(IST8310_AVGCNTL, &data);
	flag &= (data == 0x24);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_Write_Reg(IST8310_PDCNTL, 0xc0);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	flag = IST8310_I2C_Read_Reg(IST8310_PDCNTL, &data);
	flag &= (data == 0xc0);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV1_CTRL, 0x00);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_I2C_MASTER_WRITE(MPU6500_I2C_SLV4_CTRL, 0x00);
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	flag = IST8310_AuxCfg();
	RETURN_ZERO_IF_ASSERT_FAILED(flag);

	IST8310_I2C_DELAY(10);

	return flag;
}

uint8_t IST8310_Read(uint8_t* buf)
{
	uint8_t i = 0, flag = 0;
	for (i = 0; i < IST8310_BUF_SIZE; i++) {
		flag = IST8310_I2C_MASTER_READ(IST8310_R_XL + i, buf + i);
		RETURN_ZERO_IF_ASSERT_FAILED(flag);
		IST8310_I2C_DELAY(2);
	}
	return 1;
}

