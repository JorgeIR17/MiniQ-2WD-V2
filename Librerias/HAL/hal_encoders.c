/**
 * @file hal_encoders.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los encoders
 * @version 1.0
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_encoders.h"

uint16_t HAL_encoders_obtener_velocidad(uint8_t encoder)
{
	return encoder_get_speed(encoder);
}

uint16_t HAL_encoders_obtener_distancia(uint8_t encoder)
{
	uint16_t pulsos = 0;
	if(encoder == ENCODER_IZQUIERDO)
		pulsos = encoder_read(ENCODER_IZQUIERDO);
	if(encoder == ENCODER_DERECHO)
		pulsos = encoder_read(ENCODER_DERECHO);	
	return pulsos * MM_POR_PULSO;
}

void HAL_encoders_reiniciar(uint8_t encoder)
{
	encoder_reset(encoder);
}