#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

#define PWM_DIV_CLK_1	   1
#define PWM_DIV_CLK_2	   2
#define PWM_DIV_CLK_4	   3
#define PWM_DIV_CLK_8	   4
#define PWM_DIV_CLK_16     5
#define PWM_DIV_CLK_32	   6
#define PWM_DIV_CLK_64	   7
#define PWM_DIV_CLK_128    8
#define PWM_DIV_CLK_256    9
#define PWM_DIV_CLK_512    10
#define PWM_DIV_CLK_1024   11
#define PWM_DIV_CLK_2048   12
#define PWM_DIV_CLK_4096   13
#define PWM_DIV_CLK_8192   14
#define PWM_DIV_CLK_16384  15

#define EN1 DDD6
#define EN2 DDE6

#define FORWARD 0
#define BACKWARD 1

static inline void PWM_Init()
{
	DDRC |= (1<<DDC6); // Set OC4A (PC6) as output
	DDRD |= (1<<DDD7); // Set OC4D (PD7) as output

	TCCR4A |= (1<<COM4A0) | (1<<PWM4A);
	TCCR4A &= ~(1<<COM4A1);

	TCCR4C |= (1<<COM4D1) | (1<<PWM4D);
	TCCR4C &= ~(1<<COM4D0);

	TCCR4D &= ~(1<<WGM41);
	TCCR4D |= (1<<WGM40);
}

inline void PWM_Start(uint8_t divClock)
{
	TCNT4 = 0; // Reset counter

	TCCR4B &= 0b11110000; // Clear CS40, CS41, CS42
	TCCR4B |= (divClock<<CS40);
}



inline void PWM_set_duty_cycle(uint8_t motor, uint8_t value)
{
	if(motor == 0)
		OCR4A = ~(value);
	else
		OCR4D = value;
}

inline void PWM_set_direction(uint8_t motor, uint8_t direction)
{
	if(motor == 0)
	{
		if(direction == FORWARD)
			PORTD &= ~(1<<EN1);
		if(direction == BACKWARD)
			PORTD |= (1<<EN1);
	}
	else
	{	
		if(direction == FORWARD)
			PORTE &= ~(1<<EN2);
		if(direction == BACKWARD)
			PORTE |= (1<<EN2);
	}
}

inline void PWM_Stop()
{
	TCCR4B &= 0b11110000;

	PWM_set_duty_cycle(0, 0);
	PWM_set_duty_cycle(1, 0);
}

#endif /* PWM_H_ */
