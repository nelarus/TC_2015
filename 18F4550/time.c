#include <xc.h>
#include "main.h"


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
	ano-= (ano/100); //pega os 2 ultimos digitos do ano

	if(! ((ano+3)%4) ){
			if (mes==1) tabela_mes[mes-1]=6;
			else if(mes==2) tabela_mes[mes-1]=2;}

	return (( (6 - seculo*2) + dia + tabela_mes[mes-1] + ano + (ano/4))%7);
	

}

void resetar_timer1(char valor_h, char valor_l){
	 TMR1ON=0;
	 TMR1H=valor_h;
	 TMR1L=valor_l;
}