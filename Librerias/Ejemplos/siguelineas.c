/**
 * @file siguelineas.c
 * @author Jorge Ibáñez
 * @brief Ejemplo de uso del MiniQ 2WD como robot siguelíneas
 * @version 0.1
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
	STATE_INIT,
	STATE_WAIT_BLACK,
	STATE_FOLLOW_LINE,
	STATE_STOP
} States_t;


int main(void)
{	
	int8_t posicion = 0;
	
	// Inicializamos los componentes
	HAL_zumbador_init();
	HAL_sensores_init();
	HAL_motores_init();
	HAL_ledrgb_init();
	HAL_bateria_init();
	
	
	States_t currentState = STATE_INIT;
	States_t nextState = STATE_INIT;
		
	
    while (1) 
    {
		
		HAL_bateria_mostrar_nivel();
		switch(currentState)
		{
			case STATE_INIT:
				HAL_zumbador_alerta(INICIO);
				_delay_ms(1000);
				nextState = STATE_WAIT_BLACK;
				break;
				
			case STATE_WAIT_BLACK:
				posicion = HAL_sensores_obtener_posicion();
				if (posicion == 0)
					nextState = STATE_FOLLOW_LINE;
				break;
				
			case STATE_FOLLOW_LINE:
				posicion = HAL_sensores_obtener_posicion();
				if (posicion == 0) // Robot centrado
					HAL_motores_avanzar(40); 
				if (posicion == 1) // Robot un poco a la derecha
				HAL_motores_girar(0, 30);
				if (posicion == -1) // Robot un poco a la izquierda
				HAL_motores_girar(30, 0);
				if (posicion == 2) // Robot muy a la derecha
					HAL_motores_girar(0, 60); 
				if (posicion == -2) // Robot muy a la izquierda
					HAL_motores_girar(60, 0);
				
				if (posicion == ERROR_LINEA)
					nextState = STATE_STOP;
					
				_delay_ms(5);
				break;
				
			case STATE_STOP:
				HAL_motores_detener();
				HAL_zumbador_alerta(ERROR);
				_delay_ms(1000);
				nextState = STATE_WAIT_BLACK;
				break;
				
			default: // STATE_WAIT_BLACK
				posicion = HAL_sensores_obtener_posicion();
				if (posicion == 0)
					nextState = STATE_FOLLOW_LINE;
				break;	
		}
		
		currentState = nextState;
    }
}