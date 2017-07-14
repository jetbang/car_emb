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

#include "ist8310_int.h"

uint8_t IST8310_INT_Flag = 0;

static void IST8310_INT_Handler(uint8_t num)
{
	IST8310_INT_Flag = 1;
}

void IST8310_INT_Config(void)
{
    EXTI_Bind(IST8310_INT_PIN, IST8310_NVIC_PRE_PRIORITY, IST8310_NVIC_SUB_PRIORITY, EXTI_Trigger_Falling, IST8310_INT_Handler);
}
