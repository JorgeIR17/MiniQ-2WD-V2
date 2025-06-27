# MiniQ 2WD V2

Repositorio con todas las librerías de bajo nivel, periféricos y capa de abstracción hardware (HAL) necesarias para desarrollar aplicaciones sobre el robot **DFRobot MiniQ 2WD V2.0**, basado en el microcontrolador **ATMega32U4** (compatible con Arduino Leonardo).

**Documentación oficial del proyecto**:  
[https://jorgeir17.github.io/MiniQ-2WD-V2/](https://jorgeir17.github.io/MiniQ-2WD-V2/)


# Índice
- [Estructura](#estructura)
- [Instalación](#instalación)
    - [Atmel Studio](#atmel-studio)
    - [AVRdude](#avrdude)
- [Uso](#uso)
- [Licencia](#licencia)


## Estructura

El proyecto se encuentra organizado en diferentes carpetas según el nivel de abstracción del código:

### `Peripherals/`
Contiene librerías específicas para controlar los **periféricos internos** del microcontrolador ATMega32U4, como timers, ADC, interrupciones, GPIO, entre otros.

### `LowLevel/`
Implementa funciones de bajo nivel que permiten controlar directamente los **componentes físicos** del robot MiniQ 2WD, como motores, sensores infrarrojos, zumbador, etc.

### `HAL/` (Hardware Abstraction Layer)
Proporciona una **interfaz de alto nivel** para interactuar con los componentes del robot. Estas librerías encapsulan la complejidad del acceso directo al hardware y permiten un uso más intuitivo desde la aplicación.

### `Ejemplos/`
Incluye diferentes programas de ejemplo para demostrar el uso del robot y sus capacidades. Algunos ejemplos:

- Seguidor de líneas
- Evita obstáculos
- Pruebas unitarias de componentes
- Seguidor de luz

### `Pruebas/`
Contiene librerías específicas para la **validación y pruebas unitarias** de los distintos componentes del robot. Útil durante el desarrollo y depuración.

### `USB/`
Librerías para habilitar la **comunicación USB-Serial** entre el robot y un ordenador. Estas están basadas en el proyecto original de [MEAM.Design](https://medesign.seas.upenn.edu/index.php/Guides/MaEvArM-usb).

---

# Instalación

## Atmel Studio

Puedes descargar Atmel Studio 7 a través del siguiente enlace: https://www.microchip.com/en-us/tools-resources/archives/avr-sam-mcus.

Sigue estos pasos para instalar y compilar el proyecto en **Atmel Studio 7**:

1. Clona el repositorio en tu máquina local.

2. Crea un nuevo proyecto en Atmel Studio (**File -> New -> Project... -> GCC C Executable Project**).

3. En **Device Selection**, selecciona **ATmega32U4**.

4. Añade la carpeta **Librerias** a la carpeta del proyecto desde el explorador de archivos.

5. En la pestaña **Solution Explorer**, selecciona **Show All Files**, haz click derecho sobre la carpeta **Librerias** y selecciona **Include In Project**.

## AVRdude

Para poder programar el MiniQ 2WD en Atmel Studio es necesario usar la herramienta **AVRdude**. Para descargarla, sigue los siguientes pasos:

1. Descarga **AVRdude 7.2** a través del siguiente enlace: https://github.com/avrdudes/avrdude/releases.

2. Extrae la carpeta y renómbrala como **avrdude_7_2**.

3. Mueve la carpeta a **C:\Program Files**.

4. En Atmel Studio, crea una nueva herramienta externa (**Tools -> External Tools..**).

5. En el campo **Title**, escribe un nombre para la herramienta (Ej. MiniQ).

6. En el campo **Command**, escribe la ruta de avrdude.exe (C:\Program Files\avrdude_7_2\avrdude.exe).

7. En el campo **Arguments**, escribe los siguiente parámetros: (-C"C:\Program Files\avrdude_7_2\avrdude.conf" -v -patmega32u4 -cavr109 **-PCOM4** -b57600 -D -Uflash:w:"$(ProjectDir)Debug\$(TargetName).hex":i). El parámetro **-PCOM4** deberá modificarse para que coincida con el COM asignado al robot. Para ello, en Windows, ve a **Administrador de dispositivos -> Puertos (COM y LPT)** con el robot conectado por USB al PC, encendido y reiniciado, y en el apartado aparecerá el COM asignado al robot, el cual deberá aparecer en el parámetro anteriormente nombrado.

8. Por último, activa la opción **Use Output window** y selecciona **Apply**. La herramienta aparecerá en **Tools**.

# Uso

1. Para usar alguno de los códigos de ejemplo o usar uno propio, es necesario asegurarse de que sea el único con una función **main()** que sea compilado para evitar errores.
Para ello, haz click sobre el archivo en la pestaña **Solution Explorer**, y en la pestaña **Properties**, en el apartado **Advanced -> Build Action** selecciona **Compile/None**,
dependiendo del caso.

2. Una vez configurado, selecciona **Build -> Build Solution** (o F7) para compilar el programa.

3. Una vez compilado, enciende y reinicia el robot, y selecciona la herramienta creada. Es importante no tardar mucho en programar en robot, ya que a los 10 segundos de reiniciarse, se desconecta el COM y se inicia el programa que tuviera almacenado anteriormente.

4. En el caso de usar las pruebas unitarias u otro programa que requiera de comunicación serie, es necesario apagar y volver a encender el robot después de programarlo para que funcione. El puerto COM puede ser distinto al asignado para programar, por lo que se deberá encender el robot y comprobar el COM asignado para la comunicación. Para el uso de la comunicación se recomienda la herramienta PuTTY: https://www.putty.org/.

Para conocer el uso de las funciones y los programas, puedes consultar la **documentación del proyecto**.

# Licencia

Este proyecto está licenciado bajo la GNU General Public License v3.0. Consulta el archivo LICENSE para más detalles.