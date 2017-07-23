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

#include "top.h"

Top_t top;

void Top_Init(void)
{
	memset(&top, 0, sizeof(Top_t));
}

void Top_Proc(uint8_t* pbuf)
{
	if (Jud_Dec(pbuf, &top.frameHeader, &top.cmdId))
	{
		uint8_t offset = JUD_HEADER_LEN + JUD_CMD_ID_LEN;
		Wdg_Feed(WDG_IDX_JUDSYS);
		switch (top.cmdId)
		{
			case JUD_CMD_ID_GAME_INFO:
			{
				if (top.frameHeader.dataLength != sizeof(JudGameInfo_t)) break;
				memcpy(&top.gameInfo, pbuf + offset, top.frameHeader.dataLength);
				JudGameInfoCallback(&top.gameInfo);
				break;
			}
			case JUD_CMD_ID_RT_BLOOD_CHANGE:
			{
				if (top.frameHeader.dataLength != sizeof(JudRTBloodChange_t)) break;
				memcpy(&top.RTBloodChange, pbuf + offset, top.frameHeader.dataLength);
				JudRTBloodChangeCallback(&top.RTBloodChange);
				break;
			}
			case JUD_CMD_ID_RT_SHOOT_DATA:
			{
				if (top.frameHeader.dataLength != sizeof(JudRTShootData_t)) break;
				memcpy(&top.RTShootData, pbuf + offset, top.frameHeader.dataLength);
				JudRTShootDataCallback(&top.RTShootData);
				break;
			}
			default:
				break;
		}
	}
}

void JudGameInfoCallback(JudGameInfo_t* gameInfo)
{
	Wdg_Feed(WDG_IDX_JUDGIF);
	// TODO
}

void JudRTBloodChangeCallback(JudRTBloodChange_t* bloodChange)
{
	Wdg_Feed(WDG_IDX_JUDRTB);
	// TODO
}

void JudRTShootDataCallback(JudRTShootData_t* shootData)
{
	Wdg_Feed(WDG_IDX_JUDRTS);
	// TODO
}

