/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief shows the state of the user button on the red led
 * @file msp430_first_steps.ino
 */

void setup() {
  pinMode(P1_3, INPUT_PULLUP);    // user button
  pinMode(P1_0, OUTPUT);   // red led
}

void loop() {
  digitalWrite(P1_0, digitalRead(P1_3));
}
