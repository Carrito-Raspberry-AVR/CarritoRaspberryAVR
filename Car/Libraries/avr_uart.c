#include "avr_uart.h"

void inicializar_uart()
{
	// Configurar Puertos
	UART_DDR |= (1 << Pin_Tx);
	UART_DDR &= ~(1 << Pin_Rx);
	// Setear el BAUD
	UBRR0H = (BAUDRATE >> 8);
	UBRR0L = BAUDRATE;
	// Habilitar RX y TX e interrupción por RX
	UCSR0B = (1<<RXCIE0) | (1<<RXEN0) | (1<<TXEN0);
	// Setear el formato "Frame format": 8 bit data - 1 stop bit
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
}

void uart_transmitir_char(unsigned char data)
{
	// wait while register is free
	while (!( UCSR0A & (1<<UDRE0)));	
	// load data in the register
	UDR0 = data;                        
	while (!(UCSR0A & (1<<TXC0)));
}

void send_text(unsigned char data[])
{
	int k = 100;
	int i;
	for (i = 0; i < k; i+=1) {
		uart_transmitir_char(data[i]);
	}
}