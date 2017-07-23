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

static void vErrThreadFun(void* pvParam)
{
	while (1) {
		Err_Proc();
		vTaskDelay(20);
	}
}

static void vDnlThreadFun(void* pvParam)
{
	while (1) {
		Dnl_Proc();
		vTaskDelay(20);
	}
}

static void vUplThreadFun(void* pvParam)
{
	while (1) {
		Upl_Proc();
		vTaskDelay(10);
	}
}

static TaskHandle_t xErrTaskHandle = NULL;
static TaskHandle_t xDnlTaskHandle = NULL;
static TaskHandle_t xUplTaskHandle = NULL;

static void vAppTaskCreate(void)
{
	xTaskCreate(vErrThreadFun, "vErrThreadFun", 128, NULL, 1, &xErrTaskHandle);
	xTaskCreate(vDnlThreadFun, "vDnlThreadFun", 128, NULL, 1, &xDnlTaskHandle);
	xTaskCreate(vUplThreadFun, "vUplThreadFun", 128, NULL, 1, &xUplTaskHandle);
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
		// KOS_Spin();
	}
}

