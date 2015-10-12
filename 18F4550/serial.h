

extern unsigned char baud_de_operacao;//Para um m�dulo bluetooth existem dois bauds, um para o modo de comandos AT e um para operacao normal, isto �, comunica��o com outros dispositivos;
								//Nos m�dulos 4.0 esses dois bauds s�o iguais, o que significa que se o m�dulo estiver operando em 115200 o modo at ter� o mesmo baud.
								//J� os m�dulos HC-05 o baud em comando at � fixo em 38400.

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