#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../Peripherals/TMR0.h"
#include "../Peripherals/TMR1.h"
#include "../Peripherals/GPIO.h"

#define STARTING_SOUND 62
#define STARTING_SOUND_DURATION 1000 // 1000 ms

#define MATCH_SOUND 39
#define MATCH_SOUND_DURATION 500 // 500 ms

#define FAIL_SOUND 125
#define FAIL_SOUND_DURATION 1000 // 1000 ms

// Function to set buzzer pin as output
static inline void buzzer_init()
{
	OC_init();
	
	TMR0_CTC_Init();
	TMR0_CTC_enaInterrupt();
	TMR1_CTC_Init();
	TMR1_CTC_enaInterrupt();
	
	sei();
}

void buzzer_tone(uint8_t nTicks_beepFreq, uint16_t nTicks_beepDuration);

void buzzer_stop();

#endif