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
 
#ifndef __TTY_H__
#define __TTY_H__

#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32util.h"
#include "fifo.h"
#include "hal_uart.h"

#define TTY_TX_PIN PG9
#define TTY_RX_PIN PG14
#define TTY_USART USART6
#define TTY_USART_BR 115200
#define TTY_USART_WL 8
#define TTY_USART_PA 'N'
#define TTY_USART_SB 1
#define TTY_USART_FC 'N'

#define TTY_IT_CONFIG(IT,CMD) USART_ITConfig(TTY_USART, IT, CMD)
#define TTY_ENABLE_IT_TXE() TTY_IT_CONFIG(USART_IT_TXE, ENABLE)
#define TTY_DISABLE_IT_TXE() TTY_IT_CONFIG(USART_IT_TXE, DISABLE)
#define TTY_ENABLE_IT_RXNE() TTY_IT_CONFIG(USART_IT_RXNE, ENABLE)
#define TTY_DISABLE_IT_RXNE() TTY_IT_CONFIG(USART_IT_RXNE, DISABLE)
#define TTY_ENABLE_IT_IDLE() TTY_IT_CONFIG(USART_IT_IDLE, ENABLE)
#define TTY_DISABLE_IT_IDLE() TTY_IT_CONFIG(USART_IT_IDLE, DISABLE)

#define TTY_IRQ_HANDLER IRQ_HANDLER(USART6)
#define TTY_NVIC IRQ(USART6)
#define TTY_NVIC_PRE_PRIORITY 0
#define TTY_NVIC_SUB_PRIORITY 1

#define TTY_DMA_STREAM DMA2_Stream1
#define TTY_DMA_CHANNEL DMA_Channel_5

#define TTY_DMA_BUF_SIZE 128u

#define TTY_RX_FIFO_SIZE 128u
#define TTY_TX_FIFO_SIZE 128u

void Tty_Config(void);

uint32_t Tty_GetRxFifoSize(void);
uint32_t Tty_GetRxFifoUsed(void);
uint32_t Tty_GetRxFifoFree(void);
uint32_t Tty_GetTxFifoSize(void);
uint32_t Tty_GetTxFifoUsed(void);
uint32_t Tty_GetTxFifoFree(void);
int Tty_ReadByte(void);
int Tty_WriteByte(uint8_t b);
int Tty_Read(uint8_t* buf, uint32_t len);
int Tty_Peek(uint8_t* buf, uint32_t len);
int Tty_Write(const uint8_t* buf, uint32_t len);

void Tty_PutCh(uint8_t c);
uint8_t Tty_GetCh(void);
void Tty_Print(const char* str);

void TtyRxCallback(uint8_t data);
void TtyIdleCallback(const uint8_t* buf, const uint32_t len);

extern const Hal_Uart_t tty;

#ifdef __cplusplus
}
#endif

#endif
