/**
 * @file sigueluz.c
 * @author Jorge Ibáñez
 * @brief Ejemplo de uso del MiniQ 2WD como robot seguidor de luz
 * @version 1.0
 * @date 2025-06-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * En este programa el robot se comportará como un seguidor de luz, avanzando hacia la dirección en la que se encuentre. En caso de no detectar ningún haz
 * de luz, el robot se detendrá. El estado se representará mediante el color del led RGB.
 * 
 * - Verde: Luz delante.
 * - Azul: Luz a la derecha.
 * - Rojo: Luz a la izquierda.
 * - Amarillo: Ausencia de luz.
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/hal_motores.h"
#include "../HAL/hal_ledrgb.h"
#include "../HAL/hal_fotodiodos.h"


typedef enum 
{
	INIT,
	LUZ_CENTRO_ESTADO,
	LUZ_DERECHA_ESTADO,
	LUZ_IZQUIERDA_ESTADO,
	LUZ_ERROR_ESTADO
} Estado;

int main(void)
{
	// Inicializamos los componentes
	HAL_ledrgb_init();
	HAL_fotodiodos_init();
	HAL_motores_init();

	Estado estadoActual = INIT;
	Estado estadoSiguiente = INIT;

	while (1)
	{
		uint8_t luz = HAL_fotodiodos_posicion();

		switch (estadoActual)
		{
			case INIT:
				_delay_ms(3000);
				estadoSiguiente = LUZ_ERROR_ESTADO;
				break;

			case LUZ_CENTRO_ESTADO:
				HAL_motores_avanzar(80);
				HAL_ledrgb_color(VERDE);

				if (luz == LUZ_CENTRO)
					estadoSiguiente = LUZ_CENTRO_ESTADO;
				else if (luz == LUZ_DERECHA)
					estadoSiguiente = LUZ_DERECHA_ESTADO;
				else if (luz == LUZ_IZQUIERDA)
					estadoSiguiente = LUZ_IZQUIERDA_ESTADO;
				else
					estadoSiguiente = LUZ_ERROR_ESTADO;
				break;

			case LUZ_DERECHA_ESTADO:
				HAL_motores_girar(100, 60);
				HAL_ledrgb_color(AZUL);

				if (luz == LUZ_DERECHA)
					estadoSiguiente = LUZ_DERECHA_ESTADO;
				else if (luz == LUZ_CENTRO)
					estadoSiguiente = LUZ_CENTRO_ESTADO;
				else if (luz == LUZ_IZQUIERDA)
					estadoSiguiente = LUZ_IZQUIERDA_ESTADO;
				else
					estadoSiguiente = LUZ_ERROR_ESTADO;
				break;

			case LUZ_IZQUIERDA_ESTADO:
				HAL_motores_girar(60, 100);
				HAL_ledrgb_color(ROJO);

				if (luz == LUZ_IZQUIERDA)
					estadoSiguiente = LUZ_IZQUIERDA_ESTADO;
				else if (luz == LUZ_CENTRO)
					estadoSiguiente = LUZ_CENTRO_ESTADO;
				else if (luz == LUZ_DERECHA)
					estadoSiguiente = LUZ_DERECHA_ESTADO;
				else
					estadoSiguiente = LUZ_ERROR_ESTADO;
				break;

			case LUZ_ERROR_ESTADO:
				HAL_motores_detener();
				HAL_ledrgb_color(AMARILLO);

				if (luz == LUZ_CENTRO)
					estadoSiguiente = LUZ_CENTRO_ESTADO;
				else if (luz == LUZ_DERECHA)
					estadoSiguiente = LUZ_DERECHA_ESTADO;
				else if (luz == LUZ_IZQUIERDA)
					estadoSiguiente = LUZ_IZQUIERDA_ESTADO;
				else
					estadoSiguiente = LUZ_ERROR_ESTADO;
				break;

			default:
				estadoSiguiente = LUZ_ERROR_ESTADO;
				break;
		}

		estadoActual = estadoSiguiente;
		_delay_ms(15); // Retardo para evitar oscilaciones rápidas
	}
}
