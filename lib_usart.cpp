#include "lib_usart.hpp"

void setup_usart(void) {
    UBRR0L = 103;                          // baud rate 9600
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);  // enable transmit and receive
}

void serprintchar(char c) {
    while ((UCSR0A & (1 << UDRE0)) == 0) {
    };
    UDR0 = c;
}

void serprint(char* s) {
    int i = 0;
    while (1) {
        char c = s[i];
        if (c == 0) break;
        serprintchar(c);
        i++;
    }
}

void serprintuint8(uint8_t val) {
    uint8_t div = 100;
    uint8_t mod;
    uint8_t sent = 0;

    for (int i = 0; i < 3; i++) {
        mod = val % div;
        uint8_t c = val / div;
        if (c != 0 || sent) {
            serprintchar(c + 48);
            sent = 1;
        } else if (i < 2)
            serprintchar(' ');
        div /= 10;
        val = mod;
    }

    if (sent == 0)
        serprintchar('0');
}

void serprintuint16(uint16_t val) {
    uint16_t div = 10000;
    uint16_t mod;
    uint8_t sent = 0;

    for (int i = 0; i < 5; i++) {
        mod = val % div;
        uint8_t c = val / div;
        if (c != 0 || sent) {
            serprintchar(c + 48);
            sent = 1;
        } else if (i < 4)
            serprintchar(' ');
        div /= 10;
        val = mod;
    }

    if (sent == 0)
        serprintchar('0');
}

void serprintuint32(uint32_t val) {
    uint32_t div = 1000000000;
    uint32_t mod;
    uint8_t sent = 0;

    for (int i = 0; i < 10; i++) {
        mod = val % div;
        uint8_t c = val / div;
        if (c != 0 || sent) {
            serprintchar(c + 48);
            sent = 1;
        }
        div /= 10;
        val = mod;
    }

    if (sent == 0)
        serprintchar('0');
}

void serprintint(int i) {
    char s[16];
    sprintf(s, "%d", i);
    serprint(s);
}

void serprinthex(int i) {
    char s[16];
    sprintf(s, "0x%x", i);
    serprint(s);
}

void serprintfloat(float f, signed char width, unsigned char prec) {
    char s[20];
    dtostrf(f, width, prec, s);
    serprint(s);
}

void serprintmat(float* M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            serprintfloat(M[n * i + j], 12, 6);
            serprint("    ");
        }
        serprint("\n\r");
    }
}

void serprintmat_extram(uint16_t addr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            serprintfloat(extram_read_float(addr + (n * i + j) * 4), 12, 6);
            serprint("    ");
        }
        serprint("\n\r");
    }
}

uint8_t serscan(void) {
    while ((UCSR0A & (1 << RXC0)) == 0) {
    };
    return UDR0;
}

void wait_key(void) {
    serprint("press any key to continue\n\r");
    serscan();
}

void wait_key(char* message) {
    serprint(message);
    serscan();
}