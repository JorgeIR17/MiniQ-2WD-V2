/**
 * @file HAL_encoders.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso de los encoders
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_ENCODERS_H_
#define HAL_ENCODERS_H_

#include "../LowLevel/ENCODERS.h"

#define DIAMETRO_RUEDA_MM 42.0
#define PI 3.1416               // Valor de pi
#define MM_POR_PULSO 5.28

/**
 * @brief Inicializa los encoders.
 * 
 */
static inline void HAL_encoders_init()
{
	encoders_init();
}

/**
 * @brief Calcula la velocidad de una rueda.
 * 
 * @param encoder Encoder derecho o izquierdo. Es necesario hacer uso de las macros proporcionadas.
 * @return uint16_t Valor de velocidad en RPM.
 */
uint16_t HAL_encoders_get_speed(uint8_t encoder);

/**
 * @brief Calcula la distancia recorrida por una rueda.
 * 
 * @param encoder Encoder derecho o izquierdo. Es necesario hacer uso de las macros proporcionadas.
 * @return uint16_t Valor de distancia en milímetros.
 */
uint16_t HAL_encoders_get_distance(uint8_t encoder);

/**
 * @brief Reinicia el contador de pulsos de un encoder.
 * 
 * @param encoder Encoder derecho o izquierdo. Es necesario hacer uso de las macros proporcionadas.
 */
void HAL_encoders_reset(uint8_t encoder);

#endif /* HAL_ENCODERS_H_ */