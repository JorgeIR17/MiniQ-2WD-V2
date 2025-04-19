#ifndef LED_RGB_H_
#define LED_RGB_H_

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Peripherals/GPIO.h"

static inline void led_rgb_init()
{
	rgb_pin_init();
}

void led_rgb_enviar_bit(uint8_t bit_value);

void led_rgb_enviar_byte(uint8_t byte);

void led_rgb_enviar_color(uint8_t red, uint8_t green, uint8_t blue);

void led_rgb_hue_a_rgb(uint8_t hue, uint8_t* r, uint8_t* g, uint8_t* b);

void led_rgb_apagar();

#endif /* LED_RGB_H_ */