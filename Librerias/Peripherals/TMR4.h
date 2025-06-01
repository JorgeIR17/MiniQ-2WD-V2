/**
 * @file tmr4.h
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del Timer 4 del ATMega32U4.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef TMR4_H_
#define TMR4_H_

#include <avr/io.h>
#include "gpio.h"

#define TMR4_PWM_DIV_CLK_1	    1
#define TMR4_PWM_DIV_CLK_2	    2
#define TMR4_PWM_DIV_CLK_4	    3
#define TMR4_PWM_DIV_CLK_8	    4
#define TMR4_PWM_DIV_CLK_16     5
#define TMR4_PWM_DIV_CLK_32	    6
#define TMR4_PWM_DIV_CLK_64	    7
#define TMR4_PWM_DIV_CLK_128    8
#define TMR4_PWM_DIV_CLK_256    9
#define TMR4_PWM_DIV_CLK_512    10
#define TMR4_PWM_DIV_CLK_1024   11
#define TMR4_PWM_DIV_CLK_2048   12
#define TMR4_PWM_DIV_CLK_4096   13
#define TMR4_PWM_DIV_CLK_8192   14
#define TMR4_PWM_DIV_CLK_16384  15

// Sentido de las ruedas
#define FORWARD 0
#define BACKWARD 1

/**
 * @brief Inicializa el Timer 4 en modo PWM.
 * 
 */
static inline void TMR4_PWM_Init()
{
	DDRC |= (1<<DDC6); // Set OC4A (PC6) as output
	DDRD |= (1<<DDD7); // Set OC4D (PD7) as output

	//Set PWM Phase Correct Mode
	TCCR4A |= (1<<COM4A0) | (1<<PWM4A);
	TCCR4A &= ~(1<<COM4A1);

	TCCR4C |= (1<<COM4D1) | (1<<PWM4D);
	TCCR4C &= ~(1<<COM4D0);

	TCCR4D &= ~(1<<WGM41);
	TCCR4D |= (1<<WGM40);
}

/**
 * @brief Inicia el Timer 4 en modo PWM.
 * 
 * @param divClock Divisor de frecuencia. Es necesario hacer uso de las macros proporcionadas.
 */
inline void TMR4_PWM_Start(uint8_t divClock)
{
	TCNT4 = 0; // Reset counter

	TCCR4B &= 0b11110000; // Clear CS40, CS41, CS42
	TCCR4B |= (divClock<<CS40); // Set prescaler
}


/**
 * @brief Ajusta el ciclo de trabajo del PWM.
 * 
 * @param motor Motor izquierdo o derecho. 
 * @param value Valor de ciclo de trabajo.
 */
inline void TMR4_PWM_set_duty_cycle(uint8_t motor, uint8_t value)
{
	if(motor == 0) 	// Motor izquierdo
		OCR4A = ~(value);
	else 			// Motor derecho
		OCR4D = value;
}

/**
 * @brief Establece la dirección de movimiento de una rueda determinada.
 * 
 * @param motor Motor izquierdo o derecho
 * @param direction Sentido de la rueda. Es necesario hacer uso de las macros proporcionadas.
 */
inline void TMR4_PWM_set_direction(uint8_t motor, uint8_t direction)
{
	if(motor == 0) // Motor izquierdo
	{
		if(direction == FORWARD)
			PORTD &= ~(1<<MOTOR_EN1_PIN);
		if(direction == BACKWARD)
			PORTD |= (1<<MOTOR_EN1_PIN);
	}
	else // Motor derecho
	{	
		if(direction == FORWARD)
			PORTE &= ~(1<<MOTOR_EN2_PIN);
		if(direction == BACKWARD)
			PORTE |= (1<<MOTOR_EN2_PIN);
	}
}

/**
 * @brief Detiene el funcionamiento del Timer 4 en modo PWM.
 * 
 */
inline void TMR4_PWM_Stop()
{
	TCCR4B &= 0b11110000; // Clear CS40, CS41, CS42

	TMR4_PWM_set_duty_cycle(0, 0);
	TMR4_PWM_set_duty_cycle(1, 0);
}

#endif /* TMR4_H_ */
