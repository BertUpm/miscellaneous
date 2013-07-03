/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file main.cpp
 * @author Alexander Entinger, MSc
 * @brief testdriver for tilt-compensated heading calculation from the electronic compass
 */

#include <iostream>
#include <stdlib.h>
#include <stdexcept>
#include "compass.h"

int main(int argc, char **argv) {

	std::cout << "Testdriver for tilt compensated compass module" << std::endl;

	float const mag[3] = {0.95, 0.23, 0.45};
	float const acc[3] = {0.0, 0.0, 9.81};

	std::cout << "Testing module without tilt compensation" << std::endl;
	try {
		std::cout << "Heading [rad] = " << compass::calcHeading(mag[0], mag[1], mag[2]) << std::endl;
	} catch(std::runtime_error &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "Testing module with tilt compensation" << std::endl;
	try {
		std::cout << "Heading [rad] = " << compass::calcHeading(acc[0], acc[1], acc[2], mag[0], mag[1], mag[2]) << std::endl;
	} catch(std::runtime_error &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	// the two heading results should be the same, since with this accelerometer orientation
	// the z axis of the magnetic field sensor is exactly vertical

	return EXIT_SUCCESS;
}
