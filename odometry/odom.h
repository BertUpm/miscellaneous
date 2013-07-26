/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @brief class to calculate odometry data from measurement
 * @file odom.h
 */

#ifndef ODOM_H_
#define ODOM_H_

class odom {
public:
	/**
	 * @brief Constructor initialises the function
	 * @param x starting coordinate x value / m
	 * @param y starting coordinate y value / m
	 * @param theta starting angle theta / rad
	 * @param deltaT time step  / s
	 * @param D_left diameter of left wheel / m
	 * @param D_right diameter of right wheel / m
	 * @param R_left resolution of left wheel encoder / ticks/revolution
	 * @param R_right resolution of right wheel encoder / ticks/revolution
	 * @param A distance between the both wheels / m
	 */
	odom(double const x, double const y, float const theta, float const deltaT, float const D_left, float const D_right,
			unsigned int const R_left, unsigned int const R_right, float const A);

	/**
	 * @brief Destructor
	 */
	~odom() {
	}

	/**
	 * @brief updates the odometry data elements
	 * @param time_left_ms time for one segment on the left wheel in ms
	 * @param time_right_ms time for one segment on the right wheel in ms
	 * @param theta external provided theta for heading calculation
	 * @param useExternalTheta use the external theta for heading calculation
	 */
	void update(float const time_left_ms, float const time_right_ms, float const theta, bool const useExternTheta);

	/**
	 * @brief returns the position as determined by the odometric system
	 * @param x x position / m
	 * @param y y position / m
	 */
	void getPosition(double &x, double &y) const;

	/**
	 * @brief returns the speed of the vehicle in forward direction
	 * @param speed in m/s
	 */
	inline float getSpeed() const {
		return m_v;
	}

	/**
	 * @brief returns the heading
	 * @return heading in rad
	 */
	inline float getHeading() const {
		return m_theta;
	}

private:
	double m_x; // x position
	double m_y; // y position
	float m_theta;
	float m_v;
	float m_deltaT, m_D_left, m_D_right, m_R_left, m_R_right, m_A;
	float m_b_left, m_b_right; // length of one segment on left and right encoder wheel
};

#endif /* ODOM_H_ */
