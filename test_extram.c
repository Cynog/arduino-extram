#include <avr/io.h>
#include <util/delay.h>

#include "extram.h"
#include "usart.h"

int main(void) {
    // initialize usart
    setup_usart();

    // initialize shifting register
    setup_extram();

    // test shifting register
    // uint16_t addr = 54932;
    // send_addr_to_sr(addr);

    // test external RAM test is bad
    /**uint8_t data_write = 0;
    for (uint16_t addr = 0; addr < (1 << 13); addr++) {
        // write
        extram_write(addr, data_write);

        // read again
        uint8_t data_read = extram_read(addr);
        serprint("write: ");
        serprintuint8(data_write);
        serprint("   read: ");
        serprintuint8(data_read);
        serprint("\n\r");

        // increase data
        data_write++;

        // delay for better readability
        _delay_ms(10.0);
    }**/

    // write whole sram
    /**uint8_t data_write = 0;
    for (uint16_t addr = 0; addr < (1 << 4); addr++) {
        // write
        write_extram(addr, data_write);
        _delay_ms(20.0);

        // increase data
        data_write++;
    }

    // read whole sram again
    data_write = 0;
    for (uint16_t addr = 0; addr < (1 << 4); addr++) {
        // read
        uint8_t data_read = read_extram(addr);
        _delay_ms(20.0);

        // compare
        if (data_read != data_write) {
            serprint("ERROR! for addr ");
            serprintuint16(addr);
            serprint("\n\r");
        }

        // increase data
        data_write++;
    }**/

    uint8_t data;
    extram_write(10, 10);
    extram_write(20, 20);
    extram_write(30, 30);
    extram_write(40, 40);

    extram_write(0, 3);

    data = extram_read(10);
    serprintuint8(data);
    serprint("\n\r");

    data = extram_read(20);
    serprintuint8(data);
    serprint("\n\r");

    data = extram_read(30);
    serprintuint8(data);
    serprint("\n\r");
    
    data = extram_read(40);
    serprintuint8(data);
    serprint("\n\r");

    // endless loop
    while (1) {
    };
}
