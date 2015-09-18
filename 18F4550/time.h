//DIAS DA SEMANA: CORRESPONDÊNCIA DECIMAL
#define Domingo 0
#define Segunda 1
#define Terca 2
#define Quarta 3
#define Quinta 4
#define Sexta 5
#define Sabado 6

//MESES: CORRESPONDÊNCIA DECIMAL
#define Janeiro 1
#define Fevereiro 2
#define Marco 3
#define Abril 4  
#define Maio 5
#define Junho 6
#define Julho 7
#define Agosto 8
#define Setembro 9
#define Outubro 10
#define Novembro 11
#define Dezembro 12
//


typedef struct{
	unsigned char ano;//0
	unsigned char mes;//1
	unsigned char dia;//2
	unsigned char hora;//3
	unsigned char minuto;//4
	unsigned char segundo;//5
	unsigned char dia_da_semana;//6
		}Data;

void delay_ms(unsigned int delay_total);

char dia_da_semana(unsigned int ano,char mes, char dia);

void configurar_data_inicial(Data data_inicial);

void resetar_timer1(char valor_h, char valor_l);

void parar_timer0_16bits(char valor_h,char valor_l);


