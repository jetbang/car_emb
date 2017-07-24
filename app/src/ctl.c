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
 
#include "ctl.h"

/**********************************************/
/*              Logic Controller              */
/**********************************************/

Ctl_t ctl;
Pid_t pid;
Rmp_t rmp;

static void RmpGeneraterCtl(void)
{
	Rmp_Calc(&rmp);
}

static void PeriphsStateCtl(void)
{
	FS_Cpy(&ctl.fs, cmd.fs, FS_ALL);
}

static void ChassisStateCtl(void)
{
	uint8_t i = 0;

	ctl.cv.x = cmd.cv.x;
	ctl.cv.y = cmd.cv.y;
	ctl.cv.z = cmd.cv.z;

	Mec_Decomp((float*)&ctl.cv, (float*)&ctl.mv);

	for (i = 0; i < CCL_NUM; i++) {
		ctl.mc.w[i] = PID_Calc(&pid.cv.w[i], ctl.mv.w[i], odo.mv.w[i]) * rmp.out;
	}
}

static void PantiltStateCtl(void)
{
	ctl.gv.p = PID_Calc(&pid.gp.p, cmd.gp.p, odo.gp.p);
	ctl.gv.t = PID_Calc(&pid.gp.t, cmd.gp.t, odo.gp.t);
	ctl.gc.p = PID_Calc(&pid.gv.p, ctl.gv.p, odo.gv.p) * rmp.out;
	ctl.gc.t = PID_Calc(&pid.gv.t, ctl.gv.t, odo.gv.t) * rmp.out;;
}

static void Rmp_Init(Rmp_t* rmp)
{
	Rmp_Config(rmp, cfg.rmp.cnt);
	Rmp_Reset(rmp);
}

static void Cpl_Init(PID_t* pid)
{
	PID_Config(pid, 
		 cfg.cpl.kp, 
		 cfg.cpl.ki, 
		 cfg.cpl.kd, 
		 cfg.cpl.db,
		 cfg.cpl.it,
		 cfg.cpl.Emax,
		 cfg.cpl.Pmax, 
		 cfg.cpl.Imax, 
		 cfg.cpl.Dmax, 
		 cfg.cpl.Omax);
	PID_Reset(pid);
}

static void Cvl_Init(PID_t* pid)
{
	PID_Config(pid, 
		 cfg.cvl.kp, 
		 cfg.cvl.ki, 
		 cfg.cvl.kd, 
		 cfg.cvl.db,
		 cfg.cvl.it,
		 cfg.cvl.Emax,
		 cfg.cvl.Pmax, 
		 cfg.cvl.Imax, 
		 cfg.cvl.Dmax, 
		 cfg.cvl.Omax);
	PID_Reset(pid);
}

static void Gvl_Init(PID_t* pid)
{
	PID_Config(pid, 
		 cfg.gvl.kp, 
		 cfg.gvl.ki, 
		 cfg.gvl.kd, 
		 cfg.gvl.db,
		 cfg.gvl.it,
		 cfg.gvl.Emax,
		 cfg.gvl.Pmax, 
		 cfg.gvl.Imax, 
		 cfg.gvl.Dmax, 
		 cfg.gvl.Omax);
	PID_Reset(pid);
}

static void Gpl_Init(PID_t* pid)
{
	PID_Config(pid, 
		 cfg.gpl.kp, 
		 cfg.gpl.ki, 
		 cfg.gpl.kd, 
		 cfg.gpl.db,
		 cfg.gpl.it,
		 cfg.gpl.Emax,
		 cfg.gpl.Pmax, 
		 cfg.gpl.Imax, 
		 cfg.gpl.Dmax, 
		 cfg.gpl.Omax);
	PID_Reset(pid);
}

/**********************************************/
/*       Logic Controller Initialization      */
/**********************************************/
void Ctl_Init(void)
{
	uint8_t i = 0;

	Rmp_Init(&rmp);

	for (i = 0 ; i < CCL_NUM; i++) {
		Cvl_Init(&pid.cv.w[i]);
		Cpl_Init(&pid.cp.w[i]);
	}

	Gvl_Init(&pid.gv.p);
	Gpl_Init(&pid.gp.p);
	Gvl_Init(&pid.gv.t);
	Gpl_Init(&pid.gp.t);

	memset(&ctl, 0, sizeof(Ctl_t));
}

/**********************************************/
/*          Logic Controller Process          */
/**********************************************/
void Ctl_Proc(void)
{
	RmpGeneraterCtl();
	PeriphsStateCtl();
	ChassisStateCtl();
	PantiltStateCtl();
}

