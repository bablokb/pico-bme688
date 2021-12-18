## --------------------------------------------------------------------------
## Read BME688 sensor values with a Raspberry Pi Pico using the official Bosch-API
##
## Pico-Library
##
## Author: Bernhard Bablok
##
## https://github.com/bablokb/pico-bme688
## --------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.13)

include(${PICO_SDK_INIT_CMAKE_FILE})

project(bme68x)
add_library(${PROJECT_NAME} src/bme68x.c src/bme68x_platform.c)
target_link_libraries(${PROJECT_NAME} pico_stdlib hardware_i2c)
target_include_directories(${PROJECT_NAME} PUBLIC include)
