/* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @file main.cpp
 * @author Alexander Entinger, BSc
 * @brief matrix template class test file
 */

#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char **argv) {

	std::cout << "Matrix template class unit test" << std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
