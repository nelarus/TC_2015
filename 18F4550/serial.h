extern void config_serial(char baud);
extern void enviar_string_serial(const char string_a_enviar[]);
extern void enviar_caractere_serial(char carater_a_enviar);
void teste_comando_at(void);
void enviar_comando_at(unsigned char comando,char *novo_parametro);


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


//	if(comando<2) { //comandos para perguntar nome(==0) e para alterar nome(==1)
//			enviar_string_serial("NAME");
//			if(comando) enviar_string_serial(novo_parametro);
//			else enviar_caractere_serial('?');
//			}
//
//		else if(comando<4){
//			enviar_string_serial("BAUD");
//			if(comando==3) enviar_string_serial(novo_parametro);
//			else enviar_caractere_serial('?');
//			}
//
//		else if(comando<6){
//			enviar_string_serial("ROLE");
//			if(comando==5) enviar_string_serial(novo_parametro);
//			else enviar_caractere_serial('?');
//			}
//
//		else if(comando==6){
//			enviar_string_serial("ADDR?");
//			}
//
//		else if(comando==7){
//			enviar_string_serial("DISC?");}
//
//		else if(comando==8){
//				enviar_string_serial("RESET");}
//	
//		else if(comando==9){
//				enviar_string_serial("START");}
//	
//		else if(comando==10){
//				enviar_string_serial("RADD?");}
//
//		else if(comando==11){
//				enviar_string_serial("SLEEP");}



