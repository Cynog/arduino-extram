#include "extram.h"

void setup_extram(void) {
    // shifting register pins
    DDR_SER |= MASK_SER;
    DDR_SRCLK |= MASK_SRCLK;
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

uint8_t read_extram(uint16_t addr) {
}

uint8_t write_extram(uint16_t addr) {
}