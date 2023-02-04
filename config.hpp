/**
 * @file config.hpp
 * @author Cynog (github.com/Cynog)
 * @brief Configuration file for constants and IO-registers for the EXTRAM library for Arduino UNO.
 *
 */

#pragma once

////////////////////////////////* EXTRAM properties *////////////////////////////////////////////////////////////////
// most significant bit of EXTRAM addresses
#define ADDR_MSB 12

// EXTRAM size in bytes (EXTRAM number of addresses)
#define EXTRAM_SIZE (1 << 13)

////////////////////////////////* definitions for shifting register *////////////////////////////////
// most significant bit of EXTRAM addresses loaded into shifting register
#define ADDR_SR_LSB 3

// serial clock pin for shifting register
#define PORT_SRCLK PORTC
#define DDR_SRCLK DDRC
#define MASK_SRCLK (1 << PC3)

// serial pin for shifting register
#define PORT_SER PORTC
#define DDR_SER DDRC
#define MASK_SER (1 << PC2)  //! WARNING must be the same as the most significant bit of MASK_ADDR

// least significant bits of address connected directly to EXTRAM address pins
#define PORT_ADDRLSB PORTC
#define DDR_ADDRLSB DDRC
#define MASK_ADDRLSB ((1 << PC2) | (1 << PC1) | (1 << PC0))  //! WARNING: must be the least significant bits

////////////////////////////////* definitions for external SRAM *////////////////////////////////
// first EXTRAM IO-pins
#define PORT_IO0 PORTB
#define PIN_IO0 PINB
#define DDR_IO0 DDRB
#define MASK_IO0 ((1 << PB3) | (1 << PB2) | (1 << PB1) | (1 << PB0))  //! WARNING: must be the least significant bits

// other EXTRAM IO-pins
#define PORT_IO1 PORTD
#define PIN_IO1 PIND
#define DDR_IO1 DDRD
#define MASK_IO1 ((1 << PD7) | (1 << PD6) | (1 << PD5) | (1 << PD4))  //! WARNING: must be the most significant bits

// EXTRAM output enable pin
#define PORT_OE PORTB
#define DDR_OE DDRB
#define MASK_OE (1 << PB4)

// EXTRAM write enable pin
#define PORT_WE PORTB
#define DDR_WE DDRB
#define MASK_WE (1 << PB5)