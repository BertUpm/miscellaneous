/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this class allows to transmit data via serial link via xbee pro rf modules
 * @file xbee_pro.h
 */
 
#ifndef XBEE_PRO_H_
#define XBEE_PRO_H_

#include "mbed.h"

class xbee_pro
{
public:
    /**
     * @brief Constructor
     */
    xbee_pro(PinName const tx_pin, PinName const rx_pin, PinName const reset_pin, uint32_t const baudrate);
    
    /**
     * @brief Destructor
     */
    ~xbee_pro();
    
    /**
     * @brief transmit data
     */
    void send(uint8_t const *data, uint16_t const bytes);
    
    /**
     * @brief returns true if data for reading is available
     */
    bool available();
    
    /**
     * @brief returns a received byte
     */
    uint8_t read();

private:
    Serial m_serial;
    DigitalOut m_reset;
};

#endif