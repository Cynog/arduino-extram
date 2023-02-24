/**
 * @file lib_extram.hpp
 * @author Cynog (github.com/Cynog)
 * @brief External SRAM library for Arduino UNO.
 *
 */

#pragma once

#include <avr/io.h>
#include <util/delay.h>

#include "config.hpp"

/**
 * @brief Initialize IO-pins to communicate with EXTRAM
 *
 */
void extram_setup(void);

/**
 * @brief Send a EXTRAM address addr to the shifting register which has at most 16 bit. The exact number of bits is ADDR_MSB + 1
 *
 * @param addr 16-Bit integer to send
 */
void send_addr_to_sr(uint16_t addr);

/**
 * @brief Read a variable of type T to address addr on EXTRAM
 *
 * @tparam T Read a variable of type T from address addr on EXTRAM
 * @param addr EXTRAM address
 * @param ind optional parameter for arrays with starting address addr
 * @return T variable read
 */
template <typename T>
T extram_read(uint16_t addr, uint16_t ind = 0) {
    // extram address
    uint16_t addr_extram = addr + ind * sizeof(T);

    // variable to return
    T data;

    // pointer to read the single bytes
    uint8_t *ptr = reinterpret_cast<uint8_t *>(&data);

    // send starting address to shifting register
    send_addr_to_sr(addr_extram);

    // set OE active
    PORT_OE &= ~MASK_OE;

    // set IO pins to input with pullup
    DDR_IO0 &= ~MASK_IO0;
    PORT_IO0 |= MASK_IO0;
    DDR_IO1 &= ~MASK_IO1;
    PORT_IO1 |= MASK_IO1;

    // read the single bytes
    for (uint8_t i = 0; i < sizeof(T); i++) {
        // least significant bits of address
        PORT_ADDRLSB &= ~MASK_ADDRLSB;
        PORT_ADDRLSB |= MASK_ADDRLSB & (addr_extram + i);

        // wait for output ready
        _delay_us(0.12);

        // read from external RAM
        ptr[i] = PIN_IO0 & MASK_IO0;
        ptr[i] |= PIN_IO1 & MASK_IO1;
    }

    // set OE inactive
    PORT_OE |= MASK_OE;

    // return
    return data;
}

/**
 * @brief Write a variable of type T to address addr on EXTRAM
 *
 * @tparam T
 * @param data variable to write (referencing has to be possible)
 * @param addr EXTRAM address
 * @param ind optional parameter for arrays with starting address addr (WARNING: more convenient but worse performance compared to plugging in the correct address directly)
 */
template <typename T>
void extram_write(T &data, uint16_t addr, uint16_t ind = 0) {
    // extram address
    uint16_t addr_extram = addr + ind * sizeof(T);

    // pointer to write single bytes
    uint8_t *ptr = reinterpret_cast<uint8_t *>(&data);

    // send starting address to shifting register
    send_addr_to_sr(addr_extram);

    // set IO pins to output
    DDR_IO0 |= MASK_IO0;
    DDR_IO1 |= MASK_IO1;

    // write the single bytes
    for (uint8_t i = 0; i < sizeof(T); i++) {
        // least significant bits of address
        PORT_ADDRLSB &= ~MASK_ADDRLSB;
        PORT_ADDRLSB |= MASK_ADDRLSB & (addr_extram + i);

        // set IO pins
        PORT_IO0 &= ~MASK_IO0;
        PORT_IO0 |= ptr[i] & MASK_IO0;
        PORT_IO1 &= ~MASK_IO1;
        PORT_IO1 |= ptr[i] & MASK_IO1;

        // write to external RAM by giving low pulse on WE
        PORT_WE &= ~MASK_WE;
        PORT_WE |= MASK_WE;
    }
}