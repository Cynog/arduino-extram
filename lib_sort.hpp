#pragma once

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
                // swap
                T buf = list[j + 1];
                list[j + 1] = list[j];
                list[j] = buf;
            }
}

/**
 * @brief Bubble-sort a list of datatype T and length n in external ram
 *
 * @tparam T data type of list entries
 * @param addr lists starting address in EXTRAM
 * @param n length of list
 */
template <typename T>
void sort_bubble_extram(uint16_t addr, uint16_t n) {
    for (uint16_t i = 0; i < n - 1; i++)
        for (uint16_t j = 0; j < n - i - 1; j++) {
            // read values from EXTRAM //TODO performance could be improved by comparing single bytes while reading (for uint data types)
            T curr = extram_read<T>(addr + j * sizeof(T));
            T next = extram_read<T>(addr + (j + 1) * sizeof(T));
            if (curr > next) {
                // spwap
                extram_write<T>(curr, addr + (j + 1) * sizeof(T));
                extram_write<T>(next, addr + j * sizeof(T));
            }
        }
}

template <typename T>
void sort_bubble_extram_chunks(uint16_t addr, uint16_t n, uint8_t n_chunks) {
    uint16_t chunksize = n / n_chunks;
    uint16_t chunk_addrs[n_chunks];
    chunk_addrs[0] = addr;
    for (uint8_t i = 1; i < n_chunks; i++)
        chunk_addrs[i] = addr + i * chunksize * sizeof(T);

    // sort chunks buffered on internal ram
    T list[chunksize];
    for (uint8_t k = 0; k < n_chunks; k++) {
        // load chunk to internal ram
        for (uint8_t i = 0; i < chunksize; i++)
            list[i] = extram_read<T>(chunk_addrs[k] + i * sizeof(T));

        // sort
        sort_bubble(list, chunksize);

        // save sorted chunk on external ram
        for (uint8_t i = 0; i < chunksize; i++)
            extram_write<T>(list[i], chunk_addrs[k] + i * sizeof(T));
    }
}