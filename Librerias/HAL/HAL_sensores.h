#ifndef HAL_SENSORES_H_
#define HAL_SENSORES_H_

#include <avr/io.h>
#include "../LowLevel/SENSORES.h"

#define ERROR_LINEA 10
#define NADA 20

static inline void HAL_sensores_init()
{
    sensores_init();
	sensores_calibrar();
}

int8_t HAL_sensores_obtener_posicion();

uint16_t HAL_sensores_leer(uint8_t sensor);

#endif /* HAL_SENSORES_H_ */