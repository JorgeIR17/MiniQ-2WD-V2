/**
 * @file bateria.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso del medidor de batería.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef BATERIA_H_
#define BATERIA_H_

#include "../Peripherals/adc.h"

/**
 * @brief Canal de ADC del medidor de batería.
 * 
 */
#define BATTERY_CHANNEL ADC12

/**
 * @brief Voltaje de referencia
 * 
 */
#define VREF 5.0
/**
 * @brief Relación del divisor resistivo.
 * 
 */
#define DIVISOR_RATIO (3.0 / 2.0)
/**
 * @brief Valor máximo de batería.
 * 
 */
#define BATTERY_MAX 6.0
/**
 * @brief Valor mínimo de batería.
 * 
 */
#define BATTERY_MIN 4.4

/**
 * @brief Inicializa el medidor de batería.
 * 
 */
static inline void bateria_init()
{
	ADC_Init();
}

/**
 * @brief Calcula el valor de voltaje leído por el medidor de batería.
 * 
 * @return float Valor de voltaje recibido.
 */
float bateria_get_voltage();

/**
 * @brief Calcula el porcentaje de batería restante.
 * 
 * @return float Porcentaje de batería.
 */
float bateria_get_percentage();

#endif /* BATERIA_H_ */