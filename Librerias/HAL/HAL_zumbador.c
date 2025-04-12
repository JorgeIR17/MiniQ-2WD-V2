#include <avr/io.h>
#include "HAL_zumbador.h"

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

