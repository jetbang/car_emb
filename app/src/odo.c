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

static void GetFunctionalStateFdb(void)
{
}

static void GetMecanumVelocityFdb(void)
{
	odo.mv.w1 = motor[0].rate_rad;
	odo.mv.w2 = motor[1].rate_rad;
	odo.mv.w3 = motor[2].rate_rad;
	odo.mv.w4 = motor[3].rate_rad;
}

static void GetMecanumPositionFdb(void)
{
	odo.mp.w1 = motor[0].angle_rad;
	odo.mp.w2 = motor[1].angle_rad;
	odo.mp.w3 = motor[2].angle_rad;
	odo.mp.w4 = motor[3].angle_rad;
}

static void GetChassisVelocityFdb(void)
{
	Mec_Synthe((float*)&odo.mv, (float*)&odo.cv);
	//odo.cv.z = zgyro.rate_rad;
}

static void GetChassisPositionFdb(void)
{
	//Mec_Synthe((float*)&odo.mp, (float*)&odo.cp);
	//odo.cp.z = zgyro.angle_rad;

}

static void GetGimbalsVelocityFdb(void)
{
	odo.gv.p = motor[4].rate_rad;
	odo.gv.t = motor[5].rate_rad;
}

static void GetGimbalsPositionFdb(void)
{
	odo.gp.p = motor[4].angle_rad;
	odo.gp.t = motor[5].angle_rad;
}

void Odo_Init(void)
{
	memset((void*)&odo, 0, sizeof(Odo_t));
}

void Odo_Proc(void)
{
	GetFunctionalStateFdb();
	GetMecanumVelocityFdb();
	GetMecanumPositionFdb();
	GetChassisVelocityFdb();
	GetChassisPositionFdb();
	GetGimbalsVelocityFdb();
	GetGimbalsPositionFdb();
}

void Odo_Zero(void)
{
	Can_Zero();
	
	memset(&odo.cp, 0, sizeof(ChassisState_t));
	memset(&odo.cv, 0, sizeof(ChassisState_t));
	memset(&odo.mp, 0, sizeof(MecanumState_t));
	memset(&odo.mv, 0, sizeof(MecanumState_t));
	memset(&odo.gp, 0, sizeof(GimbalsState_t));
	memset(&odo.gv, 0, sizeof(GimbalsState_t));
}

