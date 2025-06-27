/**
 * @file sigueluz.c
 * @author Jorge Ibáñez
 * @brief Ejemplo de uso del MiniQ 2WD como robot seguidor de luz
 * @version 0.1
 * @date 2025-06-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * En este programa el robot se comportará como un seguidor de luz, avanzando hacia la dirección en la que se encuentre. En caso de no detectar ningún haz
 * de luz, el robot se detendrá. El estado se representará mediante el color del led RGB.
 * 
 * - Verde: Luz delante.
 * - Azul: Luz a la derecha.
 * - Rojo: Luz a la izquierda.
 * - Amarillo: Ausencia de luz.
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/hal_motores.h"
#include "../HAL/hal_ledrgb.h"
#include "../HAL/hal_fotodiodos.h"


int main(void)
{
	HAL_ledrgb_init();
	HAL_fotodiodos_init();
	HAL_motores_init();
		
	_delay_ms(3000);
	
	while(1)
	{
		if(HAL_fotodiodos_posicion() == LUZ_CENTRO)
		{ 
			HAL_motores_avanzar(80);
			HAL_ledrgb_color(VERDE);
		}
		
		if(HAL_fotodiodos_posicion() == LUZ_DERECHA) 
		{
			HAL_motores_girar(100, 60);
			HAL_ledrgb_color(AZUL);
		}
	
		if(HAL_fotodiodos_posicion() == LUZ_IZQUIERDA)
		{
			HAL_motores_girar(60, 100);
			HAL_ledrgb_color(ROJO);
		}
		if(HAL_fotodiodos_posicion() == LUZ_ERROR)
		{ 
			HAL_motores_detener();
			HAL_ledrgb_color(AMARILLO);
		}
		
		_delay_ms(15);
	}
}