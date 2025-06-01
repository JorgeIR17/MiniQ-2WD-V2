/**
 * @file hal_bateria.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso del medidor de batería
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_BATERIA_H_
#define HAL_BATERIA_H_

#include "../LowLevel/bateria.h"
#include "hal_ledrgb.h" // Para mostrar nivel de bateria

/**
 * @brief Inicializa el medidor de batería del robot.
 * 
 */
static inline void HAL_bateria_init()
{
	bateria_init();
}

/**
 * @brief Calcula el porcentaje de batería restante.
 * 
 * @return float Valor del porcentaje de batería.
 */
float HAL_bateria_porcentaje();

/**
 * @brief Muestra el valor del porcentaje de batería.
 * 
 * Esta función hace uso del led RGB para mostrar mediante colores la batería restante. Si se encuentra sobre el 40%, mostrará el color verde. 
 * Si se encuentra entre el 40% y el 15%, mostrará el color amarillo. Si el nivel se encuentra por debajo del 15%, el led parpadeará en color rojo.
 * 
 */
void HAL_bateria_mostrar_nivel();

#endif /* HAL_BATERIA_H_ */