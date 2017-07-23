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

#ifndef __CBUS_H__
#define __CBUS_H__

/**************************************************/
/*                  Control Bus                   */
/**************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>

#define CBUS_SIZE sizeof(CBUS_t)

typedef struct
{
	int32_t x;
	int32_t y;
	int32_t z;
}ChassisState_p; // Chassis state control typedef

typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}ChassisState_v; // Chassis state control typedef

typedef struct
{
	int16_t p;
	int16_t t;
	int16_t z;
}PantiltState_c; // Pantilt state control typedef

#define CBUS_VALUE_SCALE 1e3f

#pragma pack(1)

typedef struct
{
	uint32_t fs; // Flag bits
	ChassisState_v cv; // Chassis velocity, unit: linear: mm/s, angular: 1e-3rad/s
	ChassisState_p cp; // Chassis position, unit: linear: mm, angular: 1e-3rad
	PantiltState_c gv; // Pantilt velocity, unit: linear: mm/s, angular: 1e-3rad/s
	PantiltState_c gp; // Pantilt position, unit: linear: mm, angular: rad
}CBus_t;

#pragma pack()

void CBus_Init(CBus_t* cbus);

#ifdef __cplusplus
}
#endif

#endif
