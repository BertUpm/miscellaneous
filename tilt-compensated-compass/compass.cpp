/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file compass.cpp
 * @author Alexander Entinger, MSc
 * @brief calculates the tilt-compensated heading from the electronic compass
 */

#include "compass.h"
#include <math.h>
#include <stdexcept>

/**
 * @brief calculates the tilt compensated heading of the electronic compass
 * @param acc acceleration sensor data [m/s²]
 * @param mag magnetic sensor data [G]
 * @param compensate_tilt if this parameter is set to true, the tilt is compensated using accelerometer data
 * @return heading in radiant
 */
float compass::calcHeading(float const acc_x, float const acc_y, float const acc_z,
		float const mag_x, float const mag_y, float const mag_z, bool const compensate_tilt) {

		// normalise mag vector
	float const M = sqrt(pow(mag_x, 2) + pow(mag_y, 2) + pow(mag_z, 2));
	float const mx = mag_x / M;
	float const my = mag_y / M;
	float const mz = mag_z / M;

	float mx2 = mx;
	float my2 = my;

	if(compensate_tilt) {
		// normalise acc vector
		float const A = sqrt(pow(acc_x, 2) + pow(acc_y, 2) + pow(acc_z, 2));
		float const ax = acc_x / A;
		float const ay = acc_x / A;

		// calc pitch and roll
		float const pitch = asin((-1.0) * ax);
		float roll = 0.0f;
		if ((fabs(pitch) - (M_PI / 2)) < 0.001) { // pitch is 90 degrees
			roll = 0.0;
		} else {
			roll = asin(ay / cos(pitch));
		}

		// calc tilt compensated mag vector values
		mx2 = mx * cos(pitch) + mz * sin(pitch);
		my2 = mx * sin(roll) * sin(pitch) + my * cos(roll) - mz * sin(roll) * cos(pitch);
	}

	if (mx2 > 0 && my2 >= 0) {
		return atan(my2 / mx2);
	} else if (mx2 < 0) {
		return (M_PI + atan(my2 / mx2));
	} else if (mx2 > 0 && my2 <= 0) {
		return (2 * M_PI + atan(my2 / mx2));
	} else if (mx2 == 0 && my2 < 0) {
		return (M_PI / 2.0);
	} else if (mx2 == 0 && my2 > 0) {
		return (M_PI + atan(my2 / mx2));
	} else {
		throw std::runtime_error("error, heading could not be calculated");
	}
}
