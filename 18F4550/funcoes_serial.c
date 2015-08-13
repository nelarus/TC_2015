#include <xc.h>
#include "main.h"


void configurar_serial(char valor_baud){
      SYNC=0; //assincrono
      BRGH=1;
      BRG16=1;
      SPBRG= valor_baud;
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

void enviar_string_serial(char string_a_enviar[]){
	char cont=0;

	while(string_a_enviar[cont] != NULL){

		TXREG = string_a_enviar[cont];
		cont++;
		while(!TRMT){}}

	}

void enviar_caractere_serial(char caractere_a_enviar){
	TXREG = caractere_a_enviar;
	while(!TRMT){}
}