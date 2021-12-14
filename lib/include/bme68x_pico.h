// --------------------------------------------------------------------------
// Read BME688 sensor values with a Raspberry Pi Pico using the official Bosch-API
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pico-bme688
// --------------------------------------------------------------------------

#ifndef _BME68X_PICO_H
#define _USER_H

#include <bme68x.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

void pico_delay_us(uint32_t period, void *intf_ptr);
BME68X_INTF_RET_TYPE pico_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
BME68X_INTF_RET_TYPE pico_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);

int8_t bme68x_interface_init(struct bme68x_dev *bme);
void bme68x_print_result(const char api_name[], int8_t rslt);

#endif