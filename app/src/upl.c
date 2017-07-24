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

static MsgType_t msgType = MSG_TYPE_UWB;

static UwbMsg_t uwbMsg;
static OdoMsg_t odoMsg;
static ZGyroMsg_t zgyroMsg;
static VDBusMsg_t vdbusMsg;

static void Upl_PushUwbMsg(void)
{
	if (!Flag_Get(&top.flag, TOP_FLAG_GIF)) return;
	uwbMsg.frame_id++;
	uwbMsg.flag = top.gameInfo.gps.flag;
	uwbMsg.x = top.gameInfo.gps.x;
	uwbMsg.y = top.gameInfo.gps.y;
	uwbMsg.z = top.gameInfo.gps.z;
	uwbMsg.w = top.gameInfo.gps.w;
	Msg_Push(&fifo, buf[1], &msg_head_uwb, &uwbMsg);
}

static void Upl_PushOdoMsg(void)
{
	odoMsg.frame_id++;
	odoMsg.fs = odo.fs;
	odoMsg.cv.x = odo.cv.x * ODO_MSG_VALUE_SCALE;
	odoMsg.cv.y = odo.cv.y * ODO_MSG_VALUE_SCALE;
	odoMsg.cv.z = odo.cv.z * ODO_MSG_VALUE_SCALE;
	odoMsg.cp.x = odo.cp.x * ODO_MSG_VALUE_SCALE;
	odoMsg.cp.y = odo.cp.y * ODO_MSG_VALUE_SCALE;
	odoMsg.cp.z = odo.cp.z * ODO_MSG_VALUE_SCALE;
	odoMsg.gv.p = odo.gv.p * ODO_MSG_VALUE_SCALE;
	odoMsg.gp.p = odo.gp.p * ODO_MSG_VALUE_SCALE;
	odoMsg.gv.t = odo.gv.t * ODO_MSG_VALUE_SCALE;
	odoMsg.gp.t = odo.gp.p * ODO_MSG_VALUE_SCALE;
	Msg_Push(&fifo, buf[1], &msg_head_odo, &odoMsg);
}

static void Upl_PushZGyroMsg(void)
{
	zgyroMsg.frame_id++;
	zgyroMsg.angle = zgyro.angle;
	zgyroMsg.rate = zgyro.rate;
	Msg_Push(&fifo, buf[1], &msg_head_zgyro, &zgyroMsg);
}

static void Upl_PushVDBusMsg(void)
{
	vdbusMsg.frame_id++;
	DBus_Enc(&dbus, vdbusMsg.data);
	Msg_Push(&fifo, buf[1], &msg_head_zgyro, &zgyroMsg);
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
	switch (msgType) {
		case MSG_TYPE_UWB:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_uwb.attr.length + MSG_LEN_EXT) {
				Upl_PushUwbMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_ODO;
			}
			break;
		case MSG_TYPE_ODO:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_odo.attr.length + MSG_LEN_EXT) {
				Upl_PushOdoMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_ZGYRO;
			}
			break;
		case MSG_TYPE_ZGYRO:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_zgyro.attr.length + MSG_LEN_EXT) {
				Upl_PushZGyroMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_VDBUS;
			}
			break;
		case MSG_TYPE_VDBUS:
			if (IOS_COM_DEV.GetTxFifoFree() >= msg_head_vdbus.attr.length + MSG_LEN_EXT) {
				Upl_PushVDBusMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_UWB;
			}
			break;
		default:
			msgType = MSG_TYPE_UWB;
		break;
	}
}


