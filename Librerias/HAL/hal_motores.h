/**
 * @file hal_motores.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso de los motores
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_MOTORES_H_
#define HAL_MOTORES_H_

#include <avr/io.h>
#include "../LowLevel/motores.h"

/**
 * @brief Inicializa los motores del robot.
 * 
 */
static inline void HAL_motores_init()
{
    motores_init();
}

/**
 * @brief Gira las ruedas a una velocidad dada.
 * 
 * @param velocidad Velocidad de las ruedas. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, las ruedas girarán en sentido inverso.
 */
void HAL_motores_avanzar(int16_t velocidad);

/**
 * @brief Gira cada rueda a una velocidad distinta de manera independiente.
 * 
 * @param velocidad_izq Velocidad de la rueda izquierda. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, las ruedas girarán en sentido inverso.
 * @param velocidad_der Velocidad de la rueda derecha. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, las ruedas girarán en sentido inverso.
 */
void HAL_motores_girar(int16_t velocidad_izq, int16_t velocidad_der);

/**
 * @brief Detiene el movimiento de las ruedas.
 * 
 */
void HAL_motores_detener();

#endif /* HAL_MOTORES_H_ */