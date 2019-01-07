#include "avr_motor_driver.h"

Estados_motor estado_motor;

void inicializar_motor_driver()
{
	/* Inicializar Puertos */
	motor_DDR |= (1<<Pin_MI_1) | (1<<Pin_MI_2) | (1<<Pin_MD_1) | (1<<Pin_MD_2);
	
	/* Configurar Timer 0: */
	// 	- Fast PWM
	// 	- Normal Port Operation, OC0A desconectado
	TCCR0A = (0<<COM0A1) | (1<<WGM01) | (1<<WGM00);
	
	// Estado inicial
	
}

void motor_driver_manejar(Estados_motor *estado_motor)
{
	switch(estado_motor->direccion)
	{
		case adelante:
			/*motor_derecha_adelante = estado_motor->velocidad;
			motor_izquierda_adelante = estado_motor->velocidad;
			motor_derecha_atras = 0;
			motor_izquierda_atras = 0;*/
			motor_PORT |= (1<<Pin_MI_1) | (1<<Pin_MD_1);
			motor_PORT &= ~((1<<Pin_MI_2) | (1<<Pin_MD_2));
			break;
		case atras:
			/*motor_derecha_adelante = 0;
			motor_izquierda_adelante = 0;
			motor_derecha_atras = estado_motor->velocidad;
			motor_izquierda_atras = estado_motor->velocidad;*/
			motor_PORT |= (1<<Pin_MI_2) | (1<<Pin_MD_2);
			motor_PORT &= ~((1<<Pin_MI_1) | (1<<Pin_MD_1));
			break;
		case izquierda:
			/*motor_derecha_adelante = 0;
			motor_izquierda_adelante = estado_motor->velocidad;
			motor_derecha_atras = estado_motor->velocidad;
			motor_izquierda_atras = 0;*/
			motor_PORT |= (1<<Pin_MI_1) | (1<<Pin_MD_2);
			motor_PORT &= ~((1<<Pin_MI_2) | (1<<Pin_MD_1));
			break;
		case derecha:
			/*motor_derecha_adelante = estado_motor->velocidad;
			motor_izquierda_adelante = 0;
			motor_derecha_atras = 0;
			motor_izquierda_atras = estado_motor->velocidad;*/
			motor_PORT |= (1<<Pin_MI_2) | (1<<Pin_MD_1);
			motor_PORT &= ~((1<<Pin_MI_1) | (1<<Pin_MD_2));
			break;
		default:
			break;
	}
}