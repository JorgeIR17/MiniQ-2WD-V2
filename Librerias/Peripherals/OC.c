#include "OC.h"

// ISR para Timer 0
ISR(TIMER0_COMPA_vect)
{
    TOGGLEBIT(PORTB, PORTB2);
}

// ISR para Timer 1
ISR(TIMER1_COMPA_vect)
{
    CLEARBIT(PORTB, PORTB2);
    TMR0_CTC_Stop();
    TMR1_CTC_Stop();
}
