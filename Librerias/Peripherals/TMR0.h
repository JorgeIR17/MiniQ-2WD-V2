#ifndef TMR0_H_
#define TMR0_H_

#include <avr/io.h>

#define DIV_CLK_1       1
#define DIV_CLK_8       2
#define DIV_CLK_64      3
#define DIV_CLK_256     4
#define DIV_CLK_1024    5

static inline void TMR0_CTC_Init()
{
	TCCR0B &= ~(1<<WGM02);
	TCCR0A |= (1<<WGM01);
	TCCR0A &= (~(1<<WGM00));
}

static inline void TMR0_CTC_enaInterrupt()
{
	TIMSK0 |= (1<<OCIE0A);
}

static inline void TMR0_CTC_disInterrupt()
{
	TIMSK0 &= ~(1<<OCIE0A);
}

static inline void TMR0_CTC_Start(uint8_t divClock)
{
	TCNT0 = 0;
	TCCR0B &= 0b11111000;
	TCCR0B |= (divClock << CS00);
}

static inline void TMR0_CTC_Stop()
{
	TCCR0B &= 0b11111000;
}

static inline void TMR0_CTC_Set(uint8_t valueCounterA)
{
	OCR0A = valueCounterA;
}

static inline void TMR0_HW_toggleOC0A()
{
	TCCR0A &= ~(1<<COM0A1);
	TCCR0A |= (1 << COM0A0);
}

static inline void TMR0_PWM_Phase_Init()
{
	DDRD |= (1<<DDD0);
	DDRB |= (1<<DDB7);
	TCCR0A |= (1<<COM0A1) | (1<<COM0B1);
	TCCR0A |= (1<<WGM00);
	TCCR0B |= (1<<CS00);
}

static inline void TMR0_PWM_Phase_Start(uint8_t divClock)
{
	TCNT0 = 0;
	TCCR0B &= 0b11111000;
	TCCR0B |= (divClock<<CS00);
}

static inline void TMR0_PWM_Phase_Duty(uint8_t valueOCR0A, uint8_t valueOCR0B)
{
	OCR0A = valueOCR0A;
	OCR0B = valueOCR0B;
}

#endif /* TMR0_H_ */