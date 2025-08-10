/**
 * @file receptor.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de los transmisores y el receptor IR (IRM8881T).
 * @version 1.0
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef RECEPTOR_H_
#define RECEPTOR_H_

#define F_CPU 16000000UL
#include "../Peripherals/gpio.h"
#include <util/delay.h>

// Pines de los transmisores y receptor IR
#define IRR_DDR			DDRB
#define IRR_PORT		PORTB
#define IRR_PIN			DDB4

#define IRL_DDR			DDRC
#define IRL_PORT		PORTC
#define IRL_PIN			DDC7

#define IRS_DDR			DDRB
#define IRS_PORT		PORTB
#define IRS_PIN			DDB0
#define IRS_PCINT		0

#define TRANSMISOR_IZQUIERDO 0
#define TRANSMISOR_DERECHO   1

/**
 * @brief Inicializa los transmisores y el receptor IR.
 * 
 */
static inline void receptor_init()
{
	GPIO_Init(&IRR_DDR, IRR_PIN, OUTPUT);
	GPIO_Init(&IRL_DDR, IRL_PIN, OUTPUT);
	GPIO_Init(&IRS_DDR, IRS_PIN, INPUT);
	GPIO_PCInterrupt_Enable(IRS_PCINT);
	cont_obs = 0;
	
	sei();
}

/**
 * @brief Envía un pulso de 40 KHz desde uno de los transmisores al receptor IR.
 * 
 * @param transmisor Transmisor izquierdo o derecho. Es necesario hacer uso de las macros proporcionadas.
 */
void receptor_send_pulse(uint8_t transmisor);


/**
 * @brief Devuelve el valor de pulsos acumulados por el receptor IR.
 * 
 * @return uint8_t Número de pulsos acumulados
 */
uint8_t receptor_get_pulses();


/**
 * @brief Reinicia el contador de pulsos recibidos por el receptor IR. 
 * 
 */
void receptor_reset();


#endif /* RECEPTOR_H_ */