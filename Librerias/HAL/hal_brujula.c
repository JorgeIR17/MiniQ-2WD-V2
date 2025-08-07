/**
 * @file hal_brujula.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de la brujula HMC5883L
 * @version 1.0
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_brujula.h"

void HAL_brujula_read_ejes(int16_t* x, int16_t* y, int16_t* z)
{
    brujula_read(x, y, z);
}


void HAL_brujula_calibrar(int16_t* offset_x, int16_t* offset_y)
{
    int16_t x, y, z;
    int16_t x_min = 32767, x_max = -32768;
    int16_t y_min = 32767, y_max = -32768;

    HAL_motores_girar(40, -40);

    for (uint16_t i = 0; i < 500; i++) // 500 muestras (~5 segundos a 10ms)
    {
        brujula_read(&x, &y, &z);

        if (x < x_min) x_min = x;
        if (x > x_max) x_max = x;
        if (y < y_min) y_min = y;
        if (y > y_max) y_max = y;

        _delay_ms(10);
    }

    HAL_motores_detener();

    // Calcula el offset como el punto medio entre min y max
    *offset_x = (x_max + x_min) / 2;
    *offset_y = (y_max + y_min) / 2;
}

float HAL_brujula_get_heading_calibrado(int16_t offset_x, int16_t offset_y)
{
	int16_t x, y, z;
	brujula_read(&x, &y, &z);

	int16_t x_corr = x - offset_x;
	int16_t y_corr = y - offset_y;

	float heading = atan2((float)y_corr, (float)x_corr) * (180.0 / M_PI);

	if (heading < 0)
	heading += 360.0;

	return heading;
}


float HAL_brujula_diferencia_angulo(float angulo_objetivo, float angulo_actual)
{
    float diferencia = angulo_objetivo - angulo_actual;

    if (diferencia > 180.0)
        diferencia -= 360.0;
    else if (diferencia < -180.0)
        diferencia += 360.0;

    return diferencia;
}

float HAL_brujula_promedio_heading_calibrado(int16_t offset_x, int16_t offset_y, uint8_t muestras)
{
	float suma = 0;
	for (uint8_t i = 0; i < muestras; i++)
	{
		suma += HAL_brujula_get_heading_calibrado(offset_x, offset_y);
		_delay_ms(5);
	}
	return suma / muestras;
}