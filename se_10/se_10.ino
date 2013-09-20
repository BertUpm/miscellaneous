/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this sketch illustrates the functionality of the se-10 PIR proximity sensor
 * @file se_10.ino
 */

int const signal_pin = 2;
int const signal_pin_interrupt_number = 0; // compare http://arduino.cc/en/Reference/AttachInterrupt

void setup() {
  // set the signal pin to input pin
  pinMode(signal_pin, INPUT);
  // initialize serial interface
  Serial.begin(115200);
  // attach an interrupt handler when the signal goes from high to low
  attachInterrupt(signal_pin_interrupt_number, motion_detected, FALLING);
}

void loop() {
  
}

void motion_detected() {
  Serial.println("Motion detected");
}
