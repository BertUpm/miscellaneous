/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * @author Alexander Entinger
 * @file main.c
 * @description main file for receiving gps commands
 */

#include "includes.h"
#include "SoftUART.h"
#include "UART.h"

// Variable holding system internal flags
volatile s_system_flags sys;

/*
 * @brief init function for the uC
 */
void init();


int main() {

	// call the init function
	init();

	// main loop
	for(;;) {
		while(SoftUART_RxBufferEmpty()) { };
		uint8_t c;
		c = SoftUART_GetByte();
		UART_WriteBytes(&c, 1);
	}
	
	return 0;
}

/*
 * @brief init function for the uC
 */
void init() {
	
	sys.all_flags = 0;

	UART_Init(BAUD115200);

	SoftUART_Init();

	sei();

}
