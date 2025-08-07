/**
 * @file gpio.h
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los GPIO del ATMega32U4.
 * @version 1.0
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>

// Modo pin
#define INPUT 0
#define OUTPUT 1

// Valor pin
#define LOW 0
#define HIGH 1

// Estado Pullup
#define OFF 0
#define ON 1

// Modos de interrupcion
#define FALLING_EDGE 1
#define RISING_EDGE 2

// Encoders
#define PULSOS_POR_VUELTA 25    // 25 pulsos

volatile uint16_t pulsos_izq;
volatile uint16_t pulsos_der;
volatile uint16_t pulsos_rpm_izq;
volatile uint16_t pulsos_rpm_der;
volatile uint16_t rpm_izq;
volatile uint16_t rpm_der;

// LED RGB
volatile bool blink;
volatile uint16_t blink_time;

// Transmisores y Receptor IR (IRM8881T)
volatile uint8_t cont_obs;


/**
 * @brief Configura la dirección de un pin (entrada o salida).
 *
 * @param ddr Puntero al registro DDRx (por ejemplo &DDRB)
 * @param pin Número de pin (0–7)
 * @param direction Configuración como entrada o salida. Es necesario hacer uso de las macros proporcionadas
 */
static inline void GPIO_Init(volatile uint8_t* ddr, uint8_t pin, uint8_t direction) 
{
    if (direction == OUTPUT) 
    {
        *ddr |= (1 << pin);  // Output
    } 
    else 
    {
        *ddr &= ~(1 << pin); // Input
    }
}

/**
 * @brief Escribe un valor lógico en un pin de salida.
 *
 * @param port Puntero al registro PORTx (por ejemplo &PORTB)
 * @param pin Número de pin (0–7)
 * @param value Valor a escribir. Es necesario hacer uso de las macros proporcionadas, o usar exclusivamente los valores 0 o 1
 */
static inline void GPIO_Write(volatile uint8_t* port, uint8_t pin, uint8_t value) 
{
    if (value) 
        *port |= (1 << pin);   // HIGH
    else 
        *port &= ~(1 << pin);  // LOW
}

/**
 * @brief Lee el valor lógico actual de un pin.
 *
 * @param pin_reg Puntero al registro PINx (por ejemplo &PINB)
 * @param pin Número de pin (0–7)
 * @return 1 o HIGH si el pin está en HIGH, 0 o LOW si está en LOW
 */
static inline uint8_t GPIO_Read(volatile uint8_t* pin_reg, uint8_t pin) 
{
    return (*pin_reg & (1 << pin)) != 0;
}

/**
 * @brief Alterna el valor lógico de un pin de salida.
 *
 * Esta función alterna el estado del pin indicado: si está en HIGH, lo cambia a LOW, y viceversa.
 *
 * @param port Puntero al registro PORTx (por ejemplo &PORTB)
 * @param pin Número de pin (0–7)
 */
static inline void GPIO_Toggle(volatile uint8_t* port, uint8_t pin)
{
    *port ^= (1 << pin);
}


/**
 * @brief Habilita o deshabilita la resistencia pull-up interna para un pin configurado como entrada.
 *
 * @param port Puntero al registro PORTx (por ejemplo &PORTB)
 * @param pin Número de pin (0–7)
 * @param state Estado del pullup. Es necesario hacer uso de las macros proporcionadas, o usar exclusivamente los valores 0 o 1.
 */
static inline void GPIO_Pullup(volatile uint8_t* port, uint8_t pin, uint8_t state) 
{
    if(state)
        *port |= (1 << pin); // ON
    else
        *port &= ~(1 << pin); // OFF
}

/**
 * @brief Configura una interrupción externa (INT2 o INT3) en el ATmega32U4.
 *
 * Esta función permite activar una interrupción externa en uno de los pines INT2 o INT3,
 * definiendo el tipo de evento que la activa (nivel bajo, cambio, flanco de bajada o subida) y si se desea
 * habilitar la resistencia pull-up interna del pin correspondiente.
 *
 * @param int_num Número de interrupción externa (válido: 2, 3).
 * @param mode Modo de disparo de la interrupción. Puede ser:
 *  - FALLING_EDGE: Flanco de bajada
 *  - RISING_EDGE: Flanco de subida
 * @param enable_pullup Habilita (ON) o deshabilita (OFF) la resistencia pull-up interna.
 */
static inline void GPIO_Interrupt_Init(uint8_t int_num, uint8_t mode)
{
	if(int_num == 2)
	{
		GPIO_Init(&DDRD, PORTD2, INPUT);
		switch (mode) 
		{
			case FALLING_EDGE: EICRA |= (1 << ISC21); break;
			case RISING_EDGE: EICRA |= (1 << ISC20); break;
		}
		EIMSK |= (1 << INT2);
	}
    
	if(int_num == 3)
	{
		GPIO_Init(&DDRD, PORTD0, INPUT);
		switch (mode) 
		{
			case FALLING_EDGE: EICRA |= (1 << ISC31); break;
			case RISING_EDGE: EICRA |= (1 << ISC30); break;
		}
		EIMSK |= (1 << INT3);
	}
}

/**
 * @brief Habilita la interrupción por cambio de pin (PCINT0–7) en el ATmega32U4.
 *
 * @param pcint Número de pin PCINT (solo válido: 0–7)
 */
static inline void GPIO_PCInterrupt_Enable(uint8_t pcint)
{
    if (pcint <= 7) 
	{
        PCICR |= (1 << PCIE0);          // Enables PCINT0 group
        PCMSK0 |= (1 << pcint);         // Enables an specific pin
    }
}


#endif /* GPIO_H_ */