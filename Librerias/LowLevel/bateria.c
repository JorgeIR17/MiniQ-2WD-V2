/**
 * @file bateria.c
 * @author Jorge Ibáñez
 * @brief Definición de los drivers de bajo nivel para el uso del medidor de batería.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "bateria.h"

float bateria_get_voltage()
{
    uint16_t value = ADC_Read_Single_Poll(BATTERY_CHANNEL);
    float voltage = (value / 1023.0) * VREF; // Convierte el valor de ADC a voltaje
    voltage = voltage * DIVISOR_RATIO; // Aplica el factor del divisor resistivo para obtener el voltaje real
    return voltage;
}


float bateria_get_percentage()
{
    float voltage = bateria_get_voltage();
    float percentage = (voltage - BATTERY_MIN) / (BATTERY_MAX - BATTERY_MIN) * 100.0; // Se usa una regla de tres para normalizar el voltaje en un rango de 0 a 100%

    if (percentage > 100.0) percentage = 100.0;
    if (percentage < 0.0) percentage = 0.0;

    return percentage;
}
