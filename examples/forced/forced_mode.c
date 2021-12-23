// --------------------------------------------------------------------------
// Read BME688 sensor values with a Raspberry Pi Pico using the official Bosch-API
//
// This is a slightly modified version of the Bosch version (examples/forced/forced_mode.c)
// distributed with https://github.com/BoschSensortec/BME68x-Sensor-API
//
// Adapted to run on the Raspberry Pi Pico
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pico-bme688
// --------------------------------------------------------------------------

/**
 * Copyright (C) 2021 Bosch Sensortec GmbH
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "bme68x_platform.h"

static float alt_fac;

// ---------------------------------------------------------------------------
// print sensor data to console

void print_data(uint32_t ts, struct bme68x_data *data) {
  float temp, press, hum;

  temp  = 0.01f  * data->temperature;
  press = 0.01f  * data->pressure/alt_fac;
  hum   = 0.001f * data->humidity;
  printf("%lu ms, %0.1f deg C, %0.0f hPa, %0.0f%%, %lu Ohm, 0x%x\n",
         1000*ts, temp, press, hum, data->gas_resistance,data->status);
}

// ---------------------------------------------------------------------------
// main loop: read data and print data

int main(void) {
  struct bme68x_dev bme;
  int8_t rslt;
  struct bme68x_conf conf;
  struct bme68x_heatr_conf heatr_conf;
  struct bme68x_data data;
  uint32_t del_period;
  uint32_t time_ms = 0;
  uint8_t n_fields;
  uint16_t sample_count = 1;

  stdio_init_all();
  alt_fac = pow(1.0-ALTITUDE_AT_LOC/44330.0, 5.255);

  rslt = platform_interface_init(&bme);
  bme68x_print_result("bme68x_interface_init", rslt);

  rslt = bme68x_init(&bme);
  bme68x_print_result("bme68x_init", rslt);

  conf.filter  = BME68X_FILTER_OFF;
  conf.odr     = BME68X_ODR_NONE;
  conf.os_hum  = BME68X_OS_16X;
  conf.os_pres = BME68X_OS_1X;
  conf.os_temp = BME68X_OS_2X;
  rslt = bme68x_set_conf(&conf, &bme);
  bme68x_print_result("bme68x_set_conf", rslt);

  heatr_conf.enable     = BME68X_ENABLE;
  heatr_conf.heatr_temp = HEATER_TEMP;
  heatr_conf.heatr_dur  = HEATER_DURATION;
  rslt = bme68x_set_heatr_conf(BME68X_FORCED_MODE, &heatr_conf, &bme);
  bme68x_print_result("bme68x_set_heatr_conf", rslt);

  printf("TimeStamp(ms), Temperature(deg C), Pressure(Pa), Humidity(%%), Gas resistance(ohm), Status\n");

  while (true) {
    rslt = bme68x_set_op_mode(BME68X_FORCED_MODE, &bme);
    bme68x_print_result("bme68x_set_op_mode", rslt);

    /* Calculate delay period in microseconds */
    del_period = bme68x_get_meas_dur(BME68X_FORCED_MODE, &conf, &bme) +
      (heatr_conf.heatr_dur * 1000);
    bme.delay_us(del_period, bme.intf_ptr);

    time_ms = platform_get_timestamp();

    rslt = bme68x_get_data(BME68X_FORCED_MODE, &data, &n_fields, &bme);
    bme68x_print_result("bme68x_get_data", rslt);

    if (n_fields) {
      print_data(time_ms,&data);
    }
    platform_sleep_ms(1000*UPDATE_INTERVAL);
  }
  return rslt;
}
