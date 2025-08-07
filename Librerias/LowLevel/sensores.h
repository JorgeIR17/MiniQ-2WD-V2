/**
 * @file sensores.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de los sensores infrarrojos.
 * @version 1.0
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SENSORES_H_
#define SENSORES_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include "../Peripherals/adc.h"

// Canales ADC de los sensores
#define IR0 ADC7
#define IR1 ADC6
#define IR2 ADC5
#define IR3 ADC4
#define IR4 ADC1

// Definicion posicion sensores
#define IZQUIERDA 0
#define IZQUIERDA_CENTRO 1
#define CENTRO 2
#define DERECHA_CENTRO 3
#define DERECHA 4

// Definicion de valores base de blanco y negro
#define WHITE_SENSOR 900
#define BLACK_SENSOR 600

volatile uint16_t blanco;
volatile uint16_t negro;

/**
 * @brief Inicializa los sensores IR.
 * 
 */
static inline void sensores_init()
{
    ADC_Init();
	blanco = WHITE_SENSOR; // Valor base de blanco
	negro = BLACK_SENSOR; // Valor base de negro
}

/**
 * @brief Realiza una lectura de un sensor.
 * 
 * @param sensor Sensor a leer. Es necesario hacer uso de las macros proporcionadas.
 * @return uint16_t Valor leído por el sensor.
 */
uint16_t sensores_read(uint8_t sensor);

/**
 * @brief Realiza una calibración de los sensores.
 * 
 * Realiza una calibración de los sensores IR. En caso de que la calibración sea incorrecta se usarán los valores base de blanco y negro.
 * 
 */
void sensores_calibrate();

#endif /* SENSORES_H_ */