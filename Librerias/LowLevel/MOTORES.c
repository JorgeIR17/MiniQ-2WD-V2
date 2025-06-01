/**
 * @file motores.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los motores.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "motores.h"
#include <stdlib.h>

void motor_set_speed(uint8_t motor, int16_t velocidad)
{
    if(velocidad > 255)  velocidad = 255;
    if(velocidad < -255) velocidad = -255;

    if(motor == MOTOR_IZQUIERDO)
    {
        TMR4_PWM_Start(TMR4_PWM_DIV_CLK_64);
        if(velocidad >= 0) // Hacia delante
		{
            TMR4_PWM_set_direction(MOTOR_IZQUIERDO, FORWARD);
			TMR4_PWM_set_duty_cycle(MOTOR_IZQUIERDO, velocidad);
		}
        else // Hacia atras
		{
            TMR4_PWM_set_direction(MOTOR_IZQUIERDO, BACKWARD);
			TMR4_PWM_set_duty_cycle(MOTOR_IZQUIERDO, abs(velocidad));
		}
    }

    else
    {
        TMR4_PWM_Start(TMR4_PWM_DIV_CLK_64);
        if(velocidad >= 0) // Hacia delante
        {
	        TMR4_PWM_set_direction(MOTOR_DERECHO, FORWARD);
	        TMR4_PWM_set_duty_cycle(MOTOR_DERECHO, velocidad);
        }
        else // Hacia atras
        {
	        TMR4_PWM_set_direction(MOTOR_DERECHO, BACKWARD);
	        TMR4_PWM_set_duty_cycle(MOTOR_DERECHO, abs(velocidad));
        }
    }
}

void motor_stop()
{
    TMR4_PWM_Stop();
}

void motor_girar(int16_t velocidad_izq, int16_t velocidad_der)
{
    motor_set_speed(MOTOR_IZQUIERDO, velocidad_izq);
    motor_set_speed(MOTOR_DERECHO, velocidad_der);
}