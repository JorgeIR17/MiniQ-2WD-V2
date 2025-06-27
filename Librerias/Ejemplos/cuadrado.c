/**
 * @file cuadrado.c
 * @author Jorge Ibáñez
 * @brief Ejemplo de uso del MiniQ 2WD mediante recorrido en forma de cuadrado
 * @version 0.1
 * @date 2025-06-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * En este programa se realiza una calbración de la brújula, y se recorre la distancia de cada lado para posteriormente girar 90º hacia el sigueinte lado del cuadrado.
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/hal_motores.h"
#include "../HAL/hal_zumbador.h"
#include "../HAL/hal_encoders.h"
#include "../HAL/hal_brujula.h"

int main(void)
{
	// Inicializamos los componentes
	HAL_motores_init();
	HAL_encoders_init();
	HAL_brujula_init();
	HAL_zumbador_init();

	uint16_t lado = 100; // lado de 100 mm

	_delay_ms(3000);  // espera antes de iniciar calibración
	
	HAL_zumbador_nota(A4, 1000);
	_delay_ms(1000);

	int16_t offset_x = 0, offset_y = 0;
	HAL_brujula_calibrar(&offset_x, &offset_y);
	_delay_ms(1000);

	float objetivos[] = {0.0, 90.0, 180.0, 270.0};
	uint8_t total = sizeof(objetivos) / sizeof(objetivos[0]);
	
	HAL_zumbador_nota(A5, 1000);
	_delay_ms(1000);

	while (1)
	{
		for (uint8_t i = 0; i < total; i++)
		{
			// ---- Avanzar distancia lado ----
			HAL_encoders_reset(ENCODER_IZQUIERDO);
			HAL_encoders_reset(ENCODER_DERECHO);

			HAL_motores_avanzar(50);  // velocidad fija

			while (
			HAL_encoders_get_distance(ENCODER_IZQUIERDO) < lado &&
			HAL_encoders_get_distance(ENCODER_DERECHO)  < lado)
			{
				_delay_ms(10);
			}

			HAL_motores_detener();
			_delay_ms(300);

			// ---- Girar hacia el siguiente ángulo ----
			float destino = objetivos[i];
			float actual = HAL_brujula_promedio_heading_calibrado(offset_x, offset_y, 5);
			float error = HAL_brujula_diferencia_angulo(destino, actual);

			if (error > 0)
			HAL_motores_girar(35, -35);  // Derecha
			else
			HAL_motores_girar(-35, 35);  // Izquierda

			while (fabs(HAL_brujula_diferencia_angulo(
			destino, HAL_brujula_promedio_heading_calibrado(offset_x, offset_y, 5))) > 5.0) // Girar hasta alcanzar el angulo buscado
			{
				_delay_ms(10);
			}

			HAL_motores_detener();
			_delay_ms(300);
		}
	}
}