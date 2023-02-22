#pragma once

#include <math.h>

#include "lib_extram.hpp"
#include "lib_usart.hpp"

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
 * @brief Bubble-sort a list of datatype T and length n sorting chunks and later merging the sorted chunks.
 *
 * @tparam T data type of list entries
 * @param list list to sort
 * @param n length of list
 * @param n_chunks number of chunks (has to divide n)
 * @param list_sorted output sorted list
 */
template <typename T>
void sort_bubble_chunks(T* list, uint16_t n, uint8_t n_chunks, T* list_sorted) {
    // check input
    if (n % n_chunks != 0) {
        serprint("BUFFERED SORTING FAILED! n_chunks has to divide n!\n\r");
        return;
    }

    // size of each chunk
    uint16_t chunksize = n / n_chunks;

    // sort chunks
    for (uint8_t k = 0; k < n_chunks; k++) {
        sort_bubble<T>(&list[k * chunksize], chunksize);
    }

    // next smallest element of each chunk for merging
    T currvals[n_chunks];
    for (uint8_t k = 0; k < n_chunks; k++)
        currvals[k] = list[k * chunksize];

    // index of the next smallest element of each chunk for merging
    uint16_t chunk_inds[n_chunks];
    for (uint8_t k = 0; k < n_chunks; k++)
        chunk_inds[k] = 0;

    // merge sorted chunks
    for (uint16_t i = 0; i < n; i++) {
        // search smallest current element of each chunk
        uint8_t indmin = 0;
        T valmin = currvals[0];
        for (uint8_t k = 1; k < n_chunks; k++) {
            if (currvals[k] < valmin) {
                indmin = k;
                valmin = currvals[k];
            }
        }

        // insert in final list
        list_sorted[i] = valmin;

        // check chunk completely inserted in final list thus no longer needed
        chunk_inds[indmin] += 1;
        if (chunk_inds[indmin] == chunksize) {
            for (uint8_t k = indmin; k < n_chunks; k++) {
                currvals[k] = currvals[k + 1];
                chunk_inds[k] = chunk_inds[k + 1];
            }
            n_chunks -= 1;
            continue;
        }

        // load next element of the chunk
        currvals[indmin] = list[indmin * chunksize + chunk_inds[indmin]];
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

/**
 * @brief Bubble-sort a list of datatype T and length n in external RAM by sorting chunks on external/internal RAM and later merging the sorted chunks at addr_sorted.
 *
 * @tparam T data type of list entries
 * @param addr lists starting address in EXTRAM
 * @param n length of list
 * @param n_chunks number of chunks (has to divide n)
 * @param addr_sorted address where the sorted list is saved
 * @param internal optional parameter(default: true) to sort chunks buffered on internal
 */
template <typename T>
void sort_bubble_extram_chunks(uint16_t addr, uint16_t n, uint8_t n_chunks, uint16_t addr_sorted, bool internal = true) {
    // check input
    if (n % n_chunks != 0) {
        serprint("BUFFERED SORTING FAILED! n_chunks has to divide n!\n\r");
        return;
    }

    // addresses of each chunk
    uint16_t chunksize = n / n_chunks;
    uint16_t chunk_addrs[n_chunks];
    chunk_addrs[0] = addr;
    for (uint8_t k = 1; k < n_chunks; k++)
        chunk_addrs[k] = addr + k * chunksize * sizeof(T);

    // sort chunks
    if (internal) {
        // sort chunks buffered on internal ram
        T list[chunksize];
        for (uint8_t k = 0; k < n_chunks; k++) {
            // load chunk to internal ram
            for (uint8_t i = 0; i < chunksize; i++)
                list[i] = extram_read<T>(chunk_addrs[k] + i * sizeof(T));

            // sort
            sort_bubble<T>(list, chunksize);

            // save sorted chunk on external ram
            for (uint8_t i = 0; i < chunksize; i++)
                extram_write<T>(list[i], chunk_addrs[k] + i * sizeof(T));
        }
    } else {
        // sort chunks on external ram
        for (uint8_t k = 0; k < n_chunks; k++) {
            sort_bubble_extram<T>(chunk_addrs[k], chunksize);
        }
    }

    // next smallest element of each chunk for merging
    T currvals[n_chunks];
    for (uint8_t k = 0; k < n_chunks; k++)
        currvals[k] = extram_read<T>(chunk_addrs[k]);

    // index of the next smallest element of each chunk for merging
    uint16_t chunk_inds[n_chunks];
    for (uint8_t k = 0; k < n_chunks; k++)
        chunk_inds[k] = 0;

    // merge sorted chunks
    for (uint16_t i = 0; i < n; i++) {
        // search smallest current element of each chunk
        uint8_t indmin = 0;
        T valmin = currvals[0];
        for (uint8_t k = 1; k < n_chunks; k++) {
            if (currvals[k] < valmin) {
                indmin = k;
                valmin = currvals[k];
            }
        }

        // insert in final list
        extram_write<T>(valmin, addr_sorted + i * sizeof(T));

        // check chunk completely inserted in final list thus no longer needed
        chunk_inds[indmin] += 1;
        if (chunk_inds[indmin] == chunksize) {
            for (uint8_t k = indmin; k < n_chunks; k++) {
                currvals[k] = currvals[k + 1];
                chunk_inds[k] = chunk_inds[k + 1];
                chunk_addrs[k] = chunk_addrs[k + 1];
            }
            n_chunks -= 1;
            continue;
        }

        // load next element of the chunk
        currvals[indmin] = extram_read<T>(chunk_addrs[indmin] + chunk_inds[indmin] * sizeof(T));
    }
}