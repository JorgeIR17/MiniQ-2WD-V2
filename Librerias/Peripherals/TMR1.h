/**
 * @file TMR1.h
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del Timer 1 del ATMega32U4.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TMR1_H_
#define TMR1_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include "TMR0.h"

// Divisores de frecuencia de reloj
#define DIV_CLK_1       1
#define DIV_CLK_8       2
#define DIV_CLK_64      3
#define DIV_CLK_256     4
#define DIV_CLK_1024    5

/**
 * @brief Inicializa el Timer 1 en modo CTC.
 * 
 */
static inline void TMR1_CTC_Init()
{
	TCCR1A &= ~(1<<WGM11);
	TCCR1A &= ~(1<<WGM10);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
}

/**
 * @brief Activa las interrupciones del Timer 1 en modo CTC.
 * 
 */
static inline void TMR1_CTC_enaInterrupt()
{
	TIMSK1 |= (1<<OCIE1A);
}

/**
 * @brief Desactiva las interrupciones del Timer 1 en modo CTC.
 * 
 */
static inline void TMR1_CTC_disInterrupt()
{
	TIMSK1 &= ~(1<<OCIE1A);
}

/**
 * @brief Inicia el Timer 1 en modo CTC.
 * 
 * @param divClock Divisor de frecuencia. Es necesario hacer uso de las macros proporcionadas.
 */
static inline void TMR1_CTC_Start(uint8_t divClock)
{
	TCNT1H = 0;
	TCNT1L = 0;
	TCCR1B &= 0b11111000;
	TCCR1B |= (divClock << CS10);
}

/**
 * @brief Detiene el funcionamiento del Timer 1 en modo CTC.
 * 
 */
static inline void TMR1_CTC_Stop()
{
	TCCR1B &= 0b11111000;
}

/**
 * @brief Establece el valor de contador del Timer 1 en modo CTC.
 * 
 * @param valueCounterA Valor de contador.
 */
static inline void TMR1_CTC_Set(uint16_t valueCounterA)
{
	OCR1A = valueCounterA;
}

#endif /* TMR1_H_ */
