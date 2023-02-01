#include "lib_extram.hpp"

void extram_setup(void) {
    // shifting register pins
    DDR_SER |= MASK_SER;
    DDR_SRCLK |= MASK_SRCLK;

    // external ram pins
    DDR_OE |= MASK_OE;
    PORT_OE |= MASK_OE;

    DDR_WE |= MASK_WE;
    PORT_WE |= MASK_WE;
}

void send_addr_to_sr(uint16_t addr) {
    // send each bit starting from most significant
    for (uint16_t i = (1 << ADDR_MSB); i > 0; i >>= 1) {
        if (addr & i)  // send 1
            PORT_SER |= MASK_SER;
        else  // send 0
            PORT_SER &= ~MASK_SER;
        
        // read into shifting register
        PORT_SRCLK |= MASK_SRCLK;
        PORT_SRCLK &= ~MASK_SRCLK;
    }
}

uint8_t extram_read(uint16_t addr) {
    // send address to shifting register
    send_addr_to_sr(addr);

    // set OE to LOW
    PORT_OE &= ~MASK_OE;

    // set IO pins to input with pullup
    DDR_IO0 &= ~MASK_IO0;
    PORT_IO0 |= MASK_IO0;
    DDR_IO1 &= ~MASK_IO1;
    PORT_IO1 |= MASK_IO1;

    // read from RAM
    uint8_t data = PIN_IO0 & MASK_IO0;
    data |= PIN_IO1 & MASK_IO1;

    // set OE back to HIGH
    PORT_OE |= MASK_OE;

    // return
    return data;
}

void extram_write(uint16_t addr, uint8_t data) {
    // send address to shifting register
    send_addr_to_sr(addr);

    // set IO pins to output
    DDR_IO0 |= MASK_IO0;
    DDR_IO1 |= MASK_IO1;

    // set IO pins
    PORT_IO0 &= ~MASK_IO0;
    PORT_IO0 |= data & MASK_IO0;
    PORT_IO1 &= ~MASK_IO1;
    PORT_IO1 |= data & MASK_IO1;

    // give LOW pulse on WE
    PORT_WE &= ~MASK_WE;
    PORT_WE |= MASK_WE;

    // return
    return;
}

float extram_read_float(uint16_t addr) {
    // variable to return
    float data;

    // pointer to read the single bytes
    uint8_t *ptr = (uint8_t *)&data;

    // read the float
    for (uint8_t i = 0; i < 4; i++) {
        ptr[i] = extram_read(addr);
        addr++;
    }

    // return
    return data;
}

void extram_write_float(uint16_t addr, float data) {
    // pointer to write single bytes
    uint8_t *ptr = (uint8_t *)&data;

    // write the float
    for (uint8_t i = 0; i < 4; i++) {
        extram_write(addr, ptr[i]);
        addr++;
    }

    // return
    return;
}