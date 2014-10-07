/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this class implements a ringbuffer
 * @file ringbuffer.cpp
 */

#include "ringbuffer.h"
#include "critical_section.h"

/**
 * @brief Constructor
 */
ringbuffer::ringbuffer() : m_head(0), m_tail(0), m_n(0)
{

}

/**
 * @brief returns true if the ringbuffer is empty, false otherwise
 */
bool ringbuffer::is_empty()
{
	critical_section cs;
	return (m_n == 0);
}

/**
 * @brief stores an element into the ringbuffer
 */
void ringbuffer::put(uint8_t const data)
{
	critical_section cs;
	if (m_n < ringbuffer::RINGBUFFER_SIZE)
	{
		m_buffer[m_head] = data;
		m_n++;
		m_head = ringbuffer::incr_ptr(m_head);
	}
}

/**
 * @brief retrieves an element from the ringbuffer
 */
uint8_t ringbuffer::get()
{
	critical_section cs;
	uint8_t data = 0;
	if (m_n > 0) {
		data = m_buffer[m_tail];
		m_tail = ringbuffer::incr_ptr(m_tail);
		m_n--;
	}
	return data;
}

/**
 * @brief increments pointers of the ringbuffer
 */
uint16_t ringbuffer::incr_ptr(uint16_t const ptr)
{
	uint16_t const tmp = ptr + 1;
	if (tmp == ringbuffer::RINGBUFFER_SIZE)
	{
		return 0;
	}
	else
	{
		return tmp;
	}
}
