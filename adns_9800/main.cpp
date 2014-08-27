/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief main file for the adns-9800-demo project
 * @file main.cpp
 */
 
/* INCLUDE SECTION */

#include "mbed.h"
#include "adns_9800.h"

/* PROTOTYPE SECTION */ 

void init_application();

/* GLOBAL CONSTANT SECTION */

static int const USB_UART_BAUDRATE = 115200;
static PinName const MOSI = p5;
static PinName const MISO = p6;
static PinName const SCLK = p7;
static PinName const NCS = p8;

/* GLOBAL VARIABLE SECTION */

Serial usb_uart(USBTX, USBRX);
adns_9800 mouse_sensor(MOSI, MISO, SCLK, NCS);
 
int main()
{
    init_application();
    
    for(;;)
    {
        if(mouse_sensor.new_motion_data_available()) 
        {
            int16_t delta_x = 0, delta_y = 0;
            mouse_sensor.get_delta_x_y(delta_x, delta_y);
            usb_uart.printf("dx = %d, dy = %d\n", delta_x, delta_y);
        }
    }
}

/**
 * @brief intializes the application
 */
void init_application()
{
    // set baudrate to 115200
    usb_uart.baud(USB_UART_BAUDRATE);
}