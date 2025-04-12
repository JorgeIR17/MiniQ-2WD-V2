#ifndef TMR3_H_
#define TMR3_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define DIV_CLK_1       1
#define DIV_CLK_8       2
#define DIV_CLK_64      3
#define DIV_CLK_256     4
#define DIV_CLK_1024    5

#define PULSOS_POR_VUELTA 25    // 25 pulsos

volatile uint16_t pulsos_izq;
volatile uint16_t pulsos_der;
volatile uint16_t interval_izq;
volatile uint16_t interval_der;
volatile uint16_t rpm_izq;
volatile uint16_t rpm_der;

static inline void TMR3_CTC_Init()
{
    TCCR3A &= ~(1<<WGM31);
    TCCR3A &= ~(1<<WGM30);
    TCCR3B |= (1<<WGM32);
    TCCR3B &= ~(1<<WGM33);
}

static inline void TMR3_CTC_enaInterrupt()
{
    TIMSK3 |= (1<<OCIE3A);
}

static inline void TMR3_CTC_disInterrupt()
{
    TIMSK3 &= ~(1<<OCIE3A);
}

static inline void TMR3_CTC_Start(uint8_t divClock)
{
    TCNT3H = 0;
    TCNT3L = 0;
    TCCR3B &= 0b11111000;
    TCCR3B |= (divClock << CS30);
}

static inline void TMR3_CTC_Stop()
{
    TCCR3B &= 0b11111000;
}

static inline void TMR3_CTC_Set(uint16_t valueCounterA)
{
    OCR3A = valueCounterA; //15624 para 100 ms
}

static inline void TMR3_HW_toggleOC3A()
{
    TCCR3A &= ~(1<<COM3A1);
    TCCR3A |= (1 << COM3A0);
}

#endif /* TMR3_H_ */
