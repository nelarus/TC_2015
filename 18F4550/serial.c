#include "main.h"
#include <xc.h>



//void config_serial(char baud){
//      SYNC=0; //assincrono
//      BRGH=1;
//      BRG16=1;
//      SPBRG = baud;
//      TX9=0;
//      RX9=0;//tx e rx em 8 bits
//      TXEN=1; //habilita transmiss�o
//      RCIE=0; // interrup��o por recep��o
//      CREN=1;
//      SPEN=1;
//      TXCKP = 0;
//      TXIE = 0;
//      TX9 = 0;
//
//}
//

void enviar_string_serial(char *string_a_enviar){

	while(*string_a_enviar != NULL){

		TXREG = *string_a_enviar;
		string_a_enviar++;
		while(!TRMT){}}

	}

void enviar_caractere_serial(char caractere_a_enviar){
	TXREG = caractere_a_enviar;
		while(!TRMT){}
}