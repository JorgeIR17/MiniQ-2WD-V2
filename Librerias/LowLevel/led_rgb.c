/**
 * @file led_rgb.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del led RGB.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "led_rgb.h"

void led_rgb_enviar_bit(uint8_t bit)
{
	// Comunicación según el protocolo WS2812: codificación por temporización

	if (bit)
	{
		// Enviar '1': mantener el pin en HIGH ~0.7 µs, luego LOW ~0.6 µs
		GPIO_Write(&RGB_PORT, RGB_PIN, HIGH);
		_delay_us(0.7);
		GPIO_Write(&RGB_PORT, RGB_PIN, LOW);
		_delay_us(0.6);
	}
	else
	{
		// Enviar '0': mantener el pin en HIGH ~0.35 µs, luego LOW ~0.8 µs
		GPIO_Write(&RGB_PORT, RGB_PIN, HIGH);
		_delay_us(0.35);
		GPIO_Write(&RGB_PORT, RGB_PIN, LOW);
		_delay_us(0.8);
	}
}



void led_rgb_enviar_byte(uint8_t byte)
{
	for (uint8_t i = 0; i < 8; i++) // Se recorre el byte desde el MSB (7) hasta el LSB (0)
	{
		led_rgb_enviar_bit(byte & (1 << (7 - i))); // El bit actual se evalua con un AND bit a bit y se envia
	}
}

void led_rgb_enviar_color(uint8_t red, uint8_t green, uint8_t blue)
{
	cli();  // Desactiva interrupciones temporalmente
	led_rgb_enviar_byte(green/10); // Valores reducidos para reducir intensidad por seguridad
	led_rgb_enviar_byte(red/10);
	led_rgb_enviar_byte(blue/10);
	sei();  // Reactiva interrupciones
	_delay_us(50);  // Reset
}

void led_rgb_apagar() 
{
	led_rgb_enviar_color(0, 0, 0);
}