/*
* avr_lcd1602.c
* 	
* http://www.electronicwings.com
*/

#include "avr_lcd1602.h"

void LCD_Command(unsigned char cmnd) {
	LCD_DPRT = (LCD_DPRT & 0xF0) | (cmnd >> 4);		/* SEND COMMAND TO DATA PORT */
	LCD_DPRT &= ~ (1<<LCD_RS);						/* RS = 0 FOR COMMAND */
	LCD_DPRT |= (1<<LCD_EN);						/* EN = 1 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_us(100);									/* WAIT FOR MAKE ENABLE WIDE */
	
	LCD_DPRT = (LCD_DPRT & 0xF0) | (cmnd & 0x0F);	/* SEND COMMAND TO DATA PORT */
	LCD_DPRT |= (1<<LCD_EN);						/* EN = 1 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_us(2000);								/* WAIT FOR MAKE ENABLE WIDE */
}

void LCD_Char(unsigned char data) {
	LCD_DPRT = (LCD_DPRT & 0xF0) | (data >> 4);		/* SEND DATA TO DATA PORT */
	LCD_DPRT |= (1<<LCD_RS);						/* MAKE RS = 1 FOR DATA */
	LCD_DPRT |= (1<<LCD_EN);						/* EN=0 FOR H TO L PULSE */
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE */
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE */
	_delay_us(100);									/* WAIT FOR MAKE ENABLE WIDE */
	
	LCD_DPRT = (LCD_DPRT & 0xF0) | (data & 0x0F);
	LCD_DPRT |= (1<<LCD_EN);						/* EN=0 FOR H TO L PULSE*/
	_delay_us(1);									/* WAIT FOR MAKE ENABLE WIDE*/
	LCD_DPRT &= ~(1<<LCD_EN);						/* EN = 0 FOR H TO L PULSE*/
	_delay_us(2000);								/* WAIT FOR MAKE ENABLE WIDE*/
}

void inicializar_LCD() {
	LCD_DDDR = 0xFF;
	_delay_ms(20);									/* WAIT FOR SOME TIME */
	LCD_Command(0x02);								/* SEND $32 FOR INIT OT 0X02 */
	LCD_Command(0x28);								/* INIT. LCD 2 LINE, 5 X 7 MATRIX */
	LCD_Command(0x0C);								/* DISPLAY ON CURSOR ON */
	LCD_Command(0x01);								/* LCD CLEAR */
	LCD_Command(0x82);								/* SHIFT CURSOR TO WRITE */
}

void lcd_imprimir_string_xy(unsigned char row, unsigned char pos, char *str) {
	if (row == 1)
		LCD_Command((pos & 0x0F)|0x80);				/* Command of first row and required position<16 */
	else if (row == 2)
		LCD_Command((pos & 0x0F)|0xC0);				/* Command of Second row and required position<16 */
	
	LCD_String(str);								/* Call LCD string function */
}

void LCD_String(char *str) {
	int i;
	for(i=0;str[i]!=0;i++)							/* Send each char of string till the NULL */
	{
		LCD_Char (str[i]);							/* Call LCD data write */
	}
}

void lcd_limpiar() {
	LCD_Command(0x01);
	_delay_ms(3);
	LCD_Command(0x80);
}

void lcd_imprimir_mensaje(char *mensaje)
{
	
}