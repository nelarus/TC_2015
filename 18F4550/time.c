#include <xc.h>
#include "main.h"

char dia_da_semana(char dia, char mes, unsigned char ano){
	ano +=15; //ano inicial = 2015, 2 ultimos digitos = 15;
	char tabela_mes[] = {0,3,3,6,1,4,6,2,5,0,3,5};
	if(ano%4==0){
		tabela_mes[0] = 6;
		tabela_mes[1] = 2;}

	return ( dia + mes + tabela_mes[mes-1] + ano + ano/4 + (6 - ((ano/100)*2)) );
}