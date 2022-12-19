#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

void setup_timer(void);

void timer_reset(void);

uint32_t timer_getms(void);