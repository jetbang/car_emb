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

uint8_t Jud_Dec(const uint8_t* buf, void* header, void* cmdId)
{
	const JudFrameHeader_t* pheader = (JudFrameHeader_t*)buf;
	const uint8_t frameLength = JUD_GET_FRAME_LEN(pheader->dataLength);
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

