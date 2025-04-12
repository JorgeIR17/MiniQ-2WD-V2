#ifndef HAL_ENCODERS_H_
#define HAL_ENCODERS_H_

#include "../LowLevel/ENCODERS.h"

#define DIAMETRO_RUEDA_MM 42.0
#define PI 3.1416               // Valor de ?
#define MM_POR_PULSO 5.28

static inline void HAL_encoders_init()
{
	encoders_init();
}

uint16_t HAL_encoders_get_speed(uint8_t encoder);

uint16_t HAL_encoders_get_distance(uint8_t encoder);

void HAL_encoders_reset(uint8_t encoder);

#endif /* HAL_ENCODERS_H_ */