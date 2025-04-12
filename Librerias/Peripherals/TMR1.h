#ifndef TMR1_H_
#define TMR1_H_

#include <avr/io.h>

#define DIV_CLK_1       1
#define DIV_CLK_8       2
#define DIV_CLK_64      3
#define DIV_CLK_256     4
#define DIV_CLK_1024    5

static inline void TMR1_CTC_Init()
{
	TCCR1A &= ~(1<<WGM11);
	TCCR1A &= ~(1<<WGM10);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
}

static inline void TMR1_CTC_enaInterrupt()
{
	TIMSK1 |= (1<<OCIE1A);
}

static inline void TMR1_CTC_disInterrupt()
{
	TIMSK1 &= ~(1<<OCIE1A);
}

static inline void TMR1_CTC_Start(uint8_t divClock)
{
	TCNT1H = 0;
	TCNT1L = 0;
	TCCR1B &= 0b11111000;
	TCCR1B |= (divClock << CS10);
}

static inline void TMR1_CTC_Stop()
{
	TCCR1B &= 0b11111000;
}

static inline void TMR1_CTC_Set(uint16_t valueCounterA)
{
	OCR1A = valueCounterA;
}

static inline void TMR1_HW_toggleOC1A()
{
	TCCR1A &= ~(1<<COM1A1);
	TCCR1A |= (1 << COM1A0);
}

#endif /* TMR1_H_ */
