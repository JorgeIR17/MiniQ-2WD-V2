#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Librerias/HAL/hal_ledrgb.h"
#include "Librerias/HAL/hal_pulsadores.h"


int main(void)
{
	HAL_ledrgb_init();
	HAL_pulsadores_init();
	
	while(1)
	{
		if(HAL_pulsadores_key_1()) HAL_ledrgb_efecto_arcoiris(3000);
		else if(HAL_pulsadores_key_2()) HAL_ledrgb_efecto_breathing(ROJO, 100, 3000);
		else if(HAL_pulsadores_key_3()) HAL_ledrgb_parpadeo(AMARILLO, 2000);
		else HAL_ledrgb_apagar();
	}
}