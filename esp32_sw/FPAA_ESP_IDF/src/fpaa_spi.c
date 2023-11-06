
#include "esp_err.h"
#include "esp_log.h"

#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "fpaa_spi.h"

#define FILE_PATH_MAX (ESP_VFS_PATH_MAX + CONFIG_SPIFFS_OBJ_NAME_LEN)

static const char *TAG = "fpaa_spi";
//DRAM_ATTR static const uint8_t test_spi_bytes[4] = {0xDE, 0xAD, 0xBE, 0xEF };

esp_err_t init_spi(spi_device_handle_t * spi) {
    esp_err_t ret;
    spi_bus_config_t buscfg = {
        .miso_io_num = FPAA_SO_PIN,
        .mosi_io_num = FPAA_SI_PIN,
        .sclk_io_num = FPAA_SCLK_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = FPAA_PROG_MAX_BYTES * 8
    };
    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = FPAA_PROG_SCK_HZ,     //Clock out at 10 MHz
        .mode = 0,                              //SPI mode 0
        .spics_io_num = FPAA_CS1B_PIN,             //CS pin
        .queue_size = 6,                        //We want to be able to queue 7 transactions at a time
 //       .pre_cb = lcd_spi_pre_transfer_callback, // (none for now) Specify pre-transfer callback to handle D/C line
    };
    //Initialize the SPI bus
    ret = spi_bus_initialize(FPAA_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    //Attach the FPAA to the SPI bus
    ret = spi_bus_add_device(FPAA_HOST, &devcfg, spi);
    ESP_ERROR_CHECK(ret);

    return ESP_OK;
}


static void spi_prog_file(spi_device_handle_t spi, uint8_t *filedata, uint16_t filesize)
{
    esp_err_t ret;
    //Transaction descriptors. Declared static so they're not allocated on the stack; we need this memory even when this
    //function is finished because the SPI driver needs access to it even while we're already calculating the next line.
    static spi_transaction_t trans;

    //In theory, it's better to initialize trans and data only once and hang on to the initialized
    //variables. We allocate them on the stack, so we need to re-init them each call.
    memset(&trans, 0, sizeof(spi_transaction_t));
    
    trans.tx_buffer = filedata;   //send the file data
    trans.length = filesize * 8;  //Data length, in bits
    trans.flags = 0; //undo SPI_TRANS_USE_TXDATA flag

    //Queue all transactions. backgrounding so webserver is uninterrupted. jk just blocking instead
    ESP_LOGI(TAG, "Running blocking spi transaction");
    ret = spi_device_polling_transmit(spi, &trans);

    ESP_LOGI(TAG, "Completed blocking spi transaction");
    assert(ret == ESP_OK);
}


esp_err_t program_fpaa(spi_device_handle_t spi, char* filepath) {
    //wait for any previous transaction to clear out
    ESP_LOGI(TAG, "Waiting for ongoing SPI transactions");

    //spi_prog_finish(spi);
    //load file into DRAM
    FILE *fd = NULL;
    size_t fsize;
    size_t bytesread;



    ESP_LOGI(TAG, "Opening FPAA config file");
    fd = fopen(filepath, "r");
    if (!fd) {
        ESP_LOGE(TAG, "Failed to read FPAA config file : %s", filepath);
        return ESP_FAIL;
    }
    
    ESP_LOGI(TAG, "Getting FPAA config file size");
    fseek(fd, 0, SEEK_END); // seek to end of file
    fsize = ftell(fd); // get current file pointer
    fseek(fd, 0, SEEK_SET); // seek back to beginning of file
    // proceed with allocating memory and reading the file

    uint8_t * filedata;
    filedata = heap_caps_malloc(fsize, MALLOC_CAP_DMA);

    ESP_LOGI(TAG, "Reading FPAA config file into memory");
    bytesread = fread(filedata, 1, fsize, fd);

    //set up transaction and program file
    ESP_LOGI(TAG, "Sending FPAA config file to SPI");
    //set CS2b, since CS1b is being handled by the SPI controller
    gpio_set_level(FPAA_CS2B_PIN, 0);
    //write bytes
    spi_prog_file(spi, filedata, bytesread);
    //spi_prog_file(spi, test_spi_bytes,4);
    //remove chip select
    gpio_set_level(FPAA_CS2B_PIN, 1);
    free(filedata);
    return ESP_OK;
}