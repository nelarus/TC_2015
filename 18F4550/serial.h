extern void config_serial(char baud,char brg16);
extern void enviar_string_serial(const char *string_a_enviar);
extern void enviar_caractere_serial(char carater_a_enviar);

extern void teste_comando_at(void);
extern void enviar_comando_at(unsigned char comando,char *novo_parametro);


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

#define BAUD_115200 6
#define BAUD_57600 5
#define BAUD_9600 0


