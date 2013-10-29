/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /*
 * @author Alexander Entinger
 * @file NMEA_Parser.h
 * @description NMEA Parser
 */
#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include "includes.h"

typedef struct {
	uint8_t utc_time[10];
	uint8_t status;
	uint8_t latitude[9];
	uint8_t n_s;
	uint8_t longitude[9];
	uint8_t e_w;
	uint8_t speed[4];
	uint8_t course[6];
	uint8_t date[6];
	uint8_t cs[3];
} rmc_s;

/*
 * @brief parses the data
 */
void parse_data(uint8_t data);

/*
 * @brief copies the data in the struct of the caller
 */
void get_RMC_Data(rmc_s *data);

#endif
