#include <avr/io.h>
#include <util/delay.h>

#include "extram.hpp"
#include "usart.hpp"

int main(void) {
    // initialize usart
    setup_usart();

    // initialize shifting register
    setup_extram();

    // number of Bytes
    uint16_t N = (1 << 8);

    // write SRAM
    serprint("WRITING...\n\r");
    uint8_t data_write = 0;
    for (uint16_t addr = 0; addr < N; addr++) {
        // write
        extram_write(addr, data_write);

        // increase data
        data_write++;
    }
    serprint("WRITING FINISHED!\n\r\n\r");

    // read SRAM again
    serprint("READING...\n\r");
    data_write = 0;
    for (uint16_t addr = 0; addr < N; addr++) {
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
