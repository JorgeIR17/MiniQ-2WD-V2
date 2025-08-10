/**
 * @file hal_ledrgb.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso del LED RGB
 * @version 1.0
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "hal_ledrgb.h"


void HAL_ledrgb_color(uint8_t color)
{
	switch(color) // Envia el codigo RGB segun el color
	{
		case WHITE:
			led_rgb_send_color(255, 255, 255);
			break;
		case RED:
			led_rgb_send_color(255, 0, 0);
			break;
		case GREEN:
			led_rgb_send_color(0, 255, 0);
			break;
		case BLUE:
			led_rgb_send_color(0, 0, 255);
			break;
		case YELLOW:
			led_rgb_send_color(255, 255, 0);
			break;
		case MAGENTA:
			led_rgb_send_color(255, 0, 255);
			break;
		case CYAN:
			led_rgb_send_color(0, 255, 255);
			break;
		case ORANGE:
			led_rgb_send_color(255, 165, 0);
			break;
		case VIOLET:
			led_rgb_send_color(128, 0, 255);
			break;
		case PINK:
			led_rgb_send_color(255, 192, 203);
			break;
		case TURQUOISE:
			led_rgb_send_color(93, 193, 185);
			break;
		case AMBER:
			led_rgb_send_color(255, 191, 0);
			break;
		case EMERALD:
			led_rgb_send_color(0, 157, 113);
			break;
		case MAROON:
			led_rgb_send_color(128, 0, 0);
			break;
		case SKYBLUE:
			led_rgb_send_color(128, 191, 255);
			break;
		case BROWN:
			led_rgb_send_color(128, 64, 0);
			break;
		case PURPLE:
			led_rgb_send_color(128, 0, 128);
			break;
		case LIME:
			led_rgb_send_color(191, 255, 0);
			break;
		case FUCHSIA:
			led_rgb_send_color(255, 0, 128);
			break;
		case INDIGO:
			led_rgb_send_color(28, 76, 150);
			break;
		case GRAY:
			led_rgb_send_color(128, 128, 128);
			break;
		default: // si no se especifica un color existente se apaga el LED
			led_rgb_off();
			break;
	}
	
}


void HAL_ledrgb_parpadeo(uint8_t color, uint16_t duracion)
{
	blink_time = duracion;

	while (blink_time > 0)
	{
		if(blink != 0)
			HAL_ledrgb_color(color);
		else
			led_rgb_off();
	}
	led_rgb_off(); // Asegurar apagar el LED al terminar
}


void HAL_ledrgb_efecto_breathing(uint8_t color, uint16_t pasos, uint16_t duracion) 
{
	float intensidad;
	uint8_t r_base, g_base, b_base;
	uint8_t r, g, b;
	uint16_t tiempo = 0;

	switch(color)
	{
		case WHITE:     r_base = 255; g_base = 255; b_base = 255; break;
		case RED:       r_base = 255; g_base = 0;   b_base = 0;   break;
		case GREEN:     r_base = 0;   g_base = 255; b_base = 0;   break;
		case BLUE:      r_base = 0;   g_base = 0;   b_base = 255; break;
		case YELLOW:    r_base = 255; g_base = 255; b_base = 0;   break;
		case MAGENTA:   r_base = 255; g_base = 0;   b_base = 255; break;
		case CYAN:      r_base = 0;   g_base = 255; b_base = 255; break;
		case ORANGE:    r_base = 255; g_base = 165; b_base = 0;   break;
		case VIOLET:    r_base = 128; g_base = 0;   b_base = 255; break;
		case PINK:      r_base = 255; g_base = 192; b_base = 203; break;
		case TURQUOISE: r_base = 93;  g_base = 193; b_base = 185; break;
		case AMBER:     r_base = 255; g_base = 191; b_base = 0;   break;
		case EMERALD:   r_base = 0;   g_base = 157; b_base = 113; break;
		case MAROON:    r_base = 128; g_base = 0;   b_base = 0;   break;
		case SKYBLUE:   r_base = 128; g_base = 191; b_base = 255; break;
		case BROWN:     r_base = 128; g_base = 64;  b_base = 0;   break;
		case PURPLE:    r_base = 128; g_base = 0;   b_base = 128; break;
		case LIME:      r_base = 191; g_base = 255; b_base = 0;   break;
		case FUCHSIA:   r_base = 255; g_base = 0;   b_base = 128; break;
		case INDIGO:    r_base = 28;  g_base = 76;  b_base = 150; break;
		case GRAY:      r_base = 128; g_base = 128; b_base = 128; break;
		default:        led_rgb_off(); return;
	}

	while (tiempo < duracion) 
	{
		// Subida de intensidad
		for (uint16_t i = 0; i < pasos && tiempo < duracion; i++) 
		{
			intensidad = (1.0 - cos((float)i / pasos * 3.14159)) / 2.0;
			r = (uint8_t)(r_base * intensidad);
			g = (uint8_t)(g_base * intensidad);
			b = (uint8_t)(b_base * intensidad);
			led_rgb_send_color(r, g, b);
			_delay_ms(20);
			tiempo += 20;
		}

		// Bajada de intensidad
		for (uint16_t i = pasos; i > 0 && tiempo < duracion; i--) 
		{
			intensidad = (1.0 - cos((float)i / pasos * 3.14159)) / 2.0;
			r = (uint8_t)(r_base * intensidad);
			g = (uint8_t)(g_base * intensidad);
			b = (uint8_t)(b_base * intensidad);
			led_rgb_send_color(r, g, b);
			_delay_ms(20);
			tiempo += 20;
		}
	}
}

void hal_ledrgb_hue_a_rgb(uint8_t hue, uint8_t* r, uint8_t* g, uint8_t* b)
{
	uint8_t region = hue / 43; // Divide el matiz (hue) en una de las 6 regiones del espectro de color
	uint8_t resto = (hue - (region * 43)) * 6; // Calcula el resto para interpolar entre los colores base

	uint8_t p = 0; // p siempre es 0; q y t se usan para interpolar colores
	uint8_t q = (255 * (255 - resto)) / 255;
	uint8_t t = (255 * resto) / 255;

	switch (region)
	{
		case 0:
			*r = 255;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = 255;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = 255;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = 255;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = 255;
			break;
		default: // region 5
			*r = 255;
			*g = p;
			*b = q;
			break;
	}
}

void HAL_ledrgb_efecto_arcoiris(uint16_t duracion)
{
	uint8_t r, g, b;
	uint8_t hue = 0;
	uint16_t tiempo = 0;

	while (tiempo < duracion)
	{
		hal_ledrgb_hue_a_rgb(hue++, &r, &g, &b); // Convierte el matiz actual a RGB y envia el color al LED
		led_rgb_send_color(r, g, b);
		_delay_ms(20);
		tiempo += 20;
	}
}


void HAL_ledrgb_apagar()
{
	led_rgb_off();
}