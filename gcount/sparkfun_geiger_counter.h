/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief this module implements the readout of the sparkfun geiger counter and converts it to cpm
 * @file sparkfun_geiger_counter.h
 * @license MPL 2.0
 */

#ifndef SPARKFUN_GEIGER_COUNTER_H_
#define SPARKFUN_GEIGER_COUNTER_H_

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>

class sparkfun_geiger_counter {
public:
	/**
	 * @brief Constructor
	 */
	sparkfun_geiger_counter(std::string const &dev_node);

	/**
	 * @brief Destructor
	 */
	~sparkfun_geiger_counter();

	/**
	 * @brief run the geiger counter
	 */
	inline void run() { m_io.run(); }

protected:
	static size_t const BAUDRATE = 9600;
	static size_t const MEASURE_TIMER_INTERVAL = 60; // 60 seconds
	static double const CONVERT_TO_MICROSIEVERT_PER_HOUR = 1.0/108.0;

private:
	boost::asio::io_service m_io;
	boost::asio::serial_port m_serial;

	char m_c;
	size_t m_cpm_counter;
	boost::mutex m_mutex;
	/**
	 * @brief this function is called when a byte was received on the serial
	 */
	void serial_byte_received(const boost::system::error_code& e);

	boost::asio::deadline_timer m_deadline_timer;
	/**
	 * brief this function is called once a minute and is used to display and reset the cpm count
	 */
	void eval_callback(const boost::system::error_code& e);

};

#endif /* SPARKFUN_GEIGER_COUNTER_H_ */
