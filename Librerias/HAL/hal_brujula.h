/**
 * @file hal_brujula.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso de la brujula HMC5883L
 * @version 0.1
 * @date 2025-05-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef HAL_BRUJULA_H_
#define HAL_BRUJULA_H_

#define F_CPU 16000000UL
#include "../LowLevel/brujula.h"
#include "hal_motores.h"
#include <util/delay.h>
#include <math.h>

/**
 * @brief Inicializa el HMC5883L.
 * 
 */
static inline void HAL_brujula_init()
{
	brujula_init();	
}


/**
 * @brief Lee los valores de los tres ejes del magnetómetro HMC5883L.
 *
 *
 * @param[out] x Puntero donde se guardará el valor del eje X
 * @param[out] y Puntero donde se guardará el valor del eje Y
 * @param[out] z Puntero donde se guardará el valor del eje Z
 */
void HAL_brujula_leer_ejes(int16_t* x, int16_t* y, int16_t* z);


/**
 * @brief Realiza una calibración básica de la brújula.
 *
 * Guarda los máximos y mínimos en X e Y mientras el usuario gira el sensor.
 * Calcula el offset para centrar las lecturas.
 *
 * @param[out] offset_x Desplazamiento medio del eje X
 * @param[out] offset_y Desplazamiento medio del eje Y
 */
void HAL_brujula_calibrar(int16_t* offset_x, int16_t* offset_y);

/**
 * @brief Calcula el heading actual (ángulo respecto al norte) usando los offsets de calibración.
 *
 * @param offset_x Offset del eje X obtenido en calibración
 * @param offset_y Offset del eje Y obtenido en calibración
 * @return float Ángulo en grados, de 0 a 360
 */
float HAL_brujula_get_heading_calibrado(int16_t offset_x, int16_t offset_y);

/**
 * @brief Calcula la diferencia angular entre dos ángulos en grados.
 *
 * El resultado está en el rango [-180, 180], lo que indica cuánto y en qué
 * dirección se debe girar desde angulo_actual hacia angulo_objetivo.
 *
 * @param angulo_objetivo Ángulo objetivo en grados [0–360)
 * @param angulo_actual Ángulo actual en grados [0–360)
 * @return float Diferencia angular en grados (puede ser negativa)
 */
float HAL_brujula_diferencia_angulo(float angulo_objetivo, float angulo_actual);

/**
 * @brief Calcula el promedio del heading calibrado de la brújula.
 *
 * Esta función realiza varias lecturas consecutivas del ángulo (heading) actual
 * corregido con los offsets de calibración, y devuelve el valor medio.
 * Es útil para reducir el efecto de ruido o pequeñas oscilaciones en las lecturas
 * del sensor magnético.
 *
 * @param offset_x Offset de calibración para el eje X.
 * @param offset_y Offset de calibración para el eje Y.
 * @param muestras Número de lecturas consecutivas a promediar.
 * @return float Heading promedio en grados (rango de 0° a 360°).
 */
float HAL_brujula_promedio_heading_calibrado(int16_t offset_x, int16_t offset_y, uint8_t muestras);

#endif /* HAL_BRUJULA_H_ */