/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file serial.cpp
 * @author Alexander Entinger, BSc
 * @brief this file implements a class for serial communication
 * @license MPL2.0
 */

#include "serial.h"
#include <boost/bind.hpp>
#include <boost/asio/serial_port.hpp>

/**
 * @brief Constructor
 */
serial::serial(std::string const &devNode, unsigned int const baudRate) :
		m_devNode(devNode), m_baudRate(baudRate), m_io_service(), m_serial_port(m_io_service, m_devNode), m_timer(
				m_io_service), m_bytes_transferred(0) {

	m_serial_port.set_option(boost::asio::serial_port_base::baud_rate(m_baudRate));
	m_serial_port.set_option(boost::asio::serial_port_base::character_size(8));
	m_serial_port.set_option(
			boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
	m_serial_port.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
	m_serial_port.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
}

/**
 * @brief Destructor
 */
serial::~serial() {

}

/**
 * @brief write data to the serial port
 */
void serial::writeToSerial(unsigned char const *buf, unsigned int const size) {
	boost::asio::write(m_serial_port, boost::asio::buffer(buf, size));
}

/**
 * @brief read data from the serial port with timeout
 */
bool serial::readFromSerial(unsigned char *buf, unsigned int const size) {

	m_bytes_transferred = 0;

	m_io_service.reset();

	boost::asio::async_read(m_serial_port, boost::asio::buffer(buf, size),
			boost::bind(&serial::read_completed, this, boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));

	m_timer.expires_from_now(boost::posix_time::milliseconds(1000));

	m_timer.async_wait(boost::bind(&serial::timeout_expired, this, boost::asio::placeholders::error));

	m_io_service.run();

	return (m_bytes_transferred > 0);
}

/**
 *  @brief this function is called when a timeout while reading from the serial occurs
 */
void serial::timeout_expired(const boost::system::error_code& error) {
	if (error)
		return;
	m_serial_port.cancel();
}

void serial::read_completed(const boost::system::error_code& error, size_t const bytes_transferred) {
	m_bytes_transferred = bytes_transferred;
	m_timer.cancel();
}
