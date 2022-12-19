#pragma once

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib_extram.hpp"

void setup_usart(void);
void serprintchar(char c);
void serprint(char *s);
void serprintuint8(uint8_t val);
void serprintuint16(uint16_t val);
void serprintuint8(uint8_t val);
void serprintuint32(uint32_t val);
void serprintint(int i);
void serprinthex(int i);
void serprintfloat(float f, signed char width, unsigned char prec);

void serprintmat(float *M, int n);
void serprintmat_extram(uint16_t addr, int n);

uint8_t serscan(void);

void wait_key(void);
void wait_key(char *message);