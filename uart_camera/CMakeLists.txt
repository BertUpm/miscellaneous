cmake_minimum_required(VERSION 2.6)
find_package(Boost)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(camera main.cpp camera.cpp serial.cpp)
	target_link_libraries(camera boost_system)
endif()
