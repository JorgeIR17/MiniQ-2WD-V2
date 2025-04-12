#include "BUZZER.h"


void buzzer_tone(uint8_t nTicks_beepFreq, uint16_t nTicks_beepDuration)
{
	TMR0_CTC_Set(nTicks_beepFreq);
	TMR1_CTC_Set((nTicks_beepDuration * (F_CPU / 1024)) / 1000);
	
	TMR0_CTC_Start(DIV_CLK_256);
	TMR1_CTC_Start(DIV_CLK_1024);
}

void buzzer_stop()
{
	TMR0_CTC_Stop();
	TMR1_CTC_Stop();
}
