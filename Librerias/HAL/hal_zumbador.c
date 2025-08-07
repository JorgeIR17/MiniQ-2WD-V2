/**
 * @file hal_zumbador.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso del zumbador.
 * @version 1.0
 * @date 2025-05-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <avr/io.h>
#include "hal_zumbador.h"

void HAL_zumbador_alerta(uint8_t tipo)
{
    if(tipo == INICIO)
        zumbador_tone(STARTING_SOUND, STARTING_SOUND_DURATION);
    if(tipo == ACIERTO)
        zumbador_tone(MATCH_SOUND, MATCH_SOUND_DURATION);
    if(tipo == ERROR)
        zumbador_tone(FAIL_SOUND, FAIL_SOUND_DURATION);
}

void HAL_zumbador_nota(uint8_t nota, uint16_t duracion)
{
    zumbador_tone(nota, duracion);
}

void HAL_zumbador_detener()
{
    zumbador_stop();
}

