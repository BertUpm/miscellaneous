/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * @author Alexander Entinger
 * @file SoftUART.c
 * @description software uart
 */
#include "SoftUART.h"


// Prototypes
void timer2_start();
void timer2_stop();
void timer0_start();
void timer0_stop();
uint8_t timer0_active();
uint8_t IncrPtr(uint8_t ptr);
void PutToRxBuffer(uint8_t val);
uint8_t GetFromRxBuffer();
void PutToTxBuffer(uint8_t val);
uint8_t GetFromTxBuffer();


// UART States
#define IDLE  (0)
#define START (1)
#define BIT   (2)
#define STOPP (3)

// UART Receive Static Variables
static volatile uint8_t softUART_RX_State  = IDLE;
static volatile uint8_t softUART_RX_BitCnt = 0;
static volatile uint8_t softUART_RX_Data   = 0x00;
// Receive Ringbuffer
#define RX_SIZE 128
static volatile uint8_t RX_BUF[RX_SIZE];
static volatile uint8_t RX_Head = 0;
static volatile uint8_t RX_Tail = 0;
static volatile uint8_t RX_N = 0;

// UART Transmit Static Variables
static volatile uint8_t softUART_TX_State  = IDLE;
static volatile uint8_t softUART_TX_BitCnt = 0;
static volatile uint8_t softUART_TX_Data   = 0x00;
// Transmit Ringbuffer
#define TX_SIZE 32
static volatile uint8_t TX_BUF[RX_SIZE];
static volatile uint8_t TX_Head = 0;
static volatile uint8_t TX_Tail = 0;
static volatile uint8_t TX_N = 0;
 

/*
 * @brief initialization of the software uart
 */
void SoftUART_Init() {
	UART_PORT |=  (1<<TX_PIN); // set TX Pin to idle value
	UART_PORT |=  (1<<RX_PIN); // PullUp for RX
	UART_DIR  |=  (1<<TX_PIN); // set TX Pin to output
	UART_DIR  &= ~(1<<RX_PIN); // set RX Pin to input

	EICRA |= (1<<ISC11);	   // since RX is on INT1 Pin we activate 
	// interrupts if the value changes from 1 to 0 (start condition)
	EIMSK |= (1<<INT1);		   // enable interrupt for RX Pin
	sys.flag.SoftUART_Rx = 0;  // no data received so far
}

/*
 * @brief get a byte from the ringbuffer
 */
uint8_t SoftUART_GetByte() {
	return GetFromRxBuffer();
}

/*
 * @brief returns 1 if buffer is empty, 0 otherwise
 */
uint8_t SoftUART_RxBufferEmpty() {
	if(RX_N == 0) return 1;
	else          return 0;
}

/*
 * @brief store a byte to the transmit ringbuffer
 */
void SoftUART_PutByte(uint8_t val) {
	PutToTxBuffer(val);
}


/*
 * @brief ISR for the RX pin
 */
ISR(INT1_vect) {
	// start bit received, start timer 2 for decoding the message
	if(softUART_RX_State == IDLE) {
		softUART_RX_State = START;
		EIMSK &= ~(1<<INT1); // disable interrupts for RX pin
		timer2_start(); // start the reading timer
	}	
}

/*
 * @brief start timer 2
 */
void timer2_start() {
	// FOSC = 16 MHz
	// 1 Timer Step = 2 us
	// Prescaler = 32
	// Baudrate = 4800 Baud
	// Time pro Bit = 208.33333 us
	// TCNT2 Reload Value in first to get an offset of half a bit is
	// therefor 255 - 208 / (2*2) for sample
	TCNT2   = (255 - (208/4));
	// enable prescaler
	TCCR2B = (1<<CS21) | (1<<CS20);
	// enable timer 2 overflow interrupt
	TIMSK2 |= (1<<TOIE2);
}

/*
 * @brief stop timer 2
 */
void timer2_stop() {
	// disable prescaler
	TCCR2B &= ~((1<<CS22) | (1<<CS21) | (1<<CS20));
	// enable timer 2 overflow interrupt
	TIMSK2 &= ~(1<<TOIE2);
}

/*
 * @brief ISR for timer 2 overflow
 */
ISR(TIMER2_OVF_vect) {
	TCNT2 = (255 - (208/2));

	switch(softUART_RX_State) {
		case IDLE: 
		break;
		case START: {
						softUART_RX_State  = BIT;
						softUART_RX_BitCnt = 0;
						softUART_RX_Data   = 0x00;
					}
		break;
		case BIT:	{
						// read pin value and store it accordingly
						uint8_t rxPin = 0;
						if(UART_PIN & (1<<RX_PIN)) { rxPin = 1; }
						else                       { rxPin = 0; }
						softUART_RX_Data +=  (rxPin << softUART_RX_BitCnt);
						softUART_RX_BitCnt++;
						if(softUART_RX_BitCnt == 8) {
							softUART_RX_State = STOPP;
							PutToRxBuffer(softUART_RX_Data); // save data
							sys.flag.SoftUART_Rx = 1;  // data received
						}
					}
		break;
		case STOPP: {
						softUART_RX_State = IDLE;
						timer2_stop();
						EIFR  |= (1<<INTF1); // clear the eventually set interrupt flag by writing
						// a logical one to it (see datasheet page 72)
						EIMSK |= (1<<INT1); // activate interrupts again
					}	
		break;		
		default: 	softUART_RX_State = IDLE;
		break;		
	}
}

/*
 * @brief start timer 0
 */
void timer0_start() {
	// FOSC = 16 MHz
	// 1 Timer Step = 4 us
	// Prescaler = 64
	// Baudrate = 4800 Baud
	// Time pro Bit = 208.33333 us
	// TCNT0 Reload Value = 255 - 208 / 4 for transmit
	TCNT0   = (255 - (208/4));
	// enable prescaler
	TCCR0B = (1<<CS01) | (1<<CS00);
	// enable timer 0 overflow interrupt
	TIMSK0 |= (1<<TOIE0);
}

/*
 * @brief stop timer 0
 */
void timer0_stop() {
	// disable prescaler
	TCCR0B &= ~((1<<CS02) | (1<<CS01) | (1<<CS00));
	// enable timer 0 overflow interrupt
	TIMSK0 &= ~(1<<TOIE0);
}

/*
 * @brief returns 1 if timer 0 is active, 0 otherwise
 */
uint8_t timer0_active() {
	return (TCCR0B & (1<<CS00));
}

/*
 * @brief ISR for timer 0 overflow
 */
ISR(TIMER0_OVF_vect) {
	TCNT0 = (255 - (208/4));

	switch(softUART_TX_State) {
		case IDLE: 	softUART_TX_State  = START;
		break;
		case START: softUART_TX_State  = BIT;
					softUART_TX_BitCnt = 0;
					softUART_TX_Data   = GetFromTxBuffer();
					UART_PORT &= ~(1<<TX_PIN); // set start condition
		break;
		case BIT:	
					if(softUART_RX_BitCnt >= 8) {
						softUART_RX_State = STOPP;
						PutToRxBuffer(softUART_RX_Data); // save data
					}
					else {
						uint8_t txPin = (softUART_TX_Data & (1<<softUART_RX_BitCnt)) >> (softUART_RX_BitCnt);
						if(txPin == 1) { UART_PORT |=  (1<<TX_PIN); }
						else           { UART_PORT &= ~(1<<TX_PIN); }
						softUART_TX_BitCnt++;
					}
		break;
		case STOPP: UART_PORT |=  (1<<TX_PIN); // set stop condition
					if(TX_N == 0) {  // after all bits are sent -> stop tx
						softUART_RX_State = IDLE;
						timer0_stop();
					}
					else {
						softUART_RX_State = START;
					}
		break;		
		default: 	softUART_RX_State = IDLE;
		break;		
	}
}


/*
 * @brief increments pointers of the ringbuffer
 */
uint8_t IncrPtr(uint8_t ptr) {
	uint8_t tmp = ptr + 1;
	if(tmp == RX_SIZE) { return 0;   }
	else 			   { return tmp; }
}

/*
 * @brief puts received element in the rx buffer
 */
void PutToRxBuffer(uint8_t val) {
  if(RX_N < RX_SIZE) {
    RX_BUF[RX_Head] = val;
    RX_N++;
    RX_Head = IncrPtr(RX_Head);
  }
}

/*
 * @brief gets a stored element from the receive buffer
 */
uint8_t GetFromRxBuffer() {
 uint8_t tmp = 0;
 if(RX_N > 0) {
	tmp = RX_BUF[RX_Tail];
	RX_Tail = IncrPtr(RX_Tail);
	RX_N--;
 }
 return tmp;
}

/*
 * @brief puts received element in the tx buffer
 */
void PutToTxBuffer(uint8_t val) {
  if(TX_N < TX_SIZE) {
    TX_BUF[TX_Head] = val;
    TX_N++;
    TX_Head = IncrPtr(TX_Head);
	if(!timer0_active()) { timer0_start(); }
  }
}

/*
 * @brief gets a stored element from the transmit buffer
 */
uint8_t GetFromTxBuffer() {
 uint8_t tmp = 0;
 if(TX_N > 0) {
	tmp = TX_BUF[TX_Tail];
	TX_Tail = IncrPtr(TX_Tail);
	TX_N--;
 }
 return tmp;
}

