#define BADGE_ESP_WIFI_SSID      "FPAA Badge"
#define BADGE_ESP_WIFI_PASS      "security through obscurity"
#define BADGE_ESP_WIFI_CHANNEL   11
#define BADGE_MAX_STA_CONN       10

#define FPAA_HOST    SPI2_HOST

#define FPAA_SO_PIN 9
#define FPAA_SI_PIN 14
#define FPAA_SCLK_PIN 21
#define FPAA_CS1B_PIN 47

#define FPAA_RESETB_PIN 46
#define FPAA_MEMCLK_PIN 10
#define FPAA_ACTIVATE_PIN 11
#define FPAA_ERRB_PIN 12
#define FPAA_LCCB_PIN 13
#define FPAA_CS2B_PIN 48
#define FPAA_CFGFLG_PIN 45
#define FPAA_OUTPUT_PINS  ((1ULL<<FPAA_RESETB_PIN) | (1ULL<<FPAA_CS2B_PIN))
#define FPAA_HOLD_PINS  (1ULL<<FPAA_ERRB_PIN)

#define FPAA_PROG_MAX_BYTES 3204 // based on the only file I have
#define FPAA_PROG_SCK_HZ 10000000 // 10 MHz for now

// I2S Configuration
#define I2S_BLK_PIN 18
#define I2S_WS_PIN 41
#define I2S_DATA_OUT_PIN 40
#define I2S_DATA_IN_PIN I2S_GPIO_UNUSED
#define I2S_SCLK_PIN 8

//Storage config (comment for internal flash)
//#define USE_SD_CARD
#define USE_SDMMC_MODE

// SDMMC Configuration (default for ESP32-WROVER-E)
#define SDMMC_CMD_PIN 6
#define SDMMC_CLK_PIN 7
#define SDMMC_D0_PIN 15
#define SDMMC_D1_PIN 16
#define SDMMC_D2_PIN 4
#define SDMMC_D3_PIN 5