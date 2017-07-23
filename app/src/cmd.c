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

#include "cmd.h"

/**********************************************/
/*          System Command Interface          */
/**********************************************/
Cmd_t cmd;

void Cmd_Init(void)
{
	memset(&cmd, 0, sizeof(Cmd_t));
}

void Cmd_Proc(void)
{
	LIMIT(cmd.cv.x, -cfg.vel.x, cfg.vel.x);
	LIMIT(cmd.cv.y, -cfg.vel.y, cfg.vel.y);
	LIMIT(cmd.cv.z, -cfg.vel.z, cfg.vel.z);
	LIMIT(cmd.gp.p, -cfg.pos.p, cfg.pos.p);
	LIMIT(cmd.gp.t, -cfg.pos.t, cfg.pos.t);
	
	Mec_Decomp((float*)&cmd.cv, (float*)&cmd.mv);
}


