#define  F_CPU 16000000UL
#include <avr/io.h>
#include "ADC.h"


uint16_t ADC_Read_Single_Poll(uint8_t channel)
{
	ADCSRA |= (1<<ADIF); // Clear ADC interrupt flag
	ADMUX = (ADMUX & 0b11100000); // Clear channel selection bits
	ADMUX |= (channel<<MUX0); // Set channel
	ADCSRA |= (1<<ADSC); // Start conversion

	while(!(ADCSRA & (1<<ADIF))){} // Wait for conversion to complete

	return ADC;
}

uint16_t ADC_Read_Multiple_Poll(uint8_t channel, uint8_t times)
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
