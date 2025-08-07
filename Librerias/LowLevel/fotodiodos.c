/**
 * @file fotodiodos.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de diodos fotosensibles.
 * @version 1.0
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "fotodiodos.h"


uint8_t fotodiodos_position()
{
	uint16_t valor = ADC_Read_Single_Poll(PHOTODIODE_CHANNEL);
	if(valor > 970)							return 1; // Luz a la derecha
	else if(valor <= 300 && valor > 100)	return 2; // Luz delante
	else if(valor < 45)						return 3; // Luz a la izquierda
	else									return 0; // Ausencia de luz
}