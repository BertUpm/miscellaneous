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
#include "NMEA_Parser.h"

// Variable holding system internal flags
volatile s_system_flags sys;

/*
 * @brief init function for the uC
 */
void init();
/*
 * @brief transmit rmc data via serial
 */
void tx_rmc();
/*
 * @brief returns 0 if the two utc times are not equal, else 1
 */
uint8_t IsEqual(uint8_t *o, uint8_t *n);

/*
 * @brief main function
 */
int main() {

	// call the init function
	init();

	rmc_s rmc_old;

	// main loop
	for(;;) {
		// data from the EM406A received?
		if(sys.flag.SoftUART_Rx) {
			while(!SoftUART_RxBufferEmpty()) {
				parse_data(SoftUART_GetByte());
			}
			sys.flag.SoftUART_Rx = 0;
		}
		// rmc data parsed?
		if(sys.flag.RMC_RxDone) {
			rmc_s rmc_new;
			get_RMC_Data(&rmc_new);
			if(!IsEqual(rmc_old.utc_time, rmc_new.utc_time)) { 
				tx_rmc();
			}
			rmc_old = rmc_new;
			sys.flag.RMC_RxDone = 0;
		}
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

/*
 * @brief transmit rmc data via serial
 */
void tx_rmc() {
	uint8_t const title[] = {'R', 'M', 'C', ' ', 'M', 'e', 's', 's', 'a', 'g', 'e', '\n'}; // 12
	uint8_t const utc[] =   {'U', 'T', 'C', ' ', 'T', 'i', 'm', 'e', ':', ' '}; // 10
	uint8_t const stat[] =  {'S', 't', 'a', 't', 'u', 's', ' ', ' ', ':', ' '}; // 10
	uint8_t const lat[] =   {'L', 'a', 't', 'i', 't', '.', ' ', ' ', ':', ' '}; // 10
	uint8_t const longt[] = {'L', 'o', 'n', 'g', 't', '.', ' ', ' ', ':', ' '}; // 10
	rmc_s rmc;
	uint8_t message[32];
	uint8_t i;
	get_RMC_Data(&rmc);
	
	for(i=0; i<12; i++) { message[i] = title[i]; }
	UART_WriteBytes(message, 12);
	while(!UART_TxBufferEmpty()) { }

	for(i=0; i<10; i++) { message[i] = utc[i]; }
	UART_WriteBytes(message, 10);
	while(!UART_TxBufferEmpty()) { }

	for(i=0; i<10; i++) { message[i] = rmc.utc_time[i]; } message[i] = '\n';
	UART_WriteBytes(message, 11);
	while(!UART_TxBufferEmpty()) { }

	for(i=0; i<10; i++) { message[i] = stat[i]; }
	UART_WriteBytes(message, 10);
	while(!UART_TxBufferEmpty()) { }

	message[0] = rmc.status; message[1] = '\n';
	UART_WriteBytes(message, 2);
	while(!UART_TxBufferEmpty()) { }

	for(i=0; i<10; i++) { message[i] = lat[i]; }
	UART_WriteBytes(message, 10);
	while(!UART_TxBufferEmpty()) { }

	for(i=0; i<9; i++) { message[i] = rmc.latitude[i]; } message[i] = '\n';
	UART_WriteBytes(message, 10);
	while(!UART_TxBufferEmpty()) { }

	for(i=0; i<10; i++) { message[i] = longt[i]; }
	UART_WriteBytes(message, 10);
	while(!UART_TxBufferEmpty()) { }

	for(i=0; i<9; i++) { message[i] = rmc.longitude[i]; } message[i] = '\n';
	UART_WriteBytes(message, 10);
	while(!UART_TxBufferEmpty()) { }

}

/*
 * @brief returns 0 if the two utc times are not equal, else 1
 */
uint8_t IsEqual(uint8_t *o, uint8_t *n) {
	uint8_t i=0;
	for(; i<10; i++) {
		if(o[i] != n[i]) return 0;
	}
	return 1;
}


