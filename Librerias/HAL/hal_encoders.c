/**
 * @file hal_encoders.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los encoders
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_encoders.h"

uint16_t HAL_encoders_get_speed(uint8_t encoder)
{
	return encoder_get_speed(encoder);
}

uint16_t HAL_encoders_get_distance(uint8_t encoder)
{
	uint16_t pulsos = 0;
	if(encoder == ENCODER_IZQUIERDO)
		pulsos = encoder_leer(ENCODER_IZQUIERDO);
	else
		pulsos = encoder_leer(ENCODER_DERECHO);	
	return pulsos * MM_POR_PULSO;
}

void HAL_encoders_reset(uint8_t encoder)
{
	encoder_reset(encoder);
}