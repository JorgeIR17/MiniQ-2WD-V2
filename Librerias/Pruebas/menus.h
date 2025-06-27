/**
 * @file menus.h
 * @author Jorge Ibáñez
 * @brief Declaración de las funciones del menú de pruebas del DFRobot MiniQ 2WD
 * @version 0.1
 * @date 2025-06-09
 * 
 * @copyright Copyright (c) 2025
 * 
 * Para poder mostrar los menús, así como la información a mostrar en las pruebas, se ha hecho uso de la librería de USB
 * de MEAM.Design (https://medesign.seas.upenn.edu/index.php/Guides/MaEvArM-usb).
 * 
 */


#ifndef MENUS_H_
#define MENUS_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include "../USB/m_usb.h"
#include "pruebas.h"


/**
 * @brief Envía por USB una cadena de caracteres definida como variable.
 * 
 * Esta función se usa para poder enviar como parámetro una cadena de caracteres declarada en tiempo de ejecución, ya que la función
 * m_usb_tx_print_str solo acepta cadenas de caracteres declaradas en tiempo de compilación.
 * 
 * @param str Cadena de caracteres a enviar
 */
void m_usb_tx_float(float value, uint8_t width, uint8_t precision);


/**
 * @brief Envia por USB un valor de tipo float.
 * 
 * Se ha creado esta función auxiliar para poder enviar variables de tipo float, ya que la librería no dispone de ninguna.
 * 
 * @param value Valor a enviar
 * @param width Numero de caracteres (incluye punto y signo)
 * @param precision Numero de decimales
 */
void m_usb_tx_print_str(const char* str);


/**
 * @brief Borra el contenido de la terminal.
 * 
 */
void clear_terminal();


/**
 * @brief Muestra un menú por pantalla.
 * 
 * @param title Título del menú
 * @param options Opciones a elegir en el menú
 * @param num_options Número de opciones disponibles
 */
void print_menu(const char* title, const char* options[], uint8_t num_options);


/**
 * @brief Recibe el carácter enviado por el usuario.
 * 
 * @return char Carácter enviado a través del teclado
 */
char get_user_input();


/**
 * @brief Ejecuta una de las pruebas disponibles.
 * 
 * @param test_id Identificador de la prueba
 */
void run_test(uint8_t test_id);

/**
 * @brief Muestra el menú dedicado a las pruebas de bajo nivel.
 * 
 */
void submenu_bajonivel();

/**
 * @brief Muestra el menú dedicado a las pruebas de la capa HAL.
 * 
 */
void submenu_HAL();

/**
 * @brief Muestra el menú principal del programa.
 * 
 */
void menu_principal();

/**
 * @brief Inicia el menú de pruebas del robot.
 * 
 */
static inline void menu_pruebas()
{
	// Inincializamos todos los componentes
    m_usb_init();
	HAL_bateria_init();
	HAL_brujula_init();
	HAL_encoders_init();
	HAL_fotodiodos_init();
	HAL_ledrgb_init();
	HAL_motores_init();
	HAL_pulsadores_init();
	HAL_receptor_init();
	HAL_sensores_init();
	HAL_zumbador_init();
	//while (!m_usb_isconnected()); // Espera a estar conectado
	_delay_ms(7000); // Tiempo de espera para abrir la terminal

	m_usb_tx_string("Interfaz lista. Bienvenido al sistema de prueba.\n");

	menu_principal();
}

#endif