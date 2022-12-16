#include <avr/io.h>
#include <util/delay.h>

#include "extram.h"
#include "usart.h"

int main(void) {
    // initialize usart
    setup_usart();

    // initialize shifting register
    setup_extram();

    // write whole sram
    serprint("WRITING...\n\r");
    uint8_t data_write = 0;
    for (uint16_t addr = 0; addr < (1 << 13); addr++) {
        // write
        extram_write(addr, data_write);

        // increase data
        data_write++;
    }
    serprint("WRITING FINISHED!\n\r\n\r");

    // read whole sram again
    serprint("READING...\n\r");
    data_write = 0;
    for (uint16_t addr = 0; addr < (1 << 13); addr++) {
        // read
        uint8_t data_read = extram_read(addr);

        // compare
        if (data_read != data_write) {
            serprint("ERROR! for addr ");
            serprintuint16(addr);
            serprint("\n\r");
        }

        // increase data
        data_write++;
    }
    serprint("READING FINISHED!\n\r");

    // endless loop
    while (1) {
    };
}
