/**
 * @file HAL_bateria.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso del medidor de batería
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "HAL_bateria.h"

float HAL_bateria_porcentaje()
{
	return bateria_get_percentage();
}

void HAL_bateria_mostrar_nivel()
{
	float porcentaje = HAL_bateria_porcentaje();
	
	if(porcentaje >= 40.0)		HAL_ledrgb_color(VERDE);
	else if(porcentaje < 15.0)	HAL_ledrgb_parpadeo(ROJO, 1000);
	else						HAL_ledrgb_color(AMARILLO);
}
