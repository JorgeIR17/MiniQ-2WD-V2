/**
 * @file ADC.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso del ADC.
 * @version 0.1
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define AVCC 1
#define AREF 0
#define ALIGN_LEFT 1
#define ALIGN_RIGHT 0
#define PRESCALER_128 7

// Channels
#define ADC0	0
#define ADC1	1
#define ADC4	4
#define ADC5	5
#define ADC6	6
#define ADC7	7
#define ADC8	8
#define ADC12   12

/**
 * @brief Inicializa el ADC.
 * 
 */
static inline void ADC_init()
{
    //Delete previous configuration
    ADMUX = 0;
    ADCSRA = 0;

    ADMUX |= (AVCC << REFS0); // Set reference voltage
    ADMUX |= (ALIGN_RIGHT << ADLAR); // Set alignment
    ADCSRA |= (PRESCALER_128 << ADPS0); // Set prescaler
    ADCSRA |= (1 << ADEN); // Enable ADC
    ADCSRA &= ~(1 << ADATE); // Single mode
}

/**
 * @brief Realiza una lectura de un canal ADC mediante polling.
 * 
 * @param channel Canal ADC seleccionado.
 * @return uint16_t Valor obtenido por el ADC.
 */
uint16_t ADC_Read_Single_Poll(uint8_t channel);

/**
 * @brief Realiza múltiples lecturas determinadas de un canal de un canal ADC mediante polling.
 * 
 * @param channel Canal ADC seleccionado.
 * @param times Número de lecturas realizadas.
 * @return uint16_t Valor medio obtenido por el ADC.
 */
uint16_t ADC_Read_Multiple_Poll(uint8_t channel, uint8_t times);

#endif /* ADC_H_ */
