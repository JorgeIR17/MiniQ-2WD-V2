/**
 * @file TMR0.c
 * @author Jorge Ibáñez
 * @brief Definición de la interrupción ejecutada por el Timer 0 del ATMega32U4.
 * @version 0.1
 * @date 2025-05-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TMR0.h"

/**
 * @brief Interrupción del Timer 0.
 * 
 * Esta interrupción se encarga de alternar el valor del pin conectado al zumbador del robot, permitiendo emitir sonido a una frecuencia dada.
 * 
 */
ISR(TIMER0_COMPA_vect)
{
	PORTB ^= (1<<PORTB2);
}