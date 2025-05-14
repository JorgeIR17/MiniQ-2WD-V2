/**
 * @file ENCODERS.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de los encoders.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ENCODERS_H_
#define ENCODERS_H_

#include <avr/io.h>
#include "../Peripherals/GPIO.h"
#include "../Peripherals/TMR3.h"

#define ENCODER_IZQUIERDO 0
#define ENCODER_DERECHO 1

/**
 * @brief Inicializa los encoders.
 * 
 */
static inline void encoders_init()
{
    encoderpins_init();
    TMR3_CTC_Init();        // Configurar Timer 3 en modo CTC
    TMR3_CTC_Set(15624);    // Configurar OCR3A para 100 ms (con prescaler 64)
    TMR3_CTC_enaInterrupt(); // Habilitar interrupción
    TMR3_CTC_Start(DIV_CLK_64); // Iniciar con prescaler 64
	pulsos_izq = 0;
	pulsos_der = 0;
	interval_izq = 1;
	interval_der = 1;
	rpm_izq = 0;
	rpm_der = 0;
}

/**
 * @brief Lee los pulsos de un encoder.
 * 
 * @param encoder Encoder derecho o izquierdo. Es necesario hacer uso de las macros proporcionadas.
 * @return uint16_t Número de pulsos acumulados por el encoder.
 */
uint16_t encoder_leer(uint8_t encoder);

/**
 * @brief Calcula la velocidad de una rueda.
 * 
 * @param encoder Encoder derecho o izquierdo. Es necesario hacer uso de las macros proporcionadas.
 * @return uint16_t Velocidad de la rueda en RPM.
 */
uint16_t encoder_get_speed(uint8_t encoder);

/**
 * @brief Reinicia el contador de pulsos de un encoder.
 * 
 * @param encoder Encoder derecho o izquierdo. Es necesario hacer uso de las macros proporcionadas.
 */
void encoder_reset(uint8_t encoder);

#endif /* ENCODERS_H_ */