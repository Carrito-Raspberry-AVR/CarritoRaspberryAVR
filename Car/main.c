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

#include "main.h"

int main(void)
{
	// Inicializar ultra-sonido
	inicializar_ultrasonido();
	// Inicializar UART
	inicializar_uart(MY_UBRR);
	// Inicializar LCD 
	inicializar_LCD();
	// Inicializar motor driver
	inicializar_motor_driver();

	// Habilitar interrupciones globales
	sei();

	// Imprimir Inicialización
	lcd_imprimir_mensaje("Hola Futuro Estudiante");

	// Variables
	uint8_t distancia;
	uint8_t direccion;
	uint8_t velocidad;

	ESTADO = manejar_motor;

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
					uart_transmitir_char(distancia);
				}
				// Tipo de dato: Orden
				else {
					// Extraer Informacion
					velocidad = (dato_recibido && velocidad_mascara) >> 2;
					direccion = dato_recibido && direccion_mascara;
					// Configurar Estado de motor
					estado_motor.velocidad = analizar_velocidad(velocidad);
					estado_motor.direccion = direccion;
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
					estado_motor.velocidad = 0;
				}
				// Volver a menejar motor
				ESTADO = manejar_motor;
				break;

			// No se reconoce estado
			default:
				// Nada
				break;
		}
		lcd_limpiar();
		lcd_imprimir_string_xy(0, 0, "Estado:");
		lcd_imprimir_string_xy(1, 0, "XD");
    }
}

// ISR(USART_RX_vect)
// {
// 	// Guradar dato recibido
// 	dato_recibido = UDR0;
// 	// Cambiar Estado
// 	ESTADO = analizar_mensaje;
// }

// ISR(TIMER1_COMPA_vect)
// {
// 	TCCR2B = 0x01;
// 	// Enciende trigger
// 	PORTB = (1<<PINB1); 
// }

// ISR(TIMER2_COMPA_vect)
// {
// 	// Apaga trigger
// 	PORTB = (0<<PINB0); 
// 	// Desconecta el TIMER2
// 	TCCR2B = 0x00; 
// }

// ISR(INT0_vect)
// {
// 	if(FLAG == 0x00)
// 	{
// 		FLAG = 0xFF;
// 		// Guardar cuenta
// 		cuenta_tim1 = TCNT1; 
// 		// Reiniciar cuenta
// 		TCNT1 = 0x0000;
// 		// Desactiva interrupcion por OCA 
// 		TIMSK1 = 0x00; 
// 	}
// 	else if(FLAG == 0xFF)
// 	{
// 		FLAG = 0x00;
// 		// Guardar nueva cuenta
// 		ECHO = TCNT1; 
// 		// Desactiva interrupcion por OCA
// 		TIMSK1 = 0x02; 
// 		if(ECHO < 0x0100)
// 		{
// 			// Encender Alarma
// 			PORTB = (1<<PINB0); 
// 			// Sumar cuentas
// 			cuenta_tim1 = cuenta_tim1 + TCNT1; 
// 			// Cambia el ESTADO a APAGA
// 			ESTADO = 0x42; 
// 		}
// 		else
// 		{
// 			// Apaga Alarma
// 			PORTB = (0<<PINB0); 
// 			// Sumar cuentas
// 			cuenta_tim1 = cuenta_tim1 + TCNT1; 
// 			TCNT1 = cuenta_tim1;
// 		}
// 	}
// }