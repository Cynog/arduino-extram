#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#include "extram.h"
#include "usart.h"

int main(void) {
    // initialize usart
    setup_usart();

    // initialize shifting register
    setup_extram();

    // test shifting register
    uint16_t addr = 54932;
    send_addr_to_sr(addr);

    // endless loop
    while (1) {
    };
}
