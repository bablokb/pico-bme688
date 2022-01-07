## --------------------------------------------------------------------------
## Read BME688 sensor values with a Raspberry Pi Pico using the official Bosch-API
##
## example/parallel: Read sensor in parallel-mode
##
## Author: Bernhard Bablok
##
## https://github.com/bablokb/pico-bme688
## --------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.0)

project(parallel)

# program configuration
add_compile_definitions(HEATER_TEMP_PROFILE=320,100,100,100,200,200,200,320,320,320)
#add_compile_definitions(HEATER_DUR_PROFILE=5,2,10,30,5,5,5,5,5,5)
add_compile_definitions(HEATER_DUR_PROFILE=1,2,3,4,5,6,7,8,9,10)
add_compile_definitions(UPDATE_INTERVAL=10)
add_compile_definitions(WITH_UNITS)

add_executable(${PROJECT_NAME} parallel_mode.c)

pico_set_program_name(${PROJECT_NAME} "pico-bme688-parallel")
pico_set_program_version(${PROJECT_NAME} "0.1")

pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 0)

# add libraries
target_link_libraries(${PROJECT_NAME} PUBLIC pico_stdlib)
target_link_libraries(${PROJECT_NAME} PUBLIC bme68x)
target_link_libraries(${PROJECT_NAME} PUBLIC hardware_i2c)

pico_add_extra_outputs(${PROJECT_NAME})
