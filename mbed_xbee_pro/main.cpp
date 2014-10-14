/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief main file for the xbee pro s2b mbed library demo
 * @file main.cpp
 */

/* INCLUDES */

#include "mbed.h"
#include "xbee_pro.h"

/* GLOBAL CONSTANTS */

static PinName const UART_TX_PIN = p9;
static PinName const UART_RX_PIN = p10;
static PinName const RESET_PIN = p20;

/* GLOBAL VARIABLES */

xbee_pro xbee(UART_TX_PIN, UART_RX_PIN, RESET_PIN, 115200);

/* PROTOTYPES */

void init_application();

/* FUNCTIONS */

int main() 
{
    for(;;)
    {
        while(xbee.available())
        {
            uint8_t const rx_data = xbee.read();
            xbee.send(&rx_data, 1);
        }
    }
}