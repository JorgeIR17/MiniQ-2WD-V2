/**
 * @file brujula.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de la brujula HMC5883L (QMC5883L).
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef BRUJULA_H_
#define BRUJULA_H_

#define HMC5883_ADDR  0x0D  // Dirección I2C del HMC5883L (QMC5883L)

#include "../Peripherals/TWI.h"

/**
 * @brief Configura el HMC5883L (QMC5883L) en modo de medición continua.
 *
 * Envía dos bytes al sensor:
 *  - Registro 0x02 (modo)
 *  - Valor 0x00 (modo continuo)
 */
static inline void brujula_init(void)
{
	TWI_Init();

	// Registro 0x0B: Reset del sensor
	TWI_Start();
	TWI_Write(HMC5883_ADDR << 1);
	TWI_Write(0x0B);
	TWI_Write(0x01); // Reset
	TWI_Stop();

	// Registro 0x09: Control: modo continuo, 200 Hz, 8G, 16-bit
	TWI_Start();
	TWI_Write(HMC5883_ADDR << 1);
	TWI_Write(0x09);
	TWI_Write(0b00011101); // CONTINUOUS | ODR=200Hz | RNG=8G | OSR=512
	TWI_Stop();
}

/**
 * @brief Lee los datos de los tres ejes del magnetómetro HMC5883L (QMC5883L).
 *
 * Se leen 6 bytes a partir del registro 0x03: X_MSB, X_LSB, Z_MSB, Z_LSB, Y_MSB, Y_LSB.
 *
 * @param[out] x Valor del eje X
 * @param[out] y Valor del eje Y
 * @param[out] z Valor del eje Z
 */
void brujula_leer(int16_t* x, int16_t* y, int16_t* z);



#endif /* BRUJULA_H_ */