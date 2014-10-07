/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module enables entering and exiting of critical sections through an RAII-pattern
 * @file critical_section.h
 */

#ifndef CRITICAL_SECTION_H_
#define CRITICAL_SECTION_H_

#include <stdint.h>
typedef uint16_t istate_t;

class critical_section
{
public:
	/**
	 * @brief Constructor - saves interrupt state and disables interrupts
	 */
	critical_section();

	/**
	 * @brief Destructor - restores interrupt state
	 */
	~critical_section();

private:
	istate_t m_int_state;
};


#endif /* CRITICAL_SECTION_H_ */
