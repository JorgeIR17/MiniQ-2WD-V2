#include "TMR0.h"

// ISR para Timer 0
ISR(TIMER0_COMPA_vect)
{
    TOGGLEBIT(PORTB, PORTB2);
}