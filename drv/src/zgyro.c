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
 
#include "zgyro.h"

void ZGyro_RST(CAN_TypeDef* CANx)
{
    CanTxMsg msg;
    
    msg.StdId = ZGYRO_CMD_CAN_MSG_ID;
    msg.IDE = CAN_Id_Standard;
    msg.RTR = CAN_RTR_Data;
    msg.DLC = 0x08;
    
    msg.Data[0] = 0x00;
    msg.Data[1] = 0x01;
    msg.Data[2] = 0x02;
    msg.Data[3] = 0x03;
    msg.Data[4] = 0x04;
    msg.Data[5] = 0x05;
    msg.Data[6] = 0x06;
    msg.Data[7] = 0x07;
    
    CAN_Transmit(CANx, &msg);
}


