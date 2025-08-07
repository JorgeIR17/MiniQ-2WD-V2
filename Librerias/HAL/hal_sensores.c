/**
 * @file hal_sensores.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los sensores IR
 * @version 1.0
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_sensores.h"

uint16_t HAL_sensores_leer(uint8_t sensor)
{
    return sensores_read(sensor);
}

uint8_t HAL_sensores_obtener_posicion()
{
    uint16_t centro = HAL_sensores_leer(CENTRO);
    uint16_t izquierda = HAL_sensores_leer(IZQUIERDA_CENTRO);
    uint16_t derecha = HAL_sensores_leer(DERECHA_CENTRO);

    if(centro <= negro && izquierda >= blanco && derecha >= blanco)     return LINEA_CENTRO;  // Robot centrado
    if(centro <= negro && izquierda <= negro)                           return LINEA_DERECHA_CENTRO;  // Robot un poco a la derecha
    if(centro <= negro && derecha <= negro)                             return LINEA_IZQUIERDA_CENTRO; // Robot un poco a la izquierda
    if(centro >= blanco && (izquierda <= negro || (derecha >= blanco && izquierda > negro)))                          return LINEA_DERECHA;  // Robot a la derecha
    if(centro >= blanco && (derecha <= negro || (izquierda >= blanco && derecha > negro)))                            return LINEA_IZQUIERDA; // Robot a la izquierda
    if(centro >= blanco && izquierda >= blanco && derecha >= blanco)    return ERROR_LINEA; // No se detecta la linea

    return NADA; 
}