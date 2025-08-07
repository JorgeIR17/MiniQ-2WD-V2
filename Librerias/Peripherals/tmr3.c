/**
 * @file tmr3.c
 * @author Jorge Ibáñez
 * @brief Definición de la interrupción ejecutada por el Timer 3 del ATMega32U4.
 * @version 1.0
 * @date 2025-05-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "tmr3.h"

/**
 * @brief Interrupción del Timer 3.
 * 
 * Determina las velocidades de las ruedas en RPM y alterna el valor y duración del parpadeo del led RGB.
 * 
 */
ISR(TIMER3_COMPA_vect) 
{
    rpm_izq = (pulsos_rpm_izq * 600) / (PULSOS_POR_VUELTA * 1);
    rpm_der = (pulsos_rpm_der * 600) / (PULSOS_POR_VUELTA * 1);
    pulsos_rpm_izq = 0;
	pulsos_rpm_der = 0;
	
	blink = (!blink); // Alterna parpadeo del led

	
	blink_time = blink_time - 100;
}