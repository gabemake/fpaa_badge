#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "fpaa_esp_config.h"

esp_err_t init_spi(spi_device_handle_t* spi);

esp_err_t program_fpaa(spi_device_handle_t spi, char* filepath);