/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, MSc
 * @brief module for controlling the camera
 * @file camera.h
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <string>
#include "serial.h"

class camera {
public:
	/**
	 * @brief Constructor
	 * @param devNode device node of the serial interface
	 */
	camera(std::string const &dev_node);

	/**
	 * @brief Destructor
	 */
	~camera() {
	}

	/**
	 * @brief takes a picture and saves it to the filename
	 */
	bool take_and_save_picture(std::string const &file_name);

private:
	serial m_serial;
	bool m_connected;
	bool m_initialized;

	static size_t const m_baud_rate = 115200;
	static size_t const m_msg_size = 6;

	/**
	 * @brief connects to the camera after power up
	 * @return true if could connect, false otherwise
	 */
	bool connect();

	/**
	 * @brief initializes the camera and sets the package size
	 */
	bool initialize();

	/**
	 * @brief compares msg 1 byte for byte with msg, returns true if identical, false otherwise
	 */
	bool check_msg(unsigned char const *msg1, unsigned char const *msg2, size_t const num_of_bytes = m_msg_size);
};

#endif /* CAMERA_H_ */
