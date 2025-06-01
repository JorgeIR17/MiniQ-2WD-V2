/**
 * @file hal_zumbador.c
 * @author Jorge Ibáñez
 * @brief Definición de la capa HAL para el uso del zumbador.
 * @version 0.1
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
        buzzer_tone(STARTING_SOUND, STARTING_SOUND_DURATION);
    if(tipo == ACIERTO)
        buzzer_tone(MATCH_SOUND, MATCH_SOUND_DURATION);
    if(tipo == ERROR)
        buzzer_tone(FAIL_SOUND, FAIL_SOUND_DURATION);
}

void HAL_zumbador_detener()
{
    buzzer_stop();
}

