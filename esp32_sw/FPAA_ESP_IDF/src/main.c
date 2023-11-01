#include "driver/gpio.h"
#include "sdkconfig.h"
#include "driver/uart.h"
#include "fpaa_esp_config.h"
#include "fpaa_spi.h"
#include "file_server.h"
#include "i2s_dac.h"
#include "sdcard.h"
#include "wifi.h"
#define BUF_SIZE (1024)



// handles
i2s_chan_handle_t i2s_handle;
spi_device_handle_t spi;

void init_uart() {
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    //uart_set_pin(UART_NUM_0, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);
    uart_set_pin(UART_NUM_0,UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
}


void app_main()
{

    const char* base_path = "/data";
    //init uart
    init_uart();
    printf("\nUART Logging started! (if you can see this)\n");

    // configure SD card
    printf("Setting up SD card (and LittleFS)\n");
    nvs_flash_init();
    mount_storage(base_path);

    //configure SPI interface
    printf("Setting up SPI\n");
    init_spi(&spi);

    //configure I2S peripheral
    printf("Setting up I2S (for DAC)\n");
    i2s_setup(&i2s_handle);

    //start WiFi
    printf("Starting WiFi AP\n");
    wifi_init_softap();

    //start webserver
    printf("Starting webserver\n");
    start_file_server(base_path, spi);


}
