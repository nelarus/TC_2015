#include "main.h"
#include "flags.h"
#include "recebimento_dados.h"


//PARAMETRO PARA CONTAS
#define QTD_MAX_CONTAS 16
//

//PARAMETROS DO BANCO DE DADOS DE SENHAS
#define TAMANHO_SENHA 16
#define TAMANHO_MINIMO_SENHA 5
#define conta_admin 0
#define nivel_acesso senha[conta][TAMANHO_SENHA+1]
#define nivel_acesso_conta_a_ser_alterada  senha[conta_a_ser_alterada][TAMANHO_SENHA+1]
//#define NIVEL_ACESSO_MAXIMO 0xFF
//