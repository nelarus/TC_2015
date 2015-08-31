/*
 *	LCD interface header file
 *	See lcd.c for more info
 */

//Funções para uso da CGRAM

//Escrita de letras com acento na cgram

//Acentos
extern void escrever_crase_cgram(void);
extern void escrever_til_cgram(void);
extern void escrever_acento_agudo_cgram(void);
extern void escrever_acento_circunflexo_cgram(void);
//

//Letras
extern void escrever_a_maiusculo_cgram(void);
extern void escrever_a_minusculo_cgram(void);

extern void escrever_o_cgram(char maiuscula);

extern void escrever_e_minusculo_cgram(void);
extern void escrever_e_maiusculo_cgram(void);

extern void escrever_i_minusculo_cgram(void);
extern void escrever_i_maiusculo_cgram(void);
//

extern void CGRAM_goto(char pos);//ir para posição(0 a 7) da CGRAM

extern void posicao_atual_lcd(char *linha, char *coluna); //retorna posição atual do cursor do lcd

extern void escrever_simbolo_fechadura(void);

extern char escrever_simbolo_CGRAM(char simbolo); //Escreve na CGRAM do lcd o simbolo correspondnete, vide lista abaixo

extern void exibir_simbolo_lcd(char simbolo); //Exibe no lcd um dos simbolos da CGRAM



//Restante das funções


//limpa linha selecionada
extern void limpar_linha(unsigned char linha); 


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

//Substitui ultimo caractere impresso por um asterisco
void substituir_por_asterisco(void); 


/*	Set the cursor position */

#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)

//VARIÁVEIS GLOBAIS PARA USO DO LCD
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


//Caracteres especiais: Correspondência decimal

#define SIMBOLO_FECHADURA_ABERTA 215
#define SIMBOLO_FECHADURA_FECHADA 216
//


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
