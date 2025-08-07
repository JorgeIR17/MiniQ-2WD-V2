/**
 * @file hal_receptor.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso de los transmisores y el receptor IR (IRM8881T).
 * @version 1.0
 * @date 2025-06-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef HAL_RECEPTOR_H_
#define HAL_RECEPTOR_H_

#include "../LowLevel/receptor.h"
#include <stdlib.h>

// Posiciones de obstaculos
#define OBS_NADA      0
#define OBS_DERECHA   1
#define OBS_IZQUIERDA 2
#define OBS_DELANTE   3

/**
 * @brief Inicializa los transmisores y el receptor IR.
 * 
 */
static inline void HAL_receptor_init()
{
	receptor_init();
}

/**
 * @brief Detecta los obstáculos presentes cercanos al robot.
 * 
 * @param contR Contador de obstáculos a la derecha. En caso de querer almacenar el resultado, indicar un valor numérico. En caso contrario, indicar el valor NULL.
 * @param contL Contador de obstáculos a la izquierda. En caso de querer almacenar el resultado, indicar un valor numérico. En caso contrario, indicar el valor NULL.
 * @return uint8_t Posición del obstáculo. Los posibles valores son:
 * - OBS_NADA: No hay obstáculos a la vista.
 * - OBS_DERECHA: Hay un obstáculo a la derecha del robot.
 * - OBS_IZQUIERDA: Hay un obstáculo a la izquierda del robot.
 * - OBS_DELANTE: Hay un obstáculo justo delante del robot.
 */
uint8_t HAL_receptor_detectar_obstaculo(uint8_t* contR, uint8_t* contL);

#endif /* HAL_RECEPTOR_H_ */