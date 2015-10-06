#include <xc.h>
#include "main.h"
#include "time.h"


void delay_ms(unsigned int delay_total){
    unsigned int temp = 0;
    while(temp < delay_total){
        __delay_ms(1);
        temp++;}
}

char dia_da_semana(unsigned int ano,char mes, char dia){

	char tabela_mes[]= {0,3,3,6,1,4,6,2,5,0,3,5};
	unsigned char seculo;

	ano+=15; //O ano 0 no calendário do PIC é 2015,cujos 2 ultimos digitos são 15
	seculo = ano/100;
	ano-= (seculo*100); //pega os 2 ultimos digitos do ano

	if(! ((ano+3)%4) ){
			if (mes==1) tabela_mes[mes-1]=6;
			else if(mes==2) tabela_mes[mes-1]=2;}

	return (( (6 - seculo*2) + dia + tabela_mes[mes-1] + ano + (ano/4))%7);
	

}

void configurar_data_inicial(void){
	
	data_atual.ano=0;
	data_atual.mes= Janeiro;
	data_atual.dia=1;
	data_atual.dia_da_semana= dia_da_semana(	data_atual.ano,	data_atual.mes,	data_atual.dia);
	data_atual.hora=5;
	data_atual.minuto=4;
	data_atual.segundo=3;
	TMR0ON=1;}


void resetar_timer1(char valor_h, char valor_l){
	 TMR1ON=0;
	 TMR1H=valor_h;
	 TMR1L=valor_l;
}

void parar_timer0_16bits(char valor_h,char valor_l){
	TMR0IE=0;
	TMR0H=valor_h;
	TMR0L=valor_l;}

void configurar_timer0(void){
	T0CON = 0b00000111;
	TMR0H=0xC2; //TMR0=34446(1 interrupção = 1s para FOSC=16MHz)
	TMR0L= 0xF7;}

void configurar_timer1(void){
	T1CON = 0b00001110;
	TMR1H=0XC0; //TMR1 = 49152 (1 interrupção = 0.5s para cristal de 32,768khz)
	TMR1L=0;
	TMR1IE=1;}
	