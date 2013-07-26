/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @brief testdriver for the odometry module to demonstrate its usage
 * @file main.cpp
 */

#include <iostream>
#include <stdlib.h>
#include "odom.h"

int main() {

	std::cout << "Testing odometry calculation" << std::endl;

	size_t const num_iterations = 10;
	double const initial_x = 0.0f;
	double const initial_y = 0.0f;
	float const initial_theta = 0.0f;
	float const delta_t = 10.0 / 1000.0; // 10 ms
	float const D_left = 10.0 / 100.0; // 10 cm
	float const D_right = D_left;
	size_t const R_left = 100;
	size_t const R_right = 100;
	float const A = 20.0 / 100.0; // 20 cm

	{
		std::cout << "Driving a straight line at constant speed" << std::endl;

		odom odometry_system(initial_x, initial_y, initial_theta, delta_t, D_left, D_right, R_left, R_right, A);

		float const time_left_ms = 1.0;
		float const time_right_ms = time_left_ms;

		for (size_t i = 0; i < num_iterations; i++) {

			odometry_system.update(time_left_ms, time_right_ms, 1.0f, false);
			double x = 0.0, y = 0.0;
			odometry_system.getPosition(x, y);
			float const speed = odometry_system.getSpeed();
			float const theta = odometry_system.getHeading();
			std::cout << "[" << i + 1 << "] x = " << x << " m , y = " << y << " m , v = " << speed << " m/s, theta = " << theta << " rad"
					<< std::endl;
		}

	}

	{
		std::cout << "Turn on the spot at constant speed" << std::endl;

		odom odometry_system(initial_x, initial_y, initial_theta, delta_t, D_left, D_right, R_left, R_right, A);

		float const time_left_ms = -1.0;
		float const time_right_ms = 1.0;

		for (size_t i = 0; i < num_iterations; i++) {

			odometry_system.update(time_left_ms, time_right_ms, 1.0f, false);
			double x = 0.0, y = 0.0;
			odometry_system.getPosition(x, y);
			float const speed = odometry_system.getSpeed();
			float const theta = odometry_system.getHeading();
			std::cout << "[" << i + 1 << "] x = " << x << " m , y = " << y << " m , v = " << speed << " m/s, theta = " << theta << " rad"
					<< std::endl;
		}

	}

	return EXIT_SUCCESS;
}
