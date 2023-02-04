#include "lib_time.hpp"

// outer counter for ms
static volatile uint32_t timer_val = 0;

// Timer/Counter0 Compare Match A for ms counter
ISR(TIMER1_COMPA_vect) {
    timer_val++;
}

// initialize Timer/Counter1 to 1ms compare mach A interrupt
void timer_setup(void) {
    // timer 1 setup
    TCCR1B = (1 << WGM12) | (1 << CS11);  // CTC mode with OCR1A and prescaling of 8
    TIMSK1 = (1 << OCIE1A);               // compare match A interrupt
    OCR1A = 1999;                         // timer 1 TOP 1999

    // allow global interrupts
    sei();
}

// reset counters
void timer_reset(void) {
    // reset counter 1
    TCNT1 = 0;

    // reset outer ms counter
    timer_val = 0;
}

// get outer counter ms count
uint32_t timer_getms(void) {
    // return elapsed time in ms
    return timer_val;
}