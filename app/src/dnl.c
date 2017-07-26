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
 
#include "dnl.h"

/*****************************************/
/*        Down-Link Communication        */
/*****************************************/

void Dnl_ProcBotMsg(const BotMsg_t* botMsg)
{
	Wdg_Feed(WDG_IDX_CBUS);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Cci_Proc(&botMsg->cbus);
	}
}

void Dnl_ProcVRCMsg(const VRCMsg_t* vrcMsg)
{
	Wdg_Feed(WDG_IDX_VRC);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Rcp_Dec(&dbus.rcp, vrcMsg->data);
		Rci_Proc(&dbus.rcp);
	}
}

void Dnl_ProcVHCMsg(const VHCMsg_t* vhcMsg)
{
	Wdg_Feed(WDG_IDX_VHC);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Hcp_Dec(&dbus.hcp, vhcMsg->data);
		Hci_Proc(&dbus.hcp);
	}
}

void Dnl_ProcVDBusMsg(const VDBusMsg_t* vdbusMsg)
{
	Wdg_Feed(WDG_IDX_VDBUS);
	// To use this mode, the remote controller must be turned of.
	if (Wdg_HasErr(WDG_ERR_RCV)) {
		DBus_Dec(&dbus, vdbusMsg->data);
		Dci_Proc(&dbus);
	}
}

void Dnl_ProcMsg(const uint8_t typeId, const void* pData)
{
	switch (typeId)
	{
		case MSG_TYPE_IDX_BOT:
		{
			Dnl_ProcBotMsg((BotMsg_t*)pData);
			break;
		}
		case MSG_TYPE_IDX_VRC:
		{
			Dnl_ProcVRCMsg((VRCMsg_t*)pData);
			break;
		}
		case MSG_TYPE_IDX_VHC:
		{
			Dnl_ProcVHCMsg((VHCMsg_t*)pData);
			break;
		}
		case MSG_TYPE_IDX_VDBUS:
		{
			Dnl_ProcVDBusMsg((VDBusMsg_t*)pData);
			break;
		}
		default:
			break;
	}
}

void Dnl_Init(void)
{
}

void Dnl_Proc(const uint8_t* buf, const uint32_t len)
{
	uint8_t i = 0;
	void* pData = NULL;
	for (i = 0; i < MSG_TYPE_NUM; i++)
	{
		pData = Msg_GetData(buf, &msg_head[i]);
		if (pData == NULL) continue;
		Dnl_ProcMsg(i, pData);
		break;
	}
}


