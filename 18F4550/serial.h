

extern unsigned char baud_de_operacao;//Para um módulo bluetooth existem dois bauds, um para o modo de comandos AT e um para operacao normal, isto é, comunicação com outros dispositivos;
								//Nos módulos 4.0 esses dois bauds são iguais, o que significa que se o módulo estiver operando em 115200 o modo at terá o mesmo baud.
								//Já os módulos HC-05 o baud em comando at é fixo em 38400.

extern void config_serial(char baud);
extern void enviar_string_serial(const char *string_a_enviar);
extern void enviar_caractere_serial(char carater_a_enviar);
void enviar_mensagem_inicializacao(void);
extern void enviar_comando_at(unsigned char comando,const char *parametro,char versao_modulo);
void sair_modo_at(char versao_modulo);
void entrar_modo_at(char versao_modulo);
void reconfig_baud(char baud); 



#define NOME 'a'
#define BAUD 'b'
#define	ROLE 'c'
#define ENDERECO_MODULO 'd'
#define PROCURAR_MODULOS 'e'
#define RESETAR 'f'
#define START 'g'
#define ENDERECO_ULTIMO_MODULO 'h'
#define MODULO_SLEEP 'i'
#define CONECTAR_AUTOMATICAMENTE 'j'
#define CONECTAR_MODULO 'k'

#define BAUD_115200 4
#define BAUD_57600 3
#define BAUD_38400 2
#define BAUD_19200 1
#define BAUD_9600 0

#define MODULO_BT LATDbits.LD1
#define PINO_KEY LATDbits.LD0

#define HC05 0
#define BT_VERSAO_4 1