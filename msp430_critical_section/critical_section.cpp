/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module enables entering and exiting of critical sections through an RAII-pattern
 * @file critical_section.cpp
 */

#include "critical_section.h"

/**
 * @brief Constructor - saves interrupt state and disables interrupts
 */
critical_section::critical_section()
{
	m_int_state = _get_interrupt_state();
	_disable_interrupts();
}

/**
 * @brief Destructor - restores interrupt state
 */
critical_section::~critical_section()
{
	_set_interrupt_state(m_int_state);
}
