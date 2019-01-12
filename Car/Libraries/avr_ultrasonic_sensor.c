#include "avr_ultrasonic_sensor.h"

void inicializar_ultrasonido()
{
	// Ports
    DDRC |= (1<<trigger_pin);
    DDRC &= ~(1<<echo_pin);

    DDRB |= (1<<led_pin);
    /* Timer 1 */
    // - Normal port operation, OC1A/OC1B disconnected.
    TCCR1A = 0x00;
    OCR1A = calcular_OCR1A_ms(60);
    // - Configuracion CTC en OCR1A
    // - Prescaler de 64
    TCCR1B |= (1 << CS11) | (1 << CS10)| (1 << WGM12);
    // - Habilitar Interrupcion
    TIMSK1 = (1<<OCIE1A);

    /* Interrupt */
    // - Activar Interrupciones Externas en PCINT[14:8]
    PCICR = (1<<PCIE1);
    // - Enmascarar para usar solo pin PC5
    PCMSK1 = (1<<PCINT13); 
}


ISR(TIMER1_COMPA_vect)
{
    static char estado_pwm = 0;
    
	if (estado_pwm)
    {
        OCR1A = calcular_OCR1A_us(10);
        PORTC |=  (1<<trigger_pin);
    } else {
        OCR1A = calcular_OCR1A_ms(60);
        PORTC &= ~(1<<trigger_pin);
    }
    estado_pwm = ~estado_pwm;
    

}

