#include "avr_ultrasonic_sensor.h"

void inicializar_ultrasonido()
{
	/* Configurar Puertos */
	// Configurar Echo Pin
	DDRC &= ~(1<<PINC5);
	// Configurar Trigger Pin
	DDRC |= (1<<PINC4);

	/* Configurar Interrupcion Externa */
	//	- Activar Interrupciones Externas en PCINT[14:8]
	PCICR = (1<<PCIE1);
	// 	- Enmascarar para usar solo pin PC5
	PCMSK1 = (1<<PCINT13);

	/* Configurar Timer 1: */
	//	- Normal port operation, OC1A / OC1B desconectado
	// 	- Modo de operacion: CTC
	// 	- TOP OCR1A
	// 	- Update of OCR1Ax en inmediata
	// 	- TOV1 Flag: MAX
	TCCR1A = 0x00; 
	// 	- Prescaler 64 
	TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10); 
	// 	- Activa interrupcion por OCA
	TIMSK1 = (1<<OCIEA); 
	// Interrumpe en 60 ms
	OCR1A = 0x3A98; 

	/* Configurar Timer 2: */
	// 	- Modo CTC
	TCCR2A = (1<<WGM21); 
	// 	- No conectado, no inicia cuenta
	TCCR2B = 0x00; 
	// 	- Activa interrupcion por OCRA2
	TIMSK2 = (1<<OCIEA); 
	// 	- Apaga pin PB0 en 10us
	OCR2A = 160; 
}
