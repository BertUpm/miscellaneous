/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  DDRB |= (1<<5);
}

// the loop routine runs over and over again forever:
void loop() {
  PORTB ^= (1<<5);
  delay(1000);               // wait for a second
}
