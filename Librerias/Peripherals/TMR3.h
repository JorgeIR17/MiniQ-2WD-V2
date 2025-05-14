/**
 * @file TMR3.h
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del Timer 3 del ATMega32U4.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TMR3_H_
#define TMR3_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

// Divisores de frecuencia de reloj
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
volatile bool blink;

/**
 * @brief Inicializa el Timer 3 en modo CTC.
 * 
 */
static inline void TMR3_CTC_Init()
{
    TCCR3A &= ~(1<<WGM31);
    TCCR3A &= ~(1<<WGM30);
    TCCR3B |= (1<<WGM32);
    TCCR3B &= ~(1<<WGM33);
}

/**
 * @brief Activa las interrupciones del Timer 3 en modo CTC.
 * 
 */
static inline void TMR3_CTC_enaInterrupt()
{
    TIMSK3 |= (1<<OCIE3A);
}

/**
 * @brief Desactiva las interrupciones del Timer 3 en modo CTC.
 * 
 */
static inline void TMR3_CTC_disInterrupt()
{
    TIMSK3 &= ~(1<<OCIE3A);
}

/**
 * @brief Inicia el Timer 3 en modo CTC.
 * 
 * @param divClock Divisor de frecuencia. Es necesario hacer uso de las macros proporcionadas.
 */
static inline void TMR3_CTC_Start(uint8_t divClock)
{
    TCNT3H = 0;
    TCNT3L = 0;
    TCCR3B &= 0b11111000;
    TCCR3B |= (divClock << CS30);
}

/**
 * @brief Detiene el funcionamiento del Timer 3 en modo CTC.
 * 
 */
static inline void TMR3_CTC_Stop()
{
    TCCR3B &= 0b11111000;
}

/**
 * @brief Establece el valor de contador del Timer 3 en modo CTC.
 * 
 * @param valueCounterA Valor de contador.
 */
static inline void TMR3_CTC_Set(uint16_t valueCounterA)
{
    OCR3A = valueCounterA; //15624 para 100 ms con prescaler 64
}

#endif /* TMR3_H_ */
