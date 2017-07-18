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
 
#include "hci.h"

/********************************************/
/*          Host Control Interface          */
/********************************************/

#define MAF_NUM 3

static Hcf_t hcf;
static Maf_t maf[MAF_NUM];
static float buf[MAF_NUM][HCI_KEY_CTL_MAF_LEN];

static void GetPeriphsStateRef(const Hcp_t* hcp)
{
}

static void GetChassisStateRef(const Hcp_t* hcp)
{
	float sx = hcp->key.press.Shift ? cfg.vel.x : cfg.vel.x / 2.f;
	float sy = hcp->key.press.Shift ? cfg.vel.y : cfg.vel.y / 2.f;
	float sz = hcp->key.press.Shift ? cfg.vel.z : cfg.vel.z / 2.f;
	float vx = hcp->key.press.A ? -sx : hcp->key.press.D ? sx : 0;
	float vy = hcp->key.press.S ? -sy : hcp->key.press.W ? sy : 0;
	float mx = constrain(hcp->mouse.x, -MOUSE_SPEED_MAX, MOUSE_SPEED_MAX);
	float vz = map(mx, -MOUSE_SPEED_MAX, MOUSE_SPEED_MAX, -sz, sz);
	cmd.cv.x = Maf_Proc(&maf[0], vx);
	cmd.cv.y = Maf_Proc(&maf[1], vy);
	cmd.cv.z = Maf_Proc(&maf[2], vz);
}

static void GetGimbalsStateRef(const Hcp_t* hcp)
{
	float vpm = hcp->key.press.Shift ? cfg.vel.p : cfg.vel.p / 2.f;
	float vtm = hcp->key.press.Shift ? cfg.vel.t : cfg.vel.t / 2.f;
	cmd.gv.p = map(hcp->mouse.x, -MOUSE_SPEED_MAX, MOUSE_SPEED_MAX, -vpm, vpm);
	cmd.gv.t = map(hcp->mouse.y, -MOUSE_SPEED_MAX, MOUSE_SPEED_MAX, -vtm, vtm);
	cmd.gp.p += cmd.gv.p * SYS_CTL_TSC; // Integral velocity to get position
	LIMIT(cmd.gp.p, -cfg.pos.p, cfg.pos.p); // Constrain elevator position
	cmd.gp.t += cmd.gv.t * SYS_CTL_TSC; // Integral velocity to get position
	LIMIT(cmd.gp.t, -cfg.pos.t, cfg.pos.t); // Constrain elevator position
}

void Hci_PreProc(const Hcp_t* hcp)
{
	Hcf_Proc(&hcf, hcp);
}

uint8_t Hci_MouseBtn(uint8_t i)
{
	return hcf.b[i][2];
}

void Hci_Init(void)
{
	uint32_t i = 0;
	for (; i < MAF_NUM; i++) {
		Maf_Init(&maf[i], buf[i], HCI_KEY_CTL_MAF_LEN);
	}
	Hcf_Init(&hcf);
}

void Hci_Proc(const Hcp_t* hcp)
{
	Hci_PreProc(hcp);
	
	GetPeriphsStateRef(hcp);
	GetChassisStateRef(hcp);
	GetGimbalsStateRef(hcp);
}


