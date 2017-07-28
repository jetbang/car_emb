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
 
#include "cci.h"

/*************************************************/
/*            CBUS Control Interface             */
/*************************************************/

static void GetPeriphsStateRef(const CBus_t* cbus)
{
}

static void GetChassisStateRef(const CBus_t* cbus)
{
	cmd.cv.x = cbus->cv.x / CBUS_VALUE_SCALE;
	cmd.cv.y = cbus->cv.y / CBUS_VALUE_SCALE;
	cmd.cv.z = cbus->cv.z / CBUS_VALUE_SCALE;

	LIMIT(cmd.cv.x, -cfg.vel.x, cfg.vel.x);
	LIMIT(cmd.cv.y, -cfg.vel.y, cfg.vel.y);
	LIMIT(cmd.cv.z, -cfg.vel.z, cfg.vel.z);
	/*
	// Chassis position control mode
	if (Flag_Get(&cbus->fs, CBUS_FS_CP))
	{
		float pxr = cbus->cp.x / CBUS_VALUE_SCALE;
		float pyr = cbus->cp.y / CBUS_VALUE_SCALE;
		float pzr = cbus->cp.z / CBUS_VALUE_SCALE;
		float vxr = cbus->cv.x / CBUS_VALUE_SCALE;
		float vyr = cbus->cv.y / CBUS_VALUE_SCALE;
		float vzr = cbus->cv.z / CBUS_VALUE_SCALE;

		float dpx = Flag_Get(&cbus->fs, CBUS_FS_CP_ABS) ? pxr - odo.cp.x : pxr;
		float dpy = Flag_Get(&cbus->fs, CBUS_FS_CP_ABS) ? pyr - odo.cp.y : pyr;
		float dpz = Flag_Get(&cbus->fs, CBUS_FS_CP_ABS) ? pzr - odo.cp.z : pzr;

		LIMIT_ABS(vxr, cfg.vel.x);
		LIMIT_ABS(vyr, cfg.vel.y);
		LIMIT_ABS(vzr, cfg.vel.z);

		cmd.cv.x = map(dpx, -CCI_DPT_TH, CCI_DPT_TH, -1, 1) * vxr;
		cmd.cv.y = map(dpy, -CCI_DPT_TH, CCI_DPT_TH, -1, 1) * vyr;
		cmd.cv.z = map(dpz, -CCI_DPR_TH, CCI_DPR_TH, -1, 1) * vzr;

		LIMIT(cmd.cv.x, -cfg.vel.x, cfg.vel.x);
		cmd.cp.x += cmd.cv.x * SYS_CTL_TSC;

		LIMIT(cmd.cv.y, -cfg.vel.y, cfg.vel.y);
		cmd.cp.y += cmd.cv.y * SYS_CTL_TSC;

		LIMIT(cmd.cv.z, -cfg.vel.z, cfg.vel.z);
		cmd.cp.z += cmd.cv.z * SYS_CTL_TSC;
	}
	else
	{
		cmd.cv.x = cbus->cv.x / CBUS_VALUE_SCALE;
		cmd.cv.y = cbus->cv.y / CBUS_VALUE_SCALE;
		cmd.cv.z = cbus->cv.z / CBUS_VALUE_SCALE;

		LIMIT(cmd.cv.x, -cfg.vel.x, cfg.vel.x);
		LIMIT(cmd.cv.y, -cfg.vel.y, cfg.vel.y);
		LIMIT(cmd.cv.z, -cfg.vel.z, cfg.vel.z);
	}
	*/
}

static void GetPantiltStateRef(const CBus_t* cbus)
{
	/*
	cmd.gp.p += cbus->gp.p / CBUS_VALUE_SCALE;
	cmd.gp.t += cbus->gp.t / CBUS_VALUE_SCALE;
	// Pantilt position control mode
	if (Flag_Get(&cbus->fs, CBUS_FS_GP_ABS))
	{
		if (Flag_Get(&cbus->fs, CBUS_FS_GV))
		{
			cmd.gv.p = cbus->gv.p / CBUS_VALUE_SCALE;
			cmd.gv.t = cbus->gv.t / CBUS_VALUE_SCALE;
			LIMIT(cmd.gv.p, -cfg.vel.p, cfg.vel.p);
			LIMIT(cmd.gv.t, -cfg.vel.t, cfg.vel.t);
			cmd.gp.p += cbus->gp.p / CBUS_VALUE_SCALE;
			cmd.gp.t += cbus->gp.t / CBUS_VALUE_SCALE;
		}
		cmd.gp.p = cbus->gp.p / CBUS_VALUE_SCALE;
		cmd.gp.t = cbus->gp.t / CBUS_VALUE_SCALE;
	}
	else
	{
		cmd.gp.p += cbus->gp.p / CBUS_VALUE_SCALE;
		cmd.gp.t += cbus->gp.t / CBUS_VALUE_SCALE;
	}

	LIMIT(cmd.gp.p, -cfg.pos.p, cfg.pos.p);
	LIMIT(cmd.gp.t, -cfg.pos.t, cfg.pos.t);
	*/
}

void Cci_Init(void)
{
}

void Cci_Proc(const CBus_t* cbus)
{
	GetPeriphsStateRef(cbus);
	GetChassisStateRef(cbus);
	GetPantiltStateRef(cbus);
}


