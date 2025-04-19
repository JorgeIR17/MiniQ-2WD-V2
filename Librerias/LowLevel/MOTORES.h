#ifndef MOTORES_H_
#define MOTORES_H_

#include <avr/io.h>
#include "../Peripherals/PWM.h"
#include "../Peripherals/GPIO.h"

#define MOTOR_IZQUIERDO 0
#define MOTOR_DERECHO   1

static inline void motores_init()
{
	puenteH_init();
    PWM_Init();
	PWM_Stop();
}

void motor_set_speed(uint8_t motor, int16_t velocidad);

void motor_stop();

void motor_girar(int16_t velocidad_izq, int16_t velocidad_der);


#endif /* MOTORES_H_ */
