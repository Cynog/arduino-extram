#pragma once

#include <avr/io.h>
#include <stdio.h>

#include "lib_extram.hpp"

/**
 * @brief Bubble-sort a list of datatype T and length n in internal ram
 *
 * @tparam T data type of list entries
 * @param list list to sort
 * @param n length of list
 */
template <typename T>
void sort_bubble(T* list, uint16_t n) {
    for (uint16_t i = 0; i < n - 1; i++)
        for (uint16_t j = 0; j < n - i - 1; j++)
            if (list[j] > list[j + 1]) {
                T buf = list[j + 1];
                list[j + 1] = list[j];
                list[j] = buf;
            }
}

/**
 * @brief Bubble-sort a list of datatype T and length n in internal ram
 *
 * @tparam T data type of list entries
 * @param addr lists starting address in extram
 * @param n length of list
 */
template <typename T>
void sort_bubble_extram(uint16_t addr, uint16_t n) {
    for (uint16_t i = 0; i < n - 1; i++)
        for (uint16_t j = 0; j < n - i - 1; j++) {
            T curr = extram_read<T>(addr + j * sizeof(T));
            T next = extram_read<T>(addr + (j + 1) * sizeof(T));
            if (curr > next) {
                extram_write<T>(addr + (j + 1) * sizeof(T), curr);
                extram_write<T>(addr + j * sizeof(T), next);
            }
        }
}
