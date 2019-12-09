/*
    Draw a Sierpinski triangle on the display using bitwise AND operation.
*/

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "sh1106.h"

#define SDA_PIN  GPIO_NUM_21
#define SCL_PIN  GPIO_NUM_22
#define I2C_ADDR SH1106_DEFAULT_ADDR
#define I2C_PORT SH1106_DEFAULT_PORT

/*
    Initialize I2C driver.
*/
void init_i2c() {
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 1000000
    };
    i2c_param_config(I2C_PORT, &i2c_config);
    i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0);
}

void app_main() {
    init_i2c();
    // setup sh1106 display
    sh1106_t display;
    display.addr = I2C_ADDR;
    display.port = I2C_PORT;
    sh1106_init(&display);
    // draw triangle
    for (uint8_t y = 0; y < 128; y++) {
        for (uint8_t x = 0; x < 128; x++) {
            sh1106_set(&display, x, y, (x & y) == 0);
        }
    }
    // update display
    sh1106_update(&display);
}
