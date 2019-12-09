#ifndef _SH1106_H_
#define _SH1106_H_

/*
    SH1106 OLED I2C display driver for ESP32 ESP-IDF.
*/

#define SH1106_DEFAULT_ADDR 0x3C      // default I2C address
#define SH1106_DEFAULT_PORT I2C_NUM_0 // default I2C interface port

/*
    Main SH1106 display struct type. Stores all state for the display including
    page buffers.
*/
typedef struct {
    uint8_t addr;           // I2C address
    i2c_port_t port;        // I2C interface port
    uint16_t changes;       // page change bit to optimize writes
    uint8_t pages[16][128]; // page buffer
} sh1106_t;

/*
    Initialize SH1106 display. This method requires the ".addr" and ".port"
    properties to be set on the sh1106_t struct before calling.
*/
void sh1106_init(sh1106_t *display);

/*
    Write a single page (by index) to the display device.
*/
void sh1106_write_page(sh1106_t *display, uint8_t page);

/*
    Update the display by writing all pages that have changed since the last
    update.
*/
void sh1106_update(sh1106_t *display);

/*
    Clear the page buffer, solid black (does not update display).
*/
void sh1106_clear(sh1106_t *display);

/*
    Fill the page buffer, solid white (does not update display).
*/
void sh1106_fill(sh1106_t *display);

/*
    Set pixel at "x", "y" to be on/off based on "s" (does not update display).
*/
void sh1106_set(sh1106_t *display, uint8_t x, uint8_t y, bool s);

/*
    Return the state of pixel at "x", "y" (from page buffer).
*/
bool sh1106_get(sh1106_t *display, uint8_t x, uint8_t y);

#endif
