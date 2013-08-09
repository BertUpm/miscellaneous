/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/**
 * @author Alexander Entinger, MSc
 * @brief test driver for camera implementation
 * @file main.cpp
 */

#include <iostream>
#include <stdlib.h>
#include "camera.h"

void print_help() {
	std::cout << "Usage: camera device_node file_name" << std::endl;
}

int main(int argc, char **argv) {

	int const num_of_arguments = 3;

	if(argc != num_of_arguments) {
		print_help();
	} else {
		camera cam(argv[1]);
		if(!cam.take_and_save_picture(argv[2])) std::cout << "Error while taking a image." << std::endl;
	}

	return EXIT_SUCCESS;
}
