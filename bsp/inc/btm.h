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

#ifndef __BTM_H___
#define __BTM_H___

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"
#include "fifo.h"
#include "hal_uart.h"

#define BTM_TX_PIN PD5
#define BTM_RX_PIN PD6
#define BTM_USART USART2
#define BTM_USART_BR 115200
#define BTM_USART_WL 8
#define BTM_USART_PA 'N'
#define BTM_USART_SB 1
#define BTM_USART_FC 'N'

#define BTM_IT_CONFIG(IT,CMD) USART_ITConfig(BTM_USART, IT, CMD)
#define BTM_ENABLE_IT_TXE() BTM_IT_CONFIG(USART_IT_TXE, ENABLE)
#define BTM_DISABLE_IT_TXE() BTM_IT_CONFIG(USART_IT_TXE, DISABLE)
#define BTM_ENABLE_IT_RXNE() BTM_IT_CONFIG(USART_IT_RXNE, ENABLE)
#define BTM_DISABLE_IT_RXNE() BTM_IT_CONFIG(USART_IT_RXNE, DISABLE)
#define BTM_ENABLE_IT_IDLE() BTM_IT_CONFIG(USART_IT_IDLE, ENABLE)
#define BTM_DISABLE_IT_IDLE() BTM_IT_CONFIG(USART_IT_IDLE, DISABLE)

#define BTM_IRQ_HANDLER IRQ_HANDLER(USART2)
#define BTM_NVIC IRQ(USART2)
#define BTM_NVIC_PRE_PRIORITY 1
#define BTM_NVIC_SUB_PRIORITY 1

#define BTM_DMA_STREAM DMA1_Stream5
#define BTM_DMA_CHANNEL DMA_Channel_4

#define BTM_DMA_BUF_SIZE 128u

#define BTM_RX_FIFO_SIZE 128u
#define BTM_TX_FIFO_SIZE 128u

void Btm_Config(void);

uint32_t Btm_GetRxFifoSize(void);
uint32_t Btm_GetRxFifoUsed(void);
uint32_t Btm_GetRxFifoFree(void);
uint32_t Btm_GetTxFifoSize(void);
uint32_t Btm_GetTxFifoUsed(void);
uint32_t Btm_GetTxFifoFree(void);
int Btm_ReadByte(void);
int Btm_WriteByte(uint8_t b);
int Btm_Read(uint8_t* buf, uint32_t len);
int Btm_Peek(uint8_t* buf, uint32_t len);
int Btm_Write(const uint8_t* buf, uint32_t len);

void Btm_PutCh(uint8_t c);
uint8_t Btm_GetCh(void);
void Btm_Print(const char* str);

void BtmRxCallback(uint8_t data);
void BtmIdleCallback(const uint8_t* buf, const uint32_t len);

extern const Hal_Uart_t btm;

#ifdef __cplusplus
}
#endif

#endif


