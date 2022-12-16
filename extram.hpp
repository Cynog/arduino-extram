#ifndef _EXTRAM_H_
#define _EXTRAM_H_

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#include "usart.hpp"

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
#define MASK_IO0 ((1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3))

#define PORT_IO1 PORTD
#define PIN_IO1 PIND
#define DDR_IO1 DDRD
#define MASK_IO1 ((1<<PD4)|(1<<PD5)|(1<<PD6)|(1<<PD7))

#define PORT_OE PORTB
#define DDR_OE DDRB
#define MASK_OE (1<<PB4)

#define PORT_WE PORTB
#define DDR_WE DDRB
#define MASK_WE (1<<PB5)

void setup_extram(void);

/**
 * @brief send a 16-Bit integer to a shifting register
 *
 * @param addr 16-Bit integer to send
 */
void send_addr_to_sr(uint16_t addr);

uint8_t extram_read(uint16_t addr);

void extram_write(uint16_t addr, uint8_t data);

#endif  // _EXTRAM_H_