#include "main.h"
#include "banco_de_dados.h"
#include "contas.h"

unsigned char myReadI2C( void );
void enviar_endereco(char endereco_h, char endereco_l);

void escrever_byte_eeprom_externa(char endereco_h, char endereco_l, char valor);
char ler_byte_eeprom_externa(char endereco_h,char endereco_l);

void escrever_string_eeprom_externa(char endereco_h, char endereco_l, const char *string_a_escrever,char quantidade);

int ler_inteiro_eeprom_externa(int endereco_1);

void ler_string_eeprom_externa(char endereco_h, char endereco_l,char *string_a_receber, char quantidade);

void registrar_acesso(char funcao,char conta, char dia,char hora, char minuto,char mes_atual, char ano_atual);

void ler_tentativa_acesso(int inicio,int final);

void enviar_historico_acessos(char mes_inicio, char mes_final, char ano_inicial, char ano_final);

void armazenar_senha_eeprom_externa(char nova_senha[],char senha_a_armazenar[][TAMANHO_SENHA+3],char conta);

void carregar_senhas(char senha_a_carregar[][TAMANHO_SENHA+1]);

void carregar_horarios_acesso(char  horarios_a_carregar[][7][4]);

void Resetar_COM_I2C(void);

void zerar_eeprom_externa(void);


void config_inicial_bloco2(void);
void config_inicial_bloco3(void);

#define ENDERECO_INICIAL_BLOCO1 0
#define ENDERECO_INICIAL_BLOCO2 256
#define ENDERECO_INICIAL_BLOCO3 704
#define ENDERECO_INICIAL_BLOCO4 1376