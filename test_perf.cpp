#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#include "lib_extram.hpp"
#include "lib_timer.hpp"
#include "lib_usart.hpp"

int main(void) {
    // initialize usart
    usart_setup();

    // initialize extram
    extram_setup();

    // initialize timer
    timer_setup();
    uint32_t t;

    // number of addresses to write and read
    uint16_t n = 1024;

    // endless main loop
    while (1) {
        // print info
        serprint("EXTRAM ACCESSES WITH DIFFERENT DATA TYPES: ");
        serprintuint16(n);
        serprint(" EACH \n\r");

        ////////////////////////////////* UNSIGNED 8-BIT INTEGERS *////////////////////////////////
        // write EXTRAM
        serprint("\n\rUNSIGNED INT 8-BIT\n\r");
        serprint("writing: ");
        uint8_t val_uint8 = 0;
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(uint8_t); addr += sizeof(uint8_t)) {
            extram_write<uint8_t>(val_uint8, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(uint8_t); addr += sizeof(uint8_t)) {
            extram_read<uint8_t>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////////////////////* UNSIGNED 16-BIT INTEGERS *////////////////////////////////
        // write EXTRAM
        serprint("\n\rUNSIGNED INT 16-BIT\n\r");
        serprint("writing: ");
        uint16_t val_uint16 = 0;
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(uint16_t); addr += sizeof(uint16_t)) {
            extram_write<uint16_t>(val_uint16, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(uint16_t); addr += sizeof(uint16_t)) {
            extram_read<uint16_t>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////////////////////* UNSIGNED 32-BIT INTEGERS *////////////////////////////////
        // write EXTRAM
        serprint("\n\rUNSIGNED INT 32-BIT\n\r");
        serprint("writing: ");
        uint32_t val_uint32 = 0;
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(uint32_t); addr += sizeof(uint32_t)) {
            extram_write<uint32_t>(val_uint32, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(uint32_t); addr += sizeof(uint32_t)) {
            extram_read<uint32_t>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////////////////////* UNSIGNED 64-BIT INTEGERS *////////////////////////////////
        // write EXTRAM
        serprint("\n\rUNSIGNED INT 64-BIT\n\r");
        serprint("writing: ");
        uint64_t val_uint64 = 0;
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(uint64_t); addr += sizeof(uint64_t)) {
            extram_write<uint64_t>(val_uint64, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(uint64_t); addr += sizeof(uint64_t)) {
            extram_read<uint64_t>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////////////////////* FLOAT *////////////////////////////////
        // write EXTRAM
        serprint("\n\rFLOAT\n\r");
        serprint("writing: ");
        float val_float = M_PI;
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(float); addr += sizeof(float)) {
            extram_write<float>(val_float, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < n * sizeof(float); addr += sizeof(float)) {
            extram_read<float>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms\n\r");

        // wait for user to run test again
        serprint("\n\r\n\r\n\r");
        wait_key_remind("TEST FINISHED. PRESS ANY KEY TO RUN IT AGAIN.\n\r", 5000);
        serprint("\n\r");
    }
}