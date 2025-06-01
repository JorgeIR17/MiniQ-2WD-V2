/**
 * @file hal_sensores.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso de los sensores IR
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_SENSORES_H_
#define HAL_SENSORES_H_

#include <avr/io.h>
#include "../LowLevel/sensores.h"

/**
 * @brief No se detecta la línea por ninguno de los sensores.
 * 
 *
 */
#define ERROR_LINEA 10
#define NADA 20

/**
 * @brief Inicialización de los sensores infrarrojos.
 * 
 * Inicializa los sensores IR y realiza una calibración para determinar los valores de blanco y negro.
 * 
 */
static inline void HAL_sensores_init()
{
    sensores_init();
	sensores_calibrar();
}


/**
 * @brief Calcula la posición del robot con respecto a la línea.
 * 
 * @return int8_t Posición del robot. Indica si se encuentra a la izquierda, derecha, centrado o no se detecta la línea.
 */
int8_t HAL_sensores_obtener_posicion();


/**
 * @brief Devuelve el valor leído por el sensor indicado.
 * 
 * @param sensor Sensor seleccionado mediante su ubicación en el robot.
 * @return uint16_t Valor leído por el sensor.
 */
uint16_t HAL_sensores_leer(uint8_t sensor);

#endif /* HAL_SENSORES_H_ */