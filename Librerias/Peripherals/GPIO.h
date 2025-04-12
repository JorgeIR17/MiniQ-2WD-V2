#ifndef GPIO_H_
#define GPIO_H_

#include <avr/io.h>
#include "PWM.h"

static inline void puenteH_init()
{
	DDRE |= (1<<EN2);
	DDRD |= (1<<EN1);
}

static inline void encoderpins_init() 
{
    DDRD &= ~((1 << PD0) | (1 << PD2));  // Configurar PD0 y PD2 como entrada
    PORTD |= (1 << PD0) | (1 << PD2);    // Activar pull-up interno

    EICRA |= (1 << ISC20) | (1 << ISC30); // Flanco de subida
    EIMSK |= (1 << INT2) | (1 << INT3);   // Habilitar INT2 y INT3
}

#endif /* GPIO_H_ */