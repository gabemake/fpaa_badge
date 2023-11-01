# FPAA Badge ESP32-S3 code

This code is based on a bunch of examples from the ESP-IDF github repo. 

file_server example is used to manage the web interface.
sdmmc is used to manage the file storage on the SD card (FAT FS for PC compatibility)
A highly modified spi_master LCD master example is used for the FPAA programming interface
I2S is used for the DAC.

### Status
- Wifi works with default SSID/IP, no configuration yet
- webserver is running with basic file management
- SPI writes can be sent with Program button on web page
- I2S initializes, but no file playback yet
- SD Card not working yet (need breakout board for dev kit)
- Internal SPI flash being used for web server
- platformio.ini locked to my serial port name, since my mac is picky

### TODO

in no particular order...

- add SD card and spi flash support
- add Wifi customization/configuration
- add SD card wifi configuration
- add background task for .wav playback
- add osc_wav page for text/drawing .wav "rendering"
- add basic RGB LED support
- test FPAA configuration
- add ace.js for file editing
- add RGB LED dynamic lighting for port enables, etc.
- add fun LED patterns
- add I2C to badge
- add button functionality (play/pause DAC?)