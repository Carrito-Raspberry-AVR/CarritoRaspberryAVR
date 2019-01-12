/* =======================================================
* 
* Carro conectado a Internet
* 
* main.h
*
* ========================================================
* Electrónica - UTEC
*
* Asesor:
*	- Jimmy Tarrillo
*
* Alumnos: 
*	- Joseph Peña
*	- Amaru Escalante
*	- Alessio Ghio
*	- Cristian Amaya
* 	- David Shatwell
* =======================================================
*/
/* ---------------------- MACROS ---------------------- */
// Frecuencia
#define F_CPU 16000000

// UART Dependencias
#define BAUD 9600
#define BAUDRATE F_CPU / 16 / BAUD - 1

// Estados
#define manejar_motor 'a'
#define analizar_mensaje 'b'
#define analizar_ultrasonido 'c'

// Velocidad
#define velocidad_1 30
#define velocidad_2 60
#define velocidad_3 90

// Macros Functions
#define analizar_velocidad(velocidad) (1*velocidad)

// Mascaras
#define velocidad_mascara 0b01111100 
#define direccion_mascara 0b00000011


/* ---------------- Headers y Libraries ---------------- */
// AVR Libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <util/delay.h>
#include <string.h>

// Librerias de Perifericos
#include "Libraries/avr_motor_driver.c"
#include "Libraries/avr_uart.c"
#include "Libraries/avr_lcd1602.c"
#include "Libraries/avr_ultrasonic_sensor.c"

/* ------------ Declarar Varibales Globales ------------ */

char ESTADO;
uint8_t dato_recibido;