#include <xc.h>
#include "main.h"
#include "recebimento_dados.h"

char verificar_nivel_acesso(char funcao){

	return(nivel_acesso & 1<<(funcao-'0');}