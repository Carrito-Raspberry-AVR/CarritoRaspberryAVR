/*
*
*
*
*/

#ifndef AVR_BATTERY_TESTER_H_

#define AVR_BATTERY_TESTER_H_

#include <avr/interrupt.h>

uint16_t adc = 0xFFFF; 

void ADC_init();
void Mostrar_Bateria();

#endif 