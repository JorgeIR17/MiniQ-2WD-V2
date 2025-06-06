/**
 * @file hal_brujula.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de la brujula HMC5883L (QMC5883L)
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_brujula.h"


void HAL_brujula_leer_ejes(int16_t* x, int16_t* y, int16_t* z)
{
    brujula_leer(x, y, z);
}
