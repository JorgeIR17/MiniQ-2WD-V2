/**
 * @file PULSADORES.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los pulsadores.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "PULSADORES.h"

uint16_t pulsadores_leer()
{
	uint16_t valor = ADC_Read_Single_Poll(ADC8);
	if(valor > 130 && valor < 570)			return 1;
	else if(valor >= 570 && valor < 720)	return 2;
	else if(valor >= 720 && valor < 1023)	return 3;
	else									return 0; // No se detecta ningun pulsador pulsado
}