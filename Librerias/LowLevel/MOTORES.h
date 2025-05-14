/**
 * @file MOTORES.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de los motores.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MOTORES_H_
#define MOTORES_H_

#include <avr/io.h>
#include "../Peripherals/TMR4.h"
#include "../Peripherals/GPIO.h"

#define MOTOR_IZQUIERDO 0
#define MOTOR_DERECHO   1

/**
 * @brief Inicializa los motores.
 * 
 */
static inline void motores_init()
{
	puenteH_init();
    TMR4_PWM_Init();
	TMR4_PWM_Stop();
}

/**
 * @brief Gira una de las ruedas a una velocidad determinada.
 * 
 * @param motor Motor derecho o izquierdo. Es necesario hacer uso de las macros proporcionadas.
 * @param velocidad Velocidad de la rueda. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, la rueda girará en sentido inverso.
 */
void motor_set_speed(uint8_t motor, int16_t velocidad);

/**
 * @brief Detiene el movimiento de las ruedas.
 * 
 */
void motor_stop();

/**
 * @brief Gira ambas ruedas a distintas velocidades determinadas.
 * 
 * @param velocidad_izq Velocidad de la rueda izquierda. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, la rueda girará en sentido inverso.
 * @param velocidad_der Velocidad de la rueda derecha. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, la rueda girará en sentido inverso.
 */
void motor_girar(int16_t velocidad_izq, int16_t velocidad_der);


#endif /* MOTORES_H_ */
