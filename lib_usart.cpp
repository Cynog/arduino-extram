#include "lib_usart.hpp"

void usart_setup(void) {
    UBRR0L = 103;                          // baud rate 9600
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);  // enable transmit and receive
}

void serprintchar(char c) {
    // wait until USART is ready
    while ((UCSR0A & (1 << UDRE0)) == 0) {
    };

    // send char
    UDR0 = c;
}

void serprint(const char* s) {
    int i = 0;
    while (1) {
        char c = s[i];
        if (c == 0) break;  // end of string
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

void serprintint(int val) {
    char s[16];
    sprintf(s, "%d", val);
    serprint(s);
}

void serprinthex(int val) {
    char s[16];
    sprintf(s, "0x%x", val);
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
            serprintfloat(extram_read<float>(addr, n * i + j), 12, 6);
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

void wait_key(const char* message) {
    serprint(message);
    serscan();
}

void wait_key_remind(const char* message, uint32_t remindms) {
    timer_reset();
    serprint(message);
    while (1) {
        if ((UCSR0A & (1 << RXC0)) != 0) {
            serscan();
            break;
        }

        if (timer_getms() >= remindms) {
            serprint(message);
            timer_reset();
        }
    }
}