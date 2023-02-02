#pragma once

#include <avr/io.h>
#include <stdio.h>

#include "lib_extram.hpp"

void sort_bubble_uint8(uint8_t* list, uint16_t n);
void sort_bubble_extram_uint8(uint16_t addr, uint16_t n);
