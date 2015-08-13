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

void enviar_string_serial(const char string_a_enviar[]){
			char i=0;
			while(string_a_enviar[i] != NULL){
				TXREG = string_a_enviar[i];
				while(!TRMT){}
				i++;}


}
