#include "TMR3.h"

// ISR para el encoder izquierdo (INT2)
ISR(INT2_vect) { pulsos_der++; }

// ISR para el encoder derecho (INT3)
ISR(INT3_vect) { pulsos_izq++; }

// ISR del Timer4 (cada 100ms)
ISR(TIMER3_COMPA_vect) {
    rpm_izq = ((uint32_t)pulsos_izq * 600) / (PULSOS_POR_VUELTA * interval_izq); // uint32_t para evitar overflow
    rpm_der = ((uint32_t)pulsos_der * 600) / (PULSOS_POR_VUELTA * interval_der); // uint32_t para evitar overflow
	interval_izq++;
	interval_der++;
}