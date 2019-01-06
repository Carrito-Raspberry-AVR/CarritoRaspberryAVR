#ifndef AVR_UART_H_
#define AVR_UART_H_

// Puertos
#define UART_DDR DDRD

#define Pin_Tx 1
#define Pin_Rx 0

// Definir Funciones
void inicializar_uart();
void uart_transmitir_char(unsigned char data);
void send_text(unsigned char data[]);

#endif 