/**
 * @file hal_zumbador.h
 * @author Jorge Ibáñez
 * @brief Declaración de la capa HAL para el uso del zumbador
 * @version 1.0
 * @date 2025-05-04
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef HAL_ZUMBADOR_H_
#define HAL_ZUMBADOR_H_

#include <avr/io.h>
#include "../LowLevel/zumbador.h"

// Definicion de notas musicales en ingles
#define C3  238
#define Cs3 224
#define Db3 224
#define D3  212
#define Ds3 200
#define Eb3 200
#define E3  189
#define F3  178
#define Fs3 167
#define Gb3 167
#define G3  158
#define Gs3 149
#define Ab3 149
#define A3  141
#define As3 133
#define Bb3 133
#define B3  125	

#define C4  118
#define Cs4 112
#define Db4 112
#define D4  105
#define Ds4 99
#define Eb4 99
#define E4  94
#define F4  88
#define Fs4 83
#define Gb4 83
#define G4  79
#define Gs4 74
#define Ab4 74
#define A4  70
#define As4 65
#define Bb4 65
#define B4  62	

#define C5  59
#define Cs5 56
#define Db5 56
#define D5  52
#define Ds5 49
#define Eb5 49
#define E5  46
#define F5  44
#define Fs5 41
#define Gb5 41
#define G5  39
#define Gs5 36
#define Ab5 36
#define A5  34
#define As5 32
#define Bb5 32
#define B5  30	

// Definicion de notas musicales en español
#define DO3   C3
#define DOs3  Cs3
#define REb3  Db3
#define RE3   D3
#define REs3  Ds3
#define MIb3  Eb3
#define MI3   E3
#define FA3   F3
#define FAs3  Fs3
#define SOLb3 Gb3
#define SOL3  G3
#define SOLs3 Gs3
#define LAb3  Ab3
#define LA3   A3
#define LAs3  As3
#define SIb3  Bb3
#define SI3   B3	

#define DO4   C4
#define DOs4  Cs4
#define REb4  Db4
#define RE4   D4
#define REs4  Ds4
#define MIb4  Eb4
#define MI4   E4
#define FA4   F4
#define FAs4  Fs4
#define SOLb4 Gb4
#define SOL4  G4
#define SOLs4 Gs4
#define LAb4  Ab4
#define LA4   A4
#define LAs4  As4
#define SIb4  Bb4
#define SI4   B4	

#define DO5   C5
#define DOs5  Cs5
#define REb5  Db5
#define RE5   D5
#define REs5  Ds5
#define MIb5  Eb5
#define MI5   E5
#define FA5   F5
#define FAs5  Fs5
#define SOLb5 Gb5
#define SOL5  G5
#define SOLs5 Gs5
#define LAb5  Ab5
#define LA5   A5
#define LAs5  As5
#define SIb5  Bb5
#define SI5   B5	

// Frecuencia y duracion de alertas
#define STARTING_SOUND B4
#define STARTING_SOUND_DURATION 1000

#define MATCH_SOUND G5
#define MATCH_SOUND_DURATION 500

#define FAIL_SOUND B3
#define FAIL_SOUND_DURATION 1000

// Tipos de alertas
#define INICIO 1
#define ACIERTO 2
#define ERROR 3

/**
 * @brief Inicialización del zumbador.
 * 
 * Inicializa el zumbador del robot.
 * 
 */
static inline void HAL_zumbador_init()
{
    zumbador_init();
}

/**
 * @brief Emite una alerta por el zumbador.
 * 
 * Esta función emite un sonido con una frecuencia y duración determinadas según el valor del parámetro dado, siendo sus posibles valores las macros proporcionadas.
 * 
 * @param tipo Tipo de alerta. Es necesario hacer uso de las macros proporcionadas.
 */
void HAL_zumbador_alerta(uint8_t tipo);


/**
 * @brief Emite el sonido de una nota.
 * 
 * @param nota Nota emitida. Es necesario hacer uso de las macros proporcionadas, las cuales permiten emitir las 7 notas y sus semitonos de 3 octavas distintas.
 * @param duracion Duración del sonido en milisegundos.
 */
void HAL_zumbador_nota(uint8_t nota, uint16_t duracion);

/**
 * @brief Detiene el funcionamiento del zumbador.
 * 
 * Detiene cualquier sonido emitido por el zumbador.
 * 
 */
void HAL_zumbador_detener();

#endif /* HAL_ZUMBADOR_H_ */