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

#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "fun.h"

#define SYS_CTL_TSC 1e-3f // s
#define SYS_CTL_TMS 1 // ms

typedef uint32_t PeriphsState_t; // Peripherals state flag bits

typedef struct
{
	float x;
	float y;
	float z;
}ChassisState_t;

typedef union
{
	float w[4];
}MecanumState_t;

typedef struct
{
	float p;
	float t;
	float z;
}PantiltState_t;

PeriphsState_t FS_Get(const PeriphsState_t* fs, PeriphsState_t mask);
void FS_Set(PeriphsState_t* fs, PeriphsState_t mask);
void FS_Clr(PeriphsState_t* fs, PeriphsState_t mask);
void FS_Tog(PeriphsState_t* fs, PeriphsState_t mask);
void FS_Cpy(PeriphsState_t* fs, PeriphsState_t src, PeriphsState_t mask);
void FS_Det(PeriphsState_t* fs, Flag_t mask, uint32_t condition);

void CS_Set(ChassisState_t* cs, float x, float y, float z);
void MS_Set(MecanumState_t* ms, float w1, float w2, float w3, float w4);
void GS_Set(PantiltState_t* gs, float p, float t, float z);

#ifdef __cplusplus
}
#endif

#endif

