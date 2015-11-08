

//PARAMETRO PARA FREQ DE OSCILAÇÃO
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif
//




//

//

// OPERAÇÕES DE BIT
#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) 
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define inverter_bit(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
//

//DEFINIÇÕES PARA SETAR , RESETAR e ATRIBUIR VALORES
#define LIGAR 1
#define ATIVAR 1
#define ATIVADO 1
#define LIGADO 1
#define DESLIGAR 0
#define DESATIVAR 0
#define DESATIVADO 0
#define DESLIGADO 0
#define SUCESSO 1

#define DEFINIR_NOVO_VALOR '='




