/*
 *	LCD interface header file
 *	See lcd.c for more info
 */

<<<<<<< HEAD
//FunÁıes para uso da CGRAM


extern void CGRAM_goto(char pos);//ir para posiÁ„o(0 a 7) da CGRAM

extern void posicao_atual_lcd(char *linha, char *coluna); //retorna posiÁ„o atual do cursor do lcd

extern void escrever_simbolo_fechadura(void);

extern char escrever_simbolo_CGRAM(char simbolo); //Escreve na CGRAM do lcd o simbolo correspondnete, vide lista abaixo

extern void exibir_simbolo_lcd(char simbolo); //Exibe no lcd um dos simbolos da CGRAM



//Restante das funÁıes


//limpa linha selecionada
extern void limpar_linha(unsigned char linha); 

=======
>>>>>>> parent of 639478b... Vers√£o 1.0.5

/* write a byte to the LCD in 4 bit mode */

extern void lcd_write(unsigned char);

/* Clear and home the LCD */

extern void lcd_clear(void);

/* write a string of characters to the LCD */

extern void lcd_puts(const char * s);

/* Go to the specified position */

extern void lcd_goto(unsigned char pos);
	
/* intialize the LCD - call before anything else */

extern void lcd_init(void);

extern void lcd_putch(char);

<<<<<<< HEAD
//Substitui ultimo caractere impresso por um asterisco
void substituir_por_asterisco(void); 


/*	Set the cursor position */

#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)

//VARI¡VEIS GLOBAIS PARA USO DO LCD
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


//Caracteres especiais: CorrespondÍncia decimal

#define SIMBOLO_FECHADURA_ABERTA (NULL+1)
#define SIMBOLO_FECHADURA_FECHADA NULL
//


//ENDERECO DAS LINHAS

#define Linha_1 0x80
#define Linha_2 0xC0
//Linhas 1 e 2 s„o fixas para todos os tipos de LCD. Ja as linhas 3 e 4 variam do 20x4 para o 16x4 e por isso s„o declaradas como unsigned char em vez de usadas num define

//ENDERECO CGRAM
#define CGRAM(X) (0x40+(X*8))

//VALOR DECIMAL DAS LINHAS PARA USO NO LCD_GOTOXY

#define LINHA1 1
#define LINHA2 2
#define LINHA3 3
#define LINHA4 4
=======
/*	Set the cursor position */

#define	lcd_cursor(x)	lcd_write(((x)&0x7F)|0x80)
>>>>>>> parent of 639478b... Vers√£o 1.0.5
