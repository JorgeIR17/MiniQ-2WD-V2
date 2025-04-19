#include "HAL_ledrgb.h"

void HAL_ledrgb_color(uint8_t color)
{
	switch(color)
	{
		case WHITE:
			led_rgb_enviar_color(255, 255, 255);
			break;
		case RED:
			led_rgb_enviar_color(255, 0, 0);
			break;
		case GREEN:
			led_rgb_enviar_color(0, 255, 0);
			break;
		case BLUE:
			led_rgb_enviar_color(0, 0, 255);
			break;
		case YELLOW:
			led_rgb_enviar_color(255, 255, 0);
			break;
		case MAGENTA:
			led_rgb_enviar_color(255, 0, 255);
			break;
		case CYAN:
			led_rgb_enviar_color(0, 255, 255);
			break;
		case ORANGE:
			led_rgb_enviar_color(255, 165, 0);
			break;
		case VIOLET:
			led_rgb_enviar_color(128, 0, 255);
			break;
		case PINK:
			led_rgb_enviar_color(255, 192, 203);
			break;
		case TURQUOISE:
			led_rgb_enviar_color(93, 193, 185);
			break;
		case AMBER:
			led_rgb_enviar_color(255, 191, 0);
			break;
		case EMERALD:
			led_rgb_enviar_color(0, 157, 113);
			break;
		case MAROON:
			led_rgb_enviar_color(128, 0, 0);
			break;
		case SKYBLUE:
			led_rgb_enviar_color(128, 191, 255);
			break;
		case BROWN:
			led_rgb_enviar_color(128, 64, 0);
			break;
		case PURPLE:
			led_rgb_enviar_color(128, 0, 128);
			break;
		case LIME:
			led_rgb_enviar_color(191, 255, 0);
			break;
		case FUCHSIA:
			led_rgb_enviar_color(255, 0, 128);
			break;
		case INDIGO:
			led_rgb_enviar_color(28, 76, 150);
			break;
		case GRAY:
			led_rgb_enviar_color(128, 128, 128);
			break;
		default: // si no se especifica un color existente se apaga el led
			led_rgb_apagar();
			break;
	}
	
}

void HAL_ledrgb_parpadeo(uint8_t color, uint16_t duracion)
{
	uint16_t tiempo = 0;

	while (tiempo < duracion)
	{
		HAL_ledrgb_color(color);
		_delay_ms(200);
		tiempo += 200;

		led_rgb_apagar();
		_delay_ms(200);
		tiempo += 200;
	}
}

void HAL_ledrgb_efecto_breathing(uint8_t r_base, uint8_t g_base, uint8_t b_base, uint16_t pasos, uint16_t duracion)
{
	float intensidad;
	uint8_t r, g, b;
	uint16_t tiempo = 0;

	while (tiempo < duracion)
	{
		for (uint16_t i = 0; i < pasos && tiempo < duracion; i++) // fade-in
		{
			intensidad = (1.0 - cos((float)i / pasos * 3.14159)) / 2.0; // control de intensidad
			r = (uint8_t)(r_base * intensidad);
			g = (uint8_t)(g_base * intensidad);
			b = (uint8_t)(b_base * intensidad);
			led_rgb_enviar_color(r, g, b);
			_delay_ms(20);
			tiempo += 20;
		}

		for (uint16_t i = pasos; i > 0 && tiempo < duracion; i--) // fade-out
		{
			intensidad = (1.0 - cos((float)i / pasos * 3.14159)) / 2.0; // control de intensidad
			r = (uint8_t)(r_base * intensidad);
			g = (uint8_t)(g_base * intensidad);
			b = (uint8_t)(b_base * intensidad);
			led_rgb_enviar_color(r, g, b);
			_delay_ms(20);
			tiempo += 20;
		}
	}
}

void HAL_ledrgb_efecto_arcoiris(uint16_t duracion)
{
	uint8_t r, g, b;
	uint8_t hue = 0;
	uint16_t tiempo = 0;

	while (tiempo < duracion)
	{
		led_rgb_hue_a_rgb(hue++, &r, &g, &b); // Convierte el matiz actual a RGB y envía el color al LED
		led_rgb_enviar_color(r, g, b);
		_delay_ms(20);
		tiempo += 20;
	}
}

void HAL_ledrgb_apagar()
{
	led_rgb_apagar();
}