/**
 * @file hal_fotodiodos.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los diodos fotosensibles.
 * @version 1.0
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_fotodiodos.h"

uint8_t HAL_fotodiodos_posicion()
{
	return fotodiodos_position();
}