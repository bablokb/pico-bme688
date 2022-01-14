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

# defines for the library
add_compile_definitions(BME68X_DO_NOT_USE_FPU)
add_compile_definitions(BME68X_PORT=i2c1)
add_compile_definitions(BME68X_ADDR=BME68X_I2C_ADDR_HIGH)
add_compile_definitions(BME68X_SDA=2)
add_compile_definitions(BME68X_SCL=3)
#add_compile_definitions(BME68X_I2C_PU)      # use builtin-pullups
add_compile_definitions(ALTITUDE_AT_LOC=520)

# add preprocessor-constant DEBUG for Debug-builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_VERBOSE_MAKEFILE 1)
  add_compile_definitions(DEBUG)
else()
endif()

add_subdirectory(lib)
add_subdirectory(examples/parallel)
add_subdirectory(examples/sequential)