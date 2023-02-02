#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>

/**
 * @brief Initialize Timer/Counter 0 for 1ms Compare Match A interrupts
 * 
 */
void timer_setup(void);

/**
 * @brief Reset the outer 1ms counter
 * 
 */
void timer_reset(void);

/**
 * @brief Get the current value of the outer ms counter
 * 
 * @return uint32_t Get the number of ms since the setup_timer call or the last timer_reset call
 */
uint32_t timer_getms(void);