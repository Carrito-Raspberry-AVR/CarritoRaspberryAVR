#include "avr_motor_driver.h"

Estados_motor estado_motor;

void inicializar_motor_driver()
{
	/* Inicializar Puertos */
	motor_DDR |= (1<<Pin_MI_1) | (1<<Pin_MI_2) | (1<<Pin_MD_1) | (1<<Pin_MD_2);
	
	/* Configurar Timer 0: */
	// 	- Fast PWM
	// 	- Normal Port Operation, OC0A desconectado
	    // Set the Timer Mode to CTC
    TCCR0A |= (1 << WGM01);

    // Start the timer with prescaler to 64
    TCCR0B |= (1 << CS01) | (1 << CS00);

    // Enable Interrupt
    TIMSK0 = (1<<OCIEA);
	estado_motor.pin_high_1 = 6;
    estado_motor.pin_high_2 = 7;
    estado_motor.pin_low_1 = 3;
    estado_motor.pin_low_2 = 4;
	
	// Estado inicial
	estado_motor.velocidad = 50;
}

void motor_driver_manejar(Estados_motor *estado_motor)
{
	_delay_ms(1);
	if (estado_motor->velocidad == 0)
	{
		motor_habilitado = 0x00;
	}
	else 
	{
		motor_habilitado = 0xff;
	}
	switch(estado_motor->direccion)
	{
		case adelante:
			/*motor_derecha_adelante = estado_motor->velocidad;
			motor_izquierda_adelante = estado_motor->velocidad;
			motor_derecha_atras = 0;
			motor_izquierda_atras = 0;*/
			// motor_PORT |= (1<<Pin_MI_1) | (1<<Pin_MD_1);
			// motor_PORT &= ~((1<<Pin_MI_2) | (1<<Pin_MD_2));

			
			break;
		case atras:
			/*motor_derecha_adelante = 0;
			motor_izquierda_adelante = 0;
			motor_derecha_atras = estado_motor->velocidad;
			motor_izquierda_atras = estado_motor->velocidad;*/
			// motor_PORT |= (1<<Pin_MI_2) | (1<<Pin_MD_2);
			// motor_PORT &= ~((1<<Pin_MI_1) | (1<<Pin_MD_1));
			break;
		case izquierda:
			/*motor_derecha_adelante = 0;
			motor_izquierda_adelante = estado_motor->velocidad;
			motor_derecha_atras = estado_motor->velocidad;
			motor_izquierda_atras = 0;*/
			// motor_PORT |= (1<<Pin_MI_1) | (1<<Pin_MD_2);
			// motor_PORT &= ~((1<<Pin_MI_2) | (1<<Pin_MD_1));
			break;
		case derecha:
			/*motor_derecha_adelante = estado_motor->velocidad;
			motor_izquierda_adelante = 0;
			motor_derecha_atras = 0;
			motor_izquierda_atras = estado_motor->velocidad;*/
			// motor_PORT |= (1<<Pin_MI_2) | (1<<Pin_MD_1);
			// motor_PORT &= ~((1<<Pin_MI_1) | (1<<Pin_MD_2));
			break;
		default:
			break;
	}
}

ISR(TIMER0_COMPA_vect)
{
	// uart_transmitir_char(estado_motor.velocidad);
	// _delay_us(100);

    static char estado_pwm = 0;
    // if (motor_habilitado == 0xff) {
    if (estado_motor.velocidad != 0){
		if (estado_pwm)
	    {   
	        // OCR0A = tiempo_high;
	        OCR0A = calcular_pwm_high(estado_motor.velocidad);
	        PORTD |= (1<<estado_motor.pin_high_1);
	        PORTD |= (1<<estado_motor.pin_high_2);
	    } else {
	        // OCR0A = tiempo_low;
	        OCR0A = calcular_pwm_low(estado_motor.velocidad);

	        PORTD &= ~(1<<estado_motor.pin_high_1);
	        PORTD &= ~(1<<estado_motor.pin_high_2);
	    }
    }
    // else if (motor_habilitado == 0x00){
    else {
    	PORTD &= ~(1<<estado_motor.pin_high_1);
		PORTD &= ~(1<<estado_motor.pin_high_2);
    }

    estado_pwm = ~estado_pwm;

}