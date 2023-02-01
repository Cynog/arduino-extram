#pragma once

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "lib_usart.hpp"

// external SRAM properties
#define ADDR_MSB 12 // most significant bit of EXTRAM addresses
#define EXTRAM_SIZE (1 << 13)

// definitions for shifting register
#define PORT_SRCLK PORTD
#define DDR_SRCLK DDRD
#define MASK_SRCLK (1 << PD2)

#define PORT_SER PORTD
#define DDR_SER DDRD
#define MASK_SER (1 << PD3)

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
 * @brief Read a Byte stored in address addr on EXTRAM
 * 
 * @param addr EXTRAM address
 * @return uint8_t Byte read
 */
uint8_t extram_read(uint16_t addr);

/**
 * @brief Write a Byte to address addr on EXTRAM
 * 
 * @param addr EXTRAM address
 * @param data Byte to write
 */
void extram_write(uint16_t addr, uint8_t data);

/**
 * @brief Read a float(4 Byte) stored in addresses addr:addr+3 on EXTRAM
 * 
 * @param addr EXTRAM address
 * @return float Float read
 */
float extram_read_float(uint16_t addr);

/**
 * @brief Write a float(4 Byte) to addresses addr:addr+3 on EXTRAM
 * WARNING: It is the users responsibility to avoid overlapping
 * 
 * @param addr EXTRAM address
 * @param data Float to write
 */
void extram_write_float(uint16_t addr, float data);