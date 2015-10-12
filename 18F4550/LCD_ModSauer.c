#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#include "main.h"


char linha_lcd;
char linha_lcd_aux_posicao;
char coluna_lcd;
char qtd_max_colunas_lcd;
char lcd_type;
char qtd_max_linhas_lcd;
unsigned char Linha_3;
unsigned char Linha_4;


void posicao_atual_lcd(char *linha, char *coluna){
		*linha = linha_lcd_aux_posicao; //retorna linha atual do lcd
		*coluna = coluna_lcd; //retorna coluna atual do lcd
	}

//Substitui todos os caracteres de uma linha por nada, limpando a linha
void limpar_linha(unsigned char linha){
	unsigned char coluna_atual=1;
	lcd_gotoxy(linha,coluna_atual);

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
						qtd_max_linhas_lcd=2;
						break;

					case LCD_16X2:
						qtd_max_colunas_lcd=16;
						qtd_max_linhas_lcd=2;
						break;

					case LCD_20X4:
						qtd_max_colunas_lcd=20;
						qtd_max_linhas_lcd=4;
						Linha_3 = 0x94;
						Linha_4 = 0xD4;
						break;

					case LCD_16X4:
						qtd_max_colunas_lcd=16;
						qtd_max_linhas_lcd=4;
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
	lcd_write(0x40);//Endereço 0 da CGRAM
	LCD_RS=1;
	//1°caractere
	lcd_write(0x0E);//Linha 0 
	lcd_write(0x0A);//1 
	lcd_write(0x0A);//2
	lcd_write(0x0A);//3
	lcd_write(0x1F);//4
	lcd_write(0x1B);//5
	lcd_write(0x1B);//6
	lcd_write(0x1F);//7

	//2° caractere
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
					coluna_lcd=0;
						if(++linha_lcd>	qtd_max_linhas_lcd) linha_lcd=1;

     			lcd_gotoxy(linha_lcd,1);
     			break;
     case '\r'   :
				linha_lcd=1;
     			LCD_RS = 0;	// write characters
				lcd_write(0x80);
					break;
     default     :
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



//escolher posição CGRAM
void CGRAM_goto(char pos){
	LCD_RS=0;
	lcd_write(0x40 + (pos*8));}

/*
 * Go to the specified position
 */

void
lcd_gotoxy(unsigned char linha,unsigned char coluna)
{
	LCD_RS = 0;
	coluna_lcd = coluna;
	linha_lcd_aux_posicao = linha;
	switch(linha){
		case 1:
			lcd_write(Linha_1+(coluna-1));
			break;

		case 2:
			lcd_write(Linha_2+(coluna-1));
			break;

		case 3:
			lcd_write(Linha_3+(coluna-1));
			break;

		case 4:
			lcd_write(Linha_4+(coluna-1));
			break;
	}
}

/* initialise the LCD - put into 4 bit mode */

void putch(char c)
{
	lcd_putc(c);
}
