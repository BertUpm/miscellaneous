/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this file demonstrates how to read from analog pin A0 using the C programming language
 * @file analog_input_C.ino
 */

// A0 = ADC0 = PC0

void setup() {
  // initialize the serial interface
  Serial.begin(115200);
  
  // initialize the adc
  // disable digital input buffers for ADC0
  DIDR0 = (1<<ADC0D);
  // select AVcc as reference voltage and ADC0 as input
  ADMUX = (1<<REFS0);
  // enable adc
  ADCSRA = (1<<ADEN);
  // set prescaler to 128 -> fADC = 125 kHz
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

void loop() {
  // trigger adc readout
  ADCSRA |= (1<<ADSC);
  // wait for the readout to be complete
  while(ADCSRA & (1<<ADSC)) { asm(" NOP "); }
  // read the value from the adc result register
  int const sensorValue = ADC;
  // write value to user
  Serial.println(sensorValue);
  // sleep a little
  delay(500);
}
