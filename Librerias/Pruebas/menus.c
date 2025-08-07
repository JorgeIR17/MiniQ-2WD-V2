/**
 * @file menus.c
 * @author Jorge Ibáñez
 * @brief Definición de las funciones del menú de pruebas del DFRobot MiniQ 2WD
 * @version 1.0
 * @date 2025-06-09
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "menus.h"


void m_usb_tx_print_str(const char* str) 
{
	while (*str) 
	{
		m_usb_tx_char(*str++);
	}
}


void m_usb_tx_float(float value, uint8_t width, uint8_t precision) 
{
    char buf[20];
    dtostrf(value, width, precision, buf);  // convierte float a string
    m_usb_tx_print_str(buf);                // envia caracter por caracter
}



void clear_terminal() 
{
	m_usb_tx_string("\033[2J\033[H");
}



void print_menu(const char* title, const char* options[], uint8_t num_options) 
{
	clear_terminal();  // Borra la pantalla antes de mostrar nuevo menu

	m_usb_tx_string("\n--- ");
	m_usb_tx_print_str(title);
	m_usb_tx_string(" ---\n");

	for (uint8_t i = 0; i < num_options; i++) 
	{
		m_usb_tx_uint(i + 1);
		m_usb_tx_string(". ");
		m_usb_tx_print_str(options[i]);
		m_usb_tx_string("\n");
	}

	m_usb_tx_string("0. Volver\n");
	m_usb_tx_string("Seleccione una opcion (use '+' para seleccionar la opcion 10): ");
}



char get_user_input() 
{
	while (!m_usb_rx_available());  // Espera hasta que haya datos disponibles
	return m_usb_rx_char();
}

void run_test(uint8_t test_id) 
{
    clear_terminal();

    m_usb_tx_string("--- Iniciando prueba ---\n");

    switch (test_id) 
	{
		case PRUEBA_BATERIA:
            prueba_bateria();
            break;

		case PRUEBA_BRUJULA:
            prueba_brujula();
            break;

		case PRUEBA_ENCODERS:
            prueba_encoders();
            break;

		case PRUEBA_FOTODIODOS:
            prueba_HAL_fotodiodos();
            break;

		case PRUEBA_LED_RGB:
			prueba_ledrgb();
			break;

		case PRUEBA_MOTORES:
            prueba_motores();
            break;

		case PRUEBA_PULSADORES:
            prueba_pulsadores();
            break;
			
		case PRUEBA_RECEPTOR:
			prueba_receptor();
			break;
		
		case PRUEBA_SENSORES:
			prueba_sensores();
			break;
			
		case PRUEBA_ZUMBADOR:
			prueba_zumbador();
			break;
		
        case PRUEBA_HAL_BATERIA:
            prueba_HAL_bateria();
            break;

		case PRUEBA_HAL_BRUJULA:
            prueba_HAL_brujula();
            break;

		case PRUEBA_HAL_ENCODERS:
            prueba_HAL_encoders();
            break;

		case PRUEBA_HAL_FOTODIODOS:
            prueba_HAL_fotodiodos();
            break;

		case PRUEBA_HAL_LED_RGB:
            prueba_HAL_ledrgb();
            break;

		case PRUEBA_HAL_MOTORES:
            prueba_HAL_motores();
            break;

		case PRUEBA_HAL_PULSADORES:
            prueba_HAL_pulsadores();
            break;

		case PRUEBA_HAL_RECEPTOR:
            prueba_HAL_receptor();
            break;

		case PRUEBA_HAL_SENSORES:
            prueba_HAL_sensores();
            break;

		case PRUEBA_HAL_ZUMBADOR:
            prueba_HAL_zumbador();
            break;

        default:
            m_usb_tx_string("ID de prueba no reconocido.\n");
            break;
    }

    m_usb_tx_string("\nPresione cualquier tecla para continuar...");
    while (!m_usb_rx_available());
    m_usb_rx_char();
}



void submenu_bajonivel() 
{
	const char* opciones[] = {"Medidor Bateria", "Brujula", "Encoders", "Fotodiodos", "LED RGB", "Motores", "Pulsadores", "Receptor IR", "Sensores IR", "Zumbador"};
	while (1) 
	{
		print_menu("Pruebas de Bajo Nivel", opciones, 10);
		char choice = get_user_input();

		switch (choice)
		{
			case '1': run_test(PRUEBA_BATERIA); break;
			case '2': run_test(PRUEBA_BRUJULA); break;
			case '3': run_test(PRUEBA_ENCODERS); break;
			case '4': run_test(PRUEBA_FOTODIODOS); break;
			case '5': run_test(PRUEBA_LED_RGB); break;
			case '6': run_test(PRUEBA_MOTORES); break;
			case '7': run_test(PRUEBA_PULSADORES); break;
			case '8': run_test(PRUEBA_RECEPTOR); break;
			case '9': run_test(PRUEBA_SENSORES); break;
			case '+': run_test(PRUEBA_ZUMBADOR); break;
			case '0': return;
			default: m_usb_tx_string("Opcion invalida\n"); break;
		}
	}
}

void submenu_HAL() 
{
	const char* opciones[] = {"Medidor Bateria", "Brujula", "Encoders", "Fotodiodos", "LED RGB", "Motores", "Pulsadores", "Receptor IR", "Sensores IR", "Zumbador"};
	while (1) 
	{
		print_menu("Pruebas de Capa HAL", opciones, 10);
		char choice = get_user_input();

		switch (choice) 
		{
			case '1': run_test(PRUEBA_HAL_BATERIA); break;
			case '2': run_test(PRUEBA_HAL_BRUJULA); break;
			case '3': run_test(PRUEBA_HAL_ENCODERS); break;
			case '4': run_test(PRUEBA_HAL_FOTODIODOS); break;
			case '5': run_test(PRUEBA_HAL_LED_RGB); break;
			case '6': run_test(PRUEBA_HAL_MOTORES); break;
			case '7': run_test(PRUEBA_HAL_PULSADORES); break;
			case '8': run_test(PRUEBA_HAL_RECEPTOR); break;
			case '9': run_test(PRUEBA_HAL_SENSORES); break;
			case '+': run_test(PRUEBA_HAL_ZUMBADOR); break;
			case '0': return;
			default: m_usb_tx_string("Opcion invalida\n"); break;
		}
	}
}


void menu_principal() 
{
	const char* opciones[] = {"Pruebas de Bajo Nivel", "Pruebas HAL"};
	while (1) 
    {
		print_menu("Menu Principal", opciones, 2);
		char choice = get_user_input();

		switch (choice) 
        {
			case '1': submenu_bajonivel(); break;
			case '2': submenu_HAL(); break;
			case '0':
			m_usb_tx_string("\nSaliendo del menu...\n");
			return;
			default:
			m_usb_tx_string("Opcion invalida\n");
			break;
		}
	}
}