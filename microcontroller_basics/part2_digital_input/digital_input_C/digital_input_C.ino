/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this sketch illustrates the usage of the digital input pin using the C language
 * @file digital_input_C.ino
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

#include <Arduino.h>

//led_pin = PB5
#define LED_PIN  (1<<5)
#define LED_DDR  (DDRB)
#define LED_PORT (PORTB)
//dig_out_pin = PB4
#define DIG_OUT_PIN  (1<<4)
#define DIG_OUT_DDR  (DDRB)
#define DIG_OUT_PORT (PORTB)
//dig_in_pin = PB3
#define DIG_IN_PIN    (1<<3)
#define DIG_IN_DDR    (DDRB)
#define DIG_IN_PIN    (PINB)

void setup() {
  LED_DDR |= LED_PIN;  // set pin 13 (led) as output
  DIG_OUT_DDR |= DIG_OUT_PIN; // set pin 12 as output
  DIG_IN_DDR &= ~DIG_IN_PIN; // set pin 11 as input
}

void loop() {
  // toogling digital output pin with xor operation (compare to part 1)
  DIG_OUT_PORT ^= DIG_OUT_PIN;
  // read back from digital input and write the value to the led
  if(DIG_IN_PIN & DIG_IN_PIN) {
    LED_PORT |= LED_PIN;
  } else {
    LED_PORT &= ~LED_PIN;
  }
  // wait a little (1 s)
  delay(1000);
}
