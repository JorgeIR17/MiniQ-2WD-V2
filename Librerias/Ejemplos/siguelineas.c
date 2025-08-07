/**
 * @file siguelineas.c
 * @author Jorge Ibáñez
 * @brief Ejemplo de uso del MiniQ 2WD como robot siguelíneas
 * @version 1.0
 * @date 2025-06-26
 * 
 * @copyright Copyright (c) 2025
 * 
 * En este programa el robot se encargará de seguir una línea negra sobre fondo blanco. Si el robot se encuentra en estado de inicio o error,
 * se emitirá el sonido correspondiente. El led RGB mostrará el valor de batería restante del robot.
 * 
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../HAL/hal_motores.h"
#include "../HAL/hal_sensores.h"
#include "../HAL/hal_zumbador.h"
#include "../HAL/hal_ledrgb.h"
#include "../HAL/hal_bateria.h"

typedef enum 
{
	INIT,
	ESPERA_NEGRO,
	SIGUE_LINEA,
	STOP
} Estado;


int main(void)
{	
	int8_t posicion = LINEA_CENTRO;
	
	// Inicializamos los componentes
	HAL_zumbador_init();
	HAL_sensores_init();
	HAL_motores_init();
	HAL_ledrgb_init();
	HAL_bateria_init();
	
	
	Estado estadoActual = INIT;
	Estado estadoSiguiente = INIT;
		
	
    while (1) 
    {
		
		HAL_bateria_mostrar_nivel();
		switch(estadoActual)
		{
			case INIT:
				HAL_zumbador_alerta(INICIO);
				_delay_ms(1000);
				estadoSiguiente = ESPERA_NEGRO;
				break;
				
			case ESPERA_NEGRO:
				posicion = HAL_sensores_obtener_posicion();
				if (posicion == LINEA_CENTRO)
					estadoSiguiente = SIGUE_LINEA;
				break;
				
			case SIGUE_LINEA:
				posicion = HAL_sensores_obtener_posicion();
				if (posicion == LINEA_CENTRO) // Robot centrado
					HAL_motores_avanzar(40); 
				if (posicion == LINEA_DERECHA_CENTRO) // Robot un poco a la derecha
				HAL_motores_girar(0, 30);
				if (posicion == LINEA_IZQUIERDA_CENTRO) // Robot un poco a la izquierda
				HAL_motores_girar(30, 0);
				if (posicion == LINEA_DERECHA) // Robot muy a la derecha
					HAL_motores_girar(0, 60); 
				if (posicion == LINEA_IZQUIERDA) // Robot muy a la izquierda
					HAL_motores_girar(60, 0);
				
				if (posicion == ERROR_LINEA)
					estadoSiguiente = STOP;
					
				_delay_ms(5);
				break;
				
			case STOP:
				HAL_motores_detener();
				HAL_zumbador_alerta(ERROR);
				_delay_ms(1000);
				estadoSiguiente = ESPERA_NEGRO;
				break;
				
			default: // ESPERA_NEGRO
				posicion = HAL_sensores_obtener_posicion();
				if (posicion == LINEA_CENTRO)
					estadoSiguiente = SIGUE_LINEA;
				break;	
		}
		
		estadoActual = estadoSiguiente;
    }
}