/**
 * @file receptor.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los transmisores y el receptor IR (IRM8881T).
 * @version 1.0
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "receptor.h"


void receptor_send_pulse(uint8_t transmisor)
{
	if(transmisor == TRANSMISOR_DERECHO || transmisor == TRANSMISOR_IZQUIERDO)
	{
		for (uint8_t i = 0; i < 24; i++)
		{
			if(transmisor == TRANSMISOR_DERECHO)
			{
				GPIO_Write(&IRR_PORT, IRR_PIN, LOW);
				_delay_us(8);
				GPIO_Write(&IRR_PORT, IRR_PIN, HIGH);
				_delay_us(8);
			}
			else
			{
				GPIO_Write(&IRL_PORT, IRL_PIN, LOW);
				_delay_us(8);
				GPIO_Write(&IRL_PORT, IRL_PIN, HIGH);
				_delay_us(8);
			}
		}
	}	
}

uint8_t receptor_get_pulses()
{
	return cont_obs;
}

void receptor_reset()
{
	cont_obs = 0;
}