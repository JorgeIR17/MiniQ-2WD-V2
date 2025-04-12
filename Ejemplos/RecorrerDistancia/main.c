#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Librerias/HAL/HAL_motores.h"
#include "Librerias/HAL/HAL_encoders.h"



int main(void)
{
	HAL_encoders_init();
	HAL_motores_init();
	
	while(1)
	{
		HAL_motores_avanzar(40);
		uint16_t dist_i = HAL_encoders_get_distance(ENCODER_IZQUIERDO);
		uint16_t dist_d = HAL_encoders_get_distance(ENCODER_DERECHO);
		
		if(dist_i >= 500.0 && dist_d >= 500.0)
			HAL_motores_detener();		
	}	
	
}
