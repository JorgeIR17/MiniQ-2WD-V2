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

static inline void ADC_select_channel(uint16_t channel)
{
    ADMUX = (ADMUX & 0b11100000); // Clear channel selection bits
    ADMUX |= (channel << MUX0); // Set channel
}

static inline void ADC_enableInt()
{
    ADCSRA |= (1<<ADIE); // Enable ADC interrupt
}

static inline void ADC_disableInt()
{
    ADCSRA &= ~(1<<ADIE); // Disable ADC interrupt
}

static inline void ADC_START()
{
    ADCSRA |= (1<<ADSC); // Start conversion
}

uint16_t ADC_Read_Single_Poll(uint8_t channel);

uint16_t ADC_Read_Multiple_Poll(uint8_t channel, uint8_t times);

#endif /* ADC_H_ */
