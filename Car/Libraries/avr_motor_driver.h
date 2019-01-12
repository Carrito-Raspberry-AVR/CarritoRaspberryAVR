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

// Bits Registros
#define TOIE 0
#define OCIEA 1
#define OCIEB 2

// PWM
#define frecuencia_pwm 10000
#define calcular_pwm_high(DC) (DC * F_CPU / 100 / frecuencia_pwm / 64)
#define calcular_pwm_low(DC) ((100-DC)*F_CPU / 100 / frecuencia_pwm / 64)

// Structuras
struct estado_motor
{
	unsigned int velocidad;
	uint8_t direccion;

    uint8_t pin_high_1;
    uint8_t pin_low_1;
    uint8_t pin_high_2;
    uint8_t pin_low_2;
};

typedef struct estado_motor Estados_motor;

// Definir Funciones
void inicializar_motor_driver();
void motor_driver_manejar(Estados_motor *estado_motor);

unsigned int duty_cycle = 50;
char motor_habilitado = 0xff;

#endif 