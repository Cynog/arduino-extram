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

    // endless main loop
    while (1) {
        // print info
        serprint("EXTRAM FILLS WITH DIFFERENT DATA TYPES\n\r");

        ////////////////////////////////* UNSIGNED 8-BIT INTEGERS *////////////////////////////////
        // write EXTRAM
        serprint("UNSIGNED INT 8-BIT\n\r");
        serprint("writing: ");
        uint8_t val_uint8 = 0;
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(uint8_t)) {
            extram_write<uint8_t>(val_uint8, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(uint8_t)) {
            extram_read<uint8_t>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        ////////////////////////////////* UNSIGNED 16-BIT INTEGERS *////////////////////////////////
        // write EXTRAM
        serprint("\n\rUNSIGNED INT 16-BIT\n\r");
        serprint("writing: ");
        uint16_t val_uint16 = 0;
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(uint16_t)) {
            extram_write<uint16_t>(val_uint16, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(uint16_t)) {
            extram_read<uint16_t>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        ////////////////////////////////* UNSIGNED 32-BIT INTEGERS *////////////////////////////////
        // write EXTRAM
        serprint("\n\rUNSIGNED INT 32-BIT\n\r");
        serprint("writing: ");
        uint32_t val_uint32 = 0;
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(uint32_t)) {
            extram_write<uint32_t>(val_uint32, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(uint32_t)) {
            extram_read<uint32_t>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        ////////////////////////////////* UNSIGNED 64-BIT INTEGERS *////////////////////////////////
        // write EXTRAM
        serprint("\n\rUNSIGNED INT 64-BIT\n\r");
        serprint("writing: ");
        uint64_t val_uint64 = 0;
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(uint64_t)) {
            extram_write<uint64_t>(val_uint64, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(uint64_t)) {
            extram_read<uint64_t>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        ////////////////////////////////* FLOAT *////////////////////////////////
        // write EXTRAM
        serprint("\n\rFLOAT\n\r");
        serprint("writing: ");
        float val_float = M_PI;
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(float)) {
            extram_write<float>(val_float, addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        // read EXTRAM
        serprint("reading: ");
        timer_reset();
        for (uint16_t addr = 0; addr < EXTRAM_SIZE; addr += sizeof(float)) {
            extram_read<float>(addr);
        }
        t = timer_getms();
        serprintuint32(t);
        serprint(" ms (");
        serprintfloat(EXTRAM_SIZE / (float)t * 1000.0, 0, 0);
        serprint(" byte/s)\n\r");

        // wait for user to run test again
        serprint("\n\r\n\r\n\r");
        wait_key_remind("TEST FINISHED. PRESS ANY KEY TO RUN IT AGAIN.\n\r", 5000);
        serprint("\n\r");
    }
}