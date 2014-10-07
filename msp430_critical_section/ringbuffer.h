/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this class implements a ringbuffer
 * @file ringbuffer.h
 */

#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <stdint.h>
#include <stdbool.h>

class ringbuffer
{
public:
	/**
	 * @brief Constructor
	 */
	ringbuffer();

	/**
	 * @brief Destructor
	 */
	~ringbuffer() { }

	/**
	 * @brief returns true if the ringbuffer is empty, false otherwise
	 */
	bool is_empty();

	/**
	 * @brief stores an element into the ringbuffer
	 */
	void put(uint8_t const data);

	/**
	 * @brief retrieves an element from the ringbuffer
	 */
	uint8_t get();

private:
	static uint8_t const RINGBUFFER_SIZE = 128;

	uint8_t m_buffer[ringbuffer::RINGBUFFER_SIZE];
	uint16_t m_head;
	uint16_t m_tail;
	uint16_t m_n;

	/**
	 * @brief increments pointers of the ringbuffer
	 */
	uint16_t incr_ptr(uint16_t const ptr);
};

#endif
