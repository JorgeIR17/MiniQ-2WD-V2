/**
 * @file pruebas.c
 * @author Jorge Ibáñez
 * @brief Definición de las funciones de las pruebas del DFRobot MiniQ 2WD
 * @version 1.0
 * @date 2025-06-09
 * 
 * @copyright Copyright (c) 2025

*/

#include "pruebas.h"

/*-----------------PRUEBAS BAJO NIVEL------------------*/

void prueba_bateria()
{
    m_usb_tx_string("\n== PRUEBA BATERÍA ==\n");
    m_usb_tx_string("Mostrando voltaje y porcentaje actual...\n");
    m_usb_tx_string("Pulsa cualquier tecla para salir.\n");

    while (!m_usb_rx_available())
    {
        float voltaje = bateria_get_voltage();
        float porcentaje = bateria_get_percentage();

        m_usb_tx_string("\rVoltaje: ");
        m_usb_tx_float(voltaje, 6, 2);
        m_usb_tx_string(" V | Carga: ");
        m_usb_tx_float(porcentaje, 6, 2);
        m_usb_tx_string(" /100   "); // Espacios extra para limpiar residuos anteriores

        _delay_ms(500);
    }

    // Limpia el búfer de entrada
    while (m_usb_rx_available()) m_usb_rx_char();

    m_usb_tx_string("\nPrueba de batería finalizada.\n");
}



void prueba_brujula()
{
	m_usb_tx_string("\n== PRUEBA BRUJULA ==\n");
    m_usb_tx_string("Pulsa cualquier tecla para salir.\n");
	m_usb_tx_string("Mostrando valores de los ejes X, Y, Z:\n");

	int16_t x, y, z;

	while (!m_usb_rx_available())
	{
		brujula_read(&x, &y, &z);

		// Limpiar línea anterior
		m_usb_tx_string("\r                                                              \r");

		// Mostrar los valores actuales
		m_usb_tx_string("X: ");
		m_usb_tx_int(x);
		m_usb_tx_string(" | Y: ");
		m_usb_tx_int(y);
		m_usb_tx_string(" | Z: ");
		m_usb_tx_int(z);

		_delay_ms(300);
	}

    while (m_usb_rx_available()) m_usb_rx_char(); // Limpia la tecla presionada
	m_usb_tx_string("\nFin de prueba.\n");
}


void prueba_encoders()
{
	int16_t vel_izq = 0;
	int16_t vel_der = 0;
	bool salir = false;

	m_usb_tx_string("\n== PRUEBA ENCODERS ==\n");
	m_usb_tx_string("Levanta el robot del suelo.\n");
	m_usb_tx_string("Pulsa cualquier tecla para comenzar...\n");

	while (!m_usb_rx_available());
	m_usb_rx_char();

	// Mostrar pulsos con ruedas en movimiento
	encoder_reset(ENCODER_IZQUIERDO);
	encoder_reset(ENCODER_DERECHO);

	m_usb_tx_string("Pulsa cualquier tecla para mostrar RPM...\n");
	motores_spin(100, 100);

	while (!m_usb_rx_available())
	{
		m_usb_tx_string("\rPulsos IZQ: ");
		m_usb_tx_uint(encoder_read(ENCODER_IZQUIERDO));
		m_usb_tx_string(" | Pulsos DER: ");
		m_usb_tx_uint(encoder_read(ENCODER_DERECHO));
		m_usb_tx_string("   ");
		_delay_ms(200);
	}
	m_usb_rx_char();

	motores_stop();

	// Control de velocidad con teclado
	encoder_reset(ENCODER_IZQUIERDO);
	encoder_reset(ENCODER_DERECHO);

	m_usb_tx_string("\nControla velocidad ruedas:\n");
	m_usb_tx_string("'q' aumenta izquierda, 'a' disminuye izquierda\n");
	m_usb_tx_string("'w' aumenta derecha, 's' disminuye derecha\n");
	m_usb_tx_string("'0' para salir\n");

	while (!salir)
	{
		m_usb_tx_string("\rVel IZQ: ");
		m_usb_tx_int(vel_izq);
		m_usb_tx_string(" | RPM IZQ: ");
		m_usb_tx_uint(encoder_get_speed(ENCODER_IZQUIERDO));

		m_usb_tx_string(" || Vel DER: ");
		m_usb_tx_int(vel_der);
		m_usb_tx_string(" | RPM DER: ");
		m_usb_tx_uint(encoder_get_speed(ENCODER_DERECHO));
		m_usb_tx_string("   ");

		motores_spin(vel_izq, vel_der);

		if (m_usb_rx_available())
		{
			char c = m_usb_rx_char();
			switch(c)
			{
				case 'q': if(vel_izq < 255) vel_izq += 10; break;
				case 'a': if(vel_izq > -255) vel_izq -= 10; break;
				case 'w': if(vel_der < 255) vel_der += 10; break;
				case 's': if(vel_der > -255) vel_der -= 10; break;
				case '0': salir = true; break;
				default: break;
			}
		}

		_delay_ms(200);
	}

	motores_stop();
	m_usb_tx_string("\nPrueba finalizada. Motores detenidos.\n");
}






void prueba_fotodiodos()
{
	m_usb_tx_string("\n== PRUEBA FOTODIODOS ==\n");
	m_usb_tx_string("Presiona cualquier tecla para salir.\n");

	uint8_t luz_anterior = 255; // Valor inválido
	uint8_t luz_actual;

	while (!m_usb_rx_available())
	{
		luz_actual = fotodiodos_position();

		if (luz_actual != luz_anterior)
		{
			luz_anterior = luz_actual;

			m_usb_tx_string("\r                            \r");
			m_usb_tx_string("Luz detectada: ");

			switch (luz_actual)
			{
				case 1:
					m_usb_tx_string("DERECHA");
					break;
				case 2:
					m_usb_tx_string("CENTRO");
					break;
				case 3:
					m_usb_tx_string("IZQUIERDA");
					break;
				case 0:
				default:
					m_usb_tx_string("NO DETECTADA");
					break;
			}
		}
		
		_delay_ms(200);
	}

    m_usb_rx_char(); // Limpia la tecla presionada

	// Limpia la línea final antes de salir
	m_usb_tx_string("\r                          \r");
	m_usb_tx_string("Fin de prueba\n");
}



void prueba_ledrgb()
{
    uint8_t r = 0, g = 0, b = 0;
    bool salir = false;
    char tecla;

    m_usb_tx_string("\n== PRUEBA LED RGB ==\n");
    m_usb_tx_string("Ajusta los valores RGB con las siguientes teclas:\n");
    m_usb_tx_string("q/a: +R / -R\n");
    m_usb_tx_string("w/s: +G / -G\n");
    m_usb_tx_string("e/d: +B / -B\n");
    m_usb_tx_string("x: Apagar LED\n");
    m_usb_tx_string("0: Salir\n");

    while (!salir)
    {
        if (m_usb_rx_available())
        {
            tecla = m_usb_rx_char();

            switch (tecla)
            {
                case 'q': if (r < 255) r++; break;
                case 'a': if (r > 0)   r--; break;
                case 'w': if (g < 255) g++; break;
                case 's': if (g > 0)   g--; break;
                case 'e': if (b < 255) b++; break;
                case 'd': if (b > 0)   b--; break;
                case 'x': r = g = b = 0; led_rgb_off(); continue;
                case '0': salir = true; continue;
                default: continue;
            }

            // Enviar color actualizado
            led_rgb_send_color(r, g, b);

            m_usb_tx_string("\rRGB = (");
            m_usb_tx_uint(r);
            m_usb_tx_string(", ");
            m_usb_tx_uint(g);
            m_usb_tx_string(", ");
            m_usb_tx_uint(b);
            m_usb_tx_string(")      ");
        }
    }

    led_rgb_off();
    m_usb_tx_string("\n\nLED apagado. Fin de la prueba.\n");
}




void prueba_motores()
{
    int16_t vel_izq = 0;
    int16_t vel_der = 0;
    bool motores_activos = false;
    bool salir = false;

    m_usb_tx_string("\n== PRUEBA MOTORES ==\n");
    m_usb_tx_string("Controles:\n");
    m_usb_tx_string("'q' / 'a' -> + / - velocidad IZQUIERDA\n");
    m_usb_tx_string("'w' / 's' -> + / - velocidad DERECHA\n");
    m_usb_tx_string("'e'       -> Activar / Parar motores\n");
    m_usb_tx_string("'0'       -> Salir\n");

    while (!salir)
    {
        // Mostrar estado
        m_usb_tx_string("\rVel IZQ: ");
        m_usb_tx_int(vel_izq);
        m_usb_tx_string(" | Vel DER: ");
        m_usb_tx_int(vel_der);
        m_usb_tx_string(" | Motores: ");
		
		if(motores_activos)  m_usb_tx_string("ACTIVOS ");
		else m_usb_tx_string("PARADOS ");

        if (m_usb_rx_available())
        {
            char tecla = m_usb_rx_char();
            switch (tecla)
            {
                case 'q': if (vel_izq < 255) vel_izq += 10; break;
                case 'a': if (vel_izq > -255) vel_izq -= 10; break;
                case 'w': if (vel_der < 255) vel_der += 10; break;
                case 's': if (vel_der > -255) vel_der -= 10; break;

                case 'e':
                    motores_activos = !motores_activos;
                    if (motores_activos)
                        motores_spin(vel_izq, vel_der);
                    else
                        motores_stop();
                    break;

                case '0':
                    salir = true;
                    break;
            }
        }

        if (motores_activos)
        {
            // En caso de que se haya cambiado la velocidad
            motores_spin(vel_izq, vel_der);
        }

        _delay_ms(100);
    }

    motores_stop();
    m_usb_tx_string("\nPrueba de motores finalizada.\n");
}



void prueba_pulsadores() 
{
    m_usb_tx_string("\n== PRUEBA PULSADORES ==\n");
    m_usb_tx_string("Iniciando prueba de pulsadores.\n");
    m_usb_tx_string("Presiona cualquier tecla para salir.\n");

    while (!m_usb_rx_available()) 
    {
        m_usb_tx_string("\rPulsador presionado: ");

        if (pulsadores_read() == 1) 
        {
            m_usb_tx_string("KEY 1              ");
        } 
        else if (pulsadores_read() == 2) 
        {
            m_usb_tx_string("KEY 2              ");
        } 
        else if (pulsadores_read() == 3) 
        {
            m_usb_tx_string("KEY 3              ");
        } 
        else 
        {
            m_usb_tx_string("Ninguno            ");
        }

        _delay_ms(200);
    }

    m_usb_rx_char(); // Limpia la tecla presionada
    m_usb_tx_string("\nPrueba terminada.\n");
}


void prueba_receptor()
{
	m_usb_tx_string("\n== PRUEBA RECEPTOR IR ==\n");
	m_usb_tx_string("Opciones:\n");
	m_usb_tx_string("i: Enviar pulso desde TRANSMISOR_IZQUIERDO\n");
	m_usb_tx_string("d: Enviar pulso desde TRANSMISOR_DERECHO\n");
	m_usb_tx_string("r: Reiniciar contador\n");
	m_usb_tx_string("0: Salir\n");

	bool salir = false;

	while (!salir)
	{
		if (m_usb_rx_available())
		{
			char tecla = m_usb_rx_char();
			switch (tecla)
			{
				case 'i':
					receptor_send_pulse(TRANSMISOR_IZQUIERDO);
					break;
				case 'd':
					receptor_send_pulse(TRANSMISOR_DERECHO);
					break;
				case 'r':
					cont_obs = 0;
					break;
				case '0':
					salir = true;
					break;
				default:
					break;
			}
		}

		m_usb_tx_string("\rContador de pulsos: ");
        m_usb_tx_uint(cont_obs);
		
		m_usb_tx_string("   "); // limpiar residuos
		_delay_ms(100);
	}

	m_usb_tx_string("\nFin de prueba receptor.\n");
}



void prueba_sensores()
{
	bool salir = false;
	uint16_t lectura_izq, lectura_izq_c, lectura_c, lectura_der_c, lectura_der;
	
	m_usb_tx_string("\n== PRUEBA SENSORES IR ==\n");
	m_usb_tx_string("Presiona '0' para salir y realizar la calibración...\n");

	while (!salir)
	{
		if (m_usb_rx_available())
		{
			char tecla = m_usb_rx_char();
			if (tecla == '0')
				salir = true;
		}

		lectura_izq    = sensores_read(IZQUIERDA);
		lectura_izq_c  = sensores_read(IZQUIERDA_CENTRO);
		lectura_c      = sensores_read(CENTRO);
		lectura_der_c  = sensores_read(DERECHA_CENTRO);
		lectura_der    = sensores_read(DERECHA);

		m_usb_tx_string("\rIR IZQ: ");
		m_usb_tx_uint(lectura_izq);
		m_usb_tx_string(" | IZQ-C: ");
		m_usb_tx_uint(lectura_izq_c);
		m_usb_tx_string(" | CENTRO: ");
		m_usb_tx_uint(lectura_c);
		m_usb_tx_string(" | DER-C: ");
		m_usb_tx_uint(lectura_der_c);
		m_usb_tx_string(" | DER: ");
		m_usb_tx_uint(lectura_der);
		m_usb_tx_string("        "); // limpia texto previo si hay valores más largos

		_delay_ms(100);
	}

	// Calibración al terminar
	m_usb_tx_string("\n\nIniciando calibración de sensores...\n");
	sensores_calibrate();

	m_usb_tx_string("Calibración completada.\n");
	m_usb_tx_string("Valor negro: ");
	m_usb_tx_uint(negro);
	m_usb_tx_string(" | Valor blanco: ");
	m_usb_tx_uint(blanco);
	m_usb_tx_string("\n");
}




void prueba_zumbador()
{
    uint8_t freq = 50;         // Valor inicial de frecuencia
    uint16_t dur = 500;        // Duración inicial en ms
    bool salir = false;

    m_usb_tx_string("\n== PRUEBA ZUMBADOR ==\n");
    m_usb_tx_string("Teclas disponibles:\n");
    m_usb_tx_string("w: Aumentar frecuencia\n");
    m_usb_tx_string("s: Disminuir frecuencia\n");
    m_usb_tx_string("e: Aumentar duración (+100ms)\n");
    m_usb_tx_string("d: Disminuir duración (-100ms)\n");
    m_usb_tx_string("p: Reproducir tono\n");
    m_usb_tx_string("0: Salir\n");

    while (!salir)
    {
	    if (m_usb_rx_available())
	    {
		    char tecla = m_usb_rx_char();

		    switch (tecla)
		    {
			    case 'w':
			    if (freq > 1) freq--;
			    break;

			    case 's':
			    if (freq < 255) freq++;
			    break;

			    case 'e':
			    if (dur < 4000) dur += 100;
			    break;

			    case 'd':
			    if (dur > 100) dur -= 100;
			    break;

			    case 'p':
			    zumbador_tone(freq, dur);
			    break;

			    case '0':
			    salir = true;
			    break;

			    default:
			    continue;
		    }

		    m_usb_tx_string("\rFrecuencia: ");
		    m_usb_tx_uint(freq);
		    m_usb_tx_string(" ticks | Duración: ");
		    m_usb_tx_uint(dur);
		    m_usb_tx_string(" ms       "); // Espacios extra para limpiar texto anterior
	    }
    }

    m_usb_tx_string("\nFin de la prueba del zumbador.\n");
}




/*-----------------PRUEBAS HAL------------------*/




void prueba_HAL_bateria()
{
	m_usb_tx_string("\n== PRUEBA HAL BATERIA ==\n");
	m_usb_tx_string("Mostrando porcentaje de bateria y color LED correspondiente.\n");
	m_usb_tx_string("Presiona cualquier tecla para salir.\n");

	while (!m_usb_rx_available())
	{
		// Leer y mostrar el porcentaje de batería
		float porcentaje = HAL_bateria_porcentaje();

		// Limpiar línea anterior
		m_usb_tx_string("\r                                          \r");

		m_usb_tx_string("Bateria: ");
		m_usb_tx_float(porcentaje, 6, 2);
		m_usb_tx_string(" /100");

		// Mostrar el nivel con el LED
		HAL_bateria_mostrar_nivel();

		_delay_ms(500);
	}
	
	m_usb_rx_char(); // Limpia la tecla presionada

	// Apagar LED al salir
	HAL_ledrgb_apagar();
	m_usb_tx_string("\nFin de prueba.\n");
}

void prueba_HAL_brujula()
{
    int16_t offset_x = 0, offset_y = 0;
    float heading_inicial = 0.0;

    m_usb_tx_string("\n== PRUEBA HAL BRUJULA ==\n");
    m_usb_tx_string("Manten el robot en posicion estable para calibrar la brujula.\n");
    m_usb_tx_string("Presiona cualquier tecla para comenzar la calibracion...\n");

    while (!m_usb_rx_available()); // Espera entrada
    m_usb_rx_char();               // Limpia el buffer

    m_usb_tx_string("Calibrando brujula...\n");

    HAL_brujula_calibrar(&offset_x, &offset_y);

    m_usb_tx_string("Calibracion completa.\n");

    // Guardamos como referencia el heading inicial promedio
    heading_inicial = HAL_brujula_promedio_heading_calibrado(offset_x, offset_y, 10);

    m_usb_tx_string("Prueba en curso. Presiona cualquier tecla para salir.\n");

    while (!m_usb_rx_available())
    {
        float heading_actual = HAL_brujula_get_heading_calibrado(offset_x, offset_y);
        float angulo_relativo = HAL_brujula_diferencia_angulo(heading_actual, heading_inicial);

        // Limpiar línea anterior
        m_usb_tx_string("\r                                   \r");

        m_usb_tx_string("Angulo respecto al inicio: ");
        m_usb_tx_int((int)angulo_relativo);
        m_usb_tx_string("°");

        _delay_ms(200);
    }

    m_usb_rx_char(); // Limpia la tecla de salida
    m_usb_tx_string("\nFin de prueba.\n");
}



void prueba_HAL_encoders()
{
    int16_t velocidad = 0;
    bool salir = false;

    m_usb_tx_string("\n== PRUEBA HAL ENCODERS ==\n");
    m_usb_tx_string("Levanta el robot para evitar desconexión.\n");
    m_usb_tx_string("Presiona cualquier tecla para comenzar...\n");

    while (!m_usb_rx_available());
    m_usb_rx_char();

    HAL_encoders_reiniciar(ENCODER_IZQUIERDO);
    HAL_encoders_reiniciar(ENCODER_DERECHO);

    m_usb_tx_string("Usa teclas para controlar velocidad:\n");
    m_usb_tx_string("Presiona '0' para salir.\n");
    m_usb_tx_string("'i' = aumenta | 'k' = disminuye | 'r' = reset distancias | '0' = detener y salir\n");

    while (!salir)
    {
        // Leer valores actuales
        uint16_t rpm_izq = HAL_encoders_obtener_velocidad(ENCODER_IZQUIERDO);
        uint16_t rpm_der = HAL_encoders_obtener_velocidad(ENCODER_DERECHO);
        uint16_t dist_izq = HAL_encoders_obtener_distancia(ENCODER_IZQUIERDO);
        uint16_t dist_der = HAL_encoders_obtener_distancia(ENCODER_DERECHO);

        // Mostrar en terminal
        m_usb_tx_string("\rVel: ");
        m_usb_tx_int(velocidad);
        m_usb_tx_string(" | RPM I: ");
        m_usb_tx_uint(rpm_izq);
        m_usb_tx_string(" | Dist I: ");
        m_usb_tx_uint(dist_izq);
        m_usb_tx_string(" mm | RPM D: ");
        m_usb_tx_uint(rpm_der);
        m_usb_tx_string(" | Dist D: ");
        m_usb_tx_uint(dist_der);
        m_usb_tx_string(" mm     ");

        // Aplicar velocidad
        HAL_motores_avanzar(velocidad);

        // Manejo de teclado
        if (m_usb_rx_available())
        {
            char c = m_usb_rx_char();
            switch (c)
            {
                case 'i': if (velocidad < 255) velocidad += 10; break;
                case 'k': if (velocidad > -255) velocidad -= 10; break;
                case 'r':
                    HAL_encoders_reiniciar(ENCODER_IZQUIERDO);
                    HAL_encoders_reiniciar(ENCODER_DERECHO);
                    m_usb_tx_string("\nDistancias reiniciadas.\n");
                    break;
                case '0': salir = true; break;
                default: break;
            }
        }

        _delay_ms(200);
    }

    HAL_motores_detener();
    m_usb_tx_string("\nMotores detenidos. Fin de prueba.\n");
}



void prueba_HAL_fotodiodos()
{
	m_usb_tx_string("\n== PRUEBA HAL FOTODIODOS ==\n");
	m_usb_tx_string("Presiona cualquier tecla para salir.\n");

	uint8_t luz_anterior = 255; // Valor inválido
	uint8_t luz_actual;

	while (!m_usb_rx_available())
	{
		luz_actual = HAL_fotodiodos_posicion();

		if (luz_actual != luz_anterior)
		{
			luz_anterior = luz_actual;

			m_usb_tx_string("\r                            \r");
			m_usb_tx_string("Luz detectada: ");

			switch (luz_actual)
			{
				case LUZ_DERECHA:
					m_usb_tx_string("DERECHA");
					break;
				case LUZ_CENTRO:
					m_usb_tx_string("CENTRO");
					break;
				case LUZ_IZQUIERDA:
					m_usb_tx_string("IZQUIERDA");
					break;
				case LUZ_ERROR:
				default:
					m_usb_tx_string("NO DETECTADA");
					break;
			}
		}
		
		_delay_ms(200);
	}

    m_usb_rx_char(); // Limpia la tecla presionada

	// Limpia la línea final antes de salir
	m_usb_tx_string("\r                          \r");
	m_usb_tx_string("Fin de prueba\n");
}



void prueba_HAL_ledrgb()
{
    uint8_t color = WHITE;
    bool salir = false;

    m_usb_tx_string("\n== PRUEBA HAL LED RGB ==\n");
    m_usb_tx_string("Seleccione un color con las teclas:\n");
    m_usb_tx_string("1: ROJO\n");
    m_usb_tx_string("2: VERDE\n");
    m_usb_tx_string("3: AZUL\n");
    m_usb_tx_string("4: AMARILLO\n");
    m_usb_tx_string("5: MAGENTA\n");
    m_usb_tx_string("6: CYAN\n");
    m_usb_tx_string("7: BLANCO\n");
    m_usb_tx_string("8: NARANJA\n");
    m_usb_tx_string("9: APAGAR LED\n");
    m_usb_tx_string("0: SALIR\n");

    while (!salir)
    {
        if (m_usb_rx_available())
        {
            char tecla = m_usb_rx_char();

            switch (tecla)
            {
                case '1': color = RED; break;
                case '2': color = GREEN; break;
                case '3': color = BLUE; break;
                case '4': color = YELLOW; break;
                case '5': color = MAGENTA; break;
                case '6': color = CYAN; break;
                case '7': color = WHITE; break;
                case '8': color = ORANGE; break;
                case '9': HAL_ledrgb_apagar(); continue;
                case '0': salir = true; continue;
                default: continue;
            }

            HAL_ledrgb_color(color);
        }
    }

    HAL_ledrgb_apagar();
    _delay_ms(500);
	
	m_usb_tx_string("\nEfecto PARPADEO con el color seleccionado...\n");
	HAL_ledrgb_parpadeo(color, 4000);
	
	HAL_ledrgb_apagar();
	_delay_ms(500);

    m_usb_tx_string("\nEfecto BREATHING con el color seleccionado...\n");
    HAL_ledrgb_efecto_breathing(color, 50, 4000);

    _delay_ms(500);

    m_usb_tx_string("\nEfecto ARCOIRIS...\n");
    HAL_ledrgb_efecto_arcoiris(4000);

    HAL_ledrgb_apagar();
}


void prueba_HAL_motores() 
{
    m_usb_tx_string("\n== PRUEBA HAL MOTORES ==\n");
	m_usb_tx_string("Levanta el robot para evitar desconexión.\n");
	m_usb_tx_string("Presiona cualquier tecla para comenzar...\n");

	while (!m_usb_rx_available()); // Espera a que el usuario presione una tecla
	m_usb_rx_char(); // Limpia el buffer

    // Movimiento hacia adelante
    m_usb_tx_string("Avanzando...\n");
    HAL_motores_avanzar(200); // Velocidad positiva
    _delay_ms(1500);
    HAL_motores_detener();
    _delay_ms(500);

    // Movimiento hacia atrás
    m_usb_tx_string("Retrocediendo...\n");
    HAL_motores_avanzar(-200); // Velocidad negativa
    _delay_ms(1500);
    HAL_motores_detener();
    _delay_ms(500);

    // Giro
    m_usb_tx_string("Girando en el lugar...\n");
    HAL_motores_girar(200, -200); // Giro sobre su eje
    _delay_ms(1500);
    HAL_motores_detener();
    _delay_ms(500);

    m_usb_tx_string("Prueba de motores finalizada.\n");
}


void prueba_HAL_pulsadores() 
{
    m_usb_tx_string("\n== PRUEBA HAL PULSADORES ==\n");
    m_usb_tx_string("Presione cualquier tecla para salir.\n");

    while (!m_usb_rx_available()) 
    {
        m_usb_tx_string("\rPulsador presionado: ");

        if (HAL_pulsadores_key_1()) 
        {
            m_usb_tx_string("KEY 1              ");
        } 
        else if (HAL_pulsadores_key_2()) 
        {
            m_usb_tx_string("KEY 2              ");
        } 
        else if (HAL_pulsadores_key_3()) 
        {
            m_usb_tx_string("KEY 3              ");
        } 
        else 
        {
            m_usb_tx_string("Ninguno            ");
        }

        _delay_ms(200);
    }

    m_usb_rx_char(); // Limpia la tecla presionada
    m_usb_tx_string("\nPrueba terminada.\n");
}


void prueba_HAL_receptor() 
{
    m_usb_tx_string("\n== PRUEBA HAL RECEPTOR IR ==\n");
    uint8_t obstaculo;

    m_usb_tx_string("Iniciando detección de obstáculo.\n");
    m_usb_tx_string("Presione cualquier tecla para salir.\n");

    while (!m_usb_rx_available()) 
    {
        obstaculo = HAL_receptor_detectar_obstaculo(NULL, NULL);

        m_usb_tx_string("\rObstáculo: ");

        switch (obstaculo) 
        {
            case OBS_NADA:
                m_usb_tx_string("Ninguno detectado        ");
                break;
            case OBS_DERECHA:
                m_usb_tx_string("A la derecha             ");
                break;
            case OBS_IZQUIERDA:
                m_usb_tx_string("A la izquierda           ");
                break;
            case OBS_DELANTE:
                m_usb_tx_string("Frente                   ");
                break;
            default:
                m_usb_tx_string("Valor desconocido        ");
                break;
        }

        _delay_ms(300);
    }

    m_usb_rx_char(); // Limpiar buffer de entrada
    m_usb_tx_string("\nDetección terminada.\n");
}



void prueba_HAL_sensores() 
{
    m_usb_tx_string("\n== PRUEBA HAL SENSORES ==\n");
    m_usb_tx_string("Iniciando lectura de sensores de línea.\n");
    m_usb_tx_string("Presione cualquier tecla para salir.\n");

    while (!m_usb_rx_available()) 
    {
        int8_t posicion = HAL_sensores_obtener_posicion();

        m_usb_tx_string("\rEstado: ");  // Sobrescribe en la misma línea

        switch (posicion) 
        {
            case LINEA_IZQUIERDA:
                m_usb_tx_string("Muy a la izquierda       ");
                break;
            case LINEA_IZQUIERDA_CENTRO:
                m_usb_tx_string("Un poco a la izquierda   ");
                break;
            case LINEA_CENTRO:
                m_usb_tx_string("Centrado                 ");
                break;
            case LINEA_DERECHA_CENTRO:
                m_usb_tx_string("Un poco a la derecha     ");
                break;
            case LINEA_DERECHA:
                m_usb_tx_string("Muy a la derecha         ");
                break;
            case ERROR_LINEA:
                m_usb_tx_string("¡Línea no detectada!     ");
                break;
            case NADA:
            default:
                m_usb_tx_string("Sin cambio / sin datos   ");
                break;
        }

        _delay_ms(300);
    }

    m_usb_rx_char();  // Limpiar el buffer de entrada
    m_usb_tx_string("\nLectura terminada.\n");
}



void prueba_HAL_zumbador() 
{
    m_usb_tx_string("\n== PRUEBA HAL ZUMBADOR ==\n");
    m_usb_tx_string("Reproduciendo escala de Do mayor:\n");
	m_usb_tx_string("Do-Re-Mi-Fa-Sol-La-Si-Do\n");

    HAL_zumbador_nota(C4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(D4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(E4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(F4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(G4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(A4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(B4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(C5, 400);
    _delay_ms(400);

    _delay_ms(1000);

    m_usb_tx_string("Reproduciendo escala de Mi menor:\n");
	m_usb_tx_string("Mi-Fa#-Sol-La-Si-Do-Re-Mi\n");

    HAL_zumbador_nota(E4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(Fs4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(G4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(A4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(B4, 400);
    _delay_ms(400);
    HAL_zumbador_nota(C5, 400);
    _delay_ms(400);
    HAL_zumbador_nota(D5, 400);
    _delay_ms(400);
    HAL_zumbador_nota(E5, 400);
    _delay_ms(400);

    _delay_ms(1000);
}
