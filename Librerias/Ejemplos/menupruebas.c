/**
 * @file menupruebas.c
 * @author Jorge Ibáñez
 * @brief Programa de pruebas unitarias del MiniQ 2WD
 * @version 0.1
 * @date 2025-06-26
 * 
 * Para hacer uso de este programa, es necesario conectar el robot a un PC mediante USB, apagar y encender el robot y usar
 * una herramienta para conectarse al dispositivo mediante comunicación serie al puerto asignado al robot (puede ser distinto al asignado para programarlo).
 * 
 * En este programa se podrán realizar pruebas unitarias de todas las funciones para usar los componentes del robot, tanto las de bajo nivel como las de HAL.
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../USB/m_usb.h"
#include "../Pruebas/menus.h"
#include "../Pruebas/pruebas.h"



int main(void) 
{
	menu_pruebas();
}
