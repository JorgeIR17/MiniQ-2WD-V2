/**
 * @file brujula.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de la brujula HMC5883L.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef BRUJULA_H_
#define BRUJULA_H_

#define HMC5883_ADDR  0x1E  // Dirección I2C del HMC5883L

#include "../Peripherals/twi.h"

/**
 * @brief Configura el HMC5883L en modo de medición continua.
 *
 */
static inline void brujula_init(void)
{
    TWI_Init();

    // Configuración: Registro A (0x00)
    TWI_Start();
    TWI_Write(HMC5883_ADDR << 1);
    TWI_Write(0x00);       // Registro A
    TWI_Write(0x70);       // 8 muestras promediadas, 15 Hz, modo normal
    TWI_Stop();

    // Configuración: Registro B (0x01)
    TWI_Start();
    TWI_Write(HMC5883_ADDR << 1);
    TWI_Write(0x01);       // Registro B
    TWI_Write(0x20);       // Ganancia = 1.3 Ga (default)
    TWI_Stop();

    // Configuración: Modo (0x02)
    TWI_Start();
    TWI_Write(HMC5883_ADDR << 1);
    TWI_Write(0x02);       // Registro de modo
    TWI_Write(0x00);       // Modo continuo
    TWI_Stop();
}

/**
 * @brief Lee los datos de los tres ejes del magnetómetro HMC5883L.
 *
 * Se leen 6 bytes a partir del registro 0x03: X_MSB, X_LSB, Z_MSB, Z_LSB, Y_MSB, Y_LSB.
 *
 * @param[out] x Valor del eje X
 * @param[out] y Valor del eje Y
 * @param[out] z Valor del eje Z
 */
void brujula_leer(int16_t* x, int16_t* y, int16_t* z);



#endif /* BRUJULA_H_ */