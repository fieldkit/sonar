project(sonar)
cmake_minimum_required(VERSION 2.6)

set(ARDUINO_IDE "${CMAKE_CURRENT_SOURCE_DIR}/../arduino-1.8.3") 
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../arduino-cmake-minimal/cmake/")

add_subdirectory(firmware/module)
add_subdirectory(firmware/test)
