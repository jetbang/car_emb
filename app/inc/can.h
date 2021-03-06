/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
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

#ifndef __CAN_H__
#define __CAN_H__

/*********************************************/
/*          Controller Area Network          */
/*********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

#include "fun.h"
#include "wdg.h"

#define ZGYRO_FDB_CAN_MSG_ID   0x401
#define MOTOR1_FDB_CAN_MSG_ID  0x201
#define MOTOR2_FDB_CAN_MSG_ID  0x202
#define MOTOR3_FDB_CAN_MSG_ID  0x203
#define MOTOR4_FDB_CAN_MSG_ID  0x204
#define MOTOR5_FDB_CAN_MSG_ID  0x205
#define MOTOR6_FDB_CAN_MSG_ID  0x206
#define MOTOR7_FDB_CAN_MSG_ID  0x207

#define MOTOR_ECD_MOD 8192
#define MOTOR_ECD_GAP 4096

#define MOTOR_NUM 7
#define MOTOR_INIT_FRAME_CNT 100

#define MOTOR_RATE_DEG_RECIP 6.0f
#define MOTOR_RATE_RAD_RECIP 0.10471975f
#define MOTOR_ANGLE_DEG_RECIP 0.04394531f
#define MOTOR_ANGLE_RAD_RECIP 7.669904e-4f

#define ZGYRO_INIT_FRAME_CNT 100
#define ZGYRO_ORIENTATION (-1)
#define ZGYRO_RATE_DEG_RECIP 10.0f
#define ZGYRO_RATE_RAD_RECIP 0.1745329f
#define ZGYRO_ANGLE_DEG_RECIP 0.01f
#define ZGYRO_ANGLE_RAD_RECIP 1.745329e-4f

typedef struct
{
	uint32_t id;
	uint32_t frame_cnt;
	int32_t angle_fdb[2];
	int32_t bias;
	int32_t rate;
	int32_t angle;
	float rate_deg;
	float rate_rad;
	float angle_deg;
	float angle_rad;
}ZGyro_t;

typedef struct
{
	uint32_t id;
	uint32_t frame_cnt;
	uint16_t angle_fdb[2];
	int16_t rate_fdb;
	int16_t angle_diff;
	int32_t bias;
	int32_t round;
	int32_t angle_ecd;
	float rate_deg;
	float rate_rad;
	float angle_deg;
	float angle_rad;
}Motor_t;

void ZGyro_Process(ZGyro_t* zgyro, uint32_t id, uint8_t* data);
void Motor_Process(Motor_t* motor, uint32_t id, uint8_t* data);
uint8_t ZGyro_Ready(const ZGyro_t* zgyro);
uint8_t Motor_Ready(const Motor_t* motor);
void ZGyro_Reset(ZGyro_t* zgyro);
void Motor_Reset(Motor_t* motor);

void Can_Init(void);
void Can_Proc(uint32_t id, uint8_t* data);
uint8_t Can_Ready(void);

extern ZGyro_t zgyro;
extern Motor_t motor[MOTOR_NUM];

#ifdef __cplusplus
}
#endif

#endif

