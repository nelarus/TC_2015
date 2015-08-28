#include <xc.h>
#include <stdio.h>
#include "lcd.h"
#include "main.h"


char linha_lcd;
char linha_lcd_aux_posicao;
char coluna_lcd;
char qtd_max_colunas_lcd;
char lcd_type;
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

//#define A_COM_TIL 0
//#define A_COM_ACENTO_AGUDO 1
//#define A_COM_ACENTO_CIRCUNFLEXO 2
//#define O_COM_ACENTO_AGUDO 3
//#define O_COM_ACENTO_CIRCUNFLEXO 4
//#define E_COM_ACENTO_CIRCUNFLEXO 5
//#define E_COM_ACENTO_AGUDO 6
//#define SIMBOLO_FECHADURA_TRANCADA 7
//#define SIMBOLO_FECHADURA_ABERTA 8


void escrever_simbolo_CGRAM(char simbolo){
		char maiuscula=0;
		//simbolos 7 e 8 são os das fechaduras
		//0 a 6 são caracteres com acento minusculos
		//9 a 15 são caracteres com acento maisculos
		if(simbolo>SIMBOLO_FECHADURA_FECHADA){
			maiuscula=1;
			simbolo-=9;} 
		
		if(simbolo== SIMBOLO_FECHADURA_FECHADA || simbolo == SIMBOLO_FECHADURA_ABERTA){
			CGRAM_goto(7);}
		else CGRAM_goto(simbolo);

		LCD_RS=1;

		switch(simbolo){
			case A_COM_TIL:
				lcd_write(0x0D);//0
				lcd_write(0X12);//1
				lcd_write(0X00);//2
				lcd_write(0X0E);
				lcd_write(0X01);
				lcd_write(0x0F);
				lcd_write(0X1F);
				lcd_write(0X0F);	
			
				break;

			case A_COM_ACENTO_CIRCUNFLEXO:
				lcd_write(0x04);
				lcd_write(0x0A);
				lcd_write(0x00);
				lcd_write(0X0E);
				lcd_write(0X01);
				lcd_write(0x0F);
				lcd_write(0X1F);
				lcd_write(0X0F);	
				break;


			case SIMBOLO_FECHADURA_FECHADA:		
				lcd_write(0x0E);//Linha 0 
				lcd_write(0x0A);//1 
				lcd_write(0x0A);//2
				lcd_write(0x0A);//3
				lcd_write(0x1F);//4
				lcd_write(0x1B);//5
				lcd_write(0x1B);//6
				lcd_write(0x1F);//7
				break;

			case SIMBOLO_FECHADURA_ABERTA:		
				lcd_write(0x03);//0
				lcd_write(0x02);//1
				lcd_write(0x02);//2
				lcd_write(0x02);//3
				lcd_write(0x1F);//4
				lcd_write(0x1B);//5
				lcd_write(0x1B);//6
				lcd_write(0x1F);//7
				break;


		}
}

void exibir_simbolo_lcd(char simbolo){
	char maiuscula =0;

	if(simbolo>SIMBOLO_FECHADURA_FECHADA){
			maiuscula=1;
			simbolo-=9;} 
		
		if(simbolo == SIMBOLO_FECHADURA_FECHADA || simbolo == SIMBOLO_FECHADURA_ABERTA){
			CGRAM_goto(7);}
		else CGRAM_goto(simbolo);

	LCD_RS=1;
	if(simbolo>7) escrever_simbolo_CGRAM(simbolo);
	lcd_write(simbolo);
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

	escrever_simbolo_fechadura();}


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

/* write a string of chars to the LCD */

void
lcd_puts(const char * s)
{
	LCD_RS = 1;	// write characters
	while(*s)
		lcd_write(*s++);
}

/* write one character to the LCD */

void
lcd_putc(char c)
{
	 switch (c) {
     case '\f'   :
     			//LCD_RS = 0;	// write characters
					lcd_clear();	// Clear screen
          break;
     case '\n'   :
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
     			break;
     case '\r'   :
     			LCD_RS = 0;	// write characters
					lcd_write(0x80);
					break;
     default     :
				linha_lcd=1;
				coluna_lcd++;
     			LCD_RS = 1;	// write characters
				switch(c){
					case 'ã':
					break;
					
					default:
					lcd_write( c );
					break;
				}
					break;
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
	linha_lcd_aux_posicao= linha;
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
