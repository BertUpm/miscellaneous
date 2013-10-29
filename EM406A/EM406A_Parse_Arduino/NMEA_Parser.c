/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /*
 * @author Alexander Entinger
 * @file NMEA_Parser.c
 * @description NMEA Parser
 */
#include "NMEA_Parser.h"

/*
 * @brief defines for parser fsm
 */
#define SYNC 			(0) // $
#define DEVICE_ID_0		(1) // G
#define DEVICE_ID_1		(2) // P
#define MESS_ID_0   	(3) // R
#define MESS_ID_1   	(4) // M
#define MESS_ID_2   	(5) // C
#define DECISION    	(6)
#define GPRMC           (7)
#define ERROR       	(8)

#define RMC_UTC_TIME    (0)
#define RMC_STATUS      (1)
#define RMC_LATITUDE    (2)
#define RMC_N_S         (3)
#define RMC_LONGITUDE   (4)
#define RMC_E_W         (5)
#define RMC_SPEED       (6)
#define RMC_COURSE     	(7)
#define RMC_CHECKSUM    (8)

/*
 * @brief prototype section
 */
uint8_t IsRMC();
void parse_rmc_data(uint8_t data);

/*
 * @brief static variables
 */
static volatile uint8_t parse_state = SYNC;
static volatile uint8_t prot[3];
static volatile uint8_t rmc_parse_state = RMC_UTC_TIME;
static volatile uint8_t rmc_data_cnt    = 0;
static volatile rmc_s   rmc;

/*
 * @brief parses the data
 */
void parse_data(uint8_t data) {
	if(data == '$') {
		parse_state = SYNC;
	}
	
	switch(parse_state) {
		case SYNC: parse_state = DEVICE_ID_0;
		break;
		case DEVICE_ID_0: parse_state = DEVICE_ID_1;
		break;
		case DEVICE_ID_1: parse_state = MESS_ID_0;
		break;
		case MESS_ID_0: {
			parse_state = MESS_ID_1;
		    prot[0] = data;
		}            
		break;
		case MESS_ID_1: {
			parse_state = MESS_ID_2;
			prot[1] = data;
		}
		break;
		case MESS_ID_2: {
			parse_state = DECISION;
			prot[2] = data;
		}
		break;
		case DECISION: {
			if(IsRMC()) { 
				parse_state = GPRMC;
				rmc_parse_state = RMC_UTC_TIME;
				rmc_data_cnt    = 0;
			}
			else { 
				parse_state = ERROR;
			}
		}
		break;
		case GPRMC: {
			parse_rmc_data(data);
		}
		break;
		case ERROR: break;
		default:    break;
	}
	
}

/*
 * @brief copies the data in the struct of the caller
 */
void get_RMC_Data(rmc_s *data) {
	*data = rmc;
}

/*
 * @brief parses rmc data
 */
void parse_rmc_data(uint8_t data) {
	if(data == ',') { 
		rmc_data_cnt = 0;
		rmc_parse_state++;
	}
	else {
		switch(rmc_parse_state) {
			case RMC_UTC_TIME: 		rmc.utc_time[rmc_data_cnt] = data; break;
			case RMC_STATUS:		rmc.status = data; break;
			case RMC_LATITUDE: 		rmc.latitude[rmc_data_cnt] = data; break;
			case RMC_N_S: 			rmc.n_s = data; break;
			case RMC_LONGITUDE: 	rmc.longitude[rmc_data_cnt] = data; break;
			case RMC_E_W: 			rmc.e_w = data; break;
			case RMC_SPEED: 		rmc.speed[rmc_data_cnt] = data; break;
			case RMC_COURSE: 		rmc.course[rmc_data_cnt] = data; break;
			case RMC_CHECKSUM: 		rmc.cs[rmc_data_cnt] = data; sys.flag.RMC_RxDone = 1; break;
			default: break;
		}
		rmc_data_cnt++;
	}
}

/*
 * @brief returns 1 if protocol is RMC
 */
uint8_t IsRMC() {
	if(prot[0] == 'R' &&
	   prot[1] == 'M' &&
	   prot[2] == 'C') {
	   return 1;
	}
	else {
		return 0;
	}
}
