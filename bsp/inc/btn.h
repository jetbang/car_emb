/**
 * Copyright (c) 2011-2016, Jack Mo (mobangjack@foxmail.com).
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

#ifndef __BTN_H___
#define __BTN_H___

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"

#define BTN_PIN PD10

#define BTN_IS_PRESSED() (GPIO_READ_IN(BTN_PIN) == 0)

void Btn_Config(void);

#ifdef __cplusplus
}
#endif

#endif
