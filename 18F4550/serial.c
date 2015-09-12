#include <xc.h>
#include "main.h"
#include "serial.h"


void config_serial(char baud){
		SYNC=0; //assincrono
		BRGH=1;
		BRG16=1;
		SPBRG=baud;
		TX9=0;
		RX9=0;//tx e rx em 8 bits
		TXEN=1; //habilita transmissão
		RCIE=0; // interrupção por recepção
		CREN=1;
		SPEN=1;
		TXCKP = 0;
		TXIE = 0;
		TX9 = 0;
}

void enviar_caractere_serial(char carater_a_enviar){
		TXREG = carater_a_enviar;
		while(!TRMT){}
}

void enviar_string_serial(const char *string_a_enviar){
			while(*string_a_enviar != NULL){
				TXREG = *string_a_enviar;
				while(!TRMT){}
				string_a_enviar++;}


}

void teste_comando_at(void){
	enviar_string_serial("AT");}



void enviar_comando_at(unsigned char comando,char *parametro){
	enviar_string_serial("AT+");

		if(comando<=NOME) { //comandos para perguntar nome(==0) e para alterar nome(==1)
			enviar_string_serial("NAME");
			if(PERGUNTAR(NOME))enviar_string_serial(parametro);
			else enviar_caractere_serial('?');
			}

		else if(comando<=BAUD){
			enviar_string_serial("BAUD");
			if( PERGUNTAR(BAUD) ) enviar_string_serial(parametro);
			else enviar_caractere_serial('?');
			}

		else if(comando<=ROLE){
			enviar_string_serial("ROLE");
			if( PERGUNTAR(ROLE) ) enviar_string_serial(parametro);
			else enviar_caractere_serial('?');
			}

		else if( PERGUNTAR(ENDERECO_MODULO) ){
			enviar_string_serial("ADDR?");
			}

		else if( comando==PROCURAR_MODULOS ){
			enviar_string_serial("DISC?");}

		else if(comando==RESETAR){
				enviar_string_serial("RESET");}
	
		else if(comando==START){
				enviar_string_serial("START");}
	
		else if( PERGUNTAR(ENDERECO_ULTIMO_MODULO) ){
				enviar_string_serial("RADD?");}

		else if( comando==MODULO_SLEEP ){
				enviar_string_serial("SLEEP");}

		else if(comando == CONECTAR_MODULO){
				enviar_string_serial("CON");
				enviar_string_serial(parametro);}



}