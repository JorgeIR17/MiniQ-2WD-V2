#include "MOTORES.h"
#include <stdlib.h>

void motor_set_speed(uint8_t motor, int16_t velocidad)
{
    if(motor == MOTOR_IZQUIERDO)
    {
        PWM_Start(PWM_DIV_CLK_64);
        if(velocidad >= 0)
		{
            PWM_set_direction(MOTOR_IZQUIERDO, FORWARD);
			PWM_set_duty_cycle(MOTOR_IZQUIERDO, velocidad);
		}
        else
		{
            PWM_set_direction(MOTOR_IZQUIERDO, BACKWARD);
			PWM_set_duty_cycle(MOTOR_IZQUIERDO, abs(velocidad));
		}
    }

    else
    {
        PWM_Start(PWM_DIV_CLK_64);
        if(velocidad >= 0)
        {
	        PWM_set_direction(MOTOR_DERECHO, FORWARD);
	        PWM_set_duty_cycle(MOTOR_DERECHO, velocidad);
        }
        else
        {
	        PWM_set_direction(MOTOR_DERECHO, BACKWARD);
	        PWM_set_duty_cycle(MOTOR_DERECHO, abs(velocidad));
        }
    }
}

void motor_stop()
{
    PWM_Stop();
}

void motor_girar(int16_t velocidad_izq, int16_t velocidad_der)
{
    motor_set_speed(MOTOR_IZQUIERDO, velocidad_izq);
    motor_set_speed(MOTOR_DERECHO, velocidad_der);
}