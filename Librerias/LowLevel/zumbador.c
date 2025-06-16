/**
 * @file zumbador.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del zumbador.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "zumbador.h"


void zumbador_tone(uint8_t nTicks_beepFreq, uint16_t nTicks_beepDuration)
{
	TMR0_CTC_Set(nTicks_beepFreq);
	TMR1_CTC_Set((nTicks_beepDuration * (F_CPU / 1024)) / 1000);
	
	TMR0_CTC_Start(DIV_CLK_256);
	TMR1_CTC_Start(DIV_CLK_1024);
}

void zumbador_stop()
{
	TMR0_CTC_Stop();
	TMR1_CTC_Stop();
}
