#ifndef AVR_MOTOR_DRIVER_H_
#define AVR_MOTOR_DRIVER_H_

// Puertos
#define motor_PORT PORTD
#define motor_DDR DDRD

#define Pin_MI_1 3
#define Pin_MI_2 4

#define Pin_MD_1 6
#define Pin_MD_2 7

// Structuras
struct estados_motor
{
	uint8_t velocidad;
	uint8_t direccion : 2;
} estado_motor;

// Definir Funciones
void inicializar_motor_driver();
void motor_driver_manejar(estados_motor *estado_motor);



#endif 