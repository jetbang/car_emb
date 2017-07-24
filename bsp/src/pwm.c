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
 
#include "pwm.h"

void Pwm_Config(void)
{
	PWM_Bind(FRIC_PWM_PIN_1, FRIC_PWM_PIN_2, FRIC_PWM_PIN_3, FRIC_PWM_PIN_4,
	    	 FRIC_PWM_TIM,
			 FRIC_PWM_TIM_PS,
			 FRIC_PWM_TIM_PD,
			 FRIC_PWM_TIM_PW);

    PWM_Bind(CLAW_PWM_PIN_1, CLAW_PWM_PIN_2, CLAW_PWM_PIN_3, CLAW_PWM_PIN_4,
    	 CLAW_PWM_TIM,
			 CLAW_PWM_TIM_PS,
			 CLAW_PWM_TIM_PD,
			 CLAW_PWM_TIM_PW);

    TIM_Cmd(FRIC_PWM_TIM, ENABLE);
    TIM_Cmd(CLAW_PWM_TIM, ENABLE);

    FRIC_OFF();
	CLAW_OPEN();
}

