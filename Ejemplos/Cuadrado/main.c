#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "m_usb.h"
#include "Librerias/HAL/hal_motores.h"
#include "Librerias/HAL/hal_zumbador.h"
#include "Librerias/HAL/hal_encoders.h"
#include "Librerias/HAL/hal_brujula.h"

int main(void)
{
	HAL_motores_init();
	HAL_encoders_init();
	HAL_brujula_init();
	HAL_zumbador_init();

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
			// ---- Avanzar 100 mm ----
			HAL_encoders_reset(ENCODER_IZQUIERDO);
			HAL_encoders_reset(ENCODER_DERECHO);

			HAL_motores_avanzar(50);  // velocidad fija

			while (
			HAL_encoders_get_distance(ENCODER_IZQUIERDO) < 100.0 &&
			HAL_encoders_get_distance(ENCODER_DERECHO)  < 100.0)
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
			HAL_motores_girar(35, -35);  // derecha
			else
			HAL_motores_girar(-35, 35);  // izquierda

			while (fabs(HAL_brujula_diferencia_angulo(
			destino, HAL_brujula_promedio_heading_calibrado(offset_x, offset_y, 5))) > 5.0)
			{
				_delay_ms(10);
			}

			HAL_motores_detener();
			_delay_ms(300);
		}
	}
}