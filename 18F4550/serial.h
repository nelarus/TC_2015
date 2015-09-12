extern void config_serial(char baud);
extern void enviar_string_serial(const char *string_a_enviar);
extern void enviar_caractere_serial(char carater_a_enviar);

extern void teste_comando_at(void);
extern void enviar_comando_at(unsigned char comando,char *novo_parametro);


#define NOME 1
#define BAUD 3
#define	ROLE 5
#define ENDERECO_MODULO 6
#define PROCURAR_MODULOS 7
#define RESETAR 8
#define START 9
#define ENDERECO_ULTIMO_MODULO 10
#define MODULO_SLEEP 11
#define CONECTAR_AUTOMATICAMENTE 12
#define CONECTAR_MODULO 13
#define PERGUNTAR(X) comando==X


