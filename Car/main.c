/* =======================================================
* 
* Carro conectado a Internet
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

# include "main.h"

// Inicializar Variables Globales
FLAG = 0;
ESTADO = Prender;
ECHO = 0;
cuenta_tim1 = 0;

int main(void)
{
	// Inicializar ultra-sonido
	inicializar_ultrasonido();
	// Inicializar UART
	inicializar_comunicacion();
	// Inicializar LCD 
	inicializar_LCD();
	// Inicializar motor driver
	inicializar_motor_driver();

	/* Habilitar interrupciones globales */
	sei();

    while (1) 
    {
		switch (ESTADO) {
			// ¿Prende?
			case Prender:
				// Conectar PWM
				TCCR0A = (1<<COM0A1)|(1<<WGM01)|(1<<WGM00); 
				// Duty cycle mínimo para que se mueva el motor
				OCR0A = 0x5A; 
				// Iniciar Timer 0
				TCCR0B = (0<<CS02)|(1<<CS00); 
				break;

			// ¿Apaga?
			case Apagar:
				// Desconectar PWM
				TCCR0A = (0<<COM0A1)|(1<<WGM01)|(1<<WGM00); 
				// Detener Timer 0
				TCCR0B = (0<<CS02)|(0<<CS00); 
				break;

			// ¿Velocidad 1?
			case Velocidad_1:
				// Cambiar velocidad a Vel_1
				OCR0A = 0x96; 
				break;

			// ¿Velocidad 2?
			case Velocidad_2:
				// Cambiar velocidad a Vel_2
				OCR0A = 0xB9; 
				break;

			// ¿Velocidad 3?
			case Velocidad_3:
				// Cambiar velocidad a Vel_3
				OCR0A = 0xDC; 
				break;

			// ¿Velocidad 4?
			case Velocidad_4:
				// Cambiar velocidad a Vel_4
				OCR0A = 0xFF; 
				break;

			default:
				// Nada
				break;
		}
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