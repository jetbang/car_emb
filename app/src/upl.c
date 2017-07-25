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

static uint8_t len = 0;
static uint8_t buf[UPL_BUF_SIZE];

static MsgType_e msgType = MSG_TYPE_UWB;

static BotMsg_t botMsg;
static UwbMsg_t uwbMsg;
static ZGyroMsg_t zgyroMsg;
static VDBusMsg_t vdbusMsg;

static void Upl_PushBotMsg(void)
{
	botMsg.frame_id++;
	botMsg.cbus.fs = odo.fs;
	botMsg.cbus.cv.x = odo.cv.x * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.cv.y = odo.cv.y * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.cv.z = odo.cv.z * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.cp.x = odo.cp.x * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.cp.y = odo.cp.y * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.cp.z = odo.cp.z * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.gv.p = odo.gv.p * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.gp.p = odo.gp.p * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.gv.t = odo.gv.t * BOT_MSG_VALUE_SCALE;
	botMsg.cbus.gp.t = odo.gp.p * BOT_MSG_VALUE_SCALE;
	len = Msg_Pack(buf, &msg_head[MSG_TYPE_IDX_BOT], &botMsg);
}

static void Upl_PushUwbMsg(void)
{
	if (!Flag_Get(&top.flag, TOP_FLAG_GIF)) return;
	uwbMsg.frame_id++;
	uwbMsg.flag = top.gameInfo.gps.flag;
	uwbMsg.x = top.gameInfo.gps.x;
	uwbMsg.y = top.gameInfo.gps.y;
	uwbMsg.z = top.gameInfo.gps.z;
	uwbMsg.w = top.gameInfo.gps.w;
	len = Msg_Pack(buf, &msg_head[MSG_TYPE_IDX_UWB], &uwbMsg);
}

static void Upl_PushZGyroMsg(void)
{
	zgyroMsg.frame_id++;
	zgyroMsg.angle = zgyro.angle;
	zgyroMsg.rate = zgyro.rate;
	len = Msg_Pack(buf, &msg_head[MSG_TYPE_IDX_ZGYRO], &zgyroMsg);
}

static void Upl_PushVDBusMsg(void)
{
	vdbusMsg.frame_id++;
	DBus_Enc(&dbus, vdbusMsg.data);
	len = Msg_Pack(buf, &msg_head[MSG_TYPE_IDX_VDBUS], &vdbusMsg);
}

static void Upl_SendMsg(void)
{
	IOS_COM_DEV.Write(buf, len);
}

void Upl_Init(void)
{
	len = 0;
	memset(buf, 0, UPL_BUF_SIZE);
}

void Upl_Proc(void)
{
	switch (msgType) {
		case MSG_TYPE_BOT:
			if (IOS_COM_DEV.GetTxFifoFree() >= MSG_LEN_OF(BOT)) {
				Upl_PushBotMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_UWB;
			}
			break;
		case MSG_TYPE_UWB:
			if (IOS_COM_DEV.GetTxFifoFree() >= MSG_LEN_OF(UWB)) {
				Upl_PushUwbMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_ZGYRO;
			}
			break;
		case MSG_TYPE_ZGYRO:
			if (IOS_COM_DEV.GetTxFifoFree() >= MSG_LEN_OF(ZGYRO)) {
				Upl_PushZGyroMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_VDBUS;
			}
			break;
		case MSG_TYPE_VDBUS:
			if (IOS_COM_DEV.GetTxFifoFree() >= MSG_LEN_OF(VDBUS)) {
				Upl_PushVDBusMsg();
				Upl_SendMsg();
				msgType = MSG_TYPE_BOT;
			}
			break;
		default:
			msgType = MSG_TYPE_BOT;
		break;
	}
}


