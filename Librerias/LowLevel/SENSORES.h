/**
 * @file SENSORES.h
 * @author Jorge Ibáñez
 * @brief Declaración de los drivers de bajo nivel para el uso de los sensores infrarrojos.
 * @version 0.1
 * @date 2025-05-06
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef SENSORES_H_
#define SENSORES_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include "../Peripherals/ADC.h"

// Definición canales sensores

/**
 * @brief Canal ADC del sensor IR0 (IZQUIERDA)
 * 
 */
#define IR0 ADC7
/**
 * @brief Canal ADC del sensor IR1 (IZQUIERDA_CENTRO)
 * 
 */
#define IR1 ADC6
/**
 * @brief Canal ADC del sensor IR2 (CENTRO)
 * 
 */
#define IR2 ADC5
/**
 * @brief Canal ADC del sensor IR3 (DERECHA_CENTRO)
 * 
 */
#define IR3 ADC4
/**
 * @brief Canal ADC del sensor IR4 (DERECHA)
 * 
 */
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
    ADC_init();
	blanco = WHITE_SENSOR;
	negro = BLACK_SENSOR;
}

/**
 * @brief Realiza una lectura de un sensor.
 * 
 * @param sensor Sensor a leer. Es necesario hacer uso de las macros proporcionadas.
 * @return uint16_t Valor leído por el sensor.
 */
uint16_t sensores_leer(uint8_t sensor);

/**
 * @brief Realiza una calibración de los sensores.
 * 
 * Realiza una calibración de los sensores IR. En caso de que la calibración sea incorrecta se usarán los valores base de blanco y negro.
 * 
 */
void sensores_calibrar();

#endif /* SENSORES_H_ */