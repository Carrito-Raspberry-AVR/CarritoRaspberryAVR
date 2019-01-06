/*
* avr_lcd1602.h
* 	
* http://www.electronicwings.com
*/

#ifndef AVR_LCD1602_H_
#define AVR_LCD1602_H_

// #define  F_CPU 1000000UL
// #include <avr/io.h>
// #include <util/delay.h>
#define LCD_DPRT PORTD
#define LCD_DDDR DDRD	
#define LCD_RS 2
#define LCD_EN 3

void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void inicializar_LCD();
void LCD_String_xy(unsigned char, unsigned char, char *);
void LCD_String(char *str);
void lcd_limpiar();
void lcd_imprimir_mensaje(char *mensaje);

#endif 