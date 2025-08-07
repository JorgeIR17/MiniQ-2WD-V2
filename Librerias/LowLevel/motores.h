/**
 * @file motores.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de los motores.
 * @version 1.0
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef MOTORES_H_
#define MOTORES_H_

#include <avr/io.h>
#include "../Peripherals/tmr4.h"
#include "../Peripherals/gpio.h"

// Pines del puente H para motores
#define MOTOR_EN1_DDR   DDRD
#define MOTOR_EN1_PORT  PORTD
#define MOTOR_EN1_PIN   DDD6  // PD6

#define MOTOR_EN2_DDR   DDRE
#define MOTOR_EN2_PORT  PORTE
#define MOTOR_EN2_PIN   DDE6  // PE6

#define MOTOR_PWM1_DDR   DDRC
#define MOTOR_PWM1_PIN   DDC6  // PC6

#define MOTOR_PWM2_DDR   DDRD
#define MOTOR_PWM2_PIN   DDD7  // PD7

#define MOTOR_IZQUIERDO 0
#define MOTOR_DERECHO   1

// Sentido de las ruedas
#define FORWARD 0
#define BACKWARD 1

/**
 * @brief Inicializa los motores.
 * 
 */
static inline void motores_init()
{
    // Inicializar los pines como salida
    GPIO_Init(&MOTOR_PWM1_DDR, MOTOR_PWM1_PIN, OUTPUT);
    GPIO_Init(&MOTOR_PWM2_DDR, MOTOR_PWM2_PIN, OUTPUT);

	GPIO_Init(&MOTOR_EN1_DDR, MOTOR_EN1_PIN, OUTPUT);
    GPIO_Init(&MOTOR_EN2_DDR, MOTOR_EN2_PIN, OUTPUT);
	
    TMR4_PWM_Init();
	TMR4_PWM_Stop(); // Asegurar que al inicio los motores esten parados
}

/**
 * @brief Establece la dirección de movimiento de una rueda determinada.
 * 
 * @param motor Motor izquierdo o derecho
 * @param direction Sentido de la rueda. Es necesario hacer uso de las macros proporcionadas.
 */
void motores_set_direction(uint8_t motor, uint8_t direction);


/**
 * @brief Gira una de las ruedas a una velocidad determinada.
 * 
 * @param motor Motor derecho o izquierdo. Es necesario hacer uso de las macros proporcionadas.
 * @param velocidad Velocidad de la rueda. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, la rueda girará en sentido inverso.
 */
void motores_set_speed(uint8_t motor, int16_t velocidad);

/**
 * @brief Gira ambas ruedas a distintas velocidades determinadas.
 * 
 * @param velocidad_izq Velocidad de la rueda izquierda. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, la rueda girará en sentido inverso.
 * @param velocidad_der Velocidad de la rueda derecha. El valor debe ser un número entero entre -255 y 255. Si el valor es negativo, la rueda girará en sentido inverso.
 */
void motores_spin(int16_t velocidad_izq, int16_t velocidad_der);

/**
 * @brief Detiene el movimiento de las ruedas.
 * 
 */
void motores_stop();


#endif /* MOTORES_H_ */
