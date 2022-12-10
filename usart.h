#ifndef _USART_H_
#define _USART_H_

#include <avr/io.h>
#include <stdio.h>

void setup_usart(void);
void serprintchar(char c);
void serprint(char *s);
void serprintuint8(uint8_t val);
void serprintint(int i);
void serprinthex(int i); 
void serprintfloat(float f, signed char width, unsigned char prec);

void serprintmat(float *M, int n);

#endif  // _USART_H_