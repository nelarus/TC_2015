#include <htc.h>
#include <stdio.h>


 __CONFIG(FOSC_INTRCIO & WDTE_OFF & PWRTE_ON & MCLRE_ON & CP_OFF & CPD_OFF & BOREN_OFF & IESO_OFF & FCMEN_OFF);


#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif


//TESTE



struct Data_completa{
	char dia_da_semana;
	char dia;
	char mes;
	char ano;
	char hora;
	char minuto;
	char segundo;
		}data_atual;

unsigned char tamanho_senha=0;
unsigned char funcao=0;//utilizada para determinar qual função o PIC vai executar (abrir porta, fornecer histórico, fornecer status atual)
unsigned char conta=0;
unsigned char ultima_conta=0;
unsigned char FLAGS_1=0;
unsigned char ordem = 0;//usada para compararar uma sequência de dados recebidos com uma string.
unsigned char etapa=0;
unsigned char dado_recebido = 0;
unsigned char nivel_acesso=0;

char qtd_max_dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};
char senha[16];
char nova_senha[16]; //Para evitar corrompimento da senha no caso de algum erro de comunicação, só se vai repassar a nova senha quando se terminar  de a enviar
bit enviar=0; //Permite o envio de mensagens de erro a central/usuário
bit leitura_eeprom_interna=0;
bit escrita_eeprom_interna=0;
bit escrita_eeprom_externa=0;
bit leitura_eeprom_externa=0;

int endereco_inicial;
int endereco_final;


#define INICIALIZAR '*' //Se o sistema está inicializando isso significa que sua data está desincronizada. Esse caractere indica a central ou ao
						//dispositivo do usuário no caso de acesso direto que é necessário enviar a data correta ao PIC

#define PROXIMA_ETAPA '>' //TRANSIÇÃO ENTRE ETAPAS

#define INICIO 'I'
#define FIM 'F'			//INICIO E FIM DA COMUNICAÇÃO SERIAL


#define PAUSAR 'P'
#define CONTINUAR 'C' //PAUSA PARA CARREGAMENTO DE SENHA DA EEPROM E SINALIZAÇÃO PARA CONTINAR

#define OVERRUN 'O'
#define FRAME_ERROR 'F'  //CARACTERES PARA INDICAR ERRO NA COMUNICAÇÃO SERIAL


#define ABERTURA_PORTA 'a'
#define REQUERIMENTO_HISTORICO 'b'
#define REQUERIMENTO_STATUS_ATUAL 'c'
#define RECONFIGURAR_CONTA 'd'      //FUNÇÕES DO SISTEMA
#define RECONFIGURAR_FECHADURA 'e'
#define RECONFIGURAR_MODULO 'f'
#define CONFIGURAR_DATA 'g'
#define MUDAR_SENHA 'h'

#define IGNORAR 'X'
#define proxima_etapa() resetar_bit(FLAGS_1,TRANSICAO_ETAPA);etapa++;ordem=0 //PREPARAÇÃO PARA A PROXIMA ETAPA


#define etapa_inicial 0
#define etapa_recebe_funcao 1
#define etapa_login 2					//VALOR DECIMAL DE CADA ETAPA E ORDEM DAS ETAPAS
#define etapa_detalha_funcao 3
#define etapa_final 4


#define QTD_MAX_CONTAS 16		//PARAMETROS DE CONFIGURAÇÃO
#define TAMANHO_MAX_SENHA 16




#define PERMISSAO_ABRIR_PORTA 0
#define PERMISSAO_REQUERIMENTO_HISTORICO 1
#define PERMISSAO_REQUERIMENTO_STATUS_ATUAL 2
#define PERMISSAO_RECONFIGURAR_CONTA 3
#define PERMISSAO_RECONFIGURAR_FECHADURA 4  //FLAGS NIVEL DE ACESSO 
#define PERMISSAO_RECONFIGURAR_MODULO 5
#define PERMISSAO_MUDAR_SENHA_OUTRAS 6
#define PERMISSAO_MUDAR_SENHA_PROPRIA 7



#define TROCA_SENHA 0
#define TRANSICAO_ETAPA 1
#define ERRO_SENHA 2
#define ERRO_NIVEL_DE_ACESSO 3
#define ERRO_COMUNICACAO 4  //FLAGS_1 ERRO
#define ERRO_DESCONHECIDO 5
#define ERRO_PROTOCOLO 6
#define ERRO_IDENTIF_CONTA 7





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
//Pedido de acesso ao histórico: ano e mes inicial + ano e mes final. Caso se queira verificar um único mes, envia-se o caractere 'X' como ano final.
//Pedido de status atual: não precisa
//Abertura de porta: não precisa
//Transição
//Fim da comunicação

void  interrupt aux(void)
{	
	
	if(RABIF==1 && RABIE==1){
		RABIF=0;}

	if(TMR1IE==1 && TMR1IF ==1){
					if(++data_atual.segundo>59){
								data_atual.segundo=0; 

								if(++data_atual.minuto>59){

										data_atual.minuto=0;

											if(++data_atual.hora>23){ 

													data_atual.hora=0;
														if(++data_atual.dia_da_semana >6) data_atual.dia_da_semana=0;
														if(++data_atual.dia > qtd_max_dias[data_atual.mes]) {
																data_atual.dia=0;

																	if(++data_atual.mes>12) {
																			data_atual.ano++;
																				if(!(data_atual.ano+3 %4))	qtd_max_dias[data_atual.mes]=29;
																				else qtd_max_dias[data_atual.mes]=28;}	

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
					TXREG = ('0' + testar_bit(FLAGS_1,TRANSICAO_ETAPA));
					while(!TRMT){}
					//Fim retorno
	
	
	
					if(testar_bit(FLAGS_1,TRANSICAO_ETAPA)){
							if(dado_recebido != PROXIMA_ETAPA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

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
										setar_bit(FLAGS_1,TRANSICAO_ETAPA);
										conta = (dado_recebido - '0');

												if(!(conta<QTD_MAX_CONTAS)) { //A conta que se está tentando conectar não existe
													setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);}

												else{

														if(conta != ultima_conta){ //A conta que se está tentando conectar não foi a última acessada(não tem sua senha carregada na memória)
															TXREG = PAUSAR;
															leitura_eeprom_interna=1;
															while(!TRMT){}
															RCIE=0;}

														else {
															if(!(testar_bit(nivel_acesso,(funcao - '0')))) setar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);
															else  	setar_bit(FLAGS_1,TRANSICAO_ETAPA);}
														}
									}
								
								ordem++;}

					
	
					else if(etapa == etapa_login){//executa funcao

								TXREG = 'J';
								while(!TRMT){}
								TXREG = senha[ordem];
								if(senha[ordem] != dado_recebido){ 
										 setar_bit(FLAGS_1,ERRO_SENHA);
								}
								ordem++;
	
								if(ordem == tamanho_senha) setar_bit(FLAGS_1,TRANSICAO_ETAPA);
				}	

	
					else if(etapa == etapa_detalha_funcao){

								if(funcao == ABERTURA_PORTA){

											if(ordem == 2) { setar_bit(FLAGS_1,TRANSICAO_ETAPA);}
			
											if( dado_recebido != ('N'+ordem)) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
											ordem++;}
															}


								else if(funcao == REQUERIMENTO_HISTORICO){

											dado_recebido-= 'A'; //Apenas para fins de teste,pois  o software de teste para android só envia caracteres;
											
											if(ordem == 0) { 
															endereco_inicial = 1794 + (dado_recebido*26);//Espera-se que dado_recebido = ano inicial
															TXREG = PAUSAR;
															leitura_eeprom_externa=1;
															}


											else if(ordem == 1){
														endereco_inicial +=  (dado_recebido *2);  //Espera-se que dado_recebido = mes inicial
												}


											else if(ordem == 2) {
														if(dado_recebido == IGNORAR) 	setar_bit(FLAGS_1,TRANSICAO_ETAPA);
														else endereco_final = 1794 + (dado_recebido*26);} //Espera-se que dado_recebido = ano final

											else if(ordem == 3){
														endereco_final +=(dado_recebido *2);//Espera-se que dado_recebido = mes final
														TXREG = PAUSAR;
														setar_bit(FLAGS_1,TRANSICAO_ETAPA);}

											ordem++;
																	}
	
								else if(funcao == REQUERIMENTO_STATUS_ATUAL) setar_bit(FLAGS_1,TRANSICAO_ETAPA);

								else if(funcao == MUDAR_SENHA){
										
										if(dado_recebido == 'A' && ordem>0) setar_bit(FLAGS_1,TRANSICAO_ETAPA);
	
										else{
											nova_senha[ordem] = dado_recebido;
											ordem++;
												if(ordem == 14) { setar_bit(FLAGS_1,TRANSICAO_ETAPA);  setar_bit(FLAGS_1,TROCA_SENHA);}
															}	
					
															}
	
					else if(etapa == etapa_final){//Fim da comunicação
								if(dado_recebido != FIM) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
								enviar=1;
								etapa = etapa_inicial;}

					
					if(FLAGS_1 > 3) { //Bits de erro vão de 2 a 7. Se um deles estiver setado, FLAGS_1 vai estar com valor acima de 3.
									resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
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
	TRISB=0b00100000;
	TRISC=0;
	PORTC=0;

	//CONFIGURAÇÃO DAS INTERRUPÇÕES
	INTCON=0b11001000;//GIE=1;PEIE=1;RABIE=1;
	OPTION_REG=0b00000000;
	T1CON=0b00001111;
	TMR1=32768;
	PIE1=1;

	//CONFIGURAÇÃO PORTA SERIAL;
	SYNC=0;     //Assíncrona
	BRGH=1;     //
	BRG16=1;    //Registradores para geração de Baud rate;
	SPBRGH=0;   //
	SPBRG=16;   //
	SPEN=1;		//habilita a porta serial
	TX9=0;		//transmitir 8 bits
	TXEN=1;		//habilita a transmissão
	TXIE=0;
	RCIE=0;		//desabilita inicialmente a interrupção por recepção para carregar a senha na memória
	PEIE=1;		//habilita interrupção dos periféricos
	RX9=0;      //receber 8 bits
	CREN=1; 	//habilita a recepção serial

	data_atual.ano = 0;
	data_atual.mes = 1;
	data_atual.dia = 1;
	data_atual.segundo = 0;
	data_atual.minuto = 0;
	data_atual.hora = 0;
	data_atual.dia_da_semana=0;
	TXREG = INICIALIZAR;
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

			else if(leitura_eeprom_externa){
				if(endereco_inicial && endereco_final){TXREG= ',';}}

			else if(leitura_eeprom_interna){

				if(etapa == etapa_login){
					char i = 0;
					tamanho_senha=0;

					do{
					
								senha[i] = eeprom_read((conta*TAMANHO_MAX_SENHA) + i);
								TXREG= senha[i];
								while(!TRMT);
								i++; tamanho_senha++;

					}while(senha[i-1] && i<(TAMANHO_MAX_SENHA-1));

					nivel_acesso = eeprom_read((conta*TAMANHO_MAX_SENHA)+ i);
					RCIE=1;
					TXREG= CONTINUAR;
					while(!TRMT);

				}

				else if( testar_bit(FLAGS_1,TROCA_SENHA)){
					resetar_bit(FLAGS_1,TROCA_SENHA);
					char i=0;
					tamanho_senha=0;		
							while(nova_senha[i]  && i<(TAMANHO_MAX_SENHA-1)){
								senha[i] = nova_senha[i];
								eeprom_write(((conta*16) + i),senha[i]);
								while(WR){}
								i++; tamanho_senha++;}

								}
			
								}		
}
}
