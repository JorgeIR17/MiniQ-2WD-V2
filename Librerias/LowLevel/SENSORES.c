/**
 * @file SENSORES.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los sensores infrarrojos.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "SENSORES.h"

uint16_t sensores_leer(uint8_t sensor)
{
    switch (sensor)
    {
		case IZQUIERDA:
			return ADC_Read_Single_Poll(IR0);
				break;
		case IZQUIERDA_CENTRO:
			return ADC_Read_Single_Poll(IR1);
				break;
		case CENTRO:
			return ADC_Read_Single_Poll(IR2);
				break;
		case DERECHA_CENTRO:
			return ADC_Read_Single_Poll(IR3);
				break;
		case DERECHA:
			return ADC_Read_Single_Poll(IR4);
				break;
		default:
			return ADC_Read_Single_Poll(IR2); // si no se especifica se devuelve el valor central
				break;
    }

}

void sensores_calibrar()
{
	uint16_t valor_min = 1023;
	uint16_t valor_max = 0;
	uint16_t lectura;
	
	for(uint8_t vueltas = 0; vueltas < 10; vueltas++)
	{
		for(uint8_t i = IZQUIERDA; i < DERECHA; i++)
		{
			lectura = sensores_leer(i);
			if(lectura > valor_max) valor_max = lectura; // ALmacena el valor leido mas alto (blanco)
			if(lectura < valor_min) valor_min = lectura; // Almacena el valor leido mas bajo (negro)
		}
		_delay_ms(100);
	}
	
	if((valor_max - valor_min) > 100) // asegurar que se hayan leido valores correspondientes a blanco y negro
	{
		blanco = valor_max - valor_min;
		negro = valor_max - valor_min;
	}
}