/**
 * @file tmr1.c
 * @author Jorge Ibáñez
 * @brief Definición de la interrupción ejecutada por el Timer 1 del ATMega32U4.
 * @version 1.0
 * @date 2025-05-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "tmr1.h"

/**
 * @brief Interrupción del Timer 1.
 * 
 * Esta interrupción se encarga de detener el sonido del zumbador cuando se alcance la duración indicada, limpiando el valor del pin conectado al zumbador y deteniendo los timers 0 y 1.
 * 
 */
ISR(TIMER1_COMPA_vect)
{
    //PORTB &= ~(1<<BUZZER_PIN);
    GPIO_Write(&PORTB, DDB2, LOW);
    TMR0_CTC_Stop();
    TMR1_CTC_Stop();
}