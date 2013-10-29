/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /*
 * @author Alexander Entinger
 * @file UART.h
 * @description hardware uart
 */

#ifndef UART_H
#define UART_H

#include "includes.h"

#define BAUD115200 (16) // 2.1 % Error
#define BAUD76800  (25) // 0.2 % Error
#define BAUD57600  (34) // 0.8 % Error
#define BAUD38400  (51) // 0.2 % Error
#define BAUD9600   (207)// 0.2 % Error

/*
 * @brief initialization of the software uart
 */
void UART_Init(uint8_t baudrate);

/*
 * @brief access date from the ring buffer
 */
uint8_t UART_GetByte();

/*
 * @brief returns 0 if buffer is empty, otherwise a number
 */
uint8_t UART_RxBufferEmpty();

/*
 * @brief returns 0 if buffer is empty, otherwise a number
 */
uint8_t UART_TxBufferEmpty();

/*
 * @brief write an array of bytes in the ringbuffer for transmission
 */
void UART_WriteBytes(uint8_t *bytes, uint8_t size);



#endif
