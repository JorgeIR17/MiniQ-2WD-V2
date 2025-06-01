/**
 * @file hal_zumbador.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso del zumbador
 * @version 0.1
 * @date 2025-05-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_ZUMBADOR_H_
#define HAL_ZUMBADOR_H_

#include <avr/io.h>
#include "../LowLevel/buzzer.h"


#define INICIO 1
#define ACIERTO 2
#define ERROR 3

/**
 * @brief Inicialización del zumbador.
 * 
 * Inicializa el zumbador del robot.
 * 
 */
static inline void HAL_zumbador_init()
{
    buzzer_init();
}

/**
 * @brief Emite una alerta.
 * 
 * Esta función emite un sonido con una frecuencia y duración determinadas según el valor del parámetro dado, siendo sus posibles valores las macros proporcionadas.
 * 
 * @param tipo Tipo de alerta. Es necesario hacer uso de las macros proporcionadas.
 */
void HAL_zumbador_alerta(uint8_t tipo);

/**
 * @brief Detiene el funcionamiento del zumbador.
 * 
 * Detiene cualquier sonido emitido por el zumbador.
 * 
 */
void HAL_zumbador_detener();

#endif /* HAL_ZUMBADOR_H_ */