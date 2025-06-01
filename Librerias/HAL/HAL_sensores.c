/**
 * @file hal_sensores.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los sensores IR
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_sensores.h"

int8_t HAL_sensores_obtener_posicion()
{
    uint16_t centro = HAL_sensores_leer(CENTRO);
    uint16_t izquierda = HAL_sensores_leer(IZQUIERDA_CENTRO);
    uint16_t derecha = HAL_sensores_leer(DERECHA_CENTRO);

    if(centro <= negro && izquierda >= blanco && derecha >= blanco)   return 0;  // Robot centrado
    if(centro <= negro && izquierda <= negro)                       return 1;  // Robot un poco a la derecha
    if(centro <= negro && derecha <= negro)                         return -1; // Robot un poco a la izquierda
    if(centro >= blanco && izquierda <= negro)                       return 2;  // Robot a la derecha
    if(centro >= blanco && derecha <= negro)                         return -2; // Robot a la izquierda
	if(centro >= blanco && izquierda >= blanco && derecha >= blanco)   return ERROR_LINEA; // No se detecta la linea

    return NADA; 
}

uint16_t HAL_sensores_leer(uint8_t sensor)
{
    return sensores_leer(sensor);
}