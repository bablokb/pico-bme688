// --------------------------------------------------------------------------
// Read BME688 sensor values with a Raspberry Pi Pico using the official Bosch-API
//
// Author: Bernhard Bablok
//
// https://github.com/bablokb/pico-bme688
// --------------------------------------------------------------------------

#include <stdio.h>
#include "bme68x_pico.h"
#include "bme68x.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

static uint8_t _bme68x_dev_addr = BME68X_I2C_ADDR_LOW;

// --------------------------------------------------------------------------
// delay function for pico
//

void pico_delay_us(uint32_t period, void *intf_ptr) {
  sleep_us(period);
}

// --------------------------------------------------------------------------
// I2C read function for pico
//

BME68X_INTF_RET_TYPE pico_i2c_read(uint8_t reg_addr, uint8_t *reg_data,
                                              uint32_t len, void *intf_ptr) {
  uint8_t dev_addr = *(uint8_t*)intf_ptr;
  return i2c_read_blocking(BME68X_PORT,dev_addr,reg_data,(size_t) len,true);  // true - finished with bus
}

// --------------------------------------------------------------------------
// I2C write function for pico
//

BME68X_INTF_RET_TYPE pico_i2c_write(uint8_t reg_addr, const uint8_t *reg_data,
                                                  uint32_t len, void *intf_ptr) {
  uint8_t dev_addr = *(uint8_t*)intf_ptr;
  return i2c_write_blocking(BME68X_PORT,dev_addr,reg_data,(size_t)len,true);
}

// --------------------------------------------------------------------------
// Initialize I2C-interface of pico and configure device-struct
//

int8_t bme68x_interface_init(struct bme68x_dev *bme) {
  int8_t rslt = BME68X_OK;
  if (bme) {
     // I2C Initialisation. Using it at 400Khz.
    i2c_init(BME68X_PORT,400*1000);
    gpio_set_function(BME68X_SDA,GPIO_FUNC_I2C);
    gpio_set_function(BME68X_SCL,GPIO_FUNC_I2C);
    gpio_pull_up(BME68X_SDA);
    gpio_pull_up(BME68X_SCL);

    // device-structure init
    bme->read     = pico_i2c_read;
    bme->write    = pico_i2c_write;
    bme->intf     = BME68X_I2C_INTF;
    bme->delay_us = pico_delay_us;
    bme->intf_ptr = &_bme68x_dev_addr;
    bme->amb_temp = 20;              // initial ambient temperature in deg C
  } else {
    rslt = BME68X_E_NULL_PTR;
  }
  return rslt;
}

// --------------------------------------------------------------------------
// print API-result
//

void bme68x_print_result(const char api_name[], int8_t rslt) {
  switch (rslt) {
  case BME68X_OK:      /* Do nothing */
    break;
  case BME68X_E_NULL_PTR:
    printf("API name [%s]  Error [%d] : Null pointer\r\n", api_name, rslt);
    break;
  case BME68X_E_COM_FAIL:
    printf("API name [%s]  Error [%d] : Communication failure\r\n", api_name, rslt);
    break;
  case BME68X_E_INVALID_LENGTH:
    printf("API name [%s]  Error [%d] : Incorrect length parameter\r\n", api_name, rslt);
    break;
  case BME68X_E_DEV_NOT_FOUND:
    printf("API name [%s]  Error [%d] : Device not found\r\n", api_name, rslt);
    break;
  case BME68X_E_SELF_TEST:
    printf("API name [%s]  Error [%d] : Self test error\r\n", api_name, rslt);
    break;
  case BME68X_W_NO_NEW_DATA:
    printf("API name [%s]  Warning [%d] : No new data found\r\n", api_name, rslt);
    break;
  default:
    printf("API name [%s]  Error [%d] : Unknown error code\r\n", api_name, rslt);
    break;
  }
}

