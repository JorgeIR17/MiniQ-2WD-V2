#ifndef ENCODERS_H_
#define ENCODERS_H_

#include <avr/io.h>
#include "../Peripherals/GPIO.h"
#include "../Peripherals/TMR3.h"

#define ENCODER_IZQUIERDO 0
#define ENCODER_DERECHO 1

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

uint16_t encoder_leer(uint8_t encoder);

uint16_t encoder_get_speed(uint8_t encoder);

void encoder_reset(uint8_t encoder);

#endif /* ENCODERS_H_ */