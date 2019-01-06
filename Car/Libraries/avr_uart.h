#ifndef AVR_UART_H_
#define AVR_UART_H_

// Puertos
#define UART_DDR DDRD

#define Pin_Tx 1
#define Pin_Rx 0

// Definir Funciones
void inicializar_uart(unsigned int ubrr);
void uart_transmitir_char(char message);

#endif 