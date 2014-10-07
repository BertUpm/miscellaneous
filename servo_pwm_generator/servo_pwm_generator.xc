/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this file implements a servo pwm generator for 3 servo channels
 * @file servo_pwm_generator.xc
 * @license CC BY-NC-SA 4.0 ( http://creativecommons.org/licenses/by-nc-sa/4.0/ )
 */

#include <platform.h>
#include <xs1.h>
#include <timer.h>
#include <stdint.h>
#include "servo.h"

void servo_demo_task(client interface servo_control_interface sci)
{
    while(1)
    {
        for(uint32_t servo_duration_us = 1000; servo_duration_us < 2000; servo_duration_us+=50)
        {
            sci.set_pulse_duration_us(SERVO_1, servo_duration_us);
            sci.set_pulse_duration_us(SERVO_2, servo_duration_us);
            sci.set_pulse_duration_us(SERVO_3, servo_duration_us);
            delay_milliseconds(250);
        }
    }
}

int main()
{
    interface servo_control_interface sci;

    par
    {
        servo_task(sci);
        servo_demo_task(sci);
    }

    return 0;
}
