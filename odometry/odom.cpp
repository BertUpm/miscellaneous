/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, BSc
 * @brief class to calculate odometry data from measurement
 * @file odom.cpp
 */

#include "odom.h"
#include <math.h>
#include <boost/math/special_functions/fpclassify.hpp> // isnan
/**
 * @brief initialises the function
 * @param x starting coordinate x value
 * @param y starting coordinate y value
 * @param theta starting angle theta
 * @param deltaT time step
 * @param D_left diameter of left wheel
 * @param D_right diameter of right wheel
 * @param R_left resolution of left wheel encoder
 * @param R_right resolution of right wheel encoder
 * @param A distance between the both wheels
 */
odom::odom(double const x, double const y, float const theta, float const deltaT, float const D_left, float const D_right,
		unsigned int const R_left, unsigned int const R_right, float const A) {

	m_x = x;
	m_y = y;
	m_theta = theta;
	m_deltaT = deltaT;
	m_D_left = D_left;
	m_D_right = D_right;
	m_R_left = R_left;
	m_R_right = R_right;
	m_A = A;

	m_b_left = (m_D_left / 2.0) * (2.0 * M_PI / m_R_left); // segment length of left wheel
	m_b_right = (m_D_right / 2.0) * (2.0 * M_PI / m_R_right); // segment length of right wheel
}

/**
 * @brief updates the odometry data elements
 * @param time_left_ms time for one segment on the left wheel in ms
 * @param time_right_ms time for one segment on the right wheel in ms
 * @param theta external provided theta for heading calculation
 * @param useExternalTheta use the external theta for heading calculation
 */
void odom::update(float const time_left_ms, float const time_right_ms, float const theta, bool const useExternTheta) {

	double const v_left = time_left_ms != 0.0f ? m_b_left / (time_left_ms / 1000.0) : 0.0f;
	double const v_right = time_right_ms != 0.0f ? m_b_right / (time_right_ms / 1000.0) : 0.0f;

	double const d_left = v_left * m_deltaT;
	double const d_right = v_right * m_deltaT;

	double const deltaTheta = (d_right - d_left) / m_A;
	if (!boost::math::isnan(deltaTheta) && !boost::math::isinf(deltaTheta)) {
		m_theta += deltaTheta;
	}

	double const deltaD = (d_left + d_right) / 2.0;

	double th = 0.0;
	if (useExternTheta)
		th = theta;
	else
		th = m_theta;

	if (!boost::math::isnan(deltaD) && !boost::math::isinf(deltaD)) {
		m_x += deltaD * cos(th);
		m_y += deltaD * sin(th);
	}

	m_v = (v_left + v_right) / 2.0;
}

/**
 * @brief returns the position as determined by the odometric system
 * @param x x position / m
 * @param y y position / m
 */
void odom::getPosition(double &x, double &y) const {
	x = m_x;
	y = m_y;
}
