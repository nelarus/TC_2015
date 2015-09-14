

//PARAMETRO PARA FREQ DE OSCILAÇÃO
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
//

//RENOMEAÇÃO DOS PINOS DAS PORTAS E DOS LATCHES
#define FECHADURA LATCbits.LC4    //Destravamento ou não da fechadura
#define SENSOR_ABERTURA_FECHADURA PORTEbits.RE2 //Sensor magnético(reed switch)

#define FECHADURA_TRAVADA SENSOR_ABERTURA_FECHADURA==0
#define DESTRAVAR_FECHADURA() FECHADURA=1
#define TRAVAR_FECHADURA() FECHADURA=0
//

// OPERAÇÕES DE BIT
#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) 
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define inverter_bit(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
//




