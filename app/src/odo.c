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
 
#include "odo.h"

/**********************************************/
/*                  Odometer                  */
/**********************************************/

Odo_t odo;

static void GetPeriphsStateFdb(void)
{
	FS_Det(&odo.fs, FS_LASR, laser.ReadOut());
	FS_Det(&odo.fs, FS_FRIC, FRIC_IS_ON());
	//FS_Det(&odo.fs, FS_TRIG, laser.ReadOut());
}

static void GetMecanumStateFdb(void)
{
	uint8_t i = 0;
	for (i = 0; i < 4; i++) {
		odo.mp.w[i] = motor[i].angle_rad / MOTOR_REDUCTION_RATION;
		odo.mv.w[i] = motor[i].rate_rad / MOTOR_REDUCTION_RATION;
	}
}

static void GetChassisStateFdb(void)
{
	Mec_Synthe((float*)&odo.mv, (float*)&odo.cv);
	Mec_Synthe((float*)&odo.mp, (float*)&odo.cp);
}

static void GetPantiltStateFdb(void)
{
	odo.gp.p = motor[4].angle_rad;
	odo.gv.p = motor[4].rate_rad;
	odo.gp.t = motor[5].angle_rad;
	odo.gv.t = motor[5].rate_rad;
}

void Odo_Init(void)
{
	memset((void*)&odo, 0, sizeof(Odo_t));
}

void Odo_Proc(void)
{
	GetPeriphsStateFdb();
	GetMecanumStateFdb();
	GetChassisStateFdb();
	GetPantiltStateFdb();
}

