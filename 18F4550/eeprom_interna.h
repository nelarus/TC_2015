

//PARAMETROS EEPROM_INTERNA
#define ENDERECO_INICIAL 0
#define VALOR_INICIAL 0xFF


char verificar_num_contas(void); //verifica e retorna a quantidade de contas cadastradas, isto é, que possuem uma senha definida

void eeprom_config_inicial(void); //Configuração inicial da eeprom, necessária por causa do apagamento da eeprom ao programar o 18F4550.
									//Conta 0 inicia com senha = 0123456789, Conta 1 inicia com senha = abcdefghij


void carregar_senha(char conta, char senha_a_carregar[][17]);//Carrega a senha da conta selecionada, pegando a senha na eeprom interna e armazenando na string de entrada