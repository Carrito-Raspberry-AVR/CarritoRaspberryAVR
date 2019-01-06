/* =======================================================
* 
* Carro conectado a Internet
* 
* main.c
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
	inicializar_uart();
	// Inicializar LCD 
	inicializar_LCD();
	// Inicializar motor driver
	inicializar_motor_driver();

	// Habilitar interrupciones globales
	sei();

	// Imprimir Inicialización
	lcd_imprimir_string("Hola Futuro Estudiante");

    while (1) 
    {
		switch (ESTADO) {
			// ¿Manejar motor?
			case manejar_motor:
				motor_driver_manejar(&estado_motor);
				break;

			// ¿Analizar mensaje?
			case analizar_mensaje:
				// Tipo de dato: Peticion
				if (dato_recibido >> 7) {
					uart_transmitir(distancia);
				}
				// Tipo de dato: Orden
				else {
					// Extraer Informacion
					velocidad = (dato_recibido && velocidad_mascara) >> 2;
					direcccion = dato_recibido && direcccion_mascara;
					// Configurar Estado de motor
					estado_motor.velocidad = analizar_velocidad(velocidad);
					estado_motor.direcccion = analizar_direccion(direcccion);
				}
				// Volver a menejar motor
				ESTADO = manejar_motor;
				break;

			// ¿Analizar Ultrasonido?
			case analizar_ultrasonido:
				// Calcular Distancia

				// Configurar 
				if (distancia > d_30cm) {
					estado_motor.velocidad = velocidad_1;
				} else if (distancia > d_20cm) {
					estado_motor.velocidad = velocidad_2;
				} else if (distancia > d_10cm) {
					estado_motor.velocidad = velocidad_3;
				} else {
					estado_motor.velocidad = para;
				}
				// Volver a menejar motor
				ESTADO = manejar_motor;
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