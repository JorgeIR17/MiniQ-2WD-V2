/**
 * @file HAL_ledrgb.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso del led RGB
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "HAL_ledrgb.h"

void HAL_ledrgb_color(uint8_t color)
{
	switch(color) // Envia el codigo RGB segun el color
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

#include <avr/io.h>

/**
 * @brief Delay en microsegundos (us), sin usar timers ni <util/delay.h>.
 * 
 * Aproximado para una frecuencia de CPU de 16 MHz.
 * Cada iteración de bucle consume ~4 ciclos de reloj.
 * 
 * @param us Cantidad de microsegundos a esperar (máx ~4000)
 */
void delay_us(uint16_t us) {
    while (us--) {
        // 1 us = 16 ciclos -> ajustamos el bucle interno para ~1 us
        // Cada iteración son ~4 ciclos (2 por sbiw, 2 por brne)
        // Requiere 4 iteraciones para ~1 us

        for (uint8_t i = 0; i < 4; i++) {
            asm volatile("nop");
        }
    }
}

/**
 * @brief Delay en milisegundos (ms), usa delay_us internamente.
 * 
 * @param ms Cantidad de milisegundos a esperar
 */
void delay_ms(uint16_t ms) {
    while (ms--) {
        delay_us(1000);
    }
}


void HAL_ledrgb_parpadeo(uint8_t color, uint16_t duracion)
{
	uint16_t tiempo = duracion / 100;

	while (tiempo > 0)
	{
		if(blink)
			HAL_ledrgb_color(color);
		else
			led_rgb_apagar();
		tiempo--;
	}
}

void HAL_ledrgb_efecto_breathing(uint8_t color, uint16_t pasos, uint16_t duracion) {
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
		default:        led_rgb_apagar(); return;
	}

	while (tiempo < duracion) {
		// Subida de intensidad
		for (uint16_t i = 0; i < pasos && tiempo < duracion; i++) {
			intensidad = (1.0 - cos((float)i / pasos * 3.14159)) / 2.0;
			r = (uint8_t)(r_base * intensidad);
			g = (uint8_t)(g_base * intensidad);
			b = (uint8_t)(b_base * intensidad);
			led_rgb_enviar_color(r, g, b);
			_delay_ms(20);
			tiempo += 20;
		}

		// Bajada de intensidad
		for (uint16_t i = pasos; i > 0 && tiempo < duracion; i--) {
			intensidad = (1.0 - cos((float)i / pasos * 3.14159)) / 2.0;
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
		led_rgb_hue_a_rgb(hue++, &r, &g, &b); // Convierte el matiz actual a RGB y env�a el color al LED
		led_rgb_enviar_color(r, g, b);
		_delay_ms(20);
		tiempo += 20;
	}
}

void HAL_ledrgb_apagar()
{
	led_rgb_apagar();
}