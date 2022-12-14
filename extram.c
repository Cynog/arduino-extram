#include "extram.h"

void setup_extram(void) {
}

void send_addr_to_sr(uint16_t addr) {
    for (uint16_t i = (1<<15); i > 0; i >>= 1) {
        if (addr & i) {
            PORTDATA |= MASKDATA;
            serprint("1");
        } else {
            PORTDATA &= ~MASKDATA;
            serprint("0");
        }
        PORTCLK |= MASKCLK;
        PORTCLK &= ~MASKCLK;
    }

    PORTCLK |= MASKCLK;
    PORTCLK &= ~MASKCLK;
    PORTCLK |= MASKCLK;
    PORTCLK &= ~MASKCLK;
}

uint8_t read_extram(uint16_t addr) {
}

uint8_t write_extram(uint16_t addr) {
}