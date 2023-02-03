#pragma once

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "lib_usart.hpp"

// external SRAM properties
#define ADDR_MSB 12  // most significant bit of EXTRAM addresses
#define EXTRAM_SIZE (1 << 13)

// definitions for shifting register
#define PORT_SRCLK PORTC
#define DDR_SRCLK DDRC
#define MASK_SRCLK (1 << PC3)

#define PORT_SER PORTC
#define DDR_SER DDRC
#define MASK_SER (1 << PC2)

#define PORT_ADDR012 PORTC
#define DDR_ADDR012 DDRC
#define MASK_ADDR012 ((1 << PC0) | (1 << PC1) | (1 << PC2))

// definitions for external SRAM
#define PORT_IO0 PORTB
#define PIN_IO0 PINB
#define DDR_IO0 DDRB
#define MASK_IO0 ((1 << PB0) | (1 << PB1) | (1 << PB2) | (1 << PB3))

#define PORT_IO1 PORTD
#define PIN_IO1 PIND
#define DDR_IO1 DDRD
#define MASK_IO1 ((1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7))

#define PORT_OE PORTB
#define DDR_OE DDRB
#define MASK_OE (1 << PB4)

#define PORT_WE PORTB
#define DDR_WE DDRB
#define MASK_WE (1 << PB5)

/**
 * @brief Initialize IO-pins to communicate with EXTRAM

 *
 */
void extram_setup(void);

/**
 * @brief Send a address to the shifting register which has at most 16 bit. The exact number of bits is ADDR_MSB + 1
 *
 * @param addr 16-Bit integer to send
 */
void send_addr_to_sr(uint16_t addr);

/**
 * @brief Read a variable of type T from address addr on EXTRAM
 *
 * @param addr EXTRAM address
 * @return T variable read
 */
template <typename T>
T extram_read(uint16_t addr) {
    // variable to return
    T data;

    // pointer to read the single bytes
    uint8_t *ptr = reinterpret_cast<uint8_t *>(&data);

    // send starting address to shifting register
    send_addr_to_sr(addr);

    // read the single bytes
    for (uint8_t i = 0; i < sizeof(T); i++) {
        // least significant bits of address
        PORT_ADDR012 &= ~MASK_ADDR012;
        PORT_ADDR012 |= MASK_ADDR012 & (addr + i);

        // set OE to LOW
        PORT_OE &= ~MASK_OE;

        // set IO pins to input with pullup
        DDR_IO0 &= ~MASK_IO0;
        PORT_IO0 |= MASK_IO0;
        DDR_IO1 &= ~MASK_IO1;
        PORT_IO1 |= MASK_IO1;

        // read from RAM
        ptr[i] = PIN_IO0 & MASK_IO0;
        ptr[i] |= PIN_IO1 & MASK_IO1;

        // set OE back to HIGH
        PORT_OE |= MASK_OE;
    }

    // return
    return data;
}

/**
 * @brief Write a variable of type T to address addr on EXTRAM
 *
 * @param addr EXTRAM address
 * @param data variable to write
 */
template <typename T>
void extram_write(uint16_t addr, T data) {
    // pointer to write single bytes
    uint8_t *ptr = reinterpret_cast<uint8_t *>(&data);

    // send starting address to shifting register
    send_addr_to_sr(addr);

    // write the single bytes
    for (uint8_t i = 0; i < sizeof(T); i++) {
        // least significant bits of address
        PORT_ADDR012 &= ~MASK_ADDR012;
        PORT_ADDR012 |= MASK_ADDR012 & (addr + i);

        // set IO pins to output
        DDR_IO0 |= MASK_IO0;
        DDR_IO1 |= MASK_IO1;

        // set IO pins
        PORT_IO0 &= ~MASK_IO0;
        PORT_IO0 |= ptr[i] & MASK_IO0;
        PORT_IO1 &= ~MASK_IO1;
        PORT_IO1 |= ptr[i] & MASK_IO1;

        // give LOW pulse on WE
        PORT_WE &= ~MASK_WE;
        PORT_WE |= MASK_WE;
    }

    // return
    return;
}