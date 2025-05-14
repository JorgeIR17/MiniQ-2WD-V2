/**
 * @file GPIO.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso de los GPIO.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "GPIO.h"

void rgb_send_bit(uint8_t bit_value)
{
	if (bit_value)
	{
		PORTB |= (1 << PB6);
		_delay_us(0.7);
		PORTB &= ~(1 << PB6);
		_delay_us(0.6);
	}
	else
	{
		PORTB |= (1 << PB6);
		_delay_us(0.35);
		PORTB &= ~(1 << PB6);
		_delay_us(0.8);
	}
}