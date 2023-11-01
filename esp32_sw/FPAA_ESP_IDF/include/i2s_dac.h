#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_mac.h"
#include "esp_chip_info.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "driver/i2s_std.h"
#include "fpaa_esp_config.h"

// defines
#define REBOOT_WAIT 5000            // reboot after 5 seconds
#define AUDIO_BUFFER 2048           // buffer size for reading the wav file and sending to i2s
#define WAV_FILE "/sdcard/test.wav" // wav file to play

esp_err_t i2s_setup(i2s_chan_handle_t * tx_handle);
esp_err_t play_wav(i2s_chan_handle_t * tx_handle, char *fp);
