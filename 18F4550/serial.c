#include <xc.h>
#include "main.h"
#include "serial.h"
#include "recebimento_dados.h"
#include "flags.h"
#include "time.h"


void config_serial(char baud){
//= 34; //34=114800. 69 = 57971  103  38462 , com brg16=0 9600 
		SYNC=0; //assincrono
		BRGH=1;
		switch(baud){
				case BAUD_115200:
				BRG16=1;
				SPBRG =33;
				break;

				case BAUD_57600:
				BRG16=1;
				SPBRG =69;
				break;

				case BAUD_38400:
				BRG16=1;
				SPBRG =103;
				break;

				case BAUD_19200:
				BRG16=1;
				SPBRG =207;
				break;

				case BAUD_9600:
				BRG16=0;
				SPBRG =103;
				break;
		}
		TX9=0;
		RX9=0;//tx e rx em 8 bits
		TXEN=1; //habilita transmissão
		RCIE=1; // interrupção por recepção
		CREN=1;
		SPEN=1;
		TXCKP = 0;
		TXIE = 0;
		TX9 = 0;

		enviar_caractere_serial(INICIO);
		enviar_caractere_serial(INICIALIZAR);
		enviar_caractere_serial(FIM);
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

		if(comando==NOME) { //comandos para perguntar nome(==0) e para alterar nome(==1)
			enviar_string_serial("NAME");
			enviar_string_serial(parametro);
			}

		else if(comando==BAUD){
			enviar_string_serial("BAUD");
			enviar_string_serial(parametro);
			}

		else if(comando==ROLE){
			enviar_string_serial("ROLE");
			enviar_string_serial(parametro);
			 enviar_caractere_serial('?');
			}

		else if(comando == ENDERECO_MODULO){
			enviar_string_serial("ADDR?");
			}

		else if( comando==PROCURAR_MODULOS ){
			enviar_string_serial("DISC?");}

		else if(comando==RESETAR){
				enviar_string_serial("RESET");}
	
		else if(comando==START){
				enviar_string_serial("START");}
	
		else if( comando == ENDERECO_ULTIMO_MODULO ){
				enviar_string_serial("RADD?");}

		else if( comando==MODULO_SLEEP ){
				enviar_string_serial("SLEEP");}

		else if(comando == CONECTAR_MODULO){
				enviar_string_serial("CON");
				enviar_string_serial(parametro);}



}


void entrar_modo_at(char versao_bluetooth){
	if(versao_bluetooth == BT_VERSAO_2){	
		delay_ms(10);
		MODULO_BT=DESLIGAR;	
		delay_ms(10);
		PINO_KEY=LIGAR;
		MODULO_BT=LIGAR;
	}

	else{
		teste_comando_at();
		teste_comando_at();}
}

void sair_modo_at(char versao_bluetooth){

	if(versao_bluetooth == BT_VERSAO_2){
		delay_ms(10);
		MODULO_BT=DESLIGAR;
		PINO_KEY=DESLIGAR;
		delay_ms(10);
		MODULO_BT=LIGAR;}
}	
