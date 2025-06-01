/**
 * @file encoders.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los encoders.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "encoders.h"

uint16_t encoder_leer(uint8_t encoder) 
{
    if (encoder == ENCODER_IZQUIERDO) return pulsos_izq;  // Encoder izquierdo
    else return pulsos_der;               // Encoder derecho
}

uint16_t encoder_get_speed(uint8_t encoder) 
{
    if (encoder == ENCODER_IZQUIERDO) return rpm_izq;  // Encoder izquierdo
    else return rpm_der;               // Encoder derecho
}

void encoder_reset(uint8_t encoder)
{
    if (encoder == ENCODER_IZQUIERDO)
	{ 
		pulsos_izq = 0;
		interval_izq = 0;
	}
    else
	{
		pulsos_der = 0;
		interval_der = 0;
	}
}