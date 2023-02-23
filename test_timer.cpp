/**
 * @file test_time.cpp
 * @author Cynog (github.com/Cynog)
 * @brief A simple program to determine the lib_timers influence on performance by measuring the time of the delay.h _delay_ms() function.
 *
 */

#include <avr/io.h>
#include <util/delay.h>

#include "lib_timer.hpp"
#include "lib_usart.hpp"

int main(void) {
    // initialize usart
    usart_setup();

    // initialize timer
    timer_setup();
    uint32_t t;

    // endless main loop
    while (1) {
        // measure time of delay 100s
        timer_reset();
        _delay_ms(100000.);
        t = timer_getms();

        // print measured time
        serprint("measured time of 100s delay: ");
        serprintuint32(t);
        serprint(" ms\n\r");

        // wait for user to run test again
        serprint("\n\r\n\r\n\r");
        wait_key_remind("TEST FINISHED. PRESS ANY KEY TO RUN IT AGAIN.\n\r", 5000);
        serprint("\n\r");
    }
}
