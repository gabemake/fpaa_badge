#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_mac.h"
#include "esp_chip_info.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/i2s_std.h"
#include "driver/sdmmc_host.h"
#include "esp_spiffs.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"
#include "fpaa_esp_config.h"
#include "esp_err.h"
#include "soc/soc_caps.h"
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "driver/sdmmc_host.h"

esp_err_t mount_storage(const char *base_path);
