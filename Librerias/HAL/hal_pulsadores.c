/**
 * @file hal_pulsadores.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los pulsadores
 * @version 1.0
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_pulsadores.h"

bool HAL_pulsadores_key_1()
{
	return (pulsadores_read() == 1);
}

bool HAL_pulsadores_key_2()
{
	return (pulsadores_read() == 2);
}

bool HAL_pulsadores_key_3()
{
	return (pulsadores_read() == 3);
}
