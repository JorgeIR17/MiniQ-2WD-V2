/**
 * @file botonesled.c
 * @author Jorge Ibáñez
 * @brief Ejemplo de uso del MiniQ 2WD mediante muestra de efectos del led RGB con activación a través de los pulsadores
 * @version 0.1
 * @date 2025-06-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * En este programa se muestran los distintos efectos del led RGB según el pulsador presionado
 * - KEY1: Efecto arcoiris
 * - KEY2: Efecto breathing (respiración) en color rojo
 * - KEY3: Efecto de parpadeo en color amarillo
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/hal_ledrgb.h"
#include "../HAL/hal_pulsadores.h"


int main(void)
{
	HAL_ledrgb_init();
	HAL_pulsadores_init();
	
	while(1)
	{
		if(HAL_pulsadores_key_1()) HAL_ledrgb_efecto_arcoiris(5000);
		else if(HAL_pulsadores_key_2()) HAL_ledrgb_efecto_breathing(ROJO, 100, 5000);
		else if(HAL_pulsadores_key_3()) HAL_ledrgb_parpadeo(AMARILLO, 2000);
		else HAL_ledrgb_apagar();
	}
}