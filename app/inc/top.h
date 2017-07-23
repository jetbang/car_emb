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

#ifndef __TOP_H__
#define __TOP_H__

#ifdef __cpluplus
extern "C" {
#endif

#include "jud.h"
#include "wdg.h"

typedef struct
{
	JudFrameHeader_t frameHeader;
	JudCmdId_t cmdId;
	JudGameInfo_t gameInfo;
	JudRTBloodChange_t RTBloodChange;
	JudRTShootData_t RTShootData;
}Top_t;

void Top_Init(void);
void Top_Proc(uint8_t* pbuf);

void JudGameInfoCallback(JudGameInfo_t* gameInfo);
void JudRTBloodChangeCallback(JudRTBloodChange_t* bloodChange);
void JudRTShootDataCallback(JudRTShootData_t* shootData);

extern Top_t top;

#ifdef __cpluplus
}
#endif

#endif
