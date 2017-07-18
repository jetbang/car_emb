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

static void vLedThreadFun(void* pvParam)
{
	while (1) {
		LED_GREEN_TOG();
		vTaskDelay(500);
	}
}

static void vSndThreadFun(void* pvParam)
{
	while (1) {
		Snd_Proc();
		if (Clk_GetUsTick() < 1.4e6) {
			Snd_Play();
			vTaskDelay(50);
		} else {
			Snd_Stop();
			vTaskDelay(200);
		}
	}
}

static void vDnlThreadFun(void* pvParam)
{
	while (1) {
		Dnl_Proc();
		vTaskDelay(10);
	}
}

static void vUplThreadFun(void* pvParam)
{
	while (1) {
		Upl_Proc();
		vTaskDelay(10);
	}
}

static void vCtlThreadFun(void* pvParam)
{
	while (1) {
		App_Proc();
		vTaskDelay(SYS_CTL_TMS);
	}
}

static TaskHandle_t xLedTaskHandle = NULL;
static TaskHandle_t xSndTaskHandle = NULL;
static TaskHandle_t xDnlTaskHandle = NULL;
static TaskHandle_t xUplTaskHandle = NULL;
static TaskHandle_t xCtlTaskHandle = NULL;

static void vAppTaskCreate(void)
{
	xTaskCreate(vLedThreadFun, "vLedThreadFun", 128, NULL, 0, &xLedTaskHandle);
	xTaskCreate(vSndThreadFun, "vSndThreadFun", 128, NULL, 1, &xSndTaskHandle);
	xTaskCreate(vDnlThreadFun, "vDnlThreadFun", 128, NULL, 2, &xDnlTaskHandle);
	xTaskCreate(vUplThreadFun, "vUplThreadFun", 128, NULL, 2, &xUplTaskHandle);
	xTaskCreate(vCtlThreadFun, "vCtlThreadFun", 128, NULL, 3, &xCtlTaskHandle);
}

int main()
{
	//__set_PRIMASK(1); // Close global interrupt
	
	// Boot KOS
	KOS_Boot();
	
	vAppTaskCreate();
	vTaskStartScheduler();
	
	while(1)
	{
	}
}

