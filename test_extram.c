#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#include "extram.h"
#include "usart.h"

int main(void) {
    // initialize usart
    setup_usart();

    //* test shifting register
    DDRDATA |= MASKDATA;
    DDRCLK |= MASKCLK;

    uint16_t addr = 7921;
    send_addr_to_sr(addr);

    // endless loop
    while (1) {
    };
}
