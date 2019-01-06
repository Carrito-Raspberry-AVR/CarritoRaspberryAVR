#include "avr_motor_driver.h"

void inicializar_motor_driver()
{
	// Inicializar Puertos
	motor_DDR |= (1<<Pin_MI_1) | (1<<Pin_MI_2) | (1<<Pin_MD_1) | (1<<Pin_MD_2);
	// Inicializar PWM
	
	// Estado inicial
	
}

void motor_driver_manejar(estados_motor *estado_motor)
{
	// estado_motor->velocidad
	// estado_motor->direccion

}