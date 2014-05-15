/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this file demonstrates how to read from analog pin A0 using the arduino framework
 * @file analog_input_arduino.ino
 */

int analog_input_pin = A0;

void setup() {
  // initialize the serial interface
  Serial.begin(115200);
}

void loop() {
  // read the value from the sensor:
  int const sensorValue = analogRead(analog_input_pin);    
  // write value to user
  Serial.println(sensorValue);
  // sleep a little
  delay(500);
}
