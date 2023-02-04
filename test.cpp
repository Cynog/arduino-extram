#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#include "lib_extram.hpp"
#include "lib_usart.hpp"

int main(void) {
    // initialize usart
    usart_setup();

    // initialize extram
    extram_setup();

    // 256 random addresses spread over the whole external RAM with addrs[i] % 8 == 0 for all i
    uint16_t addrs[] = {2584, 5016, 7032, 2048, 1048, 1304, 992, 3064, 1208, 5312, 1752, 7136, 1240, 1536, 4136, 3544, 216, 3840, 4912, 2008, 6392, 7304, 6424, 1816, 5608, 2416, 5088, 6584, 2328, 8168, 968, 2352, 3920, 7952, 6672, 4016, 7448, 328, 6224, 6456, 1040, 2024, 3168, 6800, 1904, 5736, 5232, 872, 6608, 472, 2368, 272, 6712, 7712, 6440, 5120, 2064, 8104, 800, 1088, 4816, 1648, 8152, 5032, 3672, 5344, 1000, 6496, 1584, 552, 5840, 6408, 3712, 4344, 1344, 4768, 5872, 3184, 7432, 3048, 5304, 6032, 2400, 3936, 2192, 5848, 4096, 1128, 6024, 7640, 920, 3280, 3832, 6656, 2240, 6256, 3872, 1224, 1848, 4224, 5568, 5624, 4240, 8072, 7784, 1712, 2384, 856, 6312, 7528, 4512, 4600, 5984, 4856, 7648, 752, 5512, 3328, 960, 5000, 5656, 1184, 4880, 4104, 2896, 4416, 8080, 3952, 4528, 4504, 5920, 4384, 6136, 7744, 8144, 4432, 7336, 1368, 5040, 5320, 2600, 6448, 2272, 1064, 656, 1528, 3136, 6592, 1376, 2264, 1096, 3720, 3448, 4616, 6808, 1928, 5600, 96, 496, 5976, 1472, 1320, 4664, 3032, 3680, 696, 1576, 4992, 5648, 2744, 1856, 2952, 5616, 2768, 2792, 4032, 7992, 1408, 1504, 3880, 7496, 7104, 1136, 416, 5448, 1352, 4864, 288, 1912, 4848, 4984, 344, 3400, 7144, 5360, 264, 1960, 4248, 5688, 1512, 1232, 6832, 2760, 2120, 6952, 1440, 4544, 8120, 176, 3480, 8184, 8040, 5776, 4184, 6400, 5144, 4040, 5296, 2736, 80, 3848, 280, 704, 2168, 5200, 3056, 4264, 5992, 16, 6080, 6728, 7424, 5080, 2848, 4440, 5368, 3744, 2472, 1592, 7384, 7120, 584, 688, 88, 3384, 6936, 5248, 4128, 6160, 2832, 1008, 3688, 2552, 6464, 4576, 1432};

    ////////////////////////////////* UNSIGNED 8-BIT INTEGERS *////////////////////////////////
    // write SRAM
    serprint("UNSIGNED INT 8-BIT\n\r");
    serprint("WRITING... ");
    uint8_t val_uint8 = 0;
    for (uint16_t i = 0; i < 256; i++) {
        // write
        extram_write<uint8_t>(val_uint8, addrs[i]);

        // next value
        val_uint8++;
    }
    serprint("FINISHED!\n\r");

    // read SRAM again
    serprint("READING... ");
    val_uint8 = 0;
    for (uint16_t i = 0; i < 256; i++) {
        // read
        uint8_t read = extram_read<uint8_t>(addrs[i]);

        // compare
        if (read != val_uint8) {
            serprint("ERROR ");
            serprintuint16(i);
            serprint("\n\r");
            break;
        }

        // next value
        val_uint8++;
    }
    serprint("FINISHED!\n\r");

    ////////////////////////////////* UNSIGNED 16-BIT INTEGERS *////////////////////////////////
    // write SRAM
    serprint("\n\rUNSIGNED INT 16-BIT\n\r");
    serprint("WRITING... ");
    uint16_t val_uint16 = 0;
    for (uint16_t i = 0; i < 256; i++) {
        // write
        extram_write<uint16_t>(val_uint16, addrs[i]);

        // next value
        val_uint16 += 127;
    }
    serprint("FINISHED!\n\r");

    // read SRAM again
    serprint("READING... ");
    val_uint16 = 0;
    for (uint16_t i = 0; i < 256; i++) {
        // read
        uint16_t read = extram_read<uint16_t>(addrs[i]);

        // compare
        if (read != val_uint16) {
            serprint("ERROR ");
            serprintuint16(i);
            serprint("\n\r");
            break;
        }
        // next value
        val_uint16 += 127;
    }
    serprint("FINISHED!\n\r");

    ////////////////////////////////* UNSIGNED 32-BIT INTEGERS *////////////////////////////////
    // write SRAM
    serprint("\n\rUNSIGNED INT 32-BIT\n\r");
    serprint("WRITING... ");
    uint32_t val_uint32 = 0;
    for (uint16_t i = 0; i < 256; i++) {
        // write
        extram_write<uint32_t>(val_uint32, addrs[i]);

        // next value
        val_uint32 += 32767;
    }
    serprint("FINISHED!\n\r");

    // read SRAM again
    serprint("READING... ");
    val_uint32 = 0;
    for (uint16_t i = 0; i < 256; i++) {
        // read
        uint32_t read = extram_read<uint32_t>(addrs[i]);

        // compare
        if (read != val_uint32) {
            serprint("ERROR ");
            serprintuint16(i);
            serprint("\n\r");
            //  break;
        }

        // next value
        val_uint32 += 32767;
    }
    serprint("FINISHED!\n\r");

    ////////////////////////////////* UNSIGNED 64-BIT INTEGERS *////////////////////////////////
    // write SRAM
    serprint("\n\rUNSIGNED INT 64-BIT\n\r");
    serprint("WRITING... ");
    uint64_t val_uint64 = 0;
    for (uint64_t i = 0; i < 256; i++) {
        // write
        extram_write<uint64_t>(val_uint64, addrs[i]);

        // next value
        val_uint64 += 2147483647;
    }
    serprint("FINISHED!\n\r");

    // read SRAM again
    serprint("READING... ");
    val_uint64 = 0;

    for (uint16_t i = 0; i < 256; i++) {
        // read
        uint64_t read = extram_read<uint64_t>(addrs[i]);

        // compare
        if (read != val_uint64) {
            serprint("ERROR ");
            serprintuint16(i);
            serprint("\n\r");
            break;
        }

        // next value
        val_uint64 += 2147483647;
    }
    serprint("FINISHED!\n\r");

    ////////////////////////////////* FLOAT *////////////////////////////////
    // write SRAM
    serprint("\n\rFLOAT\n\r");
    serprint("WRITING... ");
    float val_float = M_PI;
    for (uint16_t i = 0; i < 256; i++) {
        // write
        extram_write<float>(val_float, addrs[i]);

        // next value
        val_float += M_PI;
    }
    serprint("FINISHED!\n\r");

    // read SRAM again
    serprint("READING... ");
    val_float = M_PI;
    for (uint16_t i = 0; i < 256; i++) {
        // read
        float read = extram_read<float>(addrs[i]);

        // compare
        if (read != val_float) {
            serprint("ERROR ");
            serprintuint16(i);
            serprint("\n\r");
            break;
        }

        // next value
        val_float += M_PI;
    }
    serprint("FINISHED!\n\r");

    // endless loop
    while (1) {
    };
}
