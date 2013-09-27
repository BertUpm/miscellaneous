/**
 * @author Alexander Entinger, LXRobotics
 * @brief this file demonstrates the use of an external interrupt
 * @file external_interrupt_arduino.ino
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ )
 */

int const led_pin = 13; // D13
int const signal_pin = 2; // D2
int const signal_pin_interrupt_number = 0; // INT0, compare http://arduino.cc/en/Reference/AttachInterrupt

void setup() {
  // set the led pin to be an output
  pinMode(led_pin, OUTPUT);
    // set the signal pin to input pin
  pinMode(signal_pin, INPUT_PULLUP);
  // attach an interrupt handler when the signal goes from high to low
  attachInterrupt(signal_pin_interrupt_number, toogle_led, FALLING);
}

void loop() {

}

// toogle led on interrupt
static boolean led_on = true;
void toogle_led() {
  if(led_on) digitalWrite(led_pin, HIGH);
  else digitalWrite(led_pin, LOW);
  led_on = !led_on;
}
