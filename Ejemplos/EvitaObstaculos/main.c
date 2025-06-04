#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "m_usb.h"
#include "Librerias/HAL/hal_motores.h"
#include "Librerias/HAL/hal_sensores.h"
#include "Librerias/HAL/hal_zumbador.h"
#include "Librerias/HAL/hal_encoders.h"
#include "Librerias/HAL/hal_ledrgb.h"
#include "Librerias/HAL/hal_pulsadores.h"
#include "Librerias/HAL/hal_bateria.h"
#include "Librerias/HAL/hal_fotodiodos.h"
#include "Librerias/HAL/hal_receptor.h"

int main(void)
 {
	 HAL_receptor_init();
	 HAL_ledrgb_init();
	 HAL_motores_init();
	 
	 HAL_motores_detener();
	 
	 _delay_ms(1000);
	 
	 while(1)
	 {
		 uint8_t obstaculo = HAL_receptor_detectar_obstaculo(NULL, NULL);
		 if(obstaculo == OBS_NADA)
		 {
			HAL_motores_avanzar(50);
			HAL_ledrgb_color(BLANCO);
		 }
		 
		 if(obstaculo == OBS_DERECHA)
		 {
			 HAL_motores_detener();
			 HAL_ledrgb_color(VERDE);
			 _delay_ms(1000);
			 HAL_motores_avanzar(-100);
			 _delay_ms(300);
			 HAL_motores_detener();
			 _delay_ms(300);
			 HAL_motores_girar(-100, 100);
			 _delay_ms(300);
		 }
		 
		if(obstaculo == OBS_IZQUIERDA)
		{
			HAL_motores_detener();
			HAL_ledrgb_color(AZUL);
			_delay_ms(1000);
			HAL_motores_avanzar(-100);
			_delay_ms(300);
			HAL_motores_detener();
			_delay_ms(300);
			HAL_motores_girar(-100, 100);
			_delay_ms(300);
		}
		
		if(obstaculo == OBS_DELANTE)
		{
			HAL_motores_detener();
			HAL_ledrgb_color(ROJO);
			_delay_ms(1000);
			HAL_motores_avanzar(-100);
			_delay_ms(300);
			HAL_motores_detener();
			_delay_ms(300);
			HAL_motores_girar(100, -100);
			_delay_ms(300);
		}	 
	 }
 }