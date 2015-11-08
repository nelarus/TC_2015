#include "main.h"
#include "contas.h"
#include "recebimento_dados.h"
#include "banco_de_dados.h"

void verificar_num_contas(int *contas_cadastradas, unsigned char *qtd_contas); //verifica e retorna a quantidade  de contas cadastradas, isto é, que possuem uma senha definida e quais são;

extern void eeprom_config_inicial(void); //Configuração inicial da eeprom, necessária por causa do apagamento da eeprom ao programar o 18F4550.
									//Conta 0 inicia com senha = 0123456789, Conta 1 inicia com senha = abcdefghij

void carregar_senha(char conta, char senha_a_carregar[][TAMANHO_SENHA+3]);//Carrega a senha da conta selecionada, pegando a senha na eeprom interna e armazenando na string de entrada

void armazenar_senha(char nova_senha[],char senha_a_armazenar[][TAMANHO_SENHA+3],char conta);

void armazenar_novo_nivel_de_acesso(char novo_nivel_de_acesso,char conta);