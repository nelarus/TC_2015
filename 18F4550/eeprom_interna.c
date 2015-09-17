#include <xc.h>
#include "main.h"
#include "eeprom_interna.h"


void carregar_senha( char conta, char senha_a_carregar[][18]){
					
					char i = 0;

							do{
								senha_a_carregar[conta][i] = eeprom_read((conta*TAMANHO_SENHA) + i);
								i++;} while( senha_a_carregar[conta][i-1] && i<(TAMANHO_SENHA-1));


					senha_a_carregar[conta][TAMANHO_SENHA] = 0;
					senha_a_carregar[conta][TAMANHO_SENHA+1] = eeprom_read((TAMANHO_SENHA*(conta+1))-1);
					}

void verificar_num_contas(int *contas_cadastradas, unsigned char *qtd_contas){
		char i;
		for(i=0;i<QTD_MAX_CONTAS;i++){
			if(eeprom_read(i*TAMANHO_SENHA) != VALOR_INICIAL) {
					*qtd_contas++;
					setar_bit(*contas_cadastradas,i);}
				}
}


void eeprom_config_inicial(void){
		unsigned char i;

		for(i=0;i<10;i++){
			eeprom_write(i,('0'+i));//Senha padr�o da conta 0(admin): 0123456789
			eeprom_write(TAMANHO_SENHA+i,('a'+i));
			
			}
		eeprom_write(i,0);
		eeprom_write(TAMANHO_SENHA+i,0);//null da string de cada senha

		eeprom_write(TAMANHO_SENHA-1,255);
		eeprom_write(((TAMANHO_SENHA*2)-1),0b11111100);
		}