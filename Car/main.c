/* =======================================================
* 
* Carro conectado a Internet
* 
* ========================================================
* Electr�nica - UTEC
*
* Asesor:
*	- Jimmy Tarrillo
*
* Alumnos: 
*	- Joseph Pe�a
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

	// Habilitar interrupciones globales
	sei();

	// Imprimir Inicializaci�n
	lcd_imprimir_string("Hola Futuro Estudiante");

    while (1) 
    {
		switch (ESTADO) {
			// �Ir hacia adelante?
			case avanzar_adelante:
				motor_driver_manejar(m_adelante, velocidad);
				break;

			// �Ir hacia atras?
			case avanzar_atras:
				motor_driver_manejar(m_atras, velocidad);
				break;

			// �Voltear hacia la derecha?
			case voltear_izquierda:
				motor_driver_manejar(m_izquierda, velocidad);
				break;

			// �Voltear hacia la derecha?
			case voltear_derecha:
				motor_driver_manejar(m_derecha, velocidad);
				break;

			// �Parar?
			case parar:
				motor_driver_manejar(m_parar, 0);
				break;

			// �Analizar mensaje?
			case analizar_mensaje:
				break;

			// �Analizar Ultrasonido?
			case analizar_ultrasonido:
				break;

			// No se reconoce estado
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