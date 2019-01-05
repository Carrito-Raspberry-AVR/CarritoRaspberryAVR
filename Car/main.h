#define F_CPU 16000000
#define BAUD 9600
#define MY_UBRR F_CPU / 16 / BAUD - 1

// Estados
#define Prender 0x41
#define Apagar 0x42
#define Velocidad_1 0x43
#define Velocidad_2 0x44
#define Velocidad_3 0x45
#define Velocidad_4 0x46

// #include <avr/io.h>
#include <avr/interrupt.h>
// #include <stdio.h>
// #include <stdlib.h>

#include "Libraries/avr_uart.c"
#include "Libraries/avr_motor_driver.c"
#include "Libraries/avr_ultrasonic_sensor.c"
#include "Libraries/avr_lcd1602.c"
#include "Libraries/avr_battery_tester.c"

/* Declarar varibales globales */
uint8_t FLAG;
uint8_t ESTADO;
uint16_t ECHO;
uint16_t cuenta_tim1;