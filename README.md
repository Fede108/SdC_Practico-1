# Trabajo practico n°1: Rendimiento de las computadoras
**Facultad de Ciencias Exactas, Fisicas y Naturales de la U.N.C**

**Sistemas de Computación**


Programa de 10 segundos usando el microcontrolador STM32F103C8
https://youtu.be/WYugauXQA70

# Descripción del Repositorio
Este repositorio contiene dos carpetas principales con ejemplos y prácticas relacionadas con:

- Perfilado de tiempo de ejecución (time profiling) en C usando la herramienta gprof.
- Ejemplo de código para la tarjeta STM32F103 configurada para ejecutar un programa de 10 segundos a 24 MHz, empleando la extensión de PlatformIO en Visual Studio Code.

## 1. Carpeta `timeProfiling`

En esta carpeta se encuentran los archivos necesarios para realizar el perfilado de tiempo de ejecución con `gprof`:

- **test_gprof.c** y **test_gprof_new.c**:  
  Contienen ejemplos de código en C para probar la herramienta de perfilado. Se compilan usando la bandera `-pg` para habilitar la generación de datos de perfil (archivo `gmon.out`).

- **gmon.out**:  
  Archivo generado automáticamente por `gprof` después de ejecutar los binarios compilados con la opción `-pg`.

- **analysis.txt**:  
  Documento que describe los resultados del perfilado, la interpretación de los tiempos de ejecución y cualquier conclusión obtenida.

### Cómo usar `gprof` en este proyecto

1. **Compila los archivos con la opción `-pg`:**

   ```bash
   gcc Wall -pg test_gprof.c test_gprof_new.c -o test_gprof
2. **Ejecuta el binario resultante para generar `gmon.out`:**

    ```bash
    ./test_gprof
3. **Utiliza `gprof` para analizar la salida:**
    ```bash
    gprof test_gprof gmon.out > analysis.txt
4. **Revisa el archivo `analysis.txt` para ver los resultados detallados.**

## 2. Carpeta `Lab1SoC` (STM32F103)

Esta carpeta contiene el código para la placa STM32F103, configurada para:

- Ejecutar un programa con duración de 10 segundos a una frecuencia de 24 MHz.
- Usar la extensión de [PlatformIO](https://platformio.org/) en Visual Studio Code para compilar y subir el binario a la tarjeta.

Dentro de esta carpeta encontrarás:

- **src/**:  
  Código fuente principal `main.c` para la STM32F103. 

- **include/**:  
  Archivos de cabecera con declaraciones de funciones, macros, etc.

- **platformio.ini**:  
  Archivo de configuración para PlatformIO, donde se especifica la plataforma (`ststm32`), el board (`bluepill_f103c8`), la velocidad de reloj, entre otras opciones.

### Cómo usar PlatformIO para este proyecto

1. Asegúrate de tener [Visual Studio Code](https://code.visualstudio.com/) y la extensión de PlatformIO instalados.
2. Abre la carpeta `Lab1SoC` como proyecto en VSCode.
3. Modifica el archivo `platformio.ini` si deseas cambiar la placa, la frecuencia o configuraciones adicionales.
4. Conecta la STM32F103 a tu computadora mediante el programador (ST-Link u otro).
5. En la pestaña de PlatformIO, selecciona la opción **Upload** para compilar y subir el binario.

## Requisitos

- **gcc** o cualquier otro compilador de C para la parte de perfilado (carpeta `timeProfiling`).
- **gprof** para el análisis de tiempos de ejecución.
- **Visual Studio Code** con la extensión de **PlatformIO** para la parte de STM32F103.
- **STM32F103** (o placa compatible) para ejecutar el programa a 24 MHz.
