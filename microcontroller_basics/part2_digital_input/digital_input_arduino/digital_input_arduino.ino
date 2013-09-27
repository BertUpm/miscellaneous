/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this sketch illustrates the usage of the digital input pin
 * @file digital_input_arduino.ino
 * @license CC BY-NC-SA 3.0 ( http://creativecommons.org/licenses/by-nc-sa/3.0/ ) 
 */

int const led_pin = 13;
int const dig_out_pin = 12;
int const dig_in_pin = 11;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(dig_out_pin, OUTPUT);
  pinMode(dig_in_pin, INPUT);
}

// status flag indicating the value of the next out value
boolean next_out_value_is_high = true;

void loop() {
  // set digital output pin
  if(next_out_value_is_high) {
    digitalWrite(dig_out_pin, HIGH);
  } else {
    digitalWrite(dig_out_pin, LOW);
  }
  // update the status flag
  next_out_value_is_high = !next_out_value_is_high;
  // read back from digital input
  int dig_out_pin_value = digitalRead(dig_in_pin);
  // write the value to the led
  digitalWrite(led_pin, dig_out_pin_value);
  // wait a little (1 s)
  delay(1000);
}
