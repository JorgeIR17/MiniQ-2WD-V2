#include "HAL_motores.h"

void HAL_motores_avanzar(int8_t velocidad)
{
    motor_set_speed(MOTOR_IZQUIERDO, velocidad);
    motor_set_speed(MOTOR_DERECHO, velocidad);
}

void HAL_motores_girar(int8_t velocidad_izq, int8_t velocidad_der)
{
    motor_girar(velocidad_izq, velocidad_der);
}

void HAL_motores_detener()
{
    motor_stop();
}