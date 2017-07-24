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

#ifndef __LASER_H__
#define __LASER_H__

#ifdef __cpluplus
extern "C" {
#endif

#include "stm32util.h"
#include "hal_gpio.h"

#define LASER_PIN PG13
#define LASER_WRITE(VAL) GPIO_WRITE(LASER_PIN, VAL)
#define LASER_ON() LASER_WRITE(1)
#define LASER_OFF() LASER_WRITE(0)

void Laser_Config(void);

uint8_t Laser_ReadIn(void);
uint8_t Laser_ReadOut(void);
void Laser_Write(uint8_t val);
void Laser_Toggle(void);

extern const Hal_Gpio_t laser;

#ifdef __cpluplus
}
#endif

#endif
