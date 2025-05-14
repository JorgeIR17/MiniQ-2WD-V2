/**
 * @file HAL_motores.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso de los motores
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "HAL_motores.h"

void HAL_motores_avanzar(int16_t velocidad)
{
    motor_set_speed(MOTOR_IZQUIERDO, velocidad);
    motor_set_speed(MOTOR_DERECHO, velocidad);
}

void HAL_motores_girar(int16_t velocidad_izq, int16_t velocidad_der)
{
    motor_girar(velocidad_izq, velocidad_der);
}

void HAL_motores_detener()
{
    motor_stop();
}