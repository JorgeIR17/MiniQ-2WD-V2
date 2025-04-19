#ifndef HAL_LEDRGB_H_
#define HAL_LEDRGB_H_

#include "../LowLevel/LED_RGB.h"

// Definicion de colores (Inglés y Español)

#define WHITE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define YELLOW 4
#define MAGENTA 5
#define CYAN 6
#define ORANGE 7
#define VIOLET 8
#define PINK 9
#define TURQUOISE 10
#define AMBER 11
#define EMERALD 12
#define MAROON 13
#define SKYBLUE 14
#define BROWN 15
#define PURPLE 16
#define LIME 17
#define FUCHSIA 18
#define INDIGO 19
#define GRAY 20

#define BLANCO WHITE
#define ROJO RED
#define VERDE GREEN
#define AZUL BLUE
#define AMARILLO YELLOW
#define CIAN CYAN
#define NARANJA ORANGE
#define VIOLETA VIOLET
#define ROSA PINK
#define TURQUESA TURQUOISE 
#define AMBAR AMBER
#define ESMERALDA EMERALD
#define GRANATE MAROON
#define CELESTE SKYBLUE
#define MARRON BROWN
#define PURPURA PURPLE
#define LIMA LIME
#define FUCSIA FUCHSIA
#define ANIL INDIGO
#define GRIS GRAY

static inline void HAL_ledrgb_init()
{
	led_rgb_init();
}

void HAL_ledrgb_color(uint8_t color);

void HAL_ledrgb_parpadeo(uint8_t color, uint16_t duracion);

void HAL_ledrgb_efecto_breathing(uint8_t r_base, uint8_t g_base, uint8_t b_base, uint16_t pasos, uint16_t duracion);

void HAL_ledrgb_efecto_arcoiris(uint16_t duracion);

void HAL_ledrgb_apagar();

#endif /* HAL_LEDRGB_H_ */