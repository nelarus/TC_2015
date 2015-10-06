extern void config_serial(char baud);
extern void enviar_string_serial(const char *string_a_enviar);
extern void enviar_caractere_serial(char carater_a_enviar);

extern void teste_comando_at(void);
extern void enviar_comando_at(unsigned char comando,char *parametro);
void sair_modo_at(char versao_bluetooth);
void definir_versao_bluetooth(char versao_bluetooth);



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

#define BT_VERSAO_2 0
#define BT_VERSAO_4 1


