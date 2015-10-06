

//PARAMETRO PARA FREQ DE OSCILA��O
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif
//
//PARAMETRO PARA CONTAS
#define QTD_MAX_CONTAS 16
//



//PARAMETROS DO BANCO DE DADOS DE SENHAS
#define TAMANHO_SENHA 16
#define TAMANHO_MINIMO_SENHA 5
#define conta_admin 0
#define nivel_acesso senha[conta][TAMANHO_SENHA+1]
#define nivel_acesso_conta_a_ser_alterada  senha[conta_a_ser_alterada][TAMANHO_SENHA+1]
#define NIVEL_ACESSO_MAXIMO 0xFF
//

//

// OPERA��ES DE BIT
#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) 
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define inverter_bit(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
//

//DEFINI��ES PARA SETAR E RESETAR VALORES
#define LIGAR 1
#define ATIVAR 1
#define ATIVADO 1
#define LIGADO 1
#define DESLIGAR 0
#define DESATIVAR 0
#define DESATIVADO 0
#define DESLIGADO 0



