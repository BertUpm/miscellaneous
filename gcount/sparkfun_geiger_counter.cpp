/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements the readout of the sparkfun geiger counter and converts it to cpm
 * @file sparkfun_geiger_counter.cpp
 * @license MPL 2.0
 */

#include "sparkfun_geiger_counter.h"
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

/**
 * @brief Constructor
 */
sparkfun_geiger_counter::sparkfun_geiger_counter(std::string const &dev_node) : m_io(), m_serial(m_io, dev_node), m_c(0), m_cpm_counter(0), m_deadline_timer(m_io, boost::posix_time::seconds(MEASURE_TIMER_INTERVAL)) {

	m_serial.set_option(boost::asio::serial_port_base::baud_rate(sparkfun_geiger_counter::BAUDRATE));

	boost::asio::async_read(m_serial, boost::asio::buffer(&m_c, 1), boost::bind(&sparkfun_geiger_counter::serial_byte_received, this, boost::asio::placeholders::error));

	m_deadline_timer.async_wait(boost::bind(&sparkfun_geiger_counter::eval_callback, this, boost::asio::placeholders::error));
}

/**
 * @brief Destructor
 */
sparkfun_geiger_counter::~sparkfun_geiger_counter() {
	m_serial.close();
}

/**
 * @brief this function is called when a byte was received on the serial
 */
void sparkfun_geiger_counter::serial_byte_received(const boost::system::error_code& e) {
	if(e) {
		std::cerr << e.message() << std::endl;
		return;
	}
	if(m_c == '0' || m_c == '1') {
		boost::mutex::scoped_lock lock(m_mutex);
		m_cpm_counter++;
	}
	m_c = 0;
	boost::asio::async_read(m_serial, boost::asio::buffer(&m_c, 1), boost::bind(&sparkfun_geiger_counter::serial_byte_received, this, boost::asio::placeholders::error));
}

/**
 * brief this function is called once a minute and is used to display and reset the cpm count
 */
void sparkfun_geiger_counter::eval_callback(const boost::system::error_code& e) {
	m_deadline_timer.expires_at(m_deadline_timer.expires_at() + boost::posix_time::seconds(MEASURE_TIMER_INTERVAL));
	m_deadline_timer.async_wait(boost::bind(&sparkfun_geiger_counter::eval_callback, this, boost::asio::placeholders::error));
	{
		boost::mutex::scoped_lock lock(m_mutex);
		std::cout << m_cpm_counter << " CPM, "
				<< static_cast<double>(m_cpm_counter) * CONVERT_TO_MICROSIEVERT_PER_HOUR << " microSv/h" << std::endl;

		m_cpm_counter = 0;
	}
}
