#include <htc.h>
#include <stdio.h>
#include "ext_eeprom.h"


 __CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_ON & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF);


#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif


//TESTE

char qtd_max_dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char senha[16];
char nova_senha[16];


struct Data{
	char dia_da_semana;
	char dia;
	char mes;
	char ano;
	char hora;
	char minuto;
	char segundo;
		}data_atual,data_recebida;


unsigned char ordem = 0;//usada para compararar uma sequência de dados recebidos com uma string.
unsigned char etapa=0;
unsigned char dado_recebido = 0;
unsigned char nivel_acesso;
unsigned char funcao=0;//utilizada para determinar qual função o PIC vai executar (abrir porta, fornecer histórico, fornecer status atual)
unsigned char conta=0;
unsigned char ultima_conta=0;
unsigned char FLAGS_1=0;
unsigned char qtd_total_contas=0;
unsigned char etapa_erro=0;

int endereco_inic_eeprom;
int endereco_final_eeprom;

bit enviar=0; //Permite o envio de mensagens de erro a central/usuário

#define INICIALIZAR '*' //INDICA QUE O PIC INICIALIZOU OU REINICIALIZOU
#define PROXIMA_ETAPA '>' //TRANSIÇÃO ENTRE ETAPAS

#define INICIO 'I'
#define FIM 'F'			//INICIO E FIM DA COMUNICAÇÃO SERIAL

#define PAUSAR 'P'
#define CONTINUAR 'C' //PAUSA PARA CARREGAMENTO DE SENHA DA EEPROM E SINALIZAÇÃO PARA CONTINAR

#define OVERRUN 'O'
#define FRAME_ERROR 'F'  //CARACTERES PARA INDICAR ERRO NA COMUNICAÇÃO SERIAL


#define ABERTURA_PORTA '0'
#define REQUERIMENTO_HISTORICO '1'
#define REQUERIMENTO_STATUS_ATUAL '2'
#define RECONFIGURAR_CONTA '3' //FUNÇÕES DO SISTEMA
#define RECONFIGURAR_FECHADURA '4'
#define RECONFIGURAR_MODULO '5'
#define MODO_DEBUG '6'
#define MUDAR_SENHA '7'			

#define Domingo 0
#define Segunda 1
#define Terca 2
#define Quarta 3  //DIAS DA SEMANA: CORRESPONDÊNCIA DECIMAL
#define Quinta 4
#define Sexta 5
#define Sabado 6

#define Janeiro 0
#define Fevereiro 1
#define Marco 2
#define Abril 3  //MESES: CORRESPONDÊNCIA DECIMAL
#define Maio 4
#define Junho 5
#define Julho 6
#define Agosto 7
#define Setembro 8
#define Outubro 9
#define Novembro 10
#define Dezembro 11

#define etapa_inicial 0
#define etapa_recebe_funcao 1
#define etapa_login 2					//VALOR DECIMAL DE CADA ETAPA E ORDEM DAS ETAPAS
#define etapa_detalha_funcao 3
#define etapa_final 4


#define QTD_MAX_CONTAS 16		//PARAMETROS DE CONFIGURAÇÃO DE CONTAS
#define TAMANHO_SENHA 16


#define PERMISSAO_ABRIR_PORTA 0
#define PERMISSAO_REQUERIMENTO_HISTORICO 1
#define PERMISSAO_REQUERIMENTO_STATUS_ATUAL 2
#define PERMISSAO_RECONFIGURAR_CONTA 3
#define PERMISSAO_RECONFIGURAR_FECHADURA 4  //FLAGS NIVEL DE ACESSO 
#define PERMISSAO_RECONFIGURAR_MODULO 5
#define PERMISSAO_MUDAR_SENHA_OUTRAS 6
#define PERMISSAO_MUDAR_SENHA_PROPRIA 7


#define ERRO_SENHA 6
#define ERRO_PROTOCOLO 7
#define ERRO_IDENTIF_CONTA 2
#define ERRO_NIVEL_DE_ACESSO 3
#define ERRO_COMUNICACAO 4  //FLAGS DE ERRO
#define ERRO_DESCONHECIDO 5
#define TRANSICAO_ETAPA 0
#define TROCA_SENHA 1

#define LED RC5
#define SENSOR_FECHADURA RA0
#define FECHADURA RC0



#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) // OPERAÇÕES DE BIT
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))


//Inicio da comunicação
//Transição
//O que será feito: função que será executada
//Conta que está realizando o acesso
//Transição
//Senha da conta que está acessando o sistema
//Transição
//Detalhes para a função
//Mudança de senha : 
		// se é a propria conta +
			//Se sim : senha nova
			//se não: conta + senha nova
//Pedido de acesso ao histórico: data de início e fim
//Pedido de status atual: não precisa
//Abertura de porta: não precisa
//Transição
//Fim da comunicação
void leitura_eeprom_externa(int endereco){ //Não implementado.
		TXREG = 'l';
		while(!TRMT){} }
void escrita_eeprom_externa(int endereco){ //Não implementado.
		TXREG = 'e';
		while(!TRMT){}
	}

void numero_para_ascii(char numero){
	char temp;

	temp = numero/10;
	TXREG = '0'+ temp;
	while(!TRMT){}

	TXREG = '0'+ (numero - (temp*10));
	while(!TRMT){}

	TXREG = '+';
	while(!TRMT){}
}



void verificar_num_contas(void){
		char i;
		for(i=0;i<QTD_MAX_CONTAS;i++){
			if(eeprom_read(i*TAMANHO_SENHA) != 255) qtd_total_contas++;
				}
}

void config_serial(void){
	
	//CONFIGURAÇÃO PORTA SERIAL;
	SYNC=0;     //Assíncrona
	BRGH=1;     //
	BRG16=1;    //Registradores para geração de Baud rate;
	SPBRGH=0;   //
	SPBRG=16;   //115200bps para 8MHZ de freq de oscilador;
	SPEN=1;		//habilita a porta serial
	TX9=0;		//transmitir 8 bits
	TXEN=1;		//habilita a transmissão
	TXIE=0;
	RCIE=0;		//desabilita a interrupção serial por recepção no início do programa
	PEIE=1;		//habilita interrupção dos periféricos
	RX9=0;      //receber 8 bits
	CREN=1; 	//habilita a recepção serial

}

void carregar_senha(void){
					char i = 0;

							do{
								senha[i] = eeprom_read((conta*TAMANHO_SENHA) + i);
								TXREG= senha[i];
								while(!TRMT);
								i++;} while( senha[i-1] && i<(TAMANHO_SENHA-1));

					nivel_acesso = eeprom_read((conta*TAMANHO_SENHA)+ (TAMANHO_SENHA-1));
					TXREG = nivel_acesso;
					while(!TRMT);
					RCIE=1;
					

}

void interrupt aux(void)
{	
	
	if(RABIF==1 && RABIE==1){
		RABIF=0;}

	if(TMR1IE==1 && TMR1IF ==1){
					LED=!LED;
					if(++data_atual.segundo>59){
								data_atual.segundo=0; 

								if(++data_atual.minuto>59){


										data_atual.minuto=0;

											if(++data_atual.hora>23){ 

													data_atual.hora=0;
														if(++data_atual.dia_da_semana > Sabado) data_atual.dia_da_semana = Segunda;
														if(++data_atual.dia > qtd_max_dias[data_atual.mes]) {
																data_atual.dia=0;

																	if(++data_atual.mes> Dezembro) {
																			data_atual.ano++;
																				if(!((data_atual.ano+3)%4))	qtd_max_dias[Fevereiro]=29;
																				else qtd_max_dias[Fevereiro]=28;}	

															}  

 }	}}


					TMR1+=32768;
					TMR1IF=0;}
			
	
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
						SPEN=0;
						SPEN=1;
						if(RCREG){}
						TXREG = FRAME_ERROR;
						while(!TRMT){}}
			
			else{
					dado_recebido = RCREG;
					//Retorno de caracteres para debug
					TXREG = dado_recebido;
					while(!TRMT){}
					TXREG = ('0' + etapa);
					while(!TRMT){}
					TXREG = ('0' + ordem);
					while(!TRMT){}
					TXREG = ('0' + testar_bit(FLAGS_1,TRANSICAO_ETAPA));
					if(etapa ==3) { TXREG=funcao;while(!TRMT){}}
					while(!TRMT){}
					//Fim retorno

					if(testar_bit(FLAGS_1,TRANSICAO_ETAPA)){
							TXREG = ('X');
							while(!TRMT){}

							if(dado_recebido != PROXIMA_ETAPA) {
													
													TXREG = PROXIMA_ETAPA;
													while(!TRMT){}
													setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

							resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
							ordem=0;
							etapa++;}
					
					else if(etapa == etapa_inicial){//Inicio da comunicação
								
	
								if(dado_recebido != INICIO) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

							setar_bit(FLAGS_1,TRANSICAO_ETAPA);
								}
	
					else if(etapa == etapa_recebe_funcao){
								if(ordem==0){
							    	funcao = dado_recebido;
										if(funcao<ABERTURA_PORTA && funcao>MUDAR_SENHA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}}
	
								else{
										conta = (dado_recebido - '0');
												if(!(conta<QTD_MAX_CONTAS)) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);

												else{
													if(conta != ultima_conta){
														TXREG = PAUSAR;
														while(!TRMT){}
														RCIE=0;
														}

													else setar_bit(FLAGS_1,TRANSICAO_ETAPA);
													}
									}
								
								ordem++;}

					
	
					else if(etapa == etapa_login){//executa funcao

								TXREG = 'J';
								while(!TRMT){}
								TXREG = senha[ordem];
								while(!TRMT){}

								if(senha[ordem] != dado_recebido){ 
													setar_bit(FLAGS_1,ERRO_SENHA);}
								ordem++;
								
								if(senha[ordem] == NULL) setar_bit(FLAGS_1,TRANSICAO_ETAPA);
									
								}	

	
					else if(etapa == etapa_detalha_funcao){
								if(funcao == ABERTURA_PORTA || funcao == REQUERIMENTO_STATUS_ATUAL){

									if(ordem == 2) {
											setar_bit(FLAGS_1,TRANSICAO_ETAPA);
											}
	
									else if(dado_recebido != ('N'+(ordem))) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

									ordem++;
									}
					
								else if(funcao == REQUERIMENTO_HISTORICO){
												if(ordem==0){
														endereco_inic_eeprom = (1794 + (dado_recebido *26));
													
												ordem++;
													}
}
//Não implementado

								else if(funcao == MUDAR_SENHA){
										//Para testes o fim da string será dado como '<' em vez de null
										
												if(dado_recebido == '<') {
													if(ordem<5) setar_bit(FLAGS_1,ERRO_PROTOCOLO);

													else setar_bit(FLAGS_1,TRANSICAO_ETAPA);
													}
	
										else{
											nova_senha[ordem] = dado_recebido;
											ordem++;
												if(ordem == 14) {setar_bit(FLAGS_1,TRANSICAO_ETAPA);}
											}	
					
															}
					}
	
					else if(etapa == etapa_final){//Fim da comunicação

								if(dado_recebido != FIM) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
								enviar=1;
								etapa = etapa_inicial;}

					
					
					if(FLAGS_1>3) { 
									resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
									TXREG = '0' + etapa;
									while(!TRMT){}
									etapa = etapa_inicial;	
									enviar=1;}
	
	
				}
			RCIF=0;}
							
}
void main(void)
{
	//CONFIGURAÇÃO DO CLOCK
	OSCCON=0b01110001;
	
	//CONFIGURAÇÃO DAS PORTAS
	ANSEL=0;
	ANSELH=0;
	TRISA=0b00011111;
	TRISB=0b01110000;
	TRISC=0;
	PORTC=0;
	PORTB =0b00000000;

	//CONFIGURAÇÃO DAS INTERRUPÇÕES
	INTCON=0b11001000;//GIE=1;PEIE=1;RABIE=1;
	OPTION_REG=0b00000000;
	T1CON=0b00001111;
	TMR1=32768;
	PIE1=1;
	
	config_serial();

	data_atual.dia_da_semana=0;
	data_atual.dia=0;
	data_atual.mes=0;
	data_atual.ano=0;
	data_atual.hora=0;
	data_atual.minuto=0;
	data_atual.segundo=0;

	verificar_num_contas();
	carregar_senha();
	write_i2c_device(2010,'A');
	__delay_ms(500);
	TXREG = read_i2c_device(2010);

	while(1){
		
		if(enviar==1){//O que será enviado pela serial dependerá da etapa em que o envio foi solicitado pelo programa.
					  //Se for na etapa final, por exemplo, significa que é necessário enviar de volta se o acesso foi bem sucedido ou não.
			enviar=0;
			
			TXREG = '\n';
			while(!TRMT){}
			TXREG = INICIO;
			while(!TRMT){}

						if(FLAGS_1<4){
										etapa = etapa_inicial;
										TXREG = 'O';
										while(!TRMT){}
										TXREG = 'K';
										while(!TRMT){}

												if(funcao == REQUERIMENTO_STATUS_ATUAL){
														numero_para_ascii(data_atual.ano);
														numero_para_ascii(data_atual.mes);
														numero_para_ascii(data_atual.hora);
														numero_para_ascii(data_atual.minuto);
														numero_para_ascii(data_atual.segundo);
														numero_para_ascii(qtd_total_contas);
														numero_para_ascii(QTD_MAX_CONTAS);}


												else if(funcao == MUDAR_SENHA){
													char i=0;	
														do{
															senha[i] = nova_senha[i];
															eeprom_write(((conta*16) + i),senha[i]);
															while(WR){}
															i++;} while(nova_senha[i-1]  && i<TAMANHO_SENHA);
														}
							


										}
						
						else{
			
						etapa = etapa_inicial;
							if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)){ 
												TXREG = 'E';
												while(!TRMT){} 
												TXREG = 'P';
												while(!TRMT){}
													if(funcao == MUDAR_SENHA){
																TXREG = 'S'; //indica que a nova senha tem menos que 6 caracteres;
																while(!TRMT){} 
														} 
												
												resetar_bit(FLAGS_1,ERRO_PROTOCOLO);}

							if(testar_bit(FLAGS_1,ERRO_COMUNICACAO)){
											
											TXREG = 'E';
											while(!TRMT){}
											TXREG = 'C'; 
											while(!TRMT){} 
											resetar_bit(FLAGS_1,ERRO_COMUNICACAO);}
						
				
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
															


				TXREG=FIM;
				while(!TRMT){}}
				
			

			else if(RCIE==0){
							if(etapa == etapa_recebe_funcao){
									carregar_senha();
									TXREG = CONTINUAR;
									while(!TRMT){}
									setar_bit(FLAGS_1,TRANSICAO_ETAPA);}
					}

			
		
}		
}
