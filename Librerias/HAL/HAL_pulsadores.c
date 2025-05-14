/**
 * @file HAL_pulsadores.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los pulsadores
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "HAL_pulsadores.h"

bool HAL_pulsadores_key_1()
{
	uint16_t valor = pulsadores_leer();
	return (valor == 1);
}

bool HAL_pulsadornes_key_2()
{
	uint16_t valor = pulsadores_leer();
	return (valor == 2);
}

bool HAL_botones_key_3()
{
	uint16_t valor = pulsadores_leer();
	return (valor == 3);
}
