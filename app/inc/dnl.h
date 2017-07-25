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
 
#ifndef __DNL_H__
#define __DNL_H__

/*****************************************/
/*        Down-Link Communication        */
/*****************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "ios.h"
#include "msg.h"
#include "cal.h"
#include "dci.h"
#include "cci.h"
#include "fun.h"

void Dnl_Init(void);
void Dnl_Proc(const uint8_t* buf, const uint32_t len);

void Dnl_ProcBotMsg(const BotMsg_t* botMsg);
void Dnl_ProcVRCMsg(const VRCMsg_t* vrcMsg);
void Dnl_ProcVHCMsg(const VHCMsg_t* vhcMsg);
void Dnl_ProcVDBusMsg(const VDBusMsg_t* vdbusMsg);
void Dnl_ProcMsg(const uint8_t typeId, const void* pData);

#ifdef __cplusplus
}
#endif

#endif
