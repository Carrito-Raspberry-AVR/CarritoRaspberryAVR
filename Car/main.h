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

// UART 
#define BAUD 9600
#define MY_UBRR F_CPU / 16 / BAUD - 1

// Estados
#define manejar_motor 'a'
#define manejar_motor 'b'
#define manejar_motor 'c'

// Velocidad
#define velocidad_1 0x01
#define velocidad_2 0x02
#define velocidad_3 0x03

// Macros Functions
// #define analizar_velocidad(velocidad) : 
// #define analizar_direccion(direccion)

// Mascaras
#define velocidad_mascara 0b01111100 
#define direccion_mascara 0b00000011

/* ---------------- Headers y Libraries ---------------- */

#include <avr/interrupt.h>

#include "Libraries/avr_uart.c"
#include "Libraries/avr_motor_driver.c"
#include "Libraries/avr_ultrasonic_sensor.c"
#include "Libraries/avr_lcd1602.c"
#include "Libraries/avr_battery_tester.c"

/* ------------ Declarar Varibales Globales ------------ */
uint8_t FLAG;
uint8_t ESTADO;
uint16_t ECHO;
uint16_t cuenta_tim1;