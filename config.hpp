#pragma once

// external SRAM properties
#define ADDR_MSB 12    // most significant bit of EXTRAM addresses
#define ADDR_SR_LSB 3  // most significant bit of EXTRAM addresses loaded into shifting register
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