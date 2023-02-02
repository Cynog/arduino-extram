#include "lib_sort.hpp"

void sort_bubble_uint8(uint8_t* list, uint16_t n) {
    for (uint16_t i = 0; i < n - 1; i++)
        for (uint16_t j = 0; j < n - i - 1; j++)
            if (list[j] > list[j + 1]) {
                uint8_t buf = list[j + 1];
                list[j + 1] = list[j];
                list[j] = buf;
            }
}

void sort_bubble_extram_uint8(uint16_t addr, uint16_t n) {
    for (uint16_t i = 0; i < n - 1; i++)
        for (uint16_t j = 0; j < n - i - 1; j++) {
            uint8_t curr = extram_read(addr + j);
            uint8_t next = extram_read(addr + (j + 1));
            if (curr > next) {
                extram_write(addr + (j + 1), curr);
                extram_write(addr + j, next);
            }
        }
}

void sort_bubble_uint16(uint16_t* list, uint16_t n) {
    for (uint16_t i = 0; i < n - 1; i++)
        for (uint16_t j = 0; j < n - i - 1; j++)
            if (list[j] > list[j + 1]) {
                uint16_t buf = list[j + 1];
                list[j + 1] = list[j];
                list[j] = buf;
            }
}

void sort_bubble_extram_uint16(uint16_t addr, uint16_t n) {
    for (uint16_t i = 0; i < n - 1; i++)
        for (uint16_t j = 0; j < n - i - 1; j++) {
            uint16_t curr = extram_read_uint16(addr + j * 2);
            uint16_t next = extram_read_uint16(addr + (j + 1) * 2);
            if (curr > next) {
                extram_write_uint16(addr + (j + 1) * 2, curr);
                extram_write_uint16(addr + j * 2, next);
            }
        }
}