/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, MSc
 * @brief module for controlling the camera
 * @file camera.cpp
 */

#include "camera.h"
#include <iostream>
#include <fstream>

/**
 * @brief Constructor
 * @param devNode device node of the serial interface
 */
camera::camera(std::string const &dev_node) :
		m_serial(dev_node, m_baud_rate), m_connected(connect()), m_initialized(initialize()) {

	/*if (m_connected)
		std::cout << "Camera connected" << std::endl;
	if (m_initialized)
		std::cout << "Camera initialized" << std::endl;
		*/
}

/**
 * @brief takes a picture and saves it to the filename
 */
bool camera::take_and_save_picture(std::string const &file_name) {
	if (!m_connected || !m_initialized)
		return false;

	unsigned char const snapshot_msg[m_msg_size] = { 0xAA, 0x05, 0x00, 0x00, 0x00, 0x00 };
	m_serial.writeToSerial(snapshot_msg, m_msg_size);

	unsigned char reply[m_msg_size] = { 0x00 };
	bool success = m_serial.readFromSerial(reply, m_msg_size); // read ACK
	if (!success)
		return false;

	{
		unsigned char const expected_ack_msg[m_msg_size] = { 0xAA, 0x0E, 0x05, 0x00, 0x00, 0x00 };
		bool ack_received = check_msg(reply, expected_ack_msg, 3);
		if (!ack_received)
			return false;
	}

	unsigned char const getpicture_msg[m_msg_size] = { 0xAA, 0x04, 0x01, 0x00, 0x00, 0x00 };
	m_serial.writeToSerial(getpicture_msg, m_msg_size);

	success = m_serial.readFromSerial(reply, m_msg_size); // read ACK
	if (!success)
		return false;

	{
		unsigned char const expected_ack_msg[m_msg_size] = { 0xAA, 0x0E, 0x04, 0x00, 0x00, 0x00 };
		bool ack_received = check_msg(reply, expected_ack_msg, 3);
		if (!ack_received)
			return false;
	}

	success = m_serial.readFromSerial(reply, m_msg_size); // read image data package
	if (!success)
		return false;

	unsigned char const ack_msg[m_msg_size] = { 0xAA, 0x0E, 0x00, 0x00, 0x00, 0x00 };
	m_serial.writeToSerial(ack_msg, m_msg_size); // write ack message

	/*size_t const image_data_size = (static_cast<size_t>(reply[3]) << 16) + (static_cast<size_t>(reply[4]) << 8)
			+ static_cast<size_t>(reply[5]);*/

	// now receive the image data
	std::ofstream out(file_name.c_str(), std::ios_base::out | std::ios_base::binary);

	size_t const image_package_size = 512;
	unsigned char image_package[image_package_size] = { 0x00 };

	for (size_t image_package_counter = 0; m_serial.readFromSerial(image_package, image_package_size); image_package_counter++) { // read image data package

		/*size_t const data_in_package = (static_cast<size_t>(image_package[2])
				<< 8) + static_cast<size_t>(image_package[3]);
				*/

		for (size_t i = 4; i < image_package_size-2; i++)
			out << image_package[i];

		unsigned char const img_ack_msg[m_msg_size] = { 0xAA, 0x0E, 0x00,
				static_cast<unsigned char>(image_package_counter >> 8 & 0xFF),
				static_cast<unsigned char>(image_package_counter & 0xFF) };
		m_serial.writeToSerial(img_ack_msg, m_msg_size);

	}

	out.close();

	return true;
}

/**
 * @brief connects to the camera after power up
 * @return true if could connect, false otherwise
 */
bool camera::connect() {

	size_t const max_connection_tries = 60;

	unsigned char const sync_message[m_msg_size] = { 0xAA, 0x0D, 0x00, 0x00, 0x00, 0x00 };

	bool success = false;
	unsigned char reply[m_msg_size] = { 0x00 };

	for (size_t i = 0; i < max_connection_tries; i++) {
		m_serial.writeToSerial(sync_message, m_msg_size);
		success = m_serial.readFromSerial(reply, m_msg_size); // read ACK
		if (success)
			break;
	}

	unsigned char const expected_ack_msg[m_msg_size] = { 0xAA, 0x0E, 0x0D, 0x00, 0x00, 0x00 };
	bool const ack_received = check_msg(reply, expected_ack_msg, 3);

	if (!ack_received)
		return false;

	success = m_serial.readFromSerial(reply, m_msg_size); // read SYNC

	if (!success)
		return false;

	bool const sync_received = check_msg(reply, sync_message);

	unsigned char const ack_message[m_msg_size] = { 0xAA, 0x0E, 0x0D, 0x00, 0x00, 0x00 };
	m_serial.writeToSerial(ack_message, m_msg_size); // send ACK

	return sync_received;
}

/**
 * @brief initializes the camera and sets the package size
 */
bool camera::initialize() {

	unsigned char reply[m_msg_size] = { 0x00 };

	unsigned char const init_msg[m_msg_size] = { 0xAA, 0x01, 0x00, 0x07, 0x00, 0x07 };
	m_serial.writeToSerial(init_msg, m_msg_size);

	bool success = m_serial.readFromSerial(reply, m_msg_size); // read ACK
	if (!success)
		return false;

	{
		unsigned char const expected_ack_msg[m_msg_size] = { 0xAA, 0x0E, 0x01, 0x00, 0x00, 0x00 };
		bool ack_received = check_msg(reply, expected_ack_msg, 3);
		if (!ack_received)
			return false;
	}

	unsigned char const set_size_msg[m_msg_size] = { 0xAA, 0x06, 0x08, 0x00, 0x02, 0x00 };
	m_serial.writeToSerial(set_size_msg, m_msg_size);

	success = m_serial.readFromSerial(reply, m_msg_size); // read ACK
	if (!success)
		return false;

	{
		unsigned char const expected_ack_msg[m_msg_size] = { 0xAA, 0x0E, 0x06, 0x00, 0x00, 0x00 };
		bool ack_received = check_msg(reply, expected_ack_msg, 3);
		if (!ack_received)
			return false;
	}

	return true;

}

/**
 * @brief compares msg 1 byte for byte with msg, returns true if identical, false otherwise
 */
bool camera::check_msg(unsigned char const *msg1, unsigned char const *msg2, size_t const num_of_bytes) {
	for (size_t i = 0; i < num_of_bytes; i++) {
		if (msg1[i] != msg2[i])
			return false;
	}
	return true;
}
