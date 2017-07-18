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
 
#include "main.h"

/*
typedef struct
{
	int16_t ax;
	int16_t ay;
	int16_t az;
	int16_t temp;
	int16_t gx;
	int16_t gy;
	int16_t gz;
	int16_t mx;
	int16_t my;
	int16_t mz;
}MPU_Data_t;

static void Buf2MpuData(const uint8_t* buf, MPU_Data_t* data)
{
	data->ax = (buf[0] << 8) | buf[1];
	data->ay = (buf[2] << 8) | buf[3];
	data->az= (buf[4] << 8) | buf[5];
	
	data->temp = (buf[6] << 8) | buf[7];
	
	data->gx = (buf[8] << 8) | buf[9];
	data->gy = (buf[10] << 8) | buf[11];
	data->gz = (buf[12] << 8) | buf[13];

	data->mx = (buf[14] << 8) | buf[15];
	data->my = (buf[16] << 8) | buf[17];
	data->mz = (buf[18] << 8) | buf[19];
}
*/

/*
static void vLedThreadFun(void* pvParam)
{
	while (1) {
		LED_GREEN_TOG();
		vTaskDelay(500);
	}
}

static void vSrsThreadFun(void* pvParam)
{
	while (1) {
		Srs_Proc();
		vTaskDelay(1);
	}
}

static void vDnlThreadFun(void* pvParam)
{
	while (1) {
		Dnl_Proc();
		vTaskDelay(5);
	}
}

static void vUplThreadFun(void* pvParam)
{
	while (1) {
		Upl_Proc();
		vTaskDelay(5);
	}
}

static void vDbgThreadFun(void* pvParam)
{
	//static uint32_t tick = 0;
	uint8_t i = 0;
	while (1) {
		//dbi.Print("Hello, Jack\r\n");
		//printf("Hello, Jack -> %d\r\n", ++tick);
		//printf("%f\t%f\t%f\n", odo.cv.x, odo.cv.y, odo.cv.z);
		//printf("%f\t%f\t%f\t%f\n", odo.mv.w1, odo.mv.w2, odo.mv.w3, odo.mv.w4);
		//for (i = 0; i < 4; i++) {
		//	if (*(&odo.mv.w1 + i) != 0) {
		//		printf("%d\t%d\t%d\t%d\t%d\n", i, motor[i].angle_fdb[1], motor[i].angle_fdb[0], motor[i].angle_diff, motor->rate_raw);
		//	}
		//}
		
		for (i = 0; i < 3; i++) {
			if (*(&odo.cv.x + i) != 0) {
				printf("%d\t%f\n", i, *(&odo.cv.x + i));
			}
		}
		
		vTaskDelay(50);
	}
}

static void vImuThreadFun(void* pvParam)
{
	//static MPU_Data_t imu_data;
	//static uint8_t buf[20];
	while (1) {
		//if (MPU6500_Read(buf) && IST8310_Read(buf + 14)) {
		//	Buf2MpuData(buf, &imu_data);
		//	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\r\n", imu_data.ax, imu_data.ay, imu_data.az, imu_data.temp, imu_data.gx, imu_data.gy, imu_data.gz, imu_data.mx, imu_data.my, imu_data.mz);
		//}
		vTaskDelay(100000);
	}
}

static TaskHandle_t xLedTaskHandle = NULL;
static TaskHandle_t xSrsTaskHandle = NULL;
static TaskHandle_t xDnlTaskHandle = NULL;
static TaskHandle_t xUplTaskHandle = NULL;
static TaskHandle_t xDbgTaskHandle = NULL;
static TaskHandle_t xImuTaskHandle = NULL;

static void vAppTaskCreate(void)
{
	xTaskCreate(vLedThreadFun, "vLedThreadFun", 128, NULL, 1, &xLedTaskHandle);
	xTaskCreate(vSrsThreadFun, "vSrsThreadFun", 256, NULL, 3, &xSrsTaskHandle);
	xTaskCreate(vDnlThreadFun, "vDnlThreadFun", 256, NULL, 3, &xDnlTaskHandle);
	xTaskCreate(vUplThreadFun, "vUplThreadFun", 256, NULL, 3, &xUplTaskHandle);
	xTaskCreate(vDbgThreadFun, "vDbgThreadFun", 128, NULL, 2, &xDbgTaskHandle);
	xTaskCreate(vImuThreadFun, "vImuThreadFun", 512, NULL, 2, &xImuTaskHandle);
}
*/

//MPU_Data_t imu_data;

//static uint32_t last_time = 0;
int main()
{
	//__set_PRIMASK(1); // Close global interrupt
	
	// Boot KOS
	KOS_Boot();
	
	// Play startup music
	Snd_Play();

	// Wait for startup music
	//Delay_Ms(350);
	Delay_Ms(1000);

	//Clk_DelayUs(7e5); // For more precise delay (us)

	// Stop startup music
	Snd_Stop();
	
	//vAppTaskCreate();
	//vTaskStartScheduler();
	
	//Cfg_Reset();

	while(1)
	{
		Dnl_Proc();
		if (Clk_GetUsTick() % 2000 == 0) {
			Upl_Proc();
			
		}
  }
}

