#include <xc.h>
#include "eeprom_interna.h"


void carregar_senha( char conta, char senha_a_carregar[][TAMANHO_SENHA+1]){


									
					char i = 0;

							do{
								senha_a_carregar[conta][i] = eeprom_read((conta*TAMANHO_SENHA) + i);
								i++;} while( senha_a_carregar[conta][i-1] && i<(TAMANHO_SENHA-1));


					senha_a_carregar[conta][TAMANHO_SENHA-1] = 0;
					senha_a_carregar[conta][TAMANHO_SENHA] = eeprom_read((TAMANHO_SENHA*(conta+1))-1);
					}

void verificar_num_contas(int *contas_cadastradas, unsigned char *qtd_contas){
		char i;
		for(i=0;i<QTD_MAX_CONTAS;i++){
			if(eeprom_read(i*TAMANHO_SENHA) != VALOR_INICIAL) {
					(*qtd_contas)++;
					setar_bit(*contas_cadastradas,i);}
				}
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
		eeprom_write(((TAMANHO_SENHA*2)-1),0b11111100);
		}

void armazenar_senha(char nova_senha[],char senha_a_armazenar[][TAMANHO_SENHA+3],char conta){//armazena a nova senha na RAM e na eeprom
	char i;

	for(i=0;i<TAMANHO_SENHA-1;i++){//apaga a senha anterior da eeprom
		eeprom_write( ((conta*16) + i),VALOR_INICIAL);}

	i=0;
	do{ //escreve a senha na eeprom
		senha_a_armazenar[conta][i] = nova_senha[i];
		eeprom_write( ((conta*16) + i) , nova_senha[i] );
		while(WR){}
		i++;} while(nova_senha[i-1]  && i<(TAMANHO_SENHA-1));

}

void armazenar_novo_nivel_de_acesso(char novo_nivel_de_acesso,char conta){

	eeprom_write((TAMANHO_SENHA * (conta+1))-1,novo_nivel_de_acesso);

}																																	