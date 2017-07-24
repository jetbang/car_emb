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

#include "laser.h"

const Hal_Gpio_t laser = HAL_GPIO_DEF(Laser);

void Laser_Config(void)
{
	GPIO_Out(LASER_PIN);
	LASER_OFF();
}

uint8_t Laser_ReadIn(void)
{
	return GPIO_READ_IN(LASER_PIN);
}

uint8_t Laser_ReadOut(void)
{
	return GPIO_READ_OUT(LASER_PIN);
}

void Laser_Write(uint8_t val)
{
	GPIO_WRITE(LASER_PIN, val);
}

void Laser_Toggle(void)
{
	GPIO_TOG(LASER_PIN);
}


