/**
 * @file pruebas.h
 * @author Jorge Ibáñez
 * @brief Declaración de las funciones de las pruebas del DFRobot MiniQ 2WD
 * @version 1.0
 * @date 2025-06-09
 * 
 * @copyright Copyright (c) 2025
 * 
 * Para poder mostrar los menús, así como la información a mostrar en las pruebas, se ha hecho uso de la librería de USB
 * de MEAM.Design (https://medesign.seas.upenn.edu/index.php/Guides/MaEvArM-usb).
 * 
 */


#ifndef PRUEBAS_H_
#define PRUEBAS_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include "../HAL/hal_motores.h"
#include "../HAL/hal_sensores.h"
#include "../HAL/hal_zumbador.h"
#include "../HAL/hal_encoders.h"
#include "../HAL/hal_ledrgb.h"
#include "../HAL/hal_pulsadores.h"
#include "../HAL/hal_bateria.h"
#include "../HAL/hal_fotodiodos.h"
#include "../HAL/hal_receptor.h"
#include "../HAL/hal_brujula.h"
#include "../USB/m_usb.h"
#include "menus.h"

#define PRUEBA_BATERIA          1
#define PRUEBA_BRUJULA          2
#define PRUEBA_ENCODERS         3
#define PRUEBA_FOTODIODOS       4
#define PRUEBA_LED_RGB          5
#define PRUEBA_MOTORES          6
#define PRUEBA_PULSADORES       7
#define PRUEBA_RECEPTOR         8
#define PRUEBA_SENSORES         9
#define PRUEBA_ZUMBADOR         10

#define PRUEBA_HAL_BATERIA      11
#define PRUEBA_HAL_BRUJULA      12
#define PRUEBA_HAL_ENCODERS     13
#define PRUEBA_HAL_FOTODIODOS   14
#define PRUEBA_HAL_LED_RGB      15
#define PRUEBA_HAL_MOTORES      16
#define PRUEBA_HAL_PULSADORES   17
#define PRUEBA_HAL_RECEPTOR     18
#define PRUEBA_HAL_SENSORES     19
#define PRUEBA_HAL_ZUMBADOR     20

/**
 * @brief Realiza una prueba de las funciones de bajo nivel del medidor de batería.
 * 
 * En la prueba se muestran los valores obtenidos de voltaje y el porcentaje restante de batería.
 * 
 */
void prueba_bateria();

/**
 * @brief Realiza una prueba de las funciones de bajo nivel de la brújula.
 * 
 * En la prueba se muestran los valores obtenidos de los ejes X, Y y Z.
 * 
 */
void prueba_brujula();

/**
 * @brief Realiza una prueba de las funciones de bajo nivel del medidor de los encoders.
 * 
 * En la prueba se muestran los valores obtenidos de pulsos acumulados y RPM de cada encoder.
 * Para ello, se permitirá modificar la velocidad de cada rueda individualmente.
 * 
 */
void prueba_encoders();

/**
 * @brief Realiza una prueba de las funciones de bajo nivel de los fotodiodos.
 * 
 * En la prueba se muestra la posición de la luz emitida con respecto al robot.
 * 
 */
void prueba_fotodiodos();


/**
 * @brief Realiza una prueba de las funciones de bajo nivel del LED RGB.
 * 
 * En la prueba se permite, mediante el uso de teclas, modificar los valores del código RGB enviado al LED.
 * 
 */
void prueba_ledrgb();

/**
 * @brief Realiza una prueba de las funciones de bajo nivel de los motores.
 * 
 * En la prueba se permite, mediante el uso de teclas, modificar la velocidad de cada rueda individual, y activar o parar los motores.
 * 
 */
void prueba_motores();

/**
 * @brief Realiza una prueba de las funciones de bajo nivel de los pulsadores.
 * 
 * En la prueba se muestra el pulsador presionado.
 * 
 */
void prueba_pulsadores();

/**
 * @brief Realiza una prueba de las funciones de bajo nivel del receptor IR.
 * 
 * En la prueba se muestra el contador de pulsos, y se permite, mediante el uso de teclas, enviar un pulso por uno de los transmisores y reiniciar el contador de pulsos.
 * 
 */
void prueba_receptor();

/**
 * @brief Realiza una prueba de las funciones de bajo nivel de los sensores.
 * 
 * En la prueba se muestran los valores obtenidos de cada uno de los sensores, y al finalizar se realiza una calibración y se muestran los valores obtenidos.
 * 
 */
void prueba_sensores();

/**
 * @brief Realiza una prueba de las funciones de bajo nivel de la brújula.
 * 
 * En la prueba se permite, mediante el uso de teclas, ajustar el valor de la frecuencia y duración del sonido, y emitir el sonido configurado.
 * 
 */
void prueba_zumbador();


/**
 * @brief Realiza una prueba de las funciones de la capa HAL del medidor de batería.
 * 
 * En la prueba se muestra el valor de porcentaje restante de batería, y se muestra el estado mediante el LED RGB.
 * 
 */
void prueba_HAL_bateria();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL de la brújula.
 * 
 * En la prueba se realiza una calibración de la brújula, y posteriormente se muestra el ángulo con respecto al inicio.
 * 
 */
void prueba_HAL_brujula();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL de los encoders.
 * 
 * En la prueba se muestran los valores obtenidos de y RPM y distancia recorrida de cada encoder.
 * Para ello, se permitirá modificar la velocidad de cada rueda individualmente.
 * 
 */
void prueba_HAL_encoders();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL de los fotodiodos.
 * 
 * En la prueba se muestra la posición de la luz emitida con respecto al robot.
 * 
 */
void prueba_HAL_fotodiodos();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL del LED RGB.
 * 
 * En la prueba se puede cambiar manualmente el color del LED, así como apagarlo. Posteriormente, se muestra una prueba de parpadeo y de efectos de respiración y arcoíris.
 * 
 */
void prueba_HAL_ledrgb();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL de los motores.
 * 
 * En la prueba se realiza automáticamente un avance y retroceso de ambas ruedas a velocidad constante, así como un giro.
 * 
 */
void prueba_HAL_motores();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL de los pulsadores.
 * 
 * En la prueba se muestra el pulsador presionado.
 * 
 */
void prueba_HAL_pulsadores();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL del receptor IR.
 * 
 * En la prueba se muestra en qué posición se encuentra un obstáculo con respecto al robot.
 * 
 */
void prueba_HAL_receptor();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL de los sensores.
 * 
 * En la prueba se muestra en qué posición se encuentra la línea con respecto al robot.
 * 
 */
void prueba_HAL_sensores();

/**
 * @brief Realiza una prueba de las funciones de la capa HAL del zumbador.
 * 
 * En la prueba se reproducen mediante el zumbador las escalas musicales de Do mayor y Mi menor.
 * 
 */
void prueba_HAL_zumbador();


#endif