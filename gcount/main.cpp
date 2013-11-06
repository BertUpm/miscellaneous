/**
 * @author Alexander Entinger, MSc / LXRobotics
 * @brief main file for sparkfun_geiger_counter evaluation tool
 * @file main.cpp
 * @license MPL 2.0
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include "sparkfun_geiger_counter.h"

void print_help() {
	std::cout << "gcount DEVNODE" << std::endl;
	std::cout << "\tDEVNODE device node under which the geiger counter registers itself, e.g. /dev/ttyUSB0 on Linux, COM21 on Windows" << std::endl;
}

int main(int argc, char **argv) {

	if(argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}

	std::string const dev_node(argv[1]);

	try {
		sparkfun_geiger_counter gc(dev_node);
		gc.run();
	} catch(boost::system::system_error& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    };

	return EXIT_SUCCESS;
}
