#include <xc.h>
#include "ascii.h"
#include "main.h"

char teclado_matricial(unsigned char coluna, char linha){

	char temp = ((linha-1)*4) + coluna;
	char caractere;

		switch(temp){
					case 1:
						caractere = '*';
						break;	

					case 2:
						caractere = '0';
						break;	
			
					case 3:
						caractere = 'F';
						break;
					
					case 4:
						caractere = 'D';
						break;
					
					case 5:
						caractere = '7';
						break;
					
					case 6:
						caractere = '8';
						break;
					
					case 7:
						caractere = '9';
						break;
					
					case 8:
						caractere = 'C';
						break;
					
					case 9:
						caractere = '4';
						break;
					
					case 10:
						caractere = '5';
						break;
					
					case 11:
						caractere = '6';
						break;
					
					case 12:
						caractere = 'B';
						break;
					
					case 13:
						caractere = '1';
						break;
					
					case 14:
						caractere = '2';
						break;
					
					case 15:
						caractere = '3';
						break;
					
					case 16:
						caractere = 'A';
						break;}

			return caractere;
}


void numero_para_ascii(char numero){
	int temp1;
	int temp2;

	TXREG = '+';
	while(!TRMT){}

	temp1 = numero/100;
	TXREG = '0'+ temp1;
	while(!TRMT){}

	temp2 = ((numero - temp1*100)/10);
	TXREG = '0'+ temp2;
	while(!TRMT){}

	TXREG = '0'+ (numero - (temp2*10) - (temp1*100));
	while(!TRMT){}

	TXREG = '+';
	while(!TRMT){}
}

char ascii_para_numero(char caractere3, char caractere2, char caractere1){

		if(caractere3 == NULL) caractere3 = '0'; 
		if(caractere2 == NULL) caractere2 = '0';

		char numero;
		numero=((caractere3 - '0')*100);
		numero+=((caractere2 - '0')*10);
		numero+=(caractere1 - '0');
		return numero;}