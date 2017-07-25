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

static VRCMsg_t vrcMsg;
static VHCMsg_t vhcMsg;
static CBusMsg_t cbusMsg;
static VDBusMsg_t vdbusMsg;


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

void Dnl_ProcCBusMsg(const CBusMsg_t* cbusMsg)
{
	Wdg_Feed(WDG_IDX_CBUS);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Cci_Proc(&cbusMsg->cbus);
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

/*
void Dnl_ProcSubscMsg(const SubscMsg_t* subscMsg)
{
	if (subscMsg->msg_type & MSG_TYPE_CALIB) {
	}
}

void Dnl_ProcCalibMsg(const CalibMsg_t* calibMsg)
{
	Wdg_Feed(WDG_IDX_CALIB);
	if (calibMsg->auto_cali_flag & CALIB_FLAG_BIT_POS) {
		Cal_Init();
	}
}

void Dnl_ProcIMUCalib(const IMUCalib_t* IMUCalib)
{
	Calib_SetIMU(&cfg.imu, IMUCalib);
	Cfg_SetFlag(CFG_FLAG_IMU);
	cfg_sync_flag = 1;
}

void Dnl_ProcMagCalib(const MagCalib_t* MagCalib)
{
	Calib_SetMag(&cfg.mag, MagCalib);
	Cfg_SetFlag(CFG_FLAG_MAG);
	cfg_sync_flag = 1;
}

void Dnl_ProcVelCalib(const VelCalib_t* VelCalib)
{
	Calib_SetVel(&cfg.vel, VelCalib);
	Cfg_SetFlag(CFG_FLAG_VEL);
	cfg_sync_flag = 1;
}

void Dnl_ProcMecCalib(const MecCalib_t* MecCalib)
{
	Calib_SetMec(&cfg.mec, MecCalib);
	Cfg_SetFlag(CFG_FLAG_MEC);
	cfg_sync_flag = 1;
}

void Dnl_ProcPosCalib(const PosCalib_t* PosCalib)
{
	Calib_SetPos(&cfg.pos, PosCalib);
	Cfg_SetFlag(CFG_FLAG_POS);
	cfg_sync_flag = 1;
}

void Dnl_ProcPIDCalib(const PIDCalib_t* PIDCalib)
{
	if (PIDCalib->type == PID_CALIB_TYPE_CHASSIS_VELOCITY) {
		Calib_SetPID(&cfg.cvl, PIDCalib);
		Cfg_SetFlag(CFG_FLAG_CVL);
		cfg_sync_flag = 1;
	}
	else if (PIDCalib->type == PID_CALIB_TYPE_GRABBER_VELOCITY) {
		Calib_SetPID(&cfg.gvl, PIDCalib);
		Cfg_SetFlag(CFG_FLAG_GVL);
		cfg_sync_flag = 1;
	}
	else if (PIDCalib->type == PID_CALIB_TYPE_GRABBER_POSITION) {
		Calib_SetPID(&cfg.gpl, PIDCalib);
		Cfg_SetFlag(CFG_FLAG_GPL);
		cfg_sync_flag = 1;
	}
}
*/

void Dnl_Init(void)
{
}

void Dnl_Proc(const uint8_t* buf, const uint32_t len)
{
	const MsgHead_t* headin = (MsgHead_t*)buf;
	uint32_t msgLen = headin->attr.length;
	if (headin->value != msg_head_cbus.value)
	{
		return;
	}
	if (len < msgLen + MSG_LEN_EXT)
	{
		return;
	}
	if (!CRC16Check(buf, len, headin->attr.token))
	{
		return;
	}
	ledg.Toggle();
}


