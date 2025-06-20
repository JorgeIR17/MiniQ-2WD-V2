/**
 * @file led_rgb.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso del led RGB.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef LED_RGB_H_
#define LED_RGB_H_

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../Peripherals/gpio.h"
#include "../Peripherals/tmr3.h"

/**
 * @brief Inicializa el led RGB.
 * 
 */
static inline void led_rgb_init()
{
	GPIO_Init(&RGB_DDR, RGB_PIN, OUTPUT);
    GPIO_Write(&RGB_PORT, RGB_PIN, LOW);
	
	TMR3_CTC_Init();        // Configurar Timer 3 en modo CTC
	TMR3_CTC_Set(15624);    // Configurar OCR3A para 100 ms (con prescaler 64)
	TMR3_CTC_enaInterrupt(); // Habilitar interrupcion
	TMR3_CTC_Start(DIV_CLK_64); // Iniciar con prescaler 64
	blink = true;
	blink_time = 0;
	
	sei();
}

/**
 * @brief Envia un bit al led.
 * 
 * @param bit Valor del bit.
 */
void led_rgb_enviar_bit(uint8_t bit);

/**
 * @brief Envia un byte al led.
 * 
 * @param byte Valor del byte.
 */
void led_rgb_enviar_byte(uint8_t byte);

/**
 * @brief Envía un color al led según su código RGB.
 * 
 * @param red Valor del componente R.
 * @param green Valor del componente G.
 * @param blue Valor del componente B.
 */
void led_rgb_enviar_color(uint8_t red, uint8_t green, uint8_t blue);



void led_rgb_apagar();

#endif /* LED_RGB_H_ */