/**
 * @file hal_bateria.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso del medidor de batería
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_bateria.h"

float HAL_bateria_porcentaje()
{
	return bateria_get_percentage();
}

void HAL_bateria_mostrar_nivel()
{
	float porcentaje = HAL_bateria_porcentaje();
	
	if(porcentaje > 40.0)		HAL_ledrgb_color(VERDE); // Si esta sobre el 40% se muestra luz verde
	else if(porcentaje < 15.0)	HAL_ledrgb_parpadeo(ROJO, 1000); // Si esta por debajo del 15%, la luz parpadea en color rojo
	else						HAL_ledrgb_color(AMARILLO); // Si esa entre el 15% y 40% se muestra luz amarilla
}
