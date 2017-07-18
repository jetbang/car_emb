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

static uint8_t buf[2][DNL_BUF_SIZE];
static FIFO_t fifo;

static RcpMsg_t rcpMsg;
static HcpMsg_t hcpMsg;
static DBusMsg_t dbusMsg;
static CBusMsg_t cbusMsg;

static void Dnl_ProcRcpMsg(const RcpMsg_t* rcpMsg)
{
	Wdg_Feed(WDG_IDX_RCP);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Rcp_Dec(&dbus.rcp, rcpMsg->data);
		Rci_Proc(&dbus.rcp);
	}
}


static void Dnl_ProcHcpMsg(const HcpMsg_t* hcpMsg)
{
	Wdg_Feed(WDG_IDX_HCP);
	if (Rci_Sw(SW_IDX_R) == SW_DN) {
		Hcp_Dec(&dbus.hcp, hcpMsg->data);
		Hci_Proc(&dbus.hcp);
	}
}

static void Dnl_ProcDBusMsg(const DBusMsg_t* dbusMsg)
{
	Wdg_Feed(WDG_IDX_DBUS);
	// To use this mode, the remote controller must be turned of.
	if (Wdg_HasErr(WDG_ERR_RCV)) {
		DBUS_Dec(&dbus, dbusMsg->data);
		Dci_Proc(&dbus);
	}
}

static void Dnl_ProcCBusMsg(const CBusMsg_t* cbusMsg)
{
	Wdg_Feed(WDG_IDX_CBUS);
	if (Rci_Sw(SW_IDX_R) == SW_DN && Wsm_GetWs() == WORKING_STATE_NORMAL) {
		Cci_Proc(&cbusMsg->data);
	}
}

/*
static void Dnl_ProcImuCalib(const ImuCalib_t* ImuCalib)
{
	Calib_SetIMU(&cfg.imu, ImuCalib);
	Cfg_SetFlag(CFG_FLAG_IMU);
	cfg_sync_flag = 1;
}

static void Dnl_ProcMagCalib(const MagCalib_t* MagCalib)
{
	Calib_SetMag(&cfg.mag, MagCalib);
	Cfg_SetFlag(CFG_FLAG_MAG);
	cfg_sync_flag = 1;
}

static void Dnl_ProcVelCalib(const VelCalib_t* VelCalib)
{
	Calib_SetVel(&cfg.vel, VelCalib);
	Cfg_SetFlag(CFG_FLAG_VEL);
	cfg_sync_flag = 1;
}

static void Dnl_ProcMecCalib(const MecCalib_t* MecCalib)
{
	Calib_SetMec(&cfg.mec, MecCalib);
	Cfg_SetFlag(CFG_FLAG_MEC);
	cfg_sync_flag = 1;
}

static void Dnl_ProcPosCalib(const PosCalib_t* PosCalib)
{
	Calib_SetPos(&cfg.pos, PosCalib);
	Cfg_SetFlag(CFG_FLAG_POS);
	cfg_sync_flag = 1;
}

static void Dnl_ProcPIDCalib(const PIDCalib_t* PIDCalib)
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
	FIFO_Init(&fifo, buf[0], DNL_BUF_SIZE);
}

void Dnl_Proc(void)
{
	// Get fifo free space
	int len = FIFO_GetFree(&fifo);
	// If fifo free space insufficient, pop one element out
	if (len < 1) {
		uint8_t b;
		len = FIFO_Pop(&fifo, &b, 1);
	}
	// Read input stream according to the fifo free space left
	len = IOS_COM_DEV.Read(buf[1], len);
	// If input stream not available, abort
	if (len > 0) {
		// Push stream into fifo
		FIFO_Push(&fifo, buf[1], len);
	}
	// Check if any message received
	if (Msg_Pop(&fifo, buf[1], &msg_head_rcp, &rcpMsg)) {
		Dnl_ProcRcpMsg(&rcpMsg);
	}
	else if (Msg_Pop(&fifo, buf[1], &msg_head_hcp, &hcpMsg)) {
		Dnl_ProcHcpMsg(&hcpMsg);
	}
	else if (Msg_Pop(&fifo, buf[1], &msg_head_dbus, &dbusMsg)) {
		Dnl_ProcDBusMsg(&dbusMsg);
	}
	else if (Msg_Pop(&fifo, buf[1], &msg_head_cbus, &cbusMsg)) {
		Dnl_ProcCBusMsg(&cbusMsg);
	}
}




