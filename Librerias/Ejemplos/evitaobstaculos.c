/**
 * @file evitaobstaculos.c
 * @author Jorge Ibáñez
 * @brief Ejemplo de uso del MiniQ 2WD como robot evita-obstáculos.
 * @version 1.0
 * @date 2025-06-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * En este programa el robot se desplazará hacia adelante hasta que detecte un obstáculo cercano. En tal caso, se detendrá, se desplazará marcha atrás
 * y girará hacia otra dirección para continuar el desplazamiento. El estado se mostrará mediante el color del led RGB.
 * 
 * - Blanco: No hay obstáculo.
 * - Rojo: Obstáculo delante.
 * - Verde: Obstáculo a la derecha.
 * - Azul: Obstáculo a la izquierda.
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/hal_motores.h"
#include "../HAL/hal_ledrgb.h"
#include "../HAL/hal_receptor.h"

typedef enum 
{
	SIN_OBSTACULO,
	OBSTACULO_DERECHA,
	OBSTACULO_IZQUIERDA,
	OBSTACULO_DELANTE
} Estado;

int main(void)
{
	// Inicializamos los componentes
	HAL_receptor_init();
	HAL_ledrgb_init();
	HAL_motores_init();

	_delay_ms(1000);

	Estado estadoActual = SIN_OBSTACULO;
	Estado estadoSiguiente = SIN_OBSTACULO;

	while (1)
	{
		uint8_t obstaculo = HAL_receptor_detectar_obstaculo(NULL, NULL);

		switch (estadoActual)
		{
			case SIN_OBSTACULO:
				if (obstaculo == OBS_NADA)
				{
					HAL_motores_avanzar(50);
					HAL_ledrgb_color(BLANCO);
					estadoSiguiente = SIN_OBSTACULO;
				}
				else if (obstaculo == OBS_DERECHA)
					estadoSiguiente = OBSTACULO_DERECHA;
				else if (obstaculo == OBS_IZQUIERDA)
					estadoSiguiente = OBSTACULO_IZQUIERDA;
				else if (obstaculo == OBS_DELANTE)
					estadoSiguiente = OBSTACULO_DELANTE;
				break;

			case OBSTACULO_DERECHA:
				HAL_motores_detener();
				HAL_ledrgb_color(VERDE);
				_delay_ms(1000);
				HAL_motores_avanzar(-100);
				_delay_ms(300);
				HAL_motores_detener();
				_delay_ms(300);
				HAL_motores_girar(-100, 100);
				_delay_ms(300);
				estadoSiguiente = SIN_OBSTACULO;
				break;

			case OBSTACULO_IZQUIERDA:
				HAL_motores_detener();
				HAL_ledrgb_color(AZUL);
				_delay_ms(1000);
				HAL_motores_avanzar(-100);
				_delay_ms(300);
				HAL_motores_detener();
				_delay_ms(300);
				HAL_motores_girar(-100, 100);
				_delay_ms(300);
				estadoSiguiente = SIN_OBSTACULO;
				break;

			case OBSTACULO_DELANTE:
				HAL_motores_detener();
				HAL_ledrgb_color(ROJO);
				_delay_ms(1000);
				HAL_motores_avanzar(-100);
				_delay_ms(300);
				HAL_motores_detener();
				_delay_ms(300);
				HAL_motores_girar(100, -100);
				_delay_ms(300);
				estadoSiguiente = SIN_OBSTACULO;
				break;

			default:
				estadoSiguiente = SIN_OBSTACULO;
				break;
		}

		estadoActual = estadoSiguiente;
	}
}