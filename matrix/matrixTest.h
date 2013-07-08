/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file matrixTest.h
 * @author Alexander Entinger, BSc
 * @brief test class for matrix template class
 */

#ifndef MATRIXTEST_H_
#define MATRIXTEST_H_

#include <gtest/gtest.h>

class matrixTest : public ::testing::Test {
protected:
	/**
	 * @brief Constructor
	 */
	matrixTest() { }

	/**
	 * @brief Destructor
	 */
	virtual ~matrixTest() { }

	/**
	 * @brief this called will be called right before each test
	 */
	virtual void SetUp() { }

	/**
	 * @brief this code will be called right after each test
	 */
	virtual void TearDown() { }
};


#endif /* MATRIXTEST_H_ */
