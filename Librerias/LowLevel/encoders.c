/**
 * @file encoders.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los encoders.
 * @version 1.0
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "encoders.h"

uint16_t encoder_read(uint8_t encoder) 
{
    if (encoder == ENCODER_IZQUIERDO)   return pulsos_izq;     // Encoder izquierdo
    if (encoder == ENCODER_DERECHO)     return pulsos_der;     // Encoder derecho
	
    return 0;
}

uint16_t encoder_get_speed(uint8_t encoder) 
{
    if (encoder == ENCODER_IZQUIERDO)   return rpm_izq;       // Encoder izquierdo
    if (encoder == ENCODER_DERECHO)     return rpm_der;            // Encoder derecho
	
    return 0;
}

void encoder_reset(uint8_t encoder)
{
    if (encoder == ENCODER_IZQUIERDO) pulsos_izq = 0;
    if (encoder == ENCODER_DERECHO)   pulsos_der = 0;
}