/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module demonstrate how a software pwm could be implemented
 * @file software_pwm.ino
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>

// LED Pin = D13 = PB5
#define LED_DDR		(DDRB)
#define LED_PORT	(PORTB)
#define LED			(1<<5)

uint16_t const duration_500_ms = 31250; // Unit: Timersteps
uint16_t const duration_250_ms = 15625;

void init_application() {
  // set led to output and turn it off
  LED_PORT &= ~LED;
  LED_DDR |= LED;
  // reset timer register
  TCNT1 = 0x0000;
  // set OCR1A register
  OCR1A = duration_500_ms;
  // enable output compare match interrupt A
  TIMSK1 |= (1<<OCIE1A);
  // set precaler = 256 => 1 Timerstep @ 16 MHz = 16 us, 65535 Timersteps (2^16) = 1,048576 s
  TCCR1B |= (1<<CS12);
  // globally enable interrupts
  sei();
}

int main(void) {
	
	init_application();
	
	for(;;) {

    }
}

// interrupt service routine for timer 1 compare match A
ISR(TIMER1_COMPA_vect) {
	uint16_t current_OCR1A = OCR1A;
	static bool led_on = true;
	if(led_on) {
		LED_PORT |= LED;
		OCR1A = current_OCR1A + duration_500_ms;
	}
	else {
		LED_PORT &= ~LED;
		OCR1A = current_OCR1A + duration_250_ms;
	}
	led_on = !led_on; // toogle led on every call of isr
}