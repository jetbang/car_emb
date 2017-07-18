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
 
#include "upl.h"

/*****************************************/
/*         Up-Link Communication         */
/*****************************************/

static uint8_t buf[2][UPL_BUF_SIZE];
static FIFO_t fifo;

static MsgType_t msgType = MSG_TYPE_DBUS;

static DBusMsg_t dbusMsg;
static OdomMsg_t odomMsg;
static ZGyroMsg_t zgyroMsg;
static MotorMsg_t motorMsg;

static void Upl_PushDBusMsg(void)
{
	dbusMsg.frame_id++;
	//Rcp_Enc(&dbus.rcp, dbusMsg.data);
	Msg_Push(&fifo, buf[1], &msg_head_dbus, &dbusMsg);
}

static void Upl_PushOdomMsg(void)
{
	odomMsg.frame_id++;
	odomMsg.vx = odo.cv.x * ODOM_MSG_VALUE_SCALE;
	odomMsg.vy = odo.cv.y * ODOM_MSG_VALUE_SCALE;
	odomMsg.vz = odo.cv.z * ODOM_MSG_VALUE_SCALE;
	odomMsg.px = odo.cp.x * ODOM_MSG_VALUE_SCALE;
	odomMsg.py = odo.cp.y * ODOM_MSG_VALUE_SCALE;
	odomMsg.pz = odo.cp.z * ODOM_MSG_VALUE_SCALE;
	Msg_Push(&fifo, buf[1], &msg_head_odom, &odomMsg);
}

static void Upl_PushZGyroMsg(void)
{
	zgyroMsg.frame_id++;
	zgyroMsg.angle = zgyro.angle;
	zgyroMsg.rate = zgyro.rate;
	Msg_Push(&fifo, buf[1], &msg_head_zgyro, &zgyroMsg);
}

static void Upl_PushMotorMsg(void)
{
	motorMsg.frame_id++;
	motorMsg.angle = zgyro.angle;
	motorMsg.rate = zgyro.rate;
	Msg_Push(&fifo, buf[1], &msg_head_motor, &motorMsg);
}

static void Upl_SendMsg(void)
{
	uint8_t data;
	while (!FIFO_IsEmpty(&fifo)) {
		FIFO_Pop(&fifo, &data, 1);
		IOS_COM_DEV.WriteByte(data);
	}
}

void Upl_Init(void)
{
	FIFO_Init(&fifo, buf[0], UPL_BUF_SIZE);
}

void Upl_Proc(void)
{
	uint8_t i = 0;
	switch (msgType) {
		case MSG_TYPE_DBUS:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_dbus.attr.length + MSG_LEN_EXT) {
				Upl_PushDBusMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_ZGYRO;
			}
			break;
		case MSG_TYPE_ODOM:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_odom.attr.length + MSG_LEN_EXT) {
				Upl_PushOdomMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_ZGYRO;
			}
			break;
		case MSG_TYPE_ZGYRO:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_zgyro.attr.length + MSG_LEN_EXT) {
				Upl_PushZGyroMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_MOTOR;
			}
			break;
		case MSG_TYPE_MOTOR:
			for (i = 0; i < MOTOR_NUM; i++) {

			}
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_motor.attr.length + MSG_LEN_EXT) {
				Upl_PushMotorMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_DBUS;
			}
			break;
		default:
			msgType = MSG_TYPE_DBUS;
		break;
	}
}


