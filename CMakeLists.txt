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

# Add executable. Default name is the project name, version 0.1

add_executable(pico-bme688 pico-bme688.c )

# add preprocessor-constant DEBUG for Debug-builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_VERBOSE_MAKEFILE 1)
  add_compile_definitions(DEBUG)
else()
endif()

pico_set_program_name(pico-bme688 "pico-bme688")
pico_set_program_version(pico-bme688 "0.1")

pico_enable_stdio_uart(pico-bme688 1)
pico_enable_stdio_usb(pico-bme688 0)

# Add the standard library to the build
target_link_libraries(pico-bme688 pico_stdlib)

# Add any user requested libraries
target_link_libraries(pico-bme688
        hardware_i2c
        )

pico_add_extra_outputs(pico-bme688)

