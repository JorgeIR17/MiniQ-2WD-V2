/**
 * @file tmr3.h
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del Timer 3 del ATMega32U4.
 * @version 1.0
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TMR3_H_
#define TMR3_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.h" // Para la ISR de TIMER3_COMPA_VEC

// Divisores de frecuencia de reloj
#define DIV_CLK_1       1
#define DIV_CLK_8       2
#define DIV_CLK_64      3
#define DIV_CLK_256     4
#define DIV_CLK_1024    5

/**
 * @brief Inicializa el Timer 3 en modo CTC.
 * 
 */
static inline void TMR3_CTC_Init()
{
    //Set CTC Mode
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
    //Reset counter
    TCNT3H = 0;
    TCNT3L = 0;

    TCCR3B &= 0b11111000; // Clear CS30, CS31, CS32
    TCCR3B |= (divClock << CS30); // Set prescaler
}

/**
 * @brief Detiene el funcionamiento del Timer 3 en modo CTC.
 * 
 */
static inline void TMR3_CTC_Stop()
{
    TCCR3B &= 0b11111000; // Clear CS30, CS31, CS32
}

/**
 * @brief Establece el valor de contador del Timer 3 en modo CTC.
 * 
 * @param valueCounterA Valor de contador.
 */
static inline void TMR3_CTC_Set(uint16_t valueCounterA)
{
    OCR3A = valueCounterA;
}

#endif /* TMR3_H_ */
