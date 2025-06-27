/**
 * @file recorrerdistancia.c
 * @author Jorge Ibáñez
 * @brief Ejemplo de uso del MiniQ 2WD mediante recorrido de distancia
 * @version 0.1
 * @date 2025-06-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * En este programa se realiza un desplazamiento de una longitud en línea recta en ambos sentidos, la cual irá aumentando linealmente.
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/hal_motores.h"
#include "../HAL/hal_encoders.h"



int main(void)
{
	// Inicializamos los componentes
	HAL_encoders_init();
	HAL_motores_init();
	
	_delay_ms(3000);

	uint8_t sentido = 1; // 1 -> adelante / 0 -> atras
	uint16_t distancia = 100; // Inicialmente 100 mm
	
	while(1)
	{
		if (distancia > 1000) distancia = 100; // La maxima distancia recorrida sera de 1 metro
		
		if (sentido == 1) // Desplazamiento hacia delante
		{
			HAL_motores_avanzar(70);
			uint16_t dist_i = HAL_encoders_get_distance(ENCODER_IZQUIERDO);
			uint16_t dist_d = HAL_encoders_get_distance(ENCODER_DERECHO);
			
			if(dist_i >= distancia && dist_d >= distancia) // Al alcanzar la distancia, se reinicia
			{
				HAL_motores_detener();
				HAL_encoders_reset(ENCODER_IZQUIERDO);
				HAL_encoders_reset(ENCODER_DERECHO);
				sentido = 0; // Cambio de sentido
			}
		}

		else // Desplazamiento hacia atras
		{
			HAL_motores_avanzar(-70);
			uint16_t dist_i = HAL_encoders_get_distance(ENCODER_IZQUIERDO);
			uint16_t dist_d = HAL_encoders_get_distance(ENCODER_DERECHO);
			
			if(dist_i >= distancia && dist_d >= distancia) // Al alcanzar la distancia, se reinicia
			{
				HAL_motores_detener();
				HAL_encoders_reset(ENCODER_IZQUIERDO);
				HAL_encoders_reset(ENCODER_DERECHO);
				sentido = 1; // Cambio de sentido
				distancia += 100; // Al recorrer en ambos sentidos, se aumenta la distancia a recorrer en 100 mm
			}
		}

		_delay_ms(15);
	}	
	
}
