#include "extram.h"

void setup_extram(void) {
    // shifting register pins
    DDR_SER |= MASK_SER;
    DDR_SRCLK |= MASK_SRCLK;

    // external ram pins
    DDR_OE |= MASK_OE;
    PORT_OE |= MASK_OE;

    DDR_WE |= MASK_WE;
    PORT_WE |= MASK_WE;

    // DDR_CS1 |= MASK_CS1;
    // PORT_CS1 |= MASK_CS1;
}

void send_addr_to_sr(uint16_t addr) {
    // send each bit starting from most significant
    for (uint16_t i = (1 << 15); i > 0; i >>= 1) {
        if (addr & i)  // send 1
            PORT_SER |= MASK_SER;
        else  // send 0
            PORT_SER &= ~MASK_SER;
        // read into shifting register
        PORT_SRCLK |= MASK_SRCLK;
        PORT_SRCLK &= ~MASK_SRCLK;
    }

    // required once again for refreshing the output
    PORT_SRCLK |= MASK_SRCLK;
    PORT_SRCLK &= ~MASK_SRCLK;
}

uint8_t extram_read(uint16_t addr) {
    // send address to shifting register
    send_addr_to_sr(addr);
    _delay_ms(10.0);

    // set IO pins to input with pullup
    DDR_IO0 &= ~MASK_IO0;
    PORT_IO0 |= MASK_IO0;
    DDR_IO1 &= ~MASK_IO1;
    PORT_IO1 |= MASK_IO1;
    _delay_ms(10.0);

    // set OE to LOW
    PORT_OE &= ~MASK_OE;
    _delay_ms(10.0);

    // read from RAM
    uint8_t data = PIN_IO0 & MASK_IO0;
    data |= PIN_IO1 & MASK_IO1;
    _delay_ms(10.0);

    // set OE back to HIGH
    PORT_OE |= MASK_OE;
    _delay_ms(10.0);

    // return
    return data;
}

void extram_write(uint16_t addr, uint8_t data) {
    // send address to shifting register
    send_addr_to_sr(addr);
    _delay_ms(10.0);

    // set IO pins to output
    DDR_IO0 |= MASK_IO0;
    DDR_IO1 |= MASK_IO1;
    _delay_ms(10.0);

    // set IO pins
    PORT_IO0 &= ~MASK_IO0;
    PORT_IO0 |= data & MASK_IO0;
    PORT_IO1 &= ~MASK_IO1;
    PORT_IO1 |= data & MASK_IO1;
    _delay_ms(10.0);

    // give LOW pulse on WE
    PORT_WE &= ~MASK_WE;
    _delay_ms(10.0);
    PORT_WE |= MASK_WE;
    _delay_ms(10.0);

    // return
    return;
}