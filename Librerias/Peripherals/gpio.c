/**
 * @file gpio.h
 * @author Jorge Ibáñez
 * @brief Definición de las interrupciones de cambio de pin (PCINT) del ATMega32U4.
 * @version 0.1
 * @date 2025-06-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "gpio.h"

/**
 * @brief Interrupción externa del receptor IR.
 * 
 * Incrementa el contador de pulsos del receptor IR.
 * 
 */
ISR(PCINT0_vect)
{
	cont_obs++;
}

/**
 * @brief Interrupción del encoder izquierdo.
 * 
 * Incrementa el contador de pulsos del encoder izquierdo.
 * 
 */
ISR(INT2_vect) 
{ 
	pulsos_der++; 
	pulsos_rpm_der++;
}

/**
 * @brief Interrupción del encoder derecho.
 * 
 * Incrementa el contador de pulsos del encoder derecho.
 * 
 */
ISR(INT3_vect) 
{ 
	pulsos_izq++; 
	pulsos_rpm_izq++;
}