#ifndef _EXTRAM_H_
#define _EXTRAM_H_

#include <avr/io.h>
#include <stdio.h>

void setup_extram(void);

void send_addr_to_sr(uint16_t addr);

uint8_t read_extram(uint16_t addr);

uint8_t write_extram(uint16_t addr);

#endif  // _EXTRAM_H_