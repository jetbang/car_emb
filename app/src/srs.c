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
 
#include "srs.h"

Srs_t srs[SR04_NUM];

static uint32_t id = 0;
static uint32_t tc = 0;

void Srs_Start(uint32_t i)
{
	memset(&srs[i], 0, sizeof(Srs_t));
	Med_Init(&srs[i].med);
	Maf_Init(&srs[i].maf, srs[i].buf, SR04_MAF_LEN);
	srs[i].state = SR04_STATE_IDLE;
}

void Srs_Stop(uint32_t i)
{
	srs[i].state = SR04_STATE_STOP;
}

void Srs_Init(void)
{
	uint32_t i = 0;
	for (i = 0; i < SR04_NUM; i++) {
		Srs_Start(i);
	}
}

void Srs_Trig(uint32_t i)
{
	GPIO_RST(sr04[i].trigPin);
	GPIO_SET(sr04[i].trigPin);
	srs[i].startTrig = Clk_GetUsTick();
	srs[i].state = SR04_STATE_TRIG;
}

void Srs_Func(uint32_t i)
{
	uint32_t interval = 0;
	switch (srs[i].state) {
		case SR04_STATE_IDLE:
			interval = Clk_GetUsTick() - srs[i].endEcho;
			if (interval > SR04_TRIG_TUS) {
				Srs_Trig(i);
			}
			break;
		case SR04_STATE_TRIG:
			interval = Clk_GetUsTick() - srs[i].startTrig;
			if (interval > SR04_TRIG_PULSE_WIDTH) {
				GPIO_RST(sr04[i].trigPin);
				srs[i].endTrig = Clk_GetUsTick();
				srs[i].state = SR04_STATE_WAIT;
			}
			break;
		case SR04_STATE_WAIT:
			interval = Clk_GetUsTick() - srs[i].endTrig;
			if (interval > SR04_WAIT_ECHO_TIMEOUT) {
				Srs_Trig(i);
			}
			break;
		case SR04_STATE_ECHO:
			interval = Clk_GetUsTick() - srs[i].startEcho;
			if (interval > SR04_ECHO_PULSE_WIDTH_MAX) {
				Srs_Trig(i);
			}
			break;
		case SR04_STATE_STOP:
			break;
		default:
			break;
	}
}

#define ID_MAX (SR04_NUM - 1)
#define LAST_ID (id == 0 ? ID_MAX : id == ID_MAX ? 0 : (id - 1))

#define RING_ID() do { if (++id >= SR04_NUM) id = 0; } while (0)

void Srs_Proc(void)
{
	// Check if current sonar module is idle
	if (srs[id].state == SR04_STATE_IDLE) {
		// Wait for silence
		uint32_t interval = Clk_GetUsTick() - srs[id].endEcho;
		if (interval > SR04_TRIG_TUS) {
			RING_ID();
		}
		// clear time counter
		tc = Clk_GetUsTick();
	} else {
		uint32_t dt = Clk_GetUsTick() - tc;
		if (dt > SR04_ECHO_PULSE_WIDTH_MAX + SR04_TRIG_TUS) {
			RING_ID();
			tc = Clk_GetUsTick();
		}
	} 
	Srs_Func(id);
}

void Srs_Rise(uint32_t i)
{
	if (srs[i].state == SR04_STATE_WAIT) {
		srs[i].startEcho = Clk_GetUsTick();
		srs[i].state = SR04_STATE_ECHO;
		GPIO_RST(sr04[i].trigPin);
	}
}

void Srs_Fall(uint32_t i)
{
	if (srs[i].state == SR04_STATE_ECHO) {
		srs[i].frame_cnt++;
		srs[i].endEcho = Clk_GetUsTick();
		srs[i].echo = srs[i].endEcho - srs[i].startEcho;
		srs[i].mm = (uint16_t)(srs[i].echo * SR04_ECHO_RECIP);
		Med_Proc(&srs[i].med, srs[i].mm);
		srs[i].mm_filtered = Maf_Proc(&srs[i].maf, srs[i].med.val);
		srs[i].state = SR04_STATE_IDLE;
		GPIO_RST(sr04[i].trigPin);
	}
}

void Sr04_Proc(uint8_t i, uint8_t trigger)
{
	if (i == SR04_IDX_FIXED) {
		Wdg_Feed(WDG_IDX_SR04F);
	} else if (i == SR04_IDX_MOBLE) {
		Wdg_Feed(WDG_IDX_SR04M);
	} else if (i == SR04_IDX_LEFT) {
		Wdg_Feed(WDG_IDX_SR04L);
	} else if (i == SR04_IDX_RIGHT) {
		Wdg_Feed(WDG_IDX_SR04R);
	}
	if (i < SR04_NUM) {
		// Rising edge trigger -> start echo
		if (trigger == 1) {
			Srs_Rise(i);
		}
		// Falling edge trigger -> end echo
		else if (trigger == 0) {
			Srs_Fall(i);
		}
	}
}

