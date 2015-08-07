#include <xc.h>
#include <delays.h>
#include "eeprom.h"


#define QTD_MAX_CONTAS 16
#define TAMANHO_SENHA 16

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

char verificar_num_contas(void){
		char i;
		unsigned char qtd_contas=0;
		for(i=0;i<QTD_MAX_CONTAS;i++){
			if(eeprom_read(i*TAMANHO_SENHA) != 0xFF) {qtd_contas++;}
				}
		return (qtd_contas);
}
