#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Librerias/HAL/hal_motores.h"
#include "Librerias/HAL/hal_sensores.h"
#include "Librerias/HAL/hal_zumbador.h"
#include "Librerias/HAL/hal_encoders.h"


//SIGUE-LINEAS


typedef enum {
	STATE_INIT,
	STATE_WAIT_BLACK,
	STATE_FOLLOW_LINE,
	STATE_STOP
} States_t;


int main(void)
{
	// ---------------------------------- SETUP ------------------------------
	
	uint16_t valor_sensor;
	int8_t posicion = 0;
	
	// Initializes buzzer
	HAL_zumbador_init();
	
	// Initializes opto sensors
	HAL_sensores_init();
	
	// Initializes wheels
	HAL_motores_init();
	

	// Make sure that the robot starts in STOP mode
	HAL_motores_detener();
	
	States_t currentState = STATE_INIT;
	States_t nextState = STATE_INIT;
	
	valor_sensor = HAL_sensores_leer(CENTRO); 
	
	
    // ---------------------------------- LOOP ------------------------------
    while (1) 
    {
		switch(currentState){
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
				if (posicion == 0) // Central negro y los de sus lados blancos --> FORWARD
					HAL_motores_avanzar(100); 
				if (posicion == 2) // izquierda del central negro y central blanco --> GIRO IQUIERDA BRUSCO
					HAL_motores_girar(20, 120); 
				if (posicion == -2) // derecha del central negro y central blanco --> GIRO DERECHA BRUSCO
					HAL_motores_girar(120, 20);
				if (posicion == 1) // izquierda del central negro y central negro --> GIRO IQUIERDA SUAVE
					HAL_motores_girar(60, 120);
				if (posicion == -1) // // derecha del central negro y central negro --> GIRO DERECHA SUAVE
					HAL_motores_girar(120, 60);
				
				if (posicion == ERROR_LINEA)
					nextState = STATE_STOP;
					
				_delay_ms(15);
				break;
				
			case STATE_STOP:
				HAL_motores_detener();
				_delay_ms(200);
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