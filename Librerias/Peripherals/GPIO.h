/**
 * @file GPIO.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de los GPIO del ATMega32U4.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GPIO_H_
#define GPIO_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "TMR4.h"

/**
 * @brief Inicializa el pin de la salida OC para usar el zumbador.
 * 
 */
static inline void OC_init()
{
    DDRB |= (1 << DDB2); // Pin MOSI (PB2) as output
}

/**
 * @brief Inicializa los pines del puente H para usar los motores.
 * 
 */
static inline void puenteH_init()
{
	DDRE |= (1<<EN2);
	DDRD |= (1<<EN1);
}

/**
 * @brief Inicializa los pines de los encoders.
 * 
 */
static inline void encoderpins_init() 
{
    DDRD &= ~((1 << PD0) | (1 << PD2));  // Configurar PD0 y PD2 como entrada
    PORTD |= (1 << PD0) | (1 << PD2);    // Activar pull-up interno

    EICRA |= (1 << ISC20) | (1 << ISC30); // Flanco de subida
    EIMSK |= (1 << INT2) | (1 << INT3);   // Habilitar INT2 y INT3
}

/**
 * @brief Inicializa el pin conectado al led RGB.
 * 
 */
static inline void rgb_pin_init()
{
	DDRB |= (1 << PB6);   // Configura el pin como salida
	PORTB &= ~(1 << PB6); // Pone en bajo inicialmente
}

/**
 * @brief Envía un bit al led RGB.
 * 
 * @param bit_value Valor del bit.
 */
void rgb_send_bit(uint8_t bit_value);

#endif /* GPIO_H_ */