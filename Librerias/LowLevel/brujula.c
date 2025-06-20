/**
 * @file brujula.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de la brujula HMC5883L.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "brujula.h"

void brujula_leer(int16_t* x, int16_t* y, int16_t* z)
{
    TWI_Start();
    TWI_Write(HMC5883_ADDR << 1);
    TWI_Write(0x03); // Registro de datos (X_MSB)
    TWI_Stop();

    TWI_Start();
    TWI_Write((HMC5883_ADDR << 1) | 1); // Lectura

    uint8_t xh = TWI_Read_ACK();
    uint8_t xl = TWI_Read_ACK();
    uint8_t zh = TWI_Read_ACK();
    uint8_t zl = TWI_Read_ACK();
    uint8_t yh = TWI_Read_ACK();
    uint8_t yl = TWI_Read_NACK();

    TWI_Stop();

    *x = (int16_t)((xh << 8) | xl);
    *y = (int16_t)((yh << 8) | yl);
    *z = (int16_t)((zh << 8) | zl);
}
