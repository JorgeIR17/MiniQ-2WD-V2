/**
 * @file hal_receptor.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los transmisores y el receptor IR (IRM8881T).
 * @version 0.1
 * @date 2025-06-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_receptor.h"

uint8_t HAL_receptor_detectar_obstaculo(uint8_t* contR, uint8_t* contL)
{
	uint8_t obs = OBS_NADA;
	uint8_t i;
	
	cont_obs = 0;
	for (i = 0; i < 20; i++)
	{
		receptor_enviar_pulso(TRANSMISOR_DERECHO);
		_delay_us(600);
	}
	
	if(cont_obs > 20)
		obs = OBS_DERECHA;
	if(contR != NULL)
		*contR = cont_obs;
		
	_delay_ms(50);
	
	cont_obs = 0;
	for (i = 0; i < 20; i++)
	{
		receptor_enviar_pulso(TRANSMISOR_IZQUIERDO);
		_delay_us(600);
	}
	
	if(cont_obs > 20)
	{
		if(obs == OBS_DERECHA)
			obs = OBS_DELANTE;
		else
			obs = OBS_IZQUIERDA;
	}
	if(contL != NULL)
		*contL = cont_obs;
		
	return obs;
}