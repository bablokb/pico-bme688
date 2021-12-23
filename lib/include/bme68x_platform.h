// --------------------------------------------------------------------------
// Read BME688 sensor values with a Raspberry Pi Pico using the official Bosch-API
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pico-bme688
// --------------------------------------------------------------------------

#ifndef _BME68X_PLATFORM_H
#define _BME68X_PLATFORM_H

#include <bme68x.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#define platform_sleep_ms(x) sleep_ms(x)
uint32_t platform_get_timestamp();
void platform_delay_us(uint32_t period, void *intf_ptr);

BME68X_INTF_RET_TYPE platform_i2c_read(uint8_t reg_addr, uint8_t *reg_data,
                                               uint32_t len, void *intf_ptr);
BME68X_INTF_RET_TYPE platform_i2c_write(uint8_t reg_addr,
                     const uint8_t *reg_data, uint32_t len, void *intf_ptr);

int8_t platform_interface_init(struct bme68x_dev *bme);
void bme68x_print_result(const char api_name[], int8_t rslt);

#endif
