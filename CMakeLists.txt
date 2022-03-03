## --------------------------------------------------------------------------
## Read BME688 sensor values with a Raspberry Pi Pico using the official Bosch-API
##
## Author: Bernhard Bablok
##
## https://github.com/bablokb/pico-bme688
## --------------------------------------------------------------------------

# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
#set(PICO_SDK_PATH "/data/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-bme688 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# defines for the library (override if necessary)
set(BME68X_PORT     "i2c1"                 CACHE STRING "i2c-port name")
set(BME68X_SDA      "2"                    CACHE STRING "SDA pin-number for BME68X")
set(BME68X_SCL      "3"                    CACHE STRING "SCL pin-number for BME68X")
set(BME68X_ADDR     "BME68X_I2C_ADDR_HIGH" CACHE STRING "BME68x address constant")
set(BME68X_I2C_PU   "NO_BME68X_I2C_PU"     CACHE STRING "use (NO) builtin pullups")


message(STATUS "Port:    ${BME68X_PORT}")
message(STATUS "Address: ${BME68X_ADDR}")
message(STATUS "SDA-pin: ${BME68X_SDA}")
message(STATUS "SCL-pin: ${BME68X_SCL}")
message(STATUS "Pullups: ${BME68X_I2C_PU}")

add_compile_definitions(BME68X_PORT=${BME68X_PORT})
add_compile_definitions(BME68X_ADDR=${BME68X_ADDR})
add_compile_definitions(BME68X_SDA=${BME68X_SDA})
add_compile_definitions(BME68X_SCL=${BME68X_SCL})
add_compile_definitions(${BME68X_I2C_PU})

# add preprocessor-constant DEBUG for Debug-builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_VERBOSE_MAKEFILE 1)
  add_compile_definitions(DEBUG)
else()
endif()

add_subdirectory(lib)
