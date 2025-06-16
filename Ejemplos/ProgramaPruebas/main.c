/*
 * MainPruebas.c
 *
 * Created: 09/06/2025 11:57:45
 *  Author: Jorge
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Librerias/Pruebas/m_usb.h"
#include "Librerias/Pruebas/menus.h"
#include "Librerias/Pruebas/pruebas.h"



int main(void) 
{
	menu_pruebas();
}
