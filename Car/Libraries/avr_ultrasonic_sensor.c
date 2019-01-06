#include "avr_ultrasonic_sensor.h"

void inicializar_ultrasonido()
{
	/* Configurar interrupciones externas */
	//Activa interrupciones en cualquier cambio de nivel lógico
	EICRA = 0x01; 
	//Habilita INT0
	EIMSK = 0x01; 

	/* Configurar Timer 0 */
	TCCR0A = (0<<COM0A1)|(1<<WGM01)|(1<<WGM00);

	/* Configurar Timer 1 */
	// Normal Mode, WGM11:WGM10 = 00
	TCCR1A = 0x00; 
	// Prescaler 64 - WGM13:WGM12 = 00
	TCCR1B = 0x0B; 
	// Activa interrupcion por OCA
	TIMSK1 = 0x02; 
	// Interrumpe en 60 ms
	OCR1A = 0x3A98; 

	/* Configurar Timer 2 */
	// Modo CTC
	TCCR2A = 0x02; 
	// No conectado, no inicia cuenta
	TCCR2B = 0x00; 
	// Activa interrupcion por OCRA2
	TIMSK2 = 0x02; 
	// Apaga pin PB0 en 10us
	OCR2A = 160; 
}
