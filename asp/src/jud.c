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

#include "jud.h"

JudFrameHeader_t* Jud_CheckHeader(const void* buf)
{
	const JudFrameHeader_t* pheader = (JudFrameHeader_t*)buf;
	if (pheader->sof != JUD_SOF) {
		return NULL;
	}
	if (!CRC8Check(buf, JUD_HEADER_LEN, JUD_CRC8_INIT)) {
		return NULL;
	}
	return pheader;
}

uint16_t Jud_GetCmdId(const void* buf)
{
	return *((uint16_t*)((uint8_t*)buf + JUD_HEADER_LEN));
}

uint8_t Jud_CheckData(const void* buf)
{
	const JudFrameHeader_t* pheader = (JudFrameHeader_t*)buf;
	const uint32_t frameLength = JUD_GET_FRAME_LEN(pheader->dataLength);
	if (!CRC16Check((uint8_t*)buf, frameLength, JUD_CRC16_INIT))
	{
		return 0;
	}
	return 1;
}

uint8_t Jud_GetData(const void* buf, void* data, uint32_t len)
{
	const JudFrameHeader_t* pheader = (JudFrameHeader_t*)buf;
	if (pheader->dataLength != len)
	{
		return 0;
	}
	memcpy(data, (uint8_t*)buf + JUD_DATA_OFFSET, len);
	return 1;
}

uint8_t Jud_Dec(const uint8_t* buf, const uint32_t len, void* header, void* cmdId)
{
	const JudFrameHeader_t* pheader = (JudFrameHeader_t*)buf;
	const uint32_t frameLength = JUD_GET_FRAME_LEN(pheader->dataLength);
	if (len < frameLength)
	{
		return 0;
	}
	if (pheader->sof != JUD_SOF) {
		return 0;
	}
	if (!CRC8Check(buf, JUD_HEADER_LEN, JUD_CRC8_INIT)) {
		return 0;
	}
	if (!CRC16Check(buf, frameLength, JUD_CRC16_INIT))
	{
		return 0;
	}
	memcpy(header, buf, JUD_HEADER_LEN);
	memcpy(cmdId, buf + JUD_HEADER_LEN, JUD_CMD_ID_LEN);
	return 1;
}

uint8_t Jud_Pop(FIFO_t* fifo, uint8_t* buf, void* header, void* cmdId)
{
	uint32_t len = 0;
	JudFrameHeader_t* pheader = NULL;
	if (FIFO_GetUsed(fifo) < JUD_EXT_FRAME_LEN)
	{
		return 0;
	}
	FIFO_Peek(fifo, buf, JUD_HEADER_LEN);
	pheader = (JudFrameHeader_t*)buf;
	len = JUD_GET_FRAME_LEN(pheader->dataLength);
	if (FIFO_GetUsed(fifo) < len)
	{
		return 0;
	}
	FIFO_Peek(fifo, buf, len);
	if (Jud_Dec(buf, len, header, cmdId))
	{
		FIFO_Pop(fifo, buf, len);
		return 1;
	}
	return 0;
}

