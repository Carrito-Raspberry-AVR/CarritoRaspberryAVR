#include "avr_battery_tester.h"

// adc = 0xFFFF; 

void ADC_init()
{
	/* Configurar ADC */
	ADMUX = 0x00;
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) |(1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	DIDR0 = (1<<1);
}

void Mostrar_Bateria()
{
	// 100% - 81%
	if(adc >= 0x0352) 
	{
		PORTC = (1<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1);
	}
	//  80% - 61%
	else if(adc >= 0x0305) 
	{
		PORTC = (0<<5)|(1<<4)|(1<<3)|(1<<2)|(1<<1);
	}
	// 60% - 41%
	else if(adc >= 0x03B8) 
	{
		PORTC = (0<<5)|(0<<4)|(1<<3)|(1<<2)|(1<<1);
	}
	// 40% - 21%
	else if(adc >= 0x026A) 
	{
		PORTC =(0<<5)|(0<<4)|(0<<3)|(1<<2)|(1<<1);
	}
	// 20% - 0%
	else 
	{
		PORTC =(0<<5)|(0<<4)|(0<<3)|(0<<2)|(1<<1);
	}
}

ISR(ADC_vect)
{
	adc = ADC;
}