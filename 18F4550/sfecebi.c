#include <xc.h>
#include <delays.h>
#include "sfecebi.h"

#define TAMANHO_BUFFER_SERIAL 80
#define QTD_MAX_CONTAS 16		
#define TAMANHO_SENHA 16



void config_serial(void){
		SYNC=0; //assincrono
		BRGH=1;
		BRG16=1;
		SPBRG= 35;
		TX9=0;
		RX9=0;//tx e rx em 8 bits
		TXEN=1; //habilita transmissão
		RCIE=1; // interrupção por recepção
		CREN=1;
		SPEN=1;
		TXCKP = 0;
		TXIE = 0;
		TX9 = 0;
				}

void eeprom_config_inicial(void){
		char i;
		for(i=0;i<10;i++){
			eeprom_write(i,('0'+i));//Senha padrão da conta 0(admin): 0123456789
			eeprom_write(TAMANHO_SENHA+i,('a'+i));
			
			}
		eeprom_write(i,0);
		eeprom_write(TAMANHO_SENHA+i,0);//null da string de cada senha

		eeprom_write((TAMANHO_SENHA*2),0b11111101);
		}


void verificar_num_contas(void){
		char i;
		for(i=0;i<QTD_MAX_CONTAS;i++){
			if(eeprom_read(i*TAMANHO_SENHA) != 0xFF) qtd_total_contas++;
				}
								}


void carregar_senha(void){
					TXREG = '\n';
					while(!TRMT);
					char i = 0;

							do{
								senha[conta][i] = eeprom_read((conta*TAMANHO_SENHA) + i);
								TXREG= senha[conta][i];
								while(!TRMT);
								i++;} while( senha[conta][i-1] && i<(TAMANHO_SENHA-1));

					nivel_acesso = eeprom_read((conta*TAMANHO_SENHA)+ (TAMANHO_SENHA-1));
					RCIE=1;}
					
char teclado_matricial(char coluna, char linha){

	char temp = ((linha-1)*4) + coluna;
	char caractere;

		switch(temp){
					case 1:
						caractere = 'M';
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

void delay_ms(unsigned int delay_total){
    unsigned int temp = 0;
    while(temp < delay_total){
        __delay_ms(1);
        temp++;}
}

void numero_para_ascii(char numero){
	char temp1;
	char temp2;

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
		char numero;
		numero=((caractere3 - '0')*100);
		numero+=((caractere2 - '0')*10);
		numero+=(caractere1 - '0');
		return numero;}