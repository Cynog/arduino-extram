#include <avr/pgmspace.h>

#include "lib_extram.hpp"
#include "lib_sort.hpp"
#include "lib_timer.hpp"
#include "lib_usart.hpp"

// random list to sort
const uint16_t LIST[] PROGMEM = {46443, 26043, 850, 25342, 64067, 14864, 863, 15322, 2585, 57283, 50519, 27570, 48475, 9053, 47486, 56574, 47465, 7713, 33987, 33788, 3868, 62189, 2615, 60740, 16945, 10604, 50182, 45876, 52414, 14605, 25844, 6866, 14872, 526, 16128, 17128, 3059, 20675, 13370, 29870, 42504, 38426, 65417, 34007, 37326, 18238, 3002, 21892, 37246, 43826, 34009, 54072, 42709, 27371, 25223, 40241, 25005, 2895, 13385, 40256, 39491, 43451, 35510, 51918, 35340, 40943, 17218, 24558, 14078, 23850, 39226, 53995, 27069, 28219, 23853, 57224, 30024, 12420, 31633, 53344, 7281, 51025, 20164, 19744, 49146, 22972, 11, 38213, 35500, 51228, 20718, 49542, 27184, 50825, 3679, 43107, 23773, 28862, 3193, 6700, 41502, 55697, 63943, 35168, 3495, 988, 37149, 60372, 24739, 46748, 13745, 17432, 60654, 31812, 778, 23925, 19624, 62327, 60964, 38329, 3852, 60547, 46779, 10877, 57647, 45399, 9164, 30624, 50018, 882, 64078, 40175, 20511, 30283, 60085, 36565, 30962, 44498, 17742, 6435, 6727, 21527, 7932, 30365, 64673, 27559, 9038, 41778, 14419, 1277, 20259, 38199, 12535, 57740, 51013, 46446, 55892, 39830, 41968, 9496, 29558, 64486, 4839, 28258, 43647, 2380, 34492, 52415, 36811, 10487, 57769, 40120, 54025, 25812, 19088, 34869, 19239, 40164, 44630, 64938, 60112, 17405, 18618, 45221, 2891, 638, 11359, 46793, 46346, 23321, 53977, 58631, 60196, 22990, 40757, 28576, 57857, 60134, 19131, 59953, 56193, 63220, 25316, 43496, 30644, 33766, 57639, 16665, 37566, 22944, 21539, 25886, 24222, 60803, 59585, 45963, 37147, 60208, 36903, 11171, 12447, 34344, 17308, 8912, 43179, 59285, 28143, 42232, 64902, 6952, 60378, 31730, 40453, 15709, 59067, 39684, 38503, 4063, 46184, 12548, 21785, 16739, 25160, 48414, 29989, 51370, 28597, 49491, 4831, 21687, 2101, 63901, 5105, 55788, 37647, 11362};

int main(void) {
    // initialize usart
    usart_setup();

    // initialize extram
    extram_setup();

    // initialize timer
    timer_setup();
    uint32_t t;

    // number of values
    uint16_t n = 256;

    // endless main loop
    while (1) {
        ////////////////* INTERNAL RAM *////////////////
        serprint("INTERNAL RAM\n\r");

        // initialize list for sorting
        uint16_t list[n];
        for (uint16_t i = 0; i < n; i++) {
            list[i] = pgm_read_word(LIST + i);
        }

        // sort
        timer_reset();
        sort_bubble<uint16_t>(list, n);
        t = timer_getms();

        // print sorted list
        serprint("sorted list:\n\r");
        for (uint16_t i = 0; i < n; i++) {
            serprintuint16(list[i]);
            serprint("   ");

            if ((i + 1) % 16 == 0)
                serprint("\n\r");
        }
        serprint("\n\r");

        // print time
        serprint("elapsed time: ");
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////* INTERNAL RAM CHUNKS*////////////////
        serprint("\n\r\n\rINTERNAL RAM CHUNKS\n\r");

        // initialize list for sorting
        for (uint16_t i = 0; i < n; i++) {
            list[i] = pgm_read_word(LIST + i);
        }

        // sort
        uint16_t list_sorted[n];
        uint8_t n_chunks = 16;
        timer_reset();
        sort_bubble_chunks<uint16_t>(list, n, n_chunks, list_sorted);
        t = timer_getms();

        // print sorted list
        serprint("sorted list:\n\r");
        for (uint16_t i = 0; i < n; i++) {
            serprintuint16(list_sorted[i]);
            serprint("   ");

            if ((i + 1) % 16 == 0)
                serprint("\n\r");
        }
        serprint("\n\r");

        // print time
        serprint("elapsed time: ");
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////* EXTERNAL RAM *////////////////
        serprint("\n\r\n\rEXTERNAL RAM\n\r");

        // initialize list for sorting
        uint16_t addr = 0;
        for (uint16_t i = 0; i < n; i++) {
            uint16_t tmp = pgm_read_word(LIST + i);
            extram_write<uint16_t>(tmp, addr, i);
        }

        // sort
        timer_reset();
        sort_bubble_extram<uint16_t>(addr, n);
        t = timer_getms();

        // print sorted list
        serprint("sorted list:\n\r");
        for (uint16_t i = 0; i < n; i++) {
            serprintuint16(extram_read<uint16_t>(addr, i));
            serprint("   ");

            if ((i + 1) % 16 == 0)
                serprint("\n\r");
        }
        serprint("\n\r");

        // print time
        serprint("elapsed time: ");
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////* EXTERNAL RAM EXTERNAL CHUNKS *////////////////
        serprint("\n\r\n\rEXTERNAL RAM EXTERNAL CHUNKS\n\r");

        // initialize list for sorting
        for (uint16_t i = 0; i < n; i++) {
            uint16_t tmp = pgm_read_word(LIST + i);
            extram_write<uint16_t>(tmp, addr, i);
        }

        // sort
        uint16_t addr_sorted = addr + n * sizeof(uint16_t);
        timer_reset();
        sort_bubble_extram_chunks<uint16_t>(addr, n, n_chunks, addr_sorted, false);
        t = timer_getms();

        // print sorted list
        serprint("sorted list:\n\r");
        for (uint16_t i = 0; i < n; i++) {
            serprintuint16(extram_read<uint16_t>(addr_sorted, i));
            serprint("   ");

            if ((i + 1) % 16 == 0)
                serprint("\n\r");
        }
        serprint("\n\r");

        // print time
        serprint("elapsed time: ");
        serprintuint32(t);
        serprint(" ms\n\r");

        ////////////////* EXTERNAL RAM INTERNAL CHUNKS *////////////////
        serprint("\n\r\n\rEXTERNAL RAM INTERNAL CHUNKS\n\r");

        // initialize list for sorting
        for (uint16_t i = 0; i < n; i++) {
            uint16_t tmp = pgm_read_word(LIST + i);
            extram_write<uint16_t>(tmp, addr, i);
        }

        // sort
        timer_reset();
        sort_bubble_extram_chunks<uint16_t>(addr, n, n_chunks, addr_sorted);
        t = timer_getms();

        // print sorted list
        serprint("sorted list:\n\r");
        for (uint16_t i = 0; i < n; i++) {
            serprintuint16(extram_read<uint16_t>(addr_sorted, i));
            serprint("   ");

            if ((i + 1) % 16 == 0)
                serprint("\n\r");
        }
        serprint("\n\r");

        // print time
        serprint("elapsed time: ");
        serprintuint32(t);
        serprint(" ms\n\r");

        // wait for user to run test again
        serprint("\n\r\n\r\n\r");
        wait_key_remind("TEST FINISHED. PRESS ANY KEY TO RUN IT AGAIN.\n\r", 5000);
        serprint("\n\r");
    }
}
