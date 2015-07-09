#include <htc.h>
#include <stdio.h>


 __CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_ON & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF);


#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif


//TESTE

unsigned char ordem = 0;//usada para compararar uma sequ�ncia de dados recebidos com uma string.
unsigned char etapa=0;
unsigned char dado_recebido = 0;

char senha[16];
char nova_senha[16];
unsigned char nivel_acesso;

struct Data{
	char dia;
	char mes;
	char ano;
	char hora;
	char minuto;
	char segundo;
		}data_atual;

unsigned char tamanho_senha=10;
unsigned char funcao=0;//utilizada para determinar qual fun��o o PIC vai executar (abrir porta, fornecer hist�rico, fornecer status atual)
unsigned char conta=0;
unsigned char ultima_conta=0;
unsigned char FLAGS_1=0;

bit enviar=0; //Permite o envio de mensagens de erro a central/usu�rio


#define PROXIMA_ETAPA '>' //TRANSI��O ENTRE ETAPAS

#define INICIO 'I'
#define FIM 'F'			//INICIO E FIM DA COMUNICA��O SERIAL


#define PAUSAR 'P'
#define CONTINUAR 'C' //PAUSA PARA CARREGAMENTO DE SENHA DA EEPROM E SINALIZA��O PARA CONTINAR

#define OVERRUN 'O'
#define FRAME_ERROR 'F'  //CARACTERES PARA INDICAR ERRO NA COMUNICA��O SERIAL


#define ABERTURA_PORTA '0'
#define REQUERIMENTO_HISTORICO '1'
#define REQUERIMENTO_STATUS_ATUAL '2'
#define RECONFIGURAR_CONTA '3' //FUN��ES DO SISTEMA
#define RECONFIGURAR_FECHADURA '4'
#define RECONFIGURAR_MODULO '5'
#define MUDAR_SENHA '6'			


#define proxima_etapa() resetar_bit(FLAGS_1,TRANSICAO_ETAPA);etapa++;ordem=0 //PREPARA��O PARA A PROXIMA ETAPA


#define etapa_inicial 0
#define etapa_recebe_funcao 1
#define etapa_login 2					//VALOR DECIMAL DE CADA ETAPA E ORDEM DAS ETAPAS
#define etapa_detalha_funcao 3
#define etapa_final 4


#define QTD_MAX_CONTAS 16		//PARAMETROS DE CONFIGURA��O
#define TAMANHO_SENHA 16




#define PERMISSAO_ABRIR_PORTA 0
#define PERMISSAO_REQUERIMENTO_HISTORICO 1
#define PERMISSAO_REQUERIMENTO_STATUS_ATUAL 2
#define PERMISSAO_RECONFIGURAR_CONTA 3
#define PERMISSAO_RECONFIGURAR_FECHADURA 4  //FLAGS NIVEL DE ACESSO 
#define PERMISSAO_RECONFIGURAR_MODULO 5
#define PERMISSAO_MUDAR_SENHA_OUTRAS 6
#define PERMISSAO_MUDAR_SENHA_PROPRIA 7


#define ERRO_SENHA 0
#define ERRO_PROTOCOLO 1
#define ERRO_IDENTIF_CONTA 2
#define ERRO_NIVEL_DE_ACESSO 3
#define ERRO_COMUNICACAO 4  //FLAGS DE ERRO
#define ERRO_DESCONHECIDO 5
#define TRANSICAO_ETAPA 6
#define TROCA_SENHA 7



#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) // OPERA��ES DE BIT
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))


//Inicio da comunica��o
//Transi��o
//O que ser� feito: fun��o que ser� executada
//Conta que est� realizando o acesso
//Transi��o
//Senha da conta que est� acessando o sistema
//Transi��o
//Detalhes para a fun��o
//Mudan�a de senha : 
		// se � a propria conta +
			//Se sim : senha nova
			//se n�o: conta + senha nova
//Pedido de acesso ao hist�rico: data de in�cio e fim
//Pedido de status atual: n�o precisa
//Abertura de porta: n�o precisa
//Transi��o
//Fim da comunica��o

char dias_do_mes(char mes, char ano){
			if( mes == 2 && (!((ano+4)%4))  ) return 29;
			else return (28+ ((mes + mes/8)%2) + (2%mes)+ (1/mes));
		}


void  interrupt aux(void)
{	
	
	if(RABIF==1 && RABIE==1){
		RABIF=0;}

	if(TMR1IE==1 && TMR1IF ==1){
			}
	
	if(RCIF==1 && RCIE==1){

			if(OERR==1){
				setar_bit(FLAGS_1,ERRO_COMUNICACAO);
				TXREG = OVERRUN;
				while(!TRMT){}
				CREN=0;
				CREN=1;
				//OVERRUN
					}
	
			else if(FERR==1){ 
						setar_bit(FLAGS_1,ERRO_COMUNICACAO);
						TXREG = FRAME_ERROR;}
			
			else{
					dado_recebido = RCREG;
					//Retorno de caracteres para debug
					TXREG = dado_recebido;
					while(!TRMT){}
					TXREG = ('0' + etapa);
					while(!TRMT){}
					TXREG = ('0' + ordem);
					while(!TRMT){}
					TXREG = ('0' + TRANSICAO_ETAPA);
					while(!TRMT){}
					//Fim retorno
	
	
					if(FLAGS_1) { 
									resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
									etapa = etapa_inicial;
									enviar=1;}
	
					else if(TRANSICAO_ETAPA){
							if(dado_recebido != PROXIMA_ETAPA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

							resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
							ordem=0;
							etapa++;}
					
					else if(etapa == etapa_inicial){//Inicio da comunica��o
	
								if(dado_recebido != INICIO) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

							setar_bit(FLAGS_1,TRANSICAO_ETAPA);
								}
	
					else if(etapa == etapa_recebe_funcao){
								if(ordem==0){
							    	funcao = dado_recebido;
										if(funcao<ABERTURA_PORTA && funcao>MUDAR_SENHA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}}
	
								else{
										setar_bit(FLAGS_1,TRANSICAO_ETAPA);
										conta = (dado_recebido - '0');
												if(!(conta<QTD_MAX_CONTAS)) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);

												else{
													if(conta != ultima_conta){
														TXREG = PAUSAR;
														while(!TRMT){}
														RCIE=0;}

													else setar_bit(FLAGS_1,TRANSICAO_ETAPA);
													}
									}
								
								ordem++;}

					
	
					else if(etapa == etapa_login){//executa funcao

								TXREG = 'J';
								while(!TRMT){}
								TXREG = senha[ordem];
								if(senha[ordem] != dado_recebido){ 
												if(senha[ordem+1] == NULL) setar_bit(FLAGS_1,TRANSICAO_ETAPA);
												else setar_bit(FLAGS_1,ERRO_SENHA);
								}
								ordem++;
	
								if(ordem == tamanho_senha) setar_bit(FLAGS_1,TRANSICAO_ETAPA);
				}	

	
					else if(etapa == etapa_detalha_funcao){
								if(funcao == ABERTURA_PORTA){
									if(ordem == 2) {
											setar_bit(FLAGS_1,TRANSICAO_ETAPA);
											}
	
									if( dado_recebido != ('N'+ordem)) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
									ordem++;
									}
					}
								else if(funcao == REQUERIMENTO_HISTORICO){
																	
																	setar_bit(FLAGS_1,TRANSICAO_ETAPA);}
	
								else if(funcao == REQUERIMENTO_STATUS_ATUAL)setar_bit(FLAGS_1,TRANSICAO_ETAPA);

								else if(funcao == MUDAR_SENHA){
										
										if(dado_recebido == NULL) setar_bit(FLAGS_1,TRANSICAO_ETAPA);
	
										else{
											nova_senha[ordem] = dado_recebido;
											ordem++;
												if(ordem == 14) { setar_bit(FLAGS_1,TRANSICAO_ETAPA);  setar_bit(FLAGS_1,TROCA_SENHA);		}
															}	
					
															}
	
					else if(etapa == etapa_final){//Fim da comunica��o
								if(dado_recebido != FIM) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
								enviar=1;
								etapa = etapa_inicial;}
	
	
				}
			RCIF=0;}
							
}
void main(void)
{
	//CONFIGURA��O DO CLOCK
	OSCCON=0b01110001;
	
	//CONFIGURA��O DAS PORTAS
	ANSEL=0;
	ANSELH=0;
	TRISA=0b00011111;
	TRISB=0b00100000;
	TRISC=0;
	PORTC=0;

	//CONFIGURA��O DAS INTERRUP��ES
	INTCON=0b11001000;//GIE=1;PEIE=1;RABIE=1;
	OPTION_REG=0b00000000;
	T1CON=0b00001111;
	TMR1=32768;
	PIE1=1;

	//CONFIGURA��O PORTA SERIAL;
	SYNC=0;     //Ass�ncrona
	BRGH=1;     //
	BRG16=1;    //Registradores para gera��o de Baud rate;
	SPBRGH=0;   //
	SPBRG=16;   //
	SPEN=1;		//habilita a porta serial
	TX9=0;		//transmitir 8 bits
	TXEN=1;		//habilita a transmiss�o
	TXIE=0;
	RCIE=1;		//habilita a interrup��o serial por recep��o
	PEIE=1;		//habilita interrup��o dos perif�ricos
	RX9=0;      //receber 8 bits
	CREN=1; 	//habilita a recep��o serial

	TXREG = 'B';
	while(!TRMT){}
	while(1){

			
		if(enviar==1){
			enviar=0;
			if(	testar_bit(FLAGS_1,ERRO_SENHA) == 0 && 	testar_bit(FLAGS_1,ERRO_PROTOCOLO) ==0){
							TXREG = 'O';
							while(!TRMT){}
							TXREG = 'K';
							while(!TRMT){}}

			else{

			if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)){ 
								TXREG = 'E';
								while(!TRMT){} 
								TXREG = 'P';
								while(!TRMT){} 
								resetar_bit(FLAGS_1,ERRO_PROTOCOLO);}

			if(testar_bit(FLAGS_1,ERRO_SENHA)){
							TXREG = 'E';
							while(!TRMT){}
							TXREG = 'S'; 
							while(!TRMT){} 
							resetar_bit(FLAGS_1,ERRO_SENHA);}

			if(testar_bit(FLAGS_1,ERRO_IDENTIF_CONTA)){ 
							TXREG = 'E';
							while(!TRMT){}
							TXREG = 'I'; 
							while(!TRMT){} 
							resetar_bit(FLAGS_1,ERRO_SENHA);}
				}
				
					}

			else if(RCIE==0){
					char i = 0;
					tamanho_senha=0;

							while( senha[i] && i<TAMANHO_SENHA){
								senha[i] = eeprom_read((conta*TAMANHO_SENHA) + i);
								TXREG= senha[i];
								while(!TRMT);
								i++;}
					nivel_acesso = eeprom_read((conta*TAMANHO_SENHA)+ (TAMANHO_SENHA-1));
					RCIE=1;
					TXREG= CONTINUAR;
					while(!TRMT);

				}

			else if( testar_bit(FLAGS_1,TROCA_SENHA)){
					resetar_bit(FLAGS_1,TROCA_SENHA);
					char i=0;
					tamanho_senha=0;		
							while(nova_senha[i]  && i<TAMANHO_SENHA){
								senha[i] = nova_senha[i];
								eeprom_write(((conta*16) + i),senha[i]);
								while(WR){}
								i++; tamanho_senha++;}

								}
			
}		
}
