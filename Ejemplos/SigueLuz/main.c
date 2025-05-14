#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "m_usb.h"
#include "Librerias/HAL/HAL_motores.h"
#include "Librerias/HAL/HAL_sensores.h"
#include "Librerias/HAL/HAL_zumbador.h"
#include "Librerias/HAL/HAL_encoders.h"
#include "Librerias/HAL/HAL_ledrgb.h"
#include "Librerias/HAL/HAL_pulsadores.h"
#include "Librerias/HAL/HAL_bateria.h"
#include "Librerias/HAL/HAL_fotodiodos.h"


int main(void)
{
	HAL_ledrgb_init();
	HAL_fotodiodos_init();
	HAL_motores_init();
	
	HAL_motores_detener();
	
	_delay_ms(3000);
	
	while(1)
	{
		if(HAL_fotodiodos_posicion() == LUZ_CENTRO)
		{ 
			HAL_motores_avanzar(80);
			HAL_ledrgb_color(VERDE);
		}
		
		if(HAL_fotodiodos_posicion() == LUZ_DERECHA) 
		{
			HAL_motores_girar(100, 60);
			HAL_ledrgb_color(AZUL);
		}
	
		if(HAL_fotodiodos_posicion() == LUZ_IZQUIERDA)
		{
			HAL_motores_girar(60, 100);
			HAL_ledrgb_color(ROJO);
		}
		if(HAL_fotodiodos_posicion() == LUZ_ERROR)
		{ 
			HAL_motores_detener();
			HAL_ledrgb_color(AMARILLO);
		}
		
		_delay_ms(15);
	}
}