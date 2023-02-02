#include <avr/io.h>
#include <avr/pgmspace.h>
#include <math.h>
#include <util/delay.h>

#include "lib_extram.hpp"
#include "lib_sort.hpp"
#include "lib_time.hpp"
#include "lib_usart.hpp"

// random list to sort
const uint8_t LIST[] PROGMEM = {159, 29, 41, 97, 74, 16, 80, 115, 126, 36, 167, 134, 53, 209, 138, 40, 63, 171, 23, 121, 123, 65, 87, 212, 247, 255, 236, 94, 217, 11, 184, 156, 170, 46, 179, 109, 92, 145, 117, 143, 20, 15, 208, 4, 91, 191, 38, 26, 172, 175, 79, 52, 72, 164, 193, 144, 55, 249, 149, 187, 47, 56, 48, 137, 150, 54, 58, 155, 30, 194, 141, 151, 108, 230, 203, 78, 1, 239, 213, 210, 152, 206, 113, 207, 248, 232, 154, 223, 240, 253, 195, 225, 231, 119, 12, 219, 44, 129, 100, 75, 118, 25, 146, 174, 86, 198, 133, 66, 111, 162, 122, 178, 188, 147, 189, 8, 204, 50, 34, 37, 114, 183, 104, 68, 105, 116, 160, 9, 242, 233, 177, 95, 61, 235, 131, 60, 224, 73, 89, 99, 125, 237, 57, 153, 251, 142, 241, 124, 49, 7, 90, 67, 32, 3, 214, 196, 14, 140, 5, 28, 77, 19, 88, 238, 245, 45, 107, 130, 220, 181, 200, 216, 190, 33, 24, 83, 69, 71, 246, 168, 226, 96, 165, 51, 148, 35, 211, 173, 222, 215, 2, 161, 227, 42, 229, 110, 199, 103, 169, 202, 127, 31, 6, 136, 13, 205, 176, 243, 82, 252, 120, 185, 112, 22, 180, 85, 228, 192, 102, 98, 64, 59, 106, 27, 186, 17, 76, 21, 197, 163, 84, 221, 158, 182, 62, 0, 166, 10, 234, 18, 244, 93, 201, 157, 39, 254, 132, 250, 101, 70, 139, 218, 43, 128, 81, 135};

int main(void) {
    // initialize usart
    usart_setup();

    // initialize extram
    extram_setup();

    // initialize timer
    timer_setup();
    uint32_t t;

    ////////////////* INTERNAL RAM *////////////////
    serprint("INTERNAL RAM\n\r");

    // initialize list for sorting
    uint8_t list[256];
    for (uint16_t i = 0; i < 256; i++) {
        list[i] = pgm_read_word(LIST + i);
    }

    // sort
    timer_reset();
    sort_bubble_uint8(list, 256);
    t = timer_getms();
    serprintuint32(t);
    serprint(" ms\n\r");

    // print list
    // for (uint16_t i = 0; i < 256; i++) {
    //    serprintuint8(list[i]);
    //    serprint("\n\r");
    //}

    ////////////////* EXTERNAL RAM *////////////////
    serprint("EXTERNAL RAM\n\r");

    // initialize list for sorting
    uint16_t addr = 0;
    for (uint16_t i = 0; i < 256; i++) {
        extram_write(addr + i, pgm_read_word(LIST + i));
    }

    // sort
    timer_reset();
    sort_bubble_extram_uint8(addr, 256);
    t = timer_getms();
    serprintuint32(t);
    serprint(" ms\n\r");

    // print list
    // for (uint16_t i = 0; i < 256; i++) {
    //    serprintuint8(extram_read(addr + i));
    //    serprint("\n\r");
    //}

    // endless loop
    while (1) {
    };
}
