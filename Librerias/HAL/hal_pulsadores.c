/**
 * @file hal_pulsadores.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los pulsadores
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_pulsadores.h"

bool HAL_pulsadores_key_1()
{
	return (pulsadores_leer() == 1);
}

bool HAL_pulsadores_key_2()
{
	uint16_t valor = pulsadores_leer();
	return (valor == 2);
}

bool HAL_pulsadores_key_3()
{
	uint16_t valor = pulsadores_leer();
	return (valor == 3);
}
