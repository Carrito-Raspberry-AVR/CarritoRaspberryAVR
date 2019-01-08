#ifndef AVR_MOTOR_DRIVER_H_
#define AVR_MOTOR_DRIVER_H_

// Puertos
#define motor_PORT PORTD
#define motor_DDR DDRD

#define Pin_MI_1 3
#define Pin_MI_2 4

#define Pin_MD_1 6
#define Pin_MD_2 7

// Direcciones
#define adelante 0
#define atras 1
#define izquierda 2
#define derecha 3

// Structuras
struct estado_motor
{
	uint8_t velocidad : 6;
	uint8_t direccion : 2;
};

typedef struct estado_motor Estados_motor;

// Definir Funciones
void inicializar_motor_driver();
void motor_driver_manejar(Estados_motor *estado_motor);

#endif 