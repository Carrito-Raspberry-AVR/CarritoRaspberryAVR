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
	/*inicializar_ultrasonido();*/
	// Inicializar UART
	inicializar_uart();
	// Inicializar LCD 
	inicializar_LCD();
	// Inicializar motor driver
	inicializar_motor_driver();

	// Imprimir Inicialización
	/*lcd_imprimir_mensaje("Hola Futuro Estudiante");*/
	/*lcd_limpiar();*/
	lcd_imprimir_string_xy(0, 0, "Hola Futuro     ");
	lcd_imprimir_string_xy(1, 0, "Estudiante: ");
	
	_delay_ms(1000);
	// Variables
	uint8_t distancia;
	uint8_t direccion;
	uint8_t velocidad;

	ESTADO = manejar_motor;
	
	// Habilitar interrupciones globales
	sei();

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
					/*velocidad = (dato_recibido && velocidad_mascara) >> 2;*/
					velocidad = (dato_recibido && velocidad_mascara);
					direccion = dato_recibido & direccion_mascara;
					// Configurar Estado de motor
					/*estado_motor.velocidad = analizar_velocidad(velocidad);*/
					estado_motor.velocidad = velocidad;
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
		/*lcd_imprimir_string_xy(0, 0, "Distancia:       ");
		lcd_imprimir_string_xy(1, 0, "30 cm            ");*/
    }
}

ISR(USART_RX_vect)
{
	// Guradar dato recibido
	dato_recibido = UDR0;
	// Cambiar Estado
	ESTADO = analizar_mensaje;
}

ISR(TIMER0_COMPA_vect)
{
	if (estado_timer) {
		// Cambiar a comparador A
		
		// Motores a avanzar
		
	} else {
		// Cambiar a comparador B

		// Motores a parar
		motor_PORT &= ~((1<<Pin_MD_1) | (1<<Pin_MD_2));
		motor_PORT &= ~((1<<Pin_MI_1) | (1<<Pin_MI_2));
	}
}