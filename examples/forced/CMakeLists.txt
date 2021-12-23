## --------------------------------------------------------------------------
## Read BME688 sensor values with a Raspberry Pi Pico using the official Bosch-API
##
## example/forced: Read sensor in forced-mode
##
## Author: Bernhard Bablok
##
## https://github.com/bablokb/pico-bme688
## --------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.0)

project(forced)

# program configuration
add_compile_definitions(HEATER_TEMP=300)
add_compile_definitions(HEATER_DURATION=100)
add_compile_definitions(UPDATE_INTERVAL=10)


add_executable(${PROJECT_NAME} forced_mode.c)

pico_set_program_name(${PROJECT_NAME} "pico-bme688-forced")
pico_set_program_version(${PROJECT_NAME} "0.1")

pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_enable_stdio_usb(${PROJECT_NAME} 0)

# add libraries
target_link_libraries(${PROJECT_NAME} PUBLIC pico_stdlib)
target_link_libraries(${PROJECT_NAME} PUBLIC bme68x)
target_link_libraries(${PROJECT_NAME} PUBLIC hardware_i2c)

pico_add_extra_outputs(${PROJECT_NAME})
