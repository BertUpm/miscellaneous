/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * @author Alexander Entinger
 * @file UART.c
 * @description hardware uart
 */
#include "UART.h"


// Prototypes
uint8_t HardIncrPtr(uint8_t ptr);
void HardPutToRxBuffer(uint8_t val);
uint8_t HardGetFromRxBuffer();
void HardPutToTxBuffer(uint8_t val);
uint8_t HardGetFromTxBuffer();

// Receive Ringbuffer
#define RX_SIZE 16
static volatile uint8_t RX_BUF[RX_SIZE];
static volatile uint8_t RX_Head = 0;
static volatile uint8_t RX_Tail = 0;
static volatile uint8_t RX_N = 0;
// Transmit Ringbuffer
#define TX_SIZE 64
static volatile uint8_t TX_BUF[RX_SIZE];
static volatile uint8_t TX_Head = 0;
static volatile uint8_t TX_Tail = 0;
static volatile uint8_t TX_N = 0;


/*
 * @brief initialization of the software uart
 */
void UART_Init(uint8_t baudrate) {
	UCSR0A |= (1<<U2X0);    // double read / write speed
	UCSR0B |= (1<<RXCIE0) | // enable the receive interrupt
              (1<<RXEN0)  | // enable receiver
			  (1<<TXEN0);   // enable transmitter
	UBRR0 = baudrate;
	sys.flag.UART_Rx = 0;	// no data received so far
}

/*
 * @brief access date from the ring buffer
 */
uint8_t UART_GetByte() {
	return HardGetFromRxBuffer();
}

/*
 * @brief returns 0 if buffer is empty, otherwise a number
 */
uint8_t UART_RxBufferEmpty() {
	if(RX_N == 0) return 1;
	else          return 0;
}

/*
 * @brief interrupt service routine for receiving data
 */
ISR(USART_RX_vect) {
	HardPutToRxBuffer(UDR0);
	sys.flag.UART_Rx = 1;	// data received
}

/*
 * @brief write an array of bytes in the ringbuffer for transmission
 */
void UART_WriteBytes(uint8_t *bytes, uint8_t size) {
	uint8_t i=0;
	for(; i < size; i++) { HardPutToTxBuffer(bytes[i]); }
	UCSR0B |= (1<<UDRIE0); // enable transmission
}

/*
 * @brief interrupt service routine for transmitting data
 */
ISR(USART_UDRE_vect) {
	uint8_t data = HardGetFromTxBuffer();
	UDR0 = data;
	// disable interrupt if all data is transmitted
	if(TX_N == 0) { UCSR0B &= ~(1<<UDRIE0); } 
}

/*
 * @brief increments pointers of the ringbuffer
 */
uint8_t HardIncrPtr(uint8_t ptr) {
	uint8_t tmp = ptr + 1;
	if(tmp == RX_SIZE) { return 0;   }
	else 			   { return tmp; }
}

/*
 * @brief puts received element in the rx buffer
 */
void HardPutToRxBuffer(uint8_t val) {
  if(RX_N < RX_SIZE) {
    RX_BUF[RX_Head] = val;
    RX_N++;
    RX_Head = HardIncrPtr(RX_Head);
  }
}

/*
 * @brief gets a stored element from the receive buffer
 */
uint8_t HardGetFromRxBuffer() {
 uint8_t tmp = 0;
 if(RX_N > 0) {
	tmp = RX_BUF[RX_Tail];
	RX_Tail = HardIncrPtr(RX_Tail);
	RX_N--;
 }
 return tmp;
}

/*
 * @brief puts received element in the tx buffer
 */
void HardPutToTxBuffer(uint8_t val) {
  if(TX_N < TX_SIZE) {
    TX_BUF[TX_Head] = val;
    TX_N++;
    TX_Head = HardIncrPtr(TX_Head);
  }
}

/*
 * @brief gets a stored element from the transmit buffer
 */
uint8_t HardGetFromTxBuffer() {
 uint8_t tmp = 0;
 if(TX_N > 0) {
	tmp = TX_BUF[TX_Tail];
	TX_Tail = HardIncrPtr(TX_Tail);
	TX_N--;
 }
 return tmp;
}
