/**
 * @file fotodiodos.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de diodos fotosensibles.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FOTODIODOS_H_
#define FOTODIODOS_H_

#include "../Peripherals/adc.h"

/**
 * @brief Canal de ADC de los fotodiodos.
 * 
 */
#define PHOTODIODE_CHANNEL 0

/**
 * @brief Inicializa los fotodiodos.
 * 
 */
static inline void fotodiodos_init()
{
	ADC_Init();
}

/**
 * @brief Determina la posición de la luz con respecto al robot.
 * 
 * @return uint8_t Posición de la luz.
 * · 1: Luz a la derecha
 * · 2: Luz delante.
 * · 3: Luz a la izquierda.
 * · 4: Ausencia de luz.
 */
uint8_t fotodiodos_obtener_posicion();

#endif /* FOTODIODOS_H_ */

// > 980 -> derecha
// < 900 && > 150 -> recto
// < 45 -> izquierda
// resto -> stop