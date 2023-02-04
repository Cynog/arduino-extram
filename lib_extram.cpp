#include "lib_extram.hpp"

void extram_setup(void) {
    // shifting register pins
    DDR_ADDR012 |= MASK_ADDR012;
    DDR_SRCLK |= MASK_SRCLK;

    // external ram pins
    DDR_OE |= MASK_OE;
    PORT_OE |= MASK_OE;
    DDR_WE |= MASK_WE;
    PORT_WE |= MASK_WE;
}

void send_addr_to_sr(uint16_t addr) {
    // send each bit starting from most significant
    for (uint16_t i = (1 << ADDR_MSB); i >= (1 << (ADDR_SR_LSB - 1)); i >>= 1) {
        if (addr & i)  // send 1
            PORT_SER |= MASK_SER;
        else  // send 0
            PORT_SER &= ~MASK_SER;

        // read into shifting register
        PORT_SRCLK |= MASK_SRCLK;
        PORT_SRCLK &= ~MASK_SRCLK;
    }
}