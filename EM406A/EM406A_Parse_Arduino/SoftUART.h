/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /*
 * @author Alexander Entinger
 * @file SoftUART.h
 * @description software uart
 */
#ifndef SOFTUART_H
#define SOFTUART_H

#include "includes.h"

// UART Pin/Port Definitions
#define TX_PIN (2)
#define RX_PIN (3)
#define UART_PORT (PORTD)
#define UART_DIR  (DDRD)
#define UART_PIN  (PIND)

/*
 * @brief initialization of the software uart
 */
void SoftUART_Init();

/*
 * @brief get a byte from the receive ringbuffer
 */
uint8_t SoftUART_GetByte();

/*
 * @brief returns 1 if buffer is empty, 0 otherwise
 */
uint8_t SoftUART_RxBufferEmpty();


#endif
