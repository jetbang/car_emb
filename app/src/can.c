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

#include "can.h"

/*********************************************/
/*          Controller Area Network          */
/*********************************************/

ZGyro_t zgyro;
Motor_t motor[MOTOR_NUM];

void ZGyro_Process(ZGyro_t* zgyro, uint32_t id, uint8_t* data)
{
	zgyro->id = id;
	zgyro->frame_cnt++;
	zgyro->angle_fdb[0] = zgyro->angle_fdb[1];
	zgyro->angle_fdb[1] = ZGYRO_ORIENTATION * ((int32_t)(data[0]<<24)|(int32_t)(data[1]<<16)|(int32_t)(data[2]<<8)|(int32_t)(data[3]));
	if (zgyro->frame_cnt < ZGYRO_INIT_FRAME_CNT) {
		zgyro->bias = zgyro->angle_fdb[1];
	}
	zgyro->rate = zgyro->angle_fdb[1] - zgyro->angle_fdb[0];
	zgyro->rate_deg = ZGYRO_RATE_DEG_RECIP * zgyro->rate;
	zgyro->rate_rad = ZGYRO_RATE_RAD_RECIP * zgyro->rate;
	zgyro->angle = zgyro->angle_fdb[1] - zgyro->bias;
	zgyro->angle_deg = ZGYRO_ANGLE_DEG_RECIP * zgyro->angle;
	zgyro->angle_rad = ZGYRO_ANGLE_RAD_RECIP * zgyro->angle;
}

void Motor_Process(Motor_t* motor, uint32_t id, uint8_t* data)
{
	motor->id = id;
	motor->frame_cnt++;
	motor->angle_fdb[0] = motor->angle_fdb[1];
	motor->angle_fdb[1] = (data[0] << 8) | data[1];
	motor->rate_fdb = (data[2] << 8) | data[3];
	motor->rate_deg = MOTOR_RATE_DEG_RECIP * motor->rate_fdb;
	motor->rate_rad = MOTOR_RATE_RAD_RECIP * motor->rate_fdb;
	if (motor->frame_cnt < MOTOR_INIT_FRAME_CNT) {
		motor->bias = motor->angle_fdb[1];
		motor->round = 0;
	}
	motor->angle_diff = motor->angle_fdb[1] - motor->angle_fdb[0];
	if (motor->angle_diff > MOTOR_ECD_GAP) {
		motor->round--;
		//motor->rate_raw = motor->angle_diff - MOTOR_ECD_MOD;
	} else if (motor->angle_diff < -MOTOR_ECD_GAP) {
		motor->round++;
		//motor->rate_raw = motor->angle_diff + MOTOR_ECD_MOD;
	} else {
		//motor->rate_raw = motor->angle_diff;
	}
	motor->angle_ecd = (motor->angle_fdb[1] - motor->bias) + motor->round * MOTOR_ECD_MOD;
	motor->angle_deg = MOTOR_ANGLE_DEG_RECIP * motor->angle_ecd;
	motor->angle_rad = MOTOR_ANGLE_RAD_RECIP * motor->angle_ecd;
}

uint8_t ZGyro_Ready(const ZGyro_t* zgyro)
{
	return zgyro->frame_cnt >= ZGYRO_INIT_FRAME_CNT;
}

uint8_t Motor_Ready(const Motor_t* motor)
{
	return motor->frame_cnt >= MOTOR_INIT_FRAME_CNT;
}

void ZGyro_Reset(ZGyro_t* zgyro)
{
	memset((void*)zgyro, 0, sizeof(ZGyro_t));
}

void Motor_Reset(Motor_t* motor)
{
	memset((void*)motor, 0, sizeof(Motor_t));
}

void Can_Init(void)
{
	uint8_t i = 0;
	for (; i < MOTOR_NUM; i++) {
		Motor_Reset(&motor[i]);
	}
	ZGyro_Reset(&zgyro);
}

void Can_Proc(uint32_t id, uint8_t* data)
{
	switch (id) {
	case ZGYRO_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_ZGYRO);
		ZGyro_Process(&zgyro, id, data);
		break;
	case MOTOR1_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR1);
		Motor_Process(&motor[0], id, data);
		break;
	case MOTOR2_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR2);
		Motor_Process(&motor[1], id, data);
		break;
	case MOTOR3_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR3);
		Motor_Process(&motor[2], id, data);
		break;
	case MOTOR4_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR4);
		Motor_Process(&motor[3], id, data);
		break;
	case MOTOR5_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR5);
		Motor_Process(&motor[4], id, data);
		break;
	case MOTOR6_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR6);
		Motor_Process(&motor[5], id, data);
		break;
	case MOTOR7_FDB_CAN_MSG_ID:
		Wdg_Feed(WDG_IDX_MOTOR7);
		Motor_Process(&motor[6], id, data);
		break;
	default:
		break;
	}
}

uint8_t Can_Ready(void)
{
	return ZGyro_Ready(&zgyro) &&
		   Motor_Ready(&motor[0]) &&
		   Motor_Ready(&motor[1]) &&
		   Motor_Ready(&motor[2]) &&
		   Motor_Ready(&motor[3]) &&
		   Motor_Ready(&motor[5]) &&
		   Motor_Ready(&motor[6]);
}



