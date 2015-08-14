#include <xc.h>
#include <delays.h>
#include "ascii.h"
#include "main.h"


void carregar_senha(char conta, char senha_a_carregar[][17]){
					TXREG = '\n';
					while(!TRMT);
					char i = 0;

							do{
								senha_a_carregar[conta][i] = eeprom_read((conta*TAMANHO_SENHA) + i);
								TXREG= senha_a_carregar[conta][i];
								while(!TRMT);
								i++;} while( senha_a_carregar[conta][i-1] && i<(TAMANHO_SENHA-1));


					
					senha_a_carregar[conta][TAMANHO_SENHA-1] = eeprom_read((TAMANHO_SENHA*(conta+1))-1);
					unsigned char temp;
					temp = senha_a_carregar[conta][TAMANHO_SENHA-1]; 
					numero_para_ascii(temp);
					}

char verificar_num_contas(void){
		char i;
		unsigned char qtd_contas=0;
		for(i=0;i<QTD_MAX_CONTAS;i++){
			if(eeprom_read(i*TAMANHO_SENHA) != 0xFF) {qtd_contas++;}
				}
		return (qtd_contas);
}


void eeprom_config_inicial(void){
		unsigned char i;

		for(i=0;i<10;i++){
			eeprom_write(i,('0'+i));//Senha padrão da conta 0(admin): 0123456789
			eeprom_write(TAMANHO_SENHA+i,('a'+i));
			
			}
		eeprom_write(i,0);
		eeprom_write(TAMANHO_SENHA+i,0);//null da string de cada senha

		eeprom_write(TAMANHO_SENHA-1,255);
		eeprom_write(((TAMANHO_SENHA*2)-1),0b11111101);
		}