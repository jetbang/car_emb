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

void Top_Proc(const uint8_t* buf, const uint32_t len)
{
	JudFrameHeader_t* pHeader = NULL;
	uint32_t frameLength = 0;
	void* pData = NULL;
	uint16_t cmdId = JUD_CMD_ID_INVALID;

	if (len < JUD_EXT_LEN)
	{
		return;
	}

	pHeader = Jud_GetFrameHeader(buf);
	if (pHeader == NULL)
	{
		return;
	}

	frameLength = JUD_GET_FRAME_LEN(pHeader->dataLength);
	if (len < frameLength)
	{
		return;
	}

	pData = Jud_GetData(buf);
	if (pData == NULL)
	{
		return;
	}

	cmdId = Jud_GetCmdId(buf);
	switch (cmdId)
	{
		case JUD_CMD_ID_GAME_INFO:
		{
			memcpy(&top.gameInfo, pData, pHeader->dataLength);
			JudGameInfoCallback(&top.gameInfo);
			break;
		}
		case JUD_CMD_ID_RT_BLOOD_CHANGE:
		{
			memcpy(&top.RTBloodChange, pData, pHeader->dataLength);
			JudRTBloodChangeCallback(&top.RTBloodChange);
			break;
		}
		case JUD_CMD_ID_RT_SHOOT_DATA:
		{
			memcpy(&top.RTShootData, pData, pHeader->dataLength);
			JudRTShootDataCallback(&top.RTShootData);
			break;
		}
		default:
			break;
	}
}

void JudGameInfoCallback(JudGameInfo_t* gameInfo)
{
	Wdg_Feed(WDG_IDX_JUDGIF);
	Flag_Set(&top.flag, TOP_FLAG_GIF);
}

void JudRTBloodChangeCallback(JudRTBloodChange_t* bloodChange)
{
	Wdg_Feed(WDG_IDX_JUDRTB);
	Flag_Set(&top.flag, TOP_FLAG_RTB);
}

void JudRTShootDataCallback(JudRTShootData_t* shootData)
{
	Wdg_Feed(WDG_IDX_JUDRTS);
	Flag_Set(&top.flag, TOP_FLAG_RTS);
}



