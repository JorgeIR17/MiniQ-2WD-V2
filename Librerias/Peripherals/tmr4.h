/**
 * @file tmr4.h
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del Timer 4 del ATMega32U4.
 * @version 1.0
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

/**
 * @brief Inicializa el Timer 4 en modo PWM.
 * 
 */
static inline void TMR4_PWM_Init()
{
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
 * @param pwm PWM a configurar. Si es 0 será PWM1 (!OC4A) y si es 1 será PWM2 (OC4D) 
 * @param value Valor de ciclo de trabajo.
 */
inline void TMR4_PWM_set_duty_cycle(uint8_t pwm, uint8_t value)
{
	if(pwm == 0) 	// PWM1
		OCR4A = ~(value);
	if(pwm == 1) 	// PWM2
		OCR4D = value;
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
