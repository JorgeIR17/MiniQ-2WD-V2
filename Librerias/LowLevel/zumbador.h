/**
 * @file zumbador.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso del zumbador.
 * @version 1.0
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ZUMBADOR_H_
#define ZUMBADOR_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Peripherals/tmr0.h"
#include "../Peripherals/tmr1.h"
#include "../Peripherals/gpio.h"

// Pin del zumbador
#define BUZZER_DDR      DDRB
#define BUZZER_PORT     PORTB
#define BUZZER_PIN      DDB2  // PB2

/**
 * @brief Inicializa el zumbador.
 * 
 */
static inline void zumbador_init()
{
	GPIO_Init(&BUZZER_DDR, BUZZER_PIN, OUTPUT);
	
	TMR0_CTC_Init();
	TMR0_CTC_enaInterrupt();
	TMR1_CTC_Init();
	TMR1_CTC_enaInterrupt();
	
	sei();
}

/**
 * @brief Emite un sonido dadas una frecuencia y una duración.
 * 
 * @param nTicks_beepFreq Frecuencia del sonido.
 * @param nTicks_beepDuration Duración del sonido en milisegundos.
 */
void zumbador_tone(uint8_t nTicks_beepFreq, uint16_t nTicks_beepDuration);

/**
 * @brief Detiene cualquier sonido emitido por el zumbador.
 * 
 */
void zumbador_stop();

#endif