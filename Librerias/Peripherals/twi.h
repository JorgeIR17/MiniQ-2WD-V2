/**
 * @file twi.h
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del protocolo TWI (I2C) del ATMega32U4.
 * @version 1.0
 * @date 2025-06-05
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef TWI_H_
#define TWI_H_

#include <avr/io.h>

/**
 * @brief Inicializa el hardware TWI (I2C) del ATmega32U4 a ~100 kHz.
 *
 * Fórmula: SCL_freq = F_CPU / (16 + 2 * TWBR * prescaler)
 */
static inline void TWI_Init()
{
    TWSR = 0x00;      // Prescaler = 1 (TWPS = 00)
    TWBR = 72;        // ~100 kHz a 16 MHz
}


/**
 * @brief Inicia una condicion START en el bus I2C.
 *
 * Espera hasta que se complete el bit TWINT para asegurar que la condicion START fue enviada.
 */
static inline void TWI_Start()
{
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);  // Solicita START
    while (!(TWCR & (1 << TWINT)));                    // Espera a que se complete
}


/**
 * @brief Envia una condicion STOP en el bus I2C.
 *
 * Libera el bus y espera a que el bit TWSTO se borre automaticamente.
 */
static inline void TWI_Stop()
{
    TWCR = (1 << TWSTO) | (1 << TWINT) | (1 << TWEN);  // Solicita STOP
    while (TWCR & (1 << TWSTO));                       // Espera hasta que STOP se complete
}


/**
 * @brief Escribe un byte en el bus I2C y espera la confirmacion.
 *
 * @param data Byte a transmitir
 */
static inline void TWI_Write(uint8_t data)
{
    TWDR = data;                         // Carga el dato en el registro
    TWCR = (1 << TWEN) | (1 << TWINT);   // Inicia transmision
    while (!(TWCR & (1 << TWINT)));      // Espera a que se complete
}

/**
 * @brief Lee un byte del bus I2C y envia ACK al esclavo.
 *
 * @return Byte recibido
 */
static inline uint8_t TWI_Read_ACK()
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);  // Habilita recepcion + ACK
    while (!(TWCR & (1 << TWINT)));                  // Espera al dato
    return TWDR;                                     // Devuelve el byte recibido
}


/**
 * @brief Lee el ultimo byte del bus I2C sin enviar ACK.
 *
 * Usado para el ultimo byte de una transmision de lectura.
 *
 * @return Byte recibido
 */
static inline uint8_t TWI_Read_NACK()
{
    TWCR = (1 << TWEN) | (1 << TWINT);   // Habilita recepcion sin ACK
    while (!(TWCR & (1 << TWINT)));      // Espera al dato
    return TWDR;
}



#endif /* TWI_H_ */