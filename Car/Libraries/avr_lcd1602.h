/*
* avr_lcd1602.h
* 	
* http://www.electronicwings.com
*/

#ifndef AVR_LCD1602_H_
#define AVR_LCD1602_H_

#define LCD_DPRT PORTB
#define LCD_DDDR DDRB	
#define LCD_RS 4
#define LCD_EN 5

void LCD_Command(unsigned char cmnd);
void LCD_Char(unsigned char data);
void inicializar_LCD();
void lcd_imprimir_string_xy(unsigned char, unsigned char, char *);
void LCD_String(char *str);
void lcd_limpiar();
void lcd_imprimir_mensaje(char *mensaje);

#endif 