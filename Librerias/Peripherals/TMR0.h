/**
 * @file TMR0.h
 * @author Jorge Ibáñez
 * @brief Definición de funciones para usar el Timer 0 del ATMega32U4.
 * @version 0.1
 * @date 2025-05-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TMR0_H_
#define TMR0_H_

#include <avr/io.h>
#include <avr/interrupt.h>

// Divisores de frecuencia de reloj
#define DIV_CLK_1       1
#define DIV_CLK_8       2
#define DIV_CLK_64      3
#define DIV_CLK_256     4
#define DIV_CLK_1024    5

/**
 * @brief Inicializa el Timer 0 en modo CTC.
 * 
 */
static inline void TMR0_CTC_Init()
{
	TCCR0B &= ~(1<<WGM02);
	TCCR0A |= (1<<WGM01);
	TCCR0A &= (~(1<<WGM00));
}

/**
 * @brief Activa las interrupciones del Timer 0 en modo CTC.
 * 
 */
static inline void TMR0_CTC_enaInterrupt()
{
	TIMSK0 |= (1<<OCIE0A);
}

/**
 * @brief Desactiva las interrupciones del Timer 0 en modo CTC.
 * 
 */
static inline void TMR0_CTC_disInterrupt()
{
	TIMSK0 &= ~(1<<OCIE0A);
}

/**
 * @brief Inicia el Timer 0 en modo CTC.
 * 
 * @param divClock Divisor de frecuencia. Es necesario hacer uso de las macros proporcionadas.
 */
static inline void TMR0_CTC_Start(uint8_t divClock)
{
	TCNT0 = 0;
	TCCR0B &= 0b11111000;
	TCCR0B |= (divClock << CS00);
}

/**
 * @brief Detiene el funcionamiento del Timer 0 en modo CTC.
 * 
 */
static inline void TMR0_CTC_Stop()
{
	TCCR0B &= 0b11111000;
}

/**
 * @brief Establece el valor de contador del Timer 0 en modo CTC.
 * 
 * @param valueCounterA Valor de contador.
 */
static inline void TMR0_CTC_Set(uint8_t valueCounterA)
{
	OCR0A = valueCounterA;
}

#endif /* TMR0_H_ */