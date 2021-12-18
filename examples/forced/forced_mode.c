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
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "bme68x_platform.h"

/***********************************************************************/
/*                         Macros                                      */
/***********************************************************************/

/* Macro for count of samples to be displayed */
#define SAMPLE_COUNT  UINT16_C(300)

/***********************************************************************/
/*                         Test code                                   */
/***********************************************************************/

int main(void)
{
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

    rslt = platform_interface_init(&bme);
    bme68x_print_result("bme68x_interface_init", rslt);

    rslt = bme68x_init(&bme);
    bme68x_print_result("bme68x_init", rslt);

    /* Check if rslt == BME68X_OK, report or handle if otherwise */
    conf.filter = BME68X_FILTER_OFF;
    conf.odr = BME68X_ODR_NONE;
    conf.os_hum = BME68X_OS_16X;
    conf.os_pres = BME68X_OS_1X;
    conf.os_temp = BME68X_OS_2X;
    rslt = bme68x_set_conf(&conf, &bme);
    bme68x_print_result("bme68x_set_conf", rslt);

    /* Check if rslt == BME68X_OK, report or handle if otherwise */
    heatr_conf.enable = BME68X_ENABLE;
    heatr_conf.heatr_temp = HEATER_TEMP;
    heatr_conf.heatr_dur = HEATER_DURATION;
    rslt = bme68x_set_heatr_conf(BME68X_FORCED_MODE, &heatr_conf, &bme);
    bme68x_print_result("bme68x_set_heatr_conf", rslt);

    printf("Sample, TimeStamp(ms), Temperature(deg C), Pressure(Pa), Humidity(%%), Gas resistance(ohm), Status\n");

    while (sample_count <= SAMPLE_COUNT)
    {
        rslt = bme68x_set_op_mode(BME68X_FORCED_MODE, &bme);
        bme68x_print_result("bme68x_set_op_mode", rslt);

        /* Calculate delay period in microseconds */
        del_period = bme68x_get_meas_dur(BME68X_FORCED_MODE, &conf, &bme) + (heatr_conf.heatr_dur * 1000);
        bme.delay_us(del_period, bme.intf_ptr);

        time_ms = to_ms_since_boot(get_absolute_time());

        /* Check if rslt == BME68X_OK, report or handle if otherwise */
        rslt = bme68x_get_data(BME68X_FORCED_MODE, &data, &n_fields, &bme);
        bme68x_print_result("bme68x_get_data", rslt);

        if (n_fields)
        {
#ifdef BME68X_USE_FPU
            printf("%u, %lu, %.2f, %.2f, %.2f, %.2f, 0x%x\n",
                   sample_count,
                   (long unsigned int)time_ms,
                   data.temperature,
                   data.pressure,
                   data.humidity,
                   data.gas_resistance,
                   data.status);
#else
            printf("%u, %lu, %d, %lu, %lu, %lu, 0x%x\n",
                   sample_count,
                   (long unsigned int)time_ms,
                   (data.temperature / 100),
                   (long unsigned int)data.pressure,
                   (long unsigned int)(data.humidity / 1000),
                   (long unsigned int)data.gas_resistance,
                   data.status);
#endif
            sample_count++;
        }
    }
    return rslt;
}
