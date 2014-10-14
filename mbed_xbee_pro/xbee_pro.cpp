/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this class allows to transmit data via serial link via xbee pro rf modules
 * @file xbee_pro.cpp
 */

#include "xbee_pro.h"

/**
* @brief Constructor
*/
xbee_pro::xbee_pro(PinName const tx_pin, PinName const rx_pin, PinName const reset_pin, uint32_t const baudrate) : m_serial(tx_pin, rx_pin), m_reset(reset_pin)
{
    m_serial.baud(baudrate);
    
    // reset the xbee
    m_reset = 0;
    wait(1);
    m_reset = 1; 
    wait(1); // dont forget to do a good wait here, otherwise the xbee is not yet started up
}

/**
 * @brief Destructor
 */
xbee_pro::~xbee_pro()
{
    
}

/**
 * @brief transmit data
 */
void xbee_pro::send(uint8_t const *data, uint16_t const bytes)
{
    for(uint16_t i=0; i<bytes; i++)
    {
        m_serial.putc(data[i]);
    }
}

/**
 * @brief returns true if data for reading is available
 */
bool xbee_pro::available()
{
    return m_serial.readable();
}

/**
 * @brief returns a received byte
 */
uint8_t xbee_pro::read()
{
    return m_serial.getc();    
}