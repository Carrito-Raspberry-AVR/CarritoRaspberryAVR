/* =======================================================
* 
* Carro conectado a Internet
* 
* main.c
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
* =======================================================
*/

#include "main.h"

int main(void)
{
	// Declarar el pin Debugging
	DDRB = (1<<led_pin);
	// Inicializar ultra-sonido
	inicializar_ultrasonido();
	// Inicializar UART
	inicializar_uart();
	// Inicializar LCD 
	inicializar_LCD();
	lcd_limpiar();
	// Inicializar motor driver
	inicializar_motor_driver();

	// Imprimir Inicializaci�n
	// lcd_imprimir_mensaje("Hola Futuro Estudiante");
	/*lcd_limpiar();*/
	lcd_imprimir_string_xy(0, 0, "Bienvenidos a   ");
	lcd_imprimir_string_xy(1, 0, "UTEC            ");
	
	_delay_ms(1000);
	// Variables
	uint8_t distancia;
	uint8_t direccion;
	uint8_t velocidad;

	ESTADO = manejar_motor;

	estado_motor.velocidad= 50;
	
	// Habilitar interrupciones globales
	sei();

    while (1) 
    {
    	_delay_us(1);
		switch (ESTADO) {
			// �Manejar motor?
			case manejar_motor:
				motor_driver_manejar(&estado_motor);
				break;

			// �Analizar mensaje?
			case analizar_mensaje:
				// Volver a menejar motor
				switch (dato_recibido){
					case 'a':
						// estado_motor.velocidad = 90;
						estado_motor.direccion = adelante;
						break;
					case 'b':
						estado_motor.direccion = atras;
						break;
					case 'c':
						estado_motor.direccion = izquierda;
						break;
					case 'd':
						estado_motor.direccion = derecha;
						break;
					case 'e':
						estado_motor.direccion = parar;
						break;
					case 'f':
						// uart_transmitir_char(estado_motor.direccion);
						// send_text("a");
						uart_transmitir_char('5');
						uart_transmitir_char('5');
						uart_transmitir_char(0x0a);
					default:
						break;

				}
				ESTADO = manejar_motor;
				break;

			// �Analizar Ultrasonido?
			case analizar_ultrasonido:
				// Calcular Distancia
				distancia =  distancia_ultrasonic(echo);
				// Configurar 
				if (distancia > 30) {
					estado_motor.velocidad = velocidad_3;
					PORTB &= ~(1<<led_pin);
				} 
				else if (distancia > 20) {
					estado_motor.velocidad = velocidad_2;
					PORTB &= ~(1<<led_pin);
				} 
				else if (distancia > 10) {
					estado_motor.velocidad = velocidad_1;
					PORTB &= ~(1<<led_pin);
				} 
				else {
					estado_motor.velocidad = 0;
					PORTB  |= (1<<led_pin);
					// Desactivar PCIN1
					// Timer1 compa
					// Timer0 compa
				}
				// Volver a menejar motor
				ESTADO = manejar_motor;
				break;

			// No se reconoce estado
			default:
				// Nada
				break;
		}
		// char array_str[4];
		// itoa(distancia, array_str, 10);

		// lcd_imprimir_string_xy(0, 0, "Distancia:       ");
		// lcd_imprimir_string_xy(1, 0, array_str);
		// lcd_imprimir_string_xy(1, 0, "30");
		// LCD_String(" cm    ");
    }
}

ISR(USART_RX_vect)
{
	// Guradar dato recibido
	dato_recibido = UDR0;
	// Cambiar Estado
	ESTADO = analizar_mensaje;
}

ISR(PCINT1_vect)
{
	static char interrupcion_pcint = 0xFF;
	// if (motor_habilitado) {
		if (interrupcion_pcint) {
	        cuenta = TCNT1;
	        TCNT1 = 0;
	        TIMSK1 = 0;
	    } else {
	        echo = TCNT1;
	        TIMSK1 = (1<<OCIE1A);
	        ESTADO = analizar_ultrasonido;
	        // ultrasonido_distancia = distancia_ultrasonic(echo);
	        /*
	        if (distancia_ultrasonic(echo) < 20.0) {
	            PORTB  |= (1<<led_pin);
	            estado_motor.velocidad = 20;
	        }
	        else {
	            PORTB &= ~(1<<led_pin);
	            estado_motor.velocidad = 70;
	        }
	        */
	    }
	    cuenta = cuenta + TCNT1;
	    interrupcion_pcint = ~interrupcion_pcint;
	// }
}