#include "extram.h"

void setup_extram(void) {
    // shifting register pins
    DDRDATA |= MASKDATA;
    DDRCLK |= MASKCLK;
}

void send_addr_to_sr(uint16_t addr) {
    // send each bit starting from most significant
    for (uint16_t i = (1 << 15); i > 0; i >>= 1) {
        if (addr & i) {  // send 1
            PORTDATA |= MASKDATA;
        } else {  // send 0
            PORTDATA &= ~MASKDATA;
        }
        // read into shifting register
        PORTCLK |= MASKCLK;
        PORTCLK &= ~MASKCLK;
    }

    // required once again for refreshing the output
    PORTCLK |= MASKCLK;
    PORTCLK &= ~MASKCLK;
}

uint8_t read_extram(uint16_t addr) {
}

uint8_t write_extram(uint16_t addr) {
}