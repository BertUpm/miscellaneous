/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file compass.h
 * @author Alexander Entinger, MSc
 * @brief calculates the tilt-compensated heading from the electronic compass
 */

#ifndef COMPASS_H_
#define COMPASS_H_

class compass {
public:
	/**
	 * @brief calculates the tilt compensated heading of the electronic compass
	 * @param acc acceleration sensor data [m/s²]
	 * @param mag magnetic sensor data [G]
	 * @return tilt compensated heading in radiant
	 */
	static float calcHeading(float const acc_x, float const acc_y, float const acc_z,
				float const mag_x, float const mag_y, float const mag_z) {
		return calcHeading(acc_x, acc_y, acc_z, mag_x, mag_y, mag_z, true);
	}

	/**
	 * @brief calculates the not tilt compensated heading of the electronic compass
	 * @param mag magnetic sensor data [G]
	 * @return not tilt compensated heading in radiant
	 */
	static float calcHeading(float const mag_x, float const mag_y, float const mag_z) {
		return calcHeading(0.0f, 0.0f, 0.0f, mag_x, mag_y, mag_z, false);
	}

private:
	/**
	 * @brief Constructor
	 */
	compass() { }

	/**
	 * @brief Destructor
	 */
	~compass() { }

	/**
	 * @brief calculates the tilt compensated heading of the electronic compass
	 * @param acc acceleration sensor data [m/s²]
	 * @param mag magnetic sensor data [G]
	 * @param compensate_tilt if this parameter is set to true, the tilt is compensated using accelerometer data
	 * @return heading in radiant
	 */
	static float calcHeading(float const acc_x, float const acc_y, float const acc_z,
			float const mag_x, float const mag_y, float const mag_z, bool const compensate_tilt);


};


#endif /* COMPASS_H_ */
