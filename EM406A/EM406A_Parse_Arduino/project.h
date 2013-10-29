/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
 
 /*
 * @author Alexander Entinger
 * @file project.h
 * @description variables and defines for the hole project
 */
#ifndef PROJECT_H
#define PROJECT_H

#include "includes.h"

// system flags
typedef union
{
  struct
  {
    uint8_t UART_Rx     : 1; // UART Data received
	uint8_t SoftUART_Rx : 1; // SoftUART Data received
	uint8_t RMC_RxDone  : 1; // RMC Message received
  } flag;
  uint8_t all_flags;            // Shortcut to all display flags (for reset)
} s_system_flags;
extern volatile s_system_flags sys;


#endif
