/* =======================================================
* Carro
* AVR C
* Electrónica - UTEC
 * =======================================================
*/

#define F_CPU 16000000
#define BAUD 9600
#define MY_UBRR F_CPU / 16 / BAUD - 1

// #include <avr/io.h>
#include <avr/interrupt.h>
// #include <stdio.h>
// #include <stdlib.h>

#include "Libraries/avr_uart.c"
#include "Libraries/avr_motor_driver.c"
#include "Libraries/avr_ultrasonic_sensor.c"
#include "Libraries/avr_lcd1602.c"
#include "Libraries/avr_battery_tester.c"

/* Inicializar varibales globales */
uint8_t FLAG = 0;
uint8_t ESTADO;

uint16_t ECHO = 0;

uint16_t cuenta_tim1;

int main(void)
{
	/* Configurar pila */
	// SP = RAMEND;

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

	/* Configurar puertos */
	// Sexto pin del puerto D como salida - OC0A
	DDRD = (1<<6);
	// Pines 0 y 1 del puerto B como salida
	DDRB = (1<<0) | (1<<1);
	// Todos los pines menos el 0 del puerto C como salida
	DDRC = 0xFE; 

	/* Configurar UART */
	UART_init(MY_UBRR);

	// Estado = 65
	ESTADO = 0x41; 

	/* Habilitar interrupciones globales */
	sei();

    while (1) 
    {
		
		switch (ESTADO) {
			// ¿Prende?
			case 'A':
				// Conectar PWM
				TCCR0A = (1<<COM0A1)|(1<<WGM01)|(1<<WGM00); 
				// Duty cycle mínimo para que se mueva el motor
				OCR0A = 0x5A; 
				// Iniciar Timer 0
				TCCR0B = (0<<CS02)|(1<<CS00); 
				break;

			// ¿Apaga?
			case 'B':
				// Desconectar PWM
				TCCR0A = (0<<COM0A1)|(1<<WGM01)|(1<<WGM00); 
				// Detener Timer 0
				TCCR0B = (0<<CS02)|(0<<CS00); 
				break;

			// ¿Vel_1?
			case 'C':
				// Cambiar velocidad a Vel_1
				OCR0A = 0x96; 
				break;

			// ¿Vel_2?
			case 'D':
				// Cambiar velocidad a Vel_2
				OCR0A = 0xB9; 
				break;

			// ¿Vel_3?
			case 'E':
				// Cambiar velocidad a Vel_3
				OCR0A = 0xDC; 
				break;

			// ¿Vel_4?
			case 'F':
				// Cambiar velocidad a Vel_4
				OCR0A = 0xFF; 
				break;

			default:
				//NADA	
				break;
		}

		// Mostrar_Bateria();
    }
}




ISR(TIMER1_COMPA_vect)
{
	TCCR2B = 0x01;
	// Enciende trigger
	PORTB = (1<<PINB1); 
}

ISR(TIMER2_COMPA_vect)
{
	// Apaga trigger
	PORTB = (0<<PINB0); 
	// Desconecta el TIMER2
	TCCR2B = 0x00; 
}

ISR(INT0_vect)
{
	if(FLAG == 0x00)
	{
		FLAG = 0xFF;
		// Guardar cuenta
		cuenta_tim1 = TCNT1; 
		// Reiniciar cuenta
		TCNT1 = 0x0000;
		// Desactiva interrupcion por OCA 
		TIMSK1 = 0x00; 
	}
	else if(FLAG == 0xFF)
	{
		FLAG = 0x00;
		// Guardar nueva cuenta
		ECHO = TCNT1; 
		// Desactiva interrupcion por OCA
		TIMSK1 = 0x02; 
		if(ECHO < 0x0100)
		{
			// Encender Alarma
			PORTB = (1<<PINB0); 
			// Sumar cuentas
			cuenta_tim1 = cuenta_tim1 + TCNT1; 
			// Cambia el ESTADO a APAGA
			ESTADO = 0x42; 
		}
		else
		{
			// Apaga Alarma
			PORTB = (0<<PINB0); 
			// Sumar cuentas
			cuenta_tim1 = cuenta_tim1 + TCNT1; 
			TCNT1 = cuenta_tim1;
		}
	}
}

ISR(USART_RX_vect)
{
	ESTADO = UDR0;
}

