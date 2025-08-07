/**
 * @file hal_fotodiodos.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso de los diodos fotosensibles.
 * @version 1.0
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_FOTODIODOS_H_
#define HAL_FOTODIODOS_H_

#include "../LowLevel/fotodiodos.h"

// Posiciones de luz
#define LUZ_ERROR		0
#define LUZ_DERECHA		1
#define LUZ_CENTRO		2
#define LUZ_IZQUIERDA	3

/**
 * @brief Inicializa los diodos fotosensibles.
 * 
 */
static inline void HAL_fotodiodos_init()
{
	fotodiodos_init();
}

/**
 * @brief Indica en qué posición se encuentra la luz.
 * 
 * @return uint8_t Posición de la luz. El valor devuelto debe ser igual a una de las macros proporcionadas.
 */
uint8_t HAL_fotodiodos_posicion();


#endif /* HAL_FOTODIODOS_H_ */