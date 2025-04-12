#ifndef HAL_MOTORES_H_
#define HAL_MOTORES_H_

#include <avr/io.h>
#include "../LowLevel/MOTORES.h"

static inline void HAL_motores_init()
{
    motores_init();
}

void HAL_motores_avanzar(int8_t velocidad);

void HAL_motores_girar(int8_t velocidad_izq, int8_t velocidad_der);

void HAL_motores_detener();

#endif /* HAL_MOTORES_H_ */