/**
 * @file motores.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los motores.
 * @version 1.0
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "motores.h"
#include <stdlib.h>

void motores_set_direction(uint8_t motor, uint8_t direction)
{
	if(motor == 0) // Motor izquierdo
	{
		if(direction == FORWARD)
            GPIO_Write(&MOTOR_EN1_PORT, MOTOR_EN1_PIN, LOW);
		if(direction == BACKWARD)
			GPIO_Write(&MOTOR_EN1_PORT, MOTOR_EN1_PIN, HIGH);
	}
	if (motor == 1) // Motor derecho
	{	
		if(direction == FORWARD)
            GPIO_Write(&MOTOR_EN2_PORT, MOTOR_EN2_PIN, LOW);
		if(direction == BACKWARD)
            GPIO_Write(&MOTOR_EN2_PORT, MOTOR_EN2_PIN, HIGH);
	}
}

void motores_set_speed(uint8_t motor, int16_t velocidad)
{
    if(velocidad > 255)  velocidad = 255;
    if(velocidad < -255) velocidad = -255;

    if(motor == MOTOR_IZQUIERDO)
    {
        TMR4_PWM_Start(TMR4_PWM_DIV_CLK_64);
        if(velocidad >= 0) // Hacia delante
		{
            motores_set_direction(MOTOR_IZQUIERDO, FORWARD);
			TMR4_PWM_set_duty_cycle(MOTOR_IZQUIERDO, velocidad);
		}
        else // Hacia atras
		{
            motores_set_direction(MOTOR_IZQUIERDO, BACKWARD);
			TMR4_PWM_set_duty_cycle(MOTOR_IZQUIERDO, abs(velocidad));
		}
    }

    if(motor == MOTOR_DERECHO)
    {
        TMR4_PWM_Start(TMR4_PWM_DIV_CLK_64);
        if(velocidad >= 0) // Hacia delante
        {
	        motores_set_direction(MOTOR_DERECHO, FORWARD);
	        TMR4_PWM_set_duty_cycle(MOTOR_DERECHO, velocidad);
        }
        else // Hacia atras
        {
	        motores_set_direction(MOTOR_DERECHO, BACKWARD);
	        TMR4_PWM_set_duty_cycle(MOTOR_DERECHO, abs(velocidad));
        }
    }
}

void motores_spin(int16_t velocidad_izq, int16_t velocidad_der)
{
    motores_set_speed(MOTOR_IZQUIERDO, velocidad_izq);
    motores_set_speed(MOTOR_DERECHO, velocidad_der);
}

void motores_stop()
{
    TMR4_PWM_Stop();
}