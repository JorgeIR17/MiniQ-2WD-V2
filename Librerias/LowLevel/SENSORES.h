#ifndef SENSORES_H_
#define SENSORES_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include "../Peripherals/ADC.h"

#define IR0 ADC7
#define IR1 ADC6
#define IR2 ADC5
#define IR3 ADC4
#define IR4 ADC1

// Definicion posicion sensores

#define IZQUIERDA 0
#define IZQUIERDA_CENTRO 1
#define CENTRO 2
#define DERECHA_CENTRO 3
#define DERECHA 4

#define WHITE 900
#define BLACK 600

volatile uint16_t blanco;
volatile uint16_t negro;

static inline void sensores_init()
{
    ADC_init();
	blanco = WHITE;
	negro = BLACK;
}

uint16_t sensores_leer(uint8_t sensor);

void sensores_calibrar();

#endif /* SENSORES_H_ */