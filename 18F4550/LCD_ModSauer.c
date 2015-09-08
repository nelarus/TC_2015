#include <xc.h>
#include <stdio.h>
#include "lcd.h"

#ifndef _XTAL_FREQ
 // Unless specified elsewhere, 4MHz system frequency is assumed
 #define _XTAL_FREQ 16000000
#endif

<<<<<<< HEAD

<<<<<<< HEAD

void posicao_atual_lcd(char *linha, char *coluna){
		*linha = linha_lcd_aux_posicao; //retorna linha atual do lcd
		*coluna = coluna_lcd; //retorna coluna atual do lcd
	}
=======
#define	LCD_RS LATEbits.LE0
//#define	LCD_RW RA2
#define LCD_EN LATEbits.LE1
>>>>>>> parent of 639478b... Versão 1.0.5

#define LCD_DATA	LATA

<<<<<<< HEAD
	while(coluna_atual<qtd_max_colunas_lcd){
		LCD_RS=1;
		lcd_write(0x10);
		coluna_atual++;}
}



void
lcd_init(char definir_tipo_lcd)
{
	char init_value;
	linha_lcd=1;
	init_value = 0x3;
	lcd_type = definir_tipo_lcd;

	switch(lcd_type){
					case LCD_20X2:
						qtd_max_colunas_lcd=20;
						break;

					case LCD_16X2:
						qtd_max_colunas_lcd=16;
						break;

					case LCD_20X4:
						qtd_max_colunas_lcd=20;
						Linha_3 = 0x94;
						Linha_4 = 0xD4;
						break;

					case LCD_16X4:
						qtd_max_colunas_lcd=16;
						Linha_3 = 0x90;
						Linha_4 = 0xD0;
						break;
	}
	LCD_RS = 0;
	LCD_EN = 0;
	//LCD_RW = 0;

	__delay_ms(15);	// wait 15mSec after power applied,
	LCD_DATA	 = init_value;
	LCD_STROBE();
	__delay_ms(5);
	LCD_STROBE();
	__delay_us(200);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA = 2;	// Four bit mode
	LCD_STROBE();

	lcd_write(0x28); // Set interface length
	lcd_write(0x0C); // Display On, Cursor On, Cursor OFF
	lcd_clear();	// Clear screen
	lcd_write(0x6); // Set entry Mode

	escrever_simbolo_fechadura();
}


void escrever_simbolo_fechadura(void){ //Escreve na CGRAM o simbolo de uma fechadura fechada e uma destravada
	LCD_RS=0;
	lcd_write(0x40);//Endere�o 0 da CGRAM
	LCD_RS=1;
	//1�caractere
	lcd_write(0x0E);//Linha 0 
	lcd_write(0x0A);//1 
	lcd_write(0x0A);//2
	lcd_write(0x0A);//3
	lcd_write(0x1F);//4
	lcd_write(0x1B);//5
	lcd_write(0x1B);//6
	lcd_write(0x1F);//7

	//2� caractere
	lcd_write(0x03);//0
	lcd_write(0x02);//1
	lcd_write(0x02);//2
	lcd_write(0x02);//3
	lcd_write(0x1F);//4
	lcd_write(0x1B);//5
	lcd_write(0x1B);//6
	lcd_write(0x1F);//7
	
	LCD_RS=0;
	}
/*Substitui o ultimo caractere impresso por um asterisco
*/
void substituir_por_asterisco(void){
	LCD_RS=0;
	lcd_write(0x10);
	LCD_RS=1;
	lcd_write('*');
	}
=======
#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))
>>>>>>> parent of 639478b... Versão 1.0.5
=======

#define	LCD_RS LATEbits.LE0
//#define	LCD_RW RA2
#define LCD_EN LATEbits.LE1

#define LCD_DATA	LATA

#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))
>>>>>>> parent of 639478b... Versão 1.0.5

/* write a byte to the LCD in 4 bit mode */

void
lcd_write(unsigned char c)
{
	__delay_us(40);
	LCD_DATA &= 0xF0;
	LCD_DATA |= ( ( c >> 4 ) & 0x0F );
	LCD_STROBE();
	LCD_DATA &=0xF0;
	LCD_DATA |= ( c & 0x0F );
	LCD_STROBE();
}

/*
 * 	Clear and home the LCD
 */

void
lcd_clear(void)
{
	LCD_RS = 0;
	lcd_write(0x1);
	__delay_ms(2);
}


/* write one character to the LCD */

void
lcd_putc(char c)
{
	 switch (c) {
     case '\f'   :
					coluna_lcd=0;
     			//LCD_RS = 0;	// write characters
					lcd_clear();	// Clear screen
          break;
     case '\n'   :
<<<<<<< HEAD
<<<<<<< HEAD
					coluna_lcd=0;

				switch(lcd_type){
					case LCD_20X4:
					case LCD_16X4:
						if(++linha_lcd>4) linha_lcd=1;
					break;

					case LCD_20X2:
					case LCD_16X2:
						if(++linha_lcd>2) linha_lcd=1;
					break;
				}

     			lcd_gotoxy(linha_lcd,1);
=======
     			lcd_goto(0x40);
>>>>>>> parent of 639478b... Versão 1.0.5
=======
     			lcd_goto(0x40);
>>>>>>> parent of 639478b... Versão 1.0.5
     			break;
     case '\r'   :
				linha_lcd=1;
     			LCD_RS = 0;	// write characters
				lcd_write(0x80);
					break;
     default     :
<<<<<<< HEAD
<<<<<<< HEAD
     			LCD_RS = 1;	// write characters	
				coluna_lcd++;
				linha_lcd=1;
				lcd_write( c );
					
				
				break;
		}
}

/* write a string of chars to the LCD */

void
lcd_puts(const char * s)
{
	char temp;
	LCD_RS = 1;	// write characters
	while(*s){
		temp = *s++;
		//lcd_write(*s++);
		lcd_putc(temp);
}
}



//escolher posi��o CGRAM
void CGRAM_goto(char pos){
	LCD_RS=0;
	lcd_write(0x40 + (pos*8));}
=======
     			LCD_RS = 1;	// write characters
					lcd_write( c );
					break;
		}
}

>>>>>>> parent of 639478b... Versão 1.0.5
=======
     			LCD_RS = 1;	// write characters
					lcd_write( c );
					break;
		}
}

>>>>>>> parent of 639478b... Versão 1.0.5

/*
 * Go to the specified position
 */

void
lcd_goto(unsigned char pos)
{
	LCD_RS = 0;
<<<<<<< HEAD
<<<<<<< HEAD
	coluna_lcd = coluna;
	linha_lcd_aux_posicao = linha;
	switch(linha){
		case 1:
			lcd_write(Linha_1+(coluna-1));
			break;
=======
	lcd_write(0x80+pos);
}
>>>>>>> parent of 639478b... Versão 1.0.5
=======
	lcd_write(0x80+pos);
}
>>>>>>> parent of 639478b... Versão 1.0.5

/* initialise the LCD - put into 4 bit mode */
void
lcd_init()
{
	char init_value;


<<<<<<< HEAD
<<<<<<< HEAD
		case 4:
			lcd_write(Linha_4+(coluna-1));
			break;
	}
}
=======
	init_value = 0x3;

	LCD_RS = 0;
	LCD_EN = 0;
	//LCD_RW = 0;

	__delay_ms(15);	// wait 15mSec after power applied,
	LCD_DATA	 = init_value;
	LCD_STROBE();
	__delay_ms(5);
	LCD_STROBE();
	__delay_us(200);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA = 2;	// Four bit mode
	LCD_STROBE();
>>>>>>> parent of 639478b... Versão 1.0.5

=======
	init_value = 0x3;

	LCD_RS = 0;
	LCD_EN = 0;
	//LCD_RW = 0;

	__delay_ms(15);	// wait 15mSec after power applied,
	LCD_DATA	 = init_value;
	LCD_STROBE();
	__delay_ms(5);
	LCD_STROBE();
	__delay_us(200);
	LCD_STROBE();
	__delay_us(200);
	LCD_DATA = 2;	// Four bit mode
	LCD_STROBE();

>>>>>>> parent of 639478b... Versão 1.0.5
	lcd_write(0x28); // Set interface length
	lcd_write(0x0C); // Display On, Cursor On, Cursor OFF
	lcd_clear();	// Clear screen
	lcd_write(0x6); // Set entry Mode
}

void putch(char c)
{
	lcd_putc(c);
}
