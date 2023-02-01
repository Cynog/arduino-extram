#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#include "lib_extram.hpp"
#include "lib_time.hpp"
#include "lib_usart.hpp"

int main(void) {
    // initialize usart
    usart_setup();

    // initialize shifting register
    extram_setup();

    // initialize timer
    timer_setup();
    uint32_t t;

    // 256 random addresses spread over the whole external RAM with gaps of at least 4
    uint16_t addrs[] = {5060, 6748, 7764, 4516, 4316, 8084, 5896, 236, 4640, 3420, 5992, 2480, 3852, 2756, 3392, 5476, 1248, 2012, 7532, 3900, 3128, 2032, 5808, 8152, 7000, 4156, 1472, 7688, 3100, 7232, 1664, 2076, 1780, 1040, 844, 3480, 7776, 2968, 2908, 7400, 1652, 272, 6736, 920, 6844, 6924, 6272, 4816, 3568, 1732, 6644, 1256, 1428, 6304, 4496, 1528, 432, 1052, 1208, 3332, 3432, 7124, 5224, 8108, 1900, 5156, 8072, 4672, 4748, 7864, 2024, 2436, 5220, 4280, 4980, 3628, 2404, 4364, 20, 3396, 1172, 420, 1488, 2660, 2704, 5452, 7092, 7212, 3812, 4060, 2572, 3272, 5708, 860, 8156, 5520, 2100, 7972, 4968, 4604, 1692, 5792, 8004, 5128, 2376, 4208, 4836, 56, 36, 1284, 1672, 4020, 4360, 5524, 5312, 3084, 5944, 4892, 1808, 8188, 5076, 3828, 6856, 6836, 3056, 112, 4064, 5064, 4008, 2948, 4224, 5624, 3816, 1300, 612, 928, 52, 3672, 1580, 5124, 4620, 5692, 3252, 4436, 1988, 3452, 4292, 5088, 1104, 7156, 7840, 6744, 584, 1504, 1936, 2648, 2452, 1028, 872, 7740, 3308, 6108, 5032, 6524, 5412, 7952, 5296, 6952, 2784, 6472, 1828, 2964, 5436, 1044, 3080, 1184, 2576, 940, 468, 6300, 7948, 7544, 6116, 5404, 7860, 3264, 3708, 1292, 8016, 8012, 2980, 7716, 6156, 192, 1896, 6656, 2920, 4520, 6452, 3148, 4188, 2484, 7508, 7796, 7568, 6612, 3368, 144, 2512, 5844, 6676, 1400, 5268, 4068, 2824, 804, 6432, 6600, 7428, 1524, 3312, 3904, 848, 4896, 7556, 2592, 2972, 5080, 6144, 1572, 716, 7932, 3288, 4960, 7036, 1688, 6816, 3600, 6044, 2424, 2632, 140, 836, 4872, 1848, 3436, 1128, 156, 8168, 5072, 3572, 7108, 5648, 4320, 216, 4964};

    ////////////////////////////////* UNSIGNED 8-BIT INTEGERS *////////////////////////////////
    // write SRAM
    serprint("UNSIGNED INT 8-BIT\n\r");
    serprint("WRITING... ");
    uint8_t val = 0;
    timer_reset();
    for (uint16_t i = 0; i < 256; i++) {
        // write
        extram_write(addrs[i], val);

        // next value
        val++;
    }
    t = timer_getms();
    serprint("FINISHED! ");
    serprintuint32(t);
    serprint(" ms\n\r");

    // read SRAM again
    serprint("READING... ");
    val = 0;
    timer_reset();
    for (uint16_t i = 0; i < 256; i++) {
        // read
        uint8_t read = extram_read(addrs[i]);

        // compare
        if (read != val) {
            serprint("ERROR ");
            serprintuint16(i);
            serprint(" ");
            break;
        }

        // next value
        val++;
    }
    t = timer_getms();
    serprint("FINISHED! ");
    serprintuint32(t);
    serprint(" ms\n\r");

    ////////////////////////////////* FLOAT *////////////////////////////////
    // write SRAM
    serprint("\n\r\n\rFLOAT\n\r");
    serprint("WRITING... ");
    float val_float = M_PI;
    timer_reset();
    for (uint16_t i = 0; i < 256; i++) {
        // write
        extram_write_float(addrs[i], val_float);

        // next value
        val_float += M_PI;
    }
    t = timer_getms();
    serprint("FINISHED! ");
    serprintuint32(t);
    serprint(" ms\n\r");

    // read SRAM again
    serprint("READING... ");
    val_float = M_PI;
    timer_reset();
    for (uint16_t i = 0; i < 256; i++) {
        // read
        float read = extram_read_float(addrs[i]);

        // compare
        if (read != val_float) {
            serprint("ERROR ");
            serprintuint16(i);
            serprint(" ");
            break;
        }

        // next value
        val_float += M_PI;
    }
    t = timer_getms();
    serprint("FINISHED! ");
    serprintuint32(t);
    serprint(" ms\n\r");

    // endless loop
    while (1) {
    };
}
