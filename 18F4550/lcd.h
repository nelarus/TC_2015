/*
 *	LCD interface header file
 *	See lcd.c for more info
 */

void posicao_atual_lcd(char *linha, char *coluna);

void CGRAM_goto(char pos);//ir para posição(0 a 7) da CGRAM

extern void limpar_linha(unsigned char linha);

extern void escrever_simbolo_fechadura(void);

extern void escrever_simbolo_CGRAM(char simbolo);

extern void exibir_simbolo_lcd(char simbolo);

/* write a byte to the LCD in 4 bit mode */
extern void lcd_write(unsigned char);

/* Clear and home the LCD */

extern void lcd_clear(void);

/* write a string of characters to the LCD */

extern void lcd_puts(const char * s);

/* Go to the specified position */

extern void lcd_gotoxy(unsigned char linha,unsigned char coluna);
	
/* intialize the LCD - call before anything else */

extern void lcd_init(char tipo_lcd);

extern void lcd_putch(char);

void substituir_por_asterisco(void);

/*	Set the cursor position */

#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)

extern char linha_lcd;
extern char linha_lcd_aux_posicao;
extern char coluna_lcd;
extern char qtd_max_coluna_lcd;
extern char lcd_type;

extern unsigned char Linha_3;
extern unsigned char Linha_4;



//TIPOS DE LCD
#define LCD_16X2 0
#define LCD_16X4 1
#define LCD_20X2 2
#define LCD_20X4 3

//PINOS LCD
#define	LCD_RS LATEbits.LE0
//#define	LCD_RW RE2
#define LCD_EN LATEbits.LE1

#define LCD_DATA	LATA
//

//Defines para envio de dados ao lcd
#define	LCD_STROBE()	((LCD_EN = 1),(LCD_EN=0))

//Caracteres especiais

#define A_COM_TIL 0
#define A_COM_ACENTO_AGUDO 1
#define A_COM_ACENTO_CIRCUNFLEXO 2
#define O_COM_ACENTO_AGUDO 3         
#define O_COM_ACENTO_CIRCUNFLEXO 4
#define E_COM_ACENTO_CIRCUNFLEXO 5
#define E_COM_ACENTO_AGUDO 6
#define SIMBOLO_FECHADURA_ABERTA 7
#define SIMBOLO_FECHADURA_FECHADA 8


#define LETRA_MAISCULA 0
#define LETRA_MINUSCULA 1

//ENDERECO DAS LINHAS

#define Linha_1 0x80
#define Linha_2 0xC0
//Linhas 1 e 2 são fixas para todos os tipos de LCD. Ja as linhas 3 e 4 variam do 20x4 para o 16x4 e por isso são declaradas como unsigned char em vez de usadas num define

//ENDERECO CGRAM
#define CGRAM(X) (0x40+(X*8))

//VALOR DECIMAL DAS LINHAS PARA USO NO LCD_GOTOXY

#define LINHA1 1
#define LINHA2 2
#define LINHA3 3
#define LINHA4 4
