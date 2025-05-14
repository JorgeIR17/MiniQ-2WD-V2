/**
 * @file HAL_pulsadores.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso de los pulsadores
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_PULSADORES_H_
#define HAL_PULSADORES_H_

#include "../LowLevel/PULSADORES.h"
#include <stdbool.h>

/**
 * @brief Inicializa los pulsadores del robot.
 * 
 */
static inline void HAL_pulsadores_init()
{
	pulsadores_init();
}

/**
 * @brief Comprueba si se ha presionado el pulsador KEY1.
 * 
 * @return true 
 * @return false 
 */
bool HAL_pulsadores_key_1();

/**
 * @brief Comprueba si se ha presionado el pulsador KEY2.
 * 
 * @return true 
 * @return false 
 */
bool HAL_pulsadores_key_2();

/**
 * @brief Comprueba si se ha presionado el pulsador KEY3.
 * 
 * @return true 
 * @return false 
 */
bool HAL_pulsadores_key_3();

#endif /* HAL_PULSADORES_H_ */