/**
 * @file hal_brujula.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso de la brujula HMC5883L (QMC5883L)
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef HAL_BRUJULA_H_
#define HAL_BRUJULA_H_

#include "../LowLevel/brujula.h"

/**
 * @brief Inicializa el HMC5883L (QMC5883L).
 * 
 */
static inline void HAL_brujula_init()
{
	brujula_init();	
}


/**
 * @brief Lee los valores de los tres ejes del magnetómetro HMC5883L (QMC5833L).
 *
 *
 * @param[out] x Puntero donde se guardará el valor del eje X
 * @param[out] y Puntero donde se guardará el valor del eje Y
 * @param[out] z Puntero donde se guardará el valor del eje Z
 */
void HAL_brujula_leer_ejes(int16_t* x, int16_t* y, int16_t* z);



#endif /* HAL_BRUJULA_H_ */