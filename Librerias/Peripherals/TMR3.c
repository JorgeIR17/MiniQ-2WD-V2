/**
 * @file TMR3.c
 * @author Jorge Ibáñez
 * @brief Definición de las interrupciones ejecutadas por el Timer 3 del ATMega32U4.
 * @version 0.1
 * @date 2025-05-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "TMR3.h"

/**
 * @brief Interrupción del encoder izquierdo.
 * 
 * Incrementa el contador de pulsos del encoder izquierdo.
 * 
 */
ISR(INT2_vect) { pulsos_der++; }

/**
 * @brief Interrupción del encoder derecho.
 * 
 * Incrementa el contador de pulsos del encoder derecho.
 * 
 */
ISR(INT3_vect) { pulsos_izq++; }

/**
 * @brief Interrupción del Timer 3.
 * 
 * Determina las velocidades de las ruedas en RPM y alterna el valor de parpadeo del led RGB.
 * 
 */
ISR(TIMER3_COMPA_vect) 
{
    rpm_izq = ((uint32_t)pulsos_izq * 600) / (PULSOS_POR_VUELTA * interval_izq); // uint32_t para evitar overflow
    rpm_der = ((uint32_t)pulsos_der * 600) / (PULSOS_POR_VUELTA * interval_der); // uint32_t para evitar overflow
	interval_izq++;
	interval_der++;
	
	blink = !(blink);
}