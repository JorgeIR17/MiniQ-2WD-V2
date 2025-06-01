/**
 * @file pulsadores.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de los pulsadores.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef PULSADORES_H_
#define PULSADORES_H_

#include "../Peripherals/adc.h"

/**
 * @brief Inicializa los pulsadores.
 * 
 */
static inline void pulsadores_init()
{
	ADC_init();
}

/**
 * @brief Realiza una lectura de los pulsadores.
 * 
 * Si se ha presionado KEY1, la función devuelve el valor 1.
 * Si se ha presionado KEY2, la función devuelve el valor 2.
 * Si se ha presionado KEY3, la función devuelve el valor 3.
 * En caso contrario, la función devuelve el valor 0.
 * 
 * @return uint16_t Pulsador presionado.
 */
uint16_t pulsadores_leer();

#endif /* PULSADORES_H_ */