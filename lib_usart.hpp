/**
 * @file lib_usart.hpp
 * @author Cynog (github.com/Cynog)
 * @brief A library containing some useful usart functions.
 * 
 */

#pragma once

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib_extram.hpp"
#include "lib_timer.hpp"

/**
 * @brief Initialize USART with baud rate 3600 in transmit and receive mode
 *
 */
void usart_setup(void);

/**
 * @brief Print a single character to serial port
 *
 * @param c character to print
 */
void serprintchar(char c);

/**
 * @brief Print a string to serial port
 *
 * @param s string to print
 */
void serprint(const char *s);

/**
 * @brief Print unsigned int to serial port
 *
 * @param val integer to print
 */
void serprintuint8(uint8_t val);

/**
 * @brief Print unsigned int to serial port
 *
 * @param val integer to print
 */
void serprintuint16(uint16_t val);

/**
 * @brief Print unsigned int to serial port
 *
 * @param val integer to print
 */
void serprintuint32(uint32_t val);

/**
 * @brief Print integer to serial port
 *
 * @param val integer to print
 */
void serprintint(int val);

/**
 * @brief Print integer as hex to serial port
 *
 * @param val integer to print
 */
void serprinthex(int val);

/**
 * @brief Print float to serial port
 *
 * @param f float to print
 * @param width width of printed number
 * @param prec precision of printed number
 */
void serprintfloat(float f, signed char width, unsigned char prec);

/**
 * @brief Print a square matrix to serial port
 *
 * @param M matrix to print
 * @param n size of matrix M
 */
void serprintmat(float *M, int n);

/**
 * @brief Print a square matrix from EXTRAM to serial port
 *
 * @param addr EXTRAM address of matrix
 * @param n size of matrix M
 */
void serprintmat_extram(uint16_t addr, int n);

/**
 * @brief Read a byte from serial
 *
 * @return uint8_t byte read
 */
uint8_t serscan(void);

/**
 * @brief Wait for user input
 *
 * @param message message to show
 */
void wait_key(const char *message);

/**
 * @brief Wait for user input within a certain timeout. Requires timer_setup() to be called before and modifies the current timer!
 * 
 * @param message message to show
 * @param remindms timeout to show message again
 */
void wait_key_remind(const char *message, uint32_t remindms);