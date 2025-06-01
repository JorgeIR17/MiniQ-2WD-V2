/**
 * @file hal_ledrgb.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso del led RGB
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_LEDRGB_H_
#define HAL_LEDRGB_H_

#include "../LowLevel/led_rgb.h"

// Definicion de colores
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

/**
 * @brief Inicializa el led RGB.
 * 
 */
static inline void HAL_ledrgb_init()
{
	led_rgb_init();
}

/**
 * @brief Ilumina el led RGB con el color indicado.
 * 
 * @param color Color del led. Es necesario hacer uso de las macros proporcionadas. Los nombres de los colores se encuentran disponibles en Español y en Inglés.
 */
void HAL_ledrgb_color(uint8_t color);

/**
 * @brief Realiza un efecto de parpadeo del led de un color durante un tiempo dado.
 * 
 * @param color Color del led. Es necesario hacer uso de las macros proporcionadas. Los nombres de los colores se encuentran disponibles en Español y en Inglés.
 * @param duracion Duración en milisegundos.
 */
void HAL_ledrgb_parpadeo(uint8_t color, uint16_t duracion);

/**
 * @brief Realiza un efecto de respiración del led de un color durante un tiempo dado.
 * 
 * @param color Color del led. Es necesario hacer uso de las macros proporcionadas. Los nombres de los colores se encuentran disponibles en Español y en Inglés.
 * @param pasos Indica el número de pasos del efecto. A mayor número de pasos, la intensidad aumentará de forma más progresiva.
 * @param duracion Duración en milisegundos.
 */
void HAL_ledrgb_efecto_breathing(uint8_t color, uint16_t pasos, uint16_t duracion);

/**
 * @brief Realiza un efecto de arcoiris del led durante un tiempo dado.
 * 
 * @param duracion Duración en milisegundos.
 */
void HAL_ledrgb_efecto_arcoiris(uint16_t duracion);

/**
 * @brief Apaga el led.
 * 
 */
void HAL_ledrgb_apagar();

#endif /* HAL_LEDRGB_H_ */