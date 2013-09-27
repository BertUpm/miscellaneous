/**
 * @author Alexander Entinger, LXRobotics
 * @brief this file demonstrates the use of an external interrupt
 * @file external_interrupt_C.ino
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

// led_pin = PB5
#define LED_PIN  (1<<5)
#define LED_DDR  (DDRB)
#define LED_PORT (PORTB)
// signal_pin = INT0 = PD2
#define SIGNAL_PIN    (1<<2)
#define SIGNAL_DDR    (DDRD)
#define SIGNAL_PORT   (PORTD)

void setup() {
  // set the led pin to be an output
  LED_DDR |= LED_PIN;
  // set the signal pin to input pin with pullup
  SIGNAL_DDR &= ~SIGNAL_PIN;
  SIGNAL_PORT |= SIGNAL_PIN;
  // activate the external interrupt 0 for firing, when the signal goes from high to low
  EICRA |= (1<<ISC01); // trigger int0 isr after falling edge on int0
  EIMSK |= (1<<INT0); // enable int0
}

void loop() {

}

// toogle led on external interrupt 0
ISR(INT0_vect) {
  LED_PORT ^= LED_PIN;
}
