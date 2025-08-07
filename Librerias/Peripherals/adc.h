/**
 * @file adc.h
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del ADC.
 * @version 1.0
 * @date 2025-05-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef ADC_H_
#define ADC_H_

#define F_CPU 16000000UL
#include <avr/io.h>

#define AVCC 1
#define AREF 0
#define ALIGN_LEFT 1
#define ALIGN_RIGHT 0
#define PRESCALER_128 7

// Canales
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
static inline void ADC_Init()
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
static inline uint16_t ADC_Read_Single_Poll(uint8_t channel)
{
	ADCSRA |= (1<<ADIF); // Clear ADC interrupt flag
	ADMUX = (ADMUX & 0b11100000); // Clear channel selection bits
	ADCSRB = (ADCSRB & 0b11011111);
	if(channel == ADC8) // Lectura pulsadores
	{
		ADCSRB |= (1 << MUX5);
	}
	else if(channel == ADC12) // Lectura medidor bateria
	{
		ADCSRB |= (1 << MUX5);
		ADMUX |= (4 << MUX0); // 100
	}
	else
	{
		ADMUX |= (channel<<MUX0); // Set channel
	}
	ADCSRA |= (1<<ADSC); // Start conversion

	while(!(ADCSRA & (1<<ADIF))){} // Wait for conversion to complete

	return ADC;
}


/**
 * @brief Realiza múltiples lecturas determinadas de un canal de un canal ADC mediante polling.
 * 
 * @param channel Canal ADC seleccionado.
 * @param times Número de lecturas realizadas.
 * @return uint16_t Valor medio obtenido por el ADC.
 */
static inline uint16_t ADC_Read_Multiple_Poll(uint8_t channel, uint8_t times)
{
	uint16_t aux = ADC_Read_Single_Poll(channel); // Perform one conversion to initialize ADC
	uint16_t value = 0; 
	for (uint8_t i = 1; i < times; i++)
    {
		aux += ADC_Read_Single_Poll(channel); // Sum up ADC readings
	}

	// Right shift the sum based on the number of readings
	switch(times)
    {
		case 1: break;
		case 2: value = (aux >> 1); break;
		case 4: value = (aux >> 2); break;
		case 8: value = (aux >> 3); break;
		case 16:value = (aux >> 4); break;
		default:value = aux / times; break; // If times is not a power of 2, divide by times
	}
	return value;
}

#endif /* ADC_H_ */
