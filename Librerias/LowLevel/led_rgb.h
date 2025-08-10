/**
 * @file led_rgb.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso del LED RGB.
 * @version 1.0
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

// Pin del LED RGB
#define RGB_DDR         DDRB
#define RGB_PORT        PORTB
#define RGB_PIN         DDB6

/**
 * @brief Inicializa el LED RGB.
 * 
 */
static inline void led_rgb_init()
{
	GPIO_Init(&RGB_DDR, RGB_PIN, OUTPUT);
    GPIO_Write(&RGB_PORT, RGB_PIN, LOW);
	
	TMR3_CTC_Init();        // Configurar Timer 3 en modo CTC
	TMR3_CTC_Set(49999);    // Configurar OCR3A para 200 ms (con prescaler 64)
	TMR3_CTC_enaInterrupt(); // Habilitar interrupcion
	TMR3_CTC_Start(DIV_CLK_64); // Iniciar con prescaler 64
	blink = true;
	blink_time = 0;
	
	sei();
}

/**
 * @brief Envia un bit al LED.
 * 
 * @param bit Valor del bit.
 */
void led_rgb_send_bit(uint8_t bit);

/**
 * @brief Envia un byte al LED.
 * 
 * @param byte Valor del byte.
 */
void led_rgb_send_byte(uint8_t byte);

/**
 * @brief Envía un color al LED según su código RGB.
 * 
 * @param red Valor del componente R.
 * @param green Valor del componente G.
 * @param blue Valor del componente B.
 */
void led_rgb_send_color(uint8_t red, uint8_t green, uint8_t blue);


/**
 * @brief Apaga el LED RGB.
 * 
 */
void led_rgb_off();

#endif /* LED_RGB_H_ */