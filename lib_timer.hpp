/**
 * @file lib_timer.hpp
 * @author Cynog (github.com/Cynog)
 * @brief Simple library to measure time in milliseconds.
 * 
 */

#pragma once

#include <avr/interrupt.h>
#include <avr/io.h>

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
 * @brief Get the number of ms since the setup_timer call or the last timer_reset call
 * 
 * @return uint32_t number of ms
 */
uint32_t timer_getms(void);