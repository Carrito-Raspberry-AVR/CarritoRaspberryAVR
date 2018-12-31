#include "avr_uart.h"

void UART_init(unsigned int ubrr);

void UART_init(unsigned int ubrr)
{

	//Setear el BAUD
	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;
	//Habilitar RX y TX e interrupción por RX
	UCSR0B = (1<<RXCIE0)|(1<<RXEN0)|(1<<TXEN0);
	//Setear el formato "Frame format"
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	/*	8 bit data - 1 stop bit	   */
}