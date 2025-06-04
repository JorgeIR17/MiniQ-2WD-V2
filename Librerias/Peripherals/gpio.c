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
 * @brief Incrementa el contador de pulsos del receptor IR.
 * 
 */
ISR(PCINT0_vect)
{
	cont_obs++;
}