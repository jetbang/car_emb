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

#include "act.h"

/**********************************/
/*             Action             */
/**********************************/

/*
#define SRS_ACT(FS,ID) do { \
	if (FS_Get(&ctl.fs, FS) && srs[ID].state == SR04_STATE_STOP) { \
		Srs_Start(ID); \
	} else if ((!FS_Get(&ctl.fs, FS)) && srs[ID].state != SR04_STATE_STOP) { \
		Srs_Stop(ID); \
	} \
} while (0)
	
*/

static void PeriphsStateAct(void)
{
	/*
	SRS_ACT(FS_SONAR_F,SR04_IDX_FIXED);
	SRS_ACT(FS_SONAR_M,SR04_IDX_MOBLE);
	SRS_ACT(FS_SONAR_L,SR04_IDX_LEFT);
	SRS_ACT(FS_SONAR_R,SR04_IDX_RIGHT);
	*/
}

static void ChassisStateAct(void)
{
	CM_CMD(ctl.mc.w1, ctl.mc.w2, ctl.mc.w3, ctl.mc.w4);
}

static void GrabberStateAct(void)
{
	//GM_CMD(0, ctl.gc.e);
	//GP_CMD((uint32_t)ctl.gc.c);
}

void Act_Init(void)
{
	CM_CMD(0, 0, 0, 0);
	//GM_CMD(0, 0);
	//GP_CMD(0);
	CLAW_PWM_1 = CLAW_PWM_2 = CLAW_PWM_3 = CLAW_PWM_4 = 0;
}

void Act_Proc(void)
{
	//PeriphsStateAct();
	ChassisStateAct();
	//LED_GREEN_OFF();
	//GrabberStateAct();
}
