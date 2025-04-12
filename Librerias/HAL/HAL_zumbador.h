#ifndef HAL_ZUMBADOR_H_
#define HAL_ZUMBADOR_H_

#include <avr/io.h>
#include "../LowLevel/BUZZER.h"

// Definicion de tipos de alertas

#define INICIO 1
#define ACIERTO 2
#define ERROR 3


static inline void HAL_zumbador_init()
{
    buzzer_init();
}

void HAL_zumbador_alerta(uint8_t tipo);

void HAL_zumbador_detener();

#endif /* HAL_ZUMBADOR_H_ */