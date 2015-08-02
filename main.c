#include <xc.h>
#include <delays.h>
#include <string.h>
#include "encrypt.h"
#include "ascii.h"

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

#pragma config FOSC =  HSPLL_HS
#pragma config PLLDIV = 1
#pragma config CPUDIV = OSC4_PLL6
#pragma config USBDIV = 1
#pragma config VREGEN = ON
#pragma config FCMEN = OFF   //no fail safe clock monitor 
#pragma config IESO = OFF   //oscillator switchover disabled 
#pragma config PWRT = ON           //oscillator power up timer enabled (release version only) 
#pragma config BOR = OFF      //hardware brown out reset 
#pragma config WDT = OFF   //watchdog timer disabled 
#pragma config MCLRE = ON    //MCLR pin enabled 
#pragma config LPT1OSC = OFF //timer1 low power operation 
#pragma config PBADEN = OFF   //portB 0to 4 digital - not analogue 
#pragma config LVP = OFF     //low voltage programming disabled 
#pragma config CCP2MX = OFF  //portc1 = CCP2 
#pragma config XINST = OFF         //do not allow PIC18 extended instructions 
#pragma config  STVREN = ON         //stack overflow will cause reset 
#pragma config CP0 = OFF      //code protection block 0 
#pragma config CP1 = OFF 
#pragma config CP2 = OFF 
#pragma config CP3 = OFF 
#pragma config CPB = OFF      //code protection boot block 
#pragma config CPD = OFF      //code protection data EEPROM 
#pragma config WRT0 = OFF      //write protection block 0 
#pragma config WRT1 = OFF 
#pragma config WRT2 = OFF 
#pragma config WRT3 = OFF 
#pragma config WRTB = OFF      //write protection boot block 
#pragma config WRTC = OFF      //write protection configuration register 
#pragma config WRTD = OFF      //write protection data EEPROM 
#pragma config EBTR0 = OFF      //table read protection block 0 
#pragma config EBTR1 = OFF 
#pragma config EBTR2 = OFF 
#pragma config EBTR3 = OFF 
#pragma config EBTRB = OFF      //table read protection boot block

//PARAMETROS DE CONFIGURAÇÃO DE COMUNICAÇÃO SERIAL
#define TAMANHO_BUFFER_SERIAL 80

//PARAMETROS DE CONFIGURAÇÃO DE CONTAS
#define QTD_MAX_CONTAS 16		
#define TAMANHO_SENHA 16
#define conta_admin 0
#define nivel_acesso ((conta*TAMANHO_SENHA)+ (TAMANHO_SENHA-1))

char qtd_max_dias =31;
char senha[QTD_MAX_CONTAS][TAMANHO_SENHA+1];
char nova_senha[TAMANHO_SENHA];
unsigned char buffer_serial[TAMANHO_BUFFER_SERIAL];
unsigned char qtd_caracteres_recebidos=0;
char dados_recebidos[41];
char chave_criptografia[17];
char texto_critografado[81];
char texto_descriptografado[41];

struct Data{
	unsigned char ano;//0
	char mes;//1
	char dia;//2
	char hora;//3
	char minuto;//4
	char segundo;//5
	char dia_da_semana;//6
		}data_atual,data_recebida;

unsigned char caractere_recebido = 0; //Caractere recebido pelo teclado matricial
unsigned char FLAGS_1=0;
unsigned char PORTB_SR;
unsigned char qtd_int_timer1=0;
unsigned char qtd_vezes_mesma_tecla_pressionada=0;

unsigned int endereco_inic_eeprom=5;
unsigned int endereco_final_eeprom=5;
char *ptr_data;

bit enviar=0; //Permite o envio de mensagens de erro a central/usuário
bit receber=0;
bit modo_bluetooth_teclado=0; //Indica se o usuário está se conectando por bluetooth(modo_bluetooth_teclado=0) ou teclado matricial(modo_bluetooth_teclado=1)
bit debounce=0;
bit modo_t9=0;//modo_t9=1 -> As teclas 1 a 9 do teclado matricial podem ser usadas para inserir as 26 letras do alfabeto
bit maiuscula=0;//Se for 1 as letras inseridas pelo teclado matricial serão maisculas;

//REPRESENTAÇÃO DO TECLADO MATRICIAL NO MODO_T9

//1-> Seleciona entre 1,a,b e,c(maiusculas ou minusculas)
//2-> Seleciona entre 2,d,e e,f(maiusculas ou minusculas)
//3-> Seleciona entre 3,g,h e,i(maiusculas ou minusculas)
//4-> Seleciona entre 4,j,k e,l(maiusculas ou minusculas)
//5-> Seleciona entre 5,m,n e,o(maiusculas ou minusculas)
//6-> Seleciona entre 6,p,q e,r(maiusculas ou minusculas)
//7-> Seleciona entre 7,s,t e,u(maiusculas ou minusculas)
//8-> Seleciona entre 8,v,w e,x(maiusculas ou minusculas)
//9-> Seleciona entre 9,y e z(maiusculas ou minusculas)
  
//PARAMETROS TECLADO MATRICIAL MODO T9
#define Letras_por_tecla 3

//DIAS DA SEMANA: CORRESPONDÊNCIA DECIMAL
#define Domingo 0
#define Segunda 1
#define Terca 2
#define Quarta 3
#define Quinta 4
#define Sexta 5
#define Sabado 6


//MESES: CORRESPONDÊNCIA DECIMAL
#define Janeiro 1
#define Fevereiro 2
#define Marco 3
#define Abril 4  
#define Maio 5
#define Junho 6
#define Julho 7
#define Agosto 8
#define Setembro 9
#define Outubro 10
#define Novembro 11
#define Dezembro 12

//VALOR DECIMAL DE CADA ETAPA E ORDEM DAS ETAPAS
#define etapa_inicial 0
#define etapa_recebe_funcao 1
#define etapa_login 2					
#define etapa_detalha_funcao 3
#define etapa_final 4




//MODOS DE RECEPÇÃO DE DADOS

#define MODO_TECLADO_MATRICIAL modo_bluetooth_teclado==1
#define MODO_BLUETOOTH modo_bluetooth_teclado==1
#define modo_teclado_matricial() modo_bluetooth_teclado=1;
#define modo_bluetooth() modo_bluetooth_teclado=0;

//CORRESPONDÊNCIA DE CARACTERES NA COMUNICAÇÃO SERIAL E RECEBIMENTO POR TECLADO MATRICIAL

	//FUNÇÕES DO SISTEMA
	#define ABERTURA_PORTA '0'
	#define REQUERIMENTO_HISTORICO '1'
	#define REQUERIMENTO_STATUS_ATUAL '2'
	#define RECONFIGURAR_CONTA '3' 
	#define RECONFIGURAR_PIC '4'
	#define RECONFIGURAR_MODULO '5'
	#define MUDAR_SENHA '7'	

	//OUTROS CARACTERES
	#define INICIALIZAR '*' //INDICA QUE O PIC INICIALIZOU OU REINICIALIZOU.
	#define PROXIMA_ETAPA '>' //TRANSIÇÃO ENTRE ETAPAS
	#define IGNORAR 'X' //Indica que a ação que deveria ser executa não será mais. Ex: Reconfiguração de conta: Não será feito o ajuste de hora
	#define PAUSAR 'P'
	#define CONTINUAR 'C' //PAUSA PARA CARREGAMENTO DE SENHA DA EEPROM E SINALIZAÇÃO PARA CONTINAR
	#define OVERRUN 'O'
	#define FRAME_ERROR 'F'  //CARACTERES PARA INDICAR ERRO NA COMUNICAÇÃO SERIAL
	#define INICIO 'I'		//INICIO  DA COMUNICAÇÃO SERIAL
	#define FIM 'F'			// FIM DA COMUNICAÇÃO SERIAL. 
														//No modo teclado matricial usa-se para auxiliar na inserção de letras quando modo_t9=1;
														//Ex: Para inserir a letra 'a' se aperta '1' duas vezes e por fim '#'(que aqui corresponderá a 'F')
	

	#define MAIUSCULA_MINUSCULA 'M'
	#define MODO_T9_ON_OFF 'A'
	#define MODO_DEBUG '^'	//Se o caracter recebido for esse o programa irá ignorar o protocolo e entrar em modo de debug(a ser implementado)


//FLAGS NIVEL DE ACESSO
#define PERMISSAO_ABRIR_PORTA 0
#define PERMISSAO_REQUERIMENTO_HISTORICO 1
#define PERMISSAO_REQUERIMENTO_STATUS_ATUAL 2
#define PERMISSAO_RECONFIGURAR_PROPRIA_CONTA 3
#define PERMISSAO_RECONFIGURAR_PIC 4  
#define PERMISSAO_RECONFIGURAR_MODULO 5
#define PERMISSAO_RECONFIGURAR_OUTRAS_CONTAS 6
#define PERMISSAO_MUDAR_PROPRIA_SENHA 7


//FLAGS_1;CORRESPONDÊNCIA DE BITS
#define ERRO_SENHA 6
#define ERRO_PROTOCOLO 7
#define ERRO_IDENTIF_CONTA 2
#define ERRO_NIVEL_DE_ACESSO 3
#define ERRO_COMUNICACAO 4  
#define ERRO_DESCONHECIDO 5
#define TRANSICAO_ETAPA 0
#define TROCA_SENHA 1

//RENOMEAÇÃO DOS PINOS DAS PORTAS E DOS LATCHES
#define LED PORTCbits.RC5			//Mostra que a contagem de horas está funcionando
#define FECHADURA PORTCbits.RC0    //Destravamento ou não da fechadura
#define SENSOR_ABERTURA_FECHADURA PORTAbits.RA0 //Sensor magnético(reed switch)

#define COLUNA_1 PORTBbits.RB7
#define COLUNA_2	PORTBbits.RB6
#define COLUNA_3	PORTBbits.RB5
#define COLUNA_4 PORTBbits.RB4   //Teclado matricial
#define LINHA_1 PORTDbits.RD4
#define LINHA_2 PORTDbits.RD5
#define LINHA_3 PORTDbits.RD6
#define LINHA_4 PORTDbits.RD7


#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) // OPERAÇÕES DE BIT
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))

void config_serial(void){
		SYNC=0; //assincrono
		BRGH=1;
		BRG16=1;
		SPBRG= 35;
		TX9=0;
		RX9=0;//tx e rx em 8 bits
		TXEN=1; //habilita transmissão
		RCIE=0; // interrupção por recepção
		CREN=1;
		SPEN=1;
		TXCKP = 0;
		TXIE = 0;
		TX9 = 0;
				}
char dia_da_semana(unsigned int ano,char mes, char dia){

	char tabela_mes[]= {0,3,3,6,1,4,6,2,5,0,3,5};
	unsigned int seculo;

	ano+=15; //O ano 0 no calendário do PIC é 2015,cujos 2 ultimos digitos são 15
	seculo = ano/100;
	ano-= (ano/100); //pega os 2 ultimos digitos do ano

	if(! ((ano+3)%4) ){
			if (mes==1) tabela_mes[mes-1]=6;
			else if(mes==2) tabela_mes[mes-1]=2;}

	return (( (6 - seculo*2) + dia + tabela_mes[mes-1] + ano + (ano/4))%7);
	

}
void eeprom_config_inicial(void){
		unsigned char i;

		for(i=0;i<10;i++){
			eeprom_write(i,('0'+i));//Senha padrão da conta 0(admin): 0123456789
			eeprom_write(TAMANHO_SENHA+i,('a'+i));
			
			}
		eeprom_write(i,0);
		eeprom_write(TAMANHO_SENHA+i,0);//null da string de cada senha

		eeprom_write(((TAMANHO_SENHA*2)-1),0b11111101);
		}


char verificar_num_contas(void){
		char i;
		unsigned char qtd_contas=0;
		for(i=0;i<QTD_MAX_CONTAS;i++){
			if(eeprom_read(i*TAMANHO_SENHA) != 0xFF) {qtd_contas++;}
				}
		return (qtd_contas);}


void carregar_senha(char conta){
					TXREG = '\n';
					while(!TRMT);
					char i = 0;

							do{
								senha[conta][i] = eeprom_read((conta*TAMANHO_SENHA) + i);
								TXREG= senha[conta][i];
								while(!TRMT);
								i++;} while( senha[conta][i-1] && i<(TAMANHO_SENHA-1));


					
					senha[conta][TAMANHO_SENHA] = eeprom_read((TAMANHO_SENHA*(conta+1))-1); 
					}
					

void interrupt aux(void){

			if(TMR1IE && TMR1IF){
				TMR1IF=0;
				TMR1H=0x50;
				TMR1ON=0;
				TMR1L=0;

				numero_para_ascii(qtd_vezes_mesma_tecla_pressionada);
				qtd_vezes_mesma_tecla_pressionada=0;
							
			}
			
			if(TMR0IE && TMR0IF){
					TMR0H = 0xC2;
					TMR0L+=0xF7;
					TMR0IF=0;
					LATDbits.LD1^=1;

					if(++data_atual.segundo>59){
								data_atual.segundo=0; 
								
									if(++data_atual.minuto>59){


									data_atual.minuto=0;

											if(++data_atual.hora>23){ 

											data_atual.hora=0;
																if(++data_atual.dia_da_semana > Sabado) data_atual.dia_da_semana = Segunda;
																				
																if(++data_atual.dia >= qtd_max_dias) {
																		data_atual.dia=1;
					
																		switch(++data_atual.mes){
																			case Janeiro:
																			case Marco:
																			case Maio:
																			case Julho:
																			case Agosto:
																			case Outubro:
																			case Dezembro:
																				qtd_max_dias=31;
																				break;
					
																			case Fevereiro:
																				if(!((data_atual.ano+3)%4))	qtd_max_dias=29;
																				else qtd_max_dias=28;
																				break;
					
																			case Abril:
																			case Junho:
																			case Setembro:
																			case Novembro:
																				qtd_max_dias=30;
																				break;
					
																			default:
																				data_atual.ano++;
																				data_atual.mes=0;
																				break;}
																									}  
					
					 												}	
																}
											}

						
					}

			if(TMR1IE && TMR1IF){
				LATDbits.LD2^=1;
				TMR1IF=0;
				TMR1ON=0;}

			if(RBIE && RBIF){
					char coluna=0;
					char linha=0;
					PORTB_SR=(PORTB&0xF0);
					RBIF=0;
					if(PORTB_SR != 0xF0) {
							RBIE=0;
							debounce=1;
							LATDbits.LD0^=1;
	
							if(COLUNA_1==0){coluna=1;}

							else if(COLUNA_2==0){coluna=2;}

							else if(COLUNA_3==0){coluna=3;}

							else if(COLUNA_4==0){coluna=4;}

							else{coluna=0;}//Houve algum problema na detecção de qual coluna está a tecla pressionada
						

						
						TRISB&=0x0F;
						LATB|=0xF0;

						while(PORTB&0xF0 !=	0xF0){}
						while( (PORTD&0xF0) != 0){}

						TRISD|=0xF0;
	
							if(LINHA_1==1){linha=1;}

							else if(LINHA_2==1){linha=2;}

							else if(LINHA_3==1){linha=3;}

							else if(LINHA_4==1){linha=4;}
							
							else{linha=0;}//Houve algum problema na detecção de qual linha está a tecla pressionada

							if(linha && coluna){//Não faz nada se houve algum erro na detecção da linha ou da linha
								TXREG = '\n';
								while(!TRMT){}
								caractere_recebido = teclado_matricial(coluna,linha);
								TXREG = caractere_recebido;
								numero_para_ascii(linha);
								numero_para_ascii(coluna);}
						
					
						TRISB|=0xF0;
						LATD&=0x0F;
						TRISD&=0X0F;

						while( (PORTD&0xF0) != 0x00){}
						while( (PORTB&0xF0) != 0xF0){}
							
					}

					PORTB_SR=(PORTB&0xF0);}

			if(RCIE && RCIF){
				
					if(OERR==1){
						setar_bit(FLAGS_1,ERRO_COMUNICACAO);
						char temp;
						do{ 
				            temp = RCREG; 
				            CREN = 0; 
				            CREN = 1;
							if(temp){}
 
				          }while(OERR);
						enviar=1;
						receber=0;
						//OVERRUN
							}
			
					else if(FERR==1){ 
								setar_bit(FLAGS_1,ERRO_COMUNICACAO);
								char temp;
									do{
									temp = RCREG;
									SPEN=0;
									SPEN=1;
									if(temp){}
									}while(FERR);
								enviar=1;
								receber=0;}
					
					else{	
							buffer_serial[qtd_caracteres_recebidos] = RCREG;

							if(++qtd_caracteres_recebidos == TAMANHO_BUFFER_SERIAL || buffer_serial[qtd_caracteres_recebidos-1] == FIM){receber=1;}
						}

					RCIF=0;}

}


int main(void){

	unsigned char ordem = 0;//usada para compararar uma sequência de dados recebidos com uma string.
	unsigned char etapa=0;
	unsigned char funcao=0;//utilizada para determinar qual função o PIC vai executar (abrir porta, fornecer histórico, fornecer status atual)
	unsigned char conta=0;
	unsigned char conta_a_ser_alterada=0;
	unsigned char cont=0;
	unsigned char qtd_total_contas=0;	
	unsigned char ultimo_caractere_recebido=0;

	//CONFIGURAÇÃO OSCILADOR
	OSCCON=0XF0;

	//CONFIGURAÇÃO INTERRUPÇÕES
	INTCON = 0b11100000;
	INTCON2 =0b00000000;
	PIE1=0b00100001;
	RCONbits.IPEN = 0;

	
	//CONFIGURAÇÃO TIMER0(CONTAGEM HORAS)
	T0CON = 0b10000111;
	TMR0H=0xC2; //TMR0=34446(1 interrupção = 1s para FOSC=16MHz)
	TMR0L= 0xF7;

	//CONFIGURAÇÃO DAS PORTAS
	LATD=0;
	
	TRISB=0xF0;
	LATB=0x0F;
	TRISC=0xC3;
	TRISD=0x00;
	ADCON1=0XFF;
	CMCON=0X07;

	//CONFIGURAÇÃO TIMER1(CONTAGEM DE TEMPO NO MODO_T9)
	T1CON = 0b00001110;
	TMR1H=0;
	TMR1L=0;


	if(eeprom_read(0) == 0xFF)	eeprom_config_inicial();

	config_serial();
	qtd_total_contas = verificar_num_contas();
	numero_para_ascii(qtd_total_contas);

		for(conta=0;conta<qtd_total_contas;conta++){
				carregar_senha(conta);}

	conta=0;
	RCIE=1;

	data_atual.ano=0;
	data_atual.mes=1;
	data_atual.dia=1;
	data_atual.dia_da_semana= dia_da_semana(data_atual.ano,data_atual.mes,data_atual.dia);
	data_atual.hora=0;
	data_atual.minuto=0;
	data_atual.segundo=0;
	PORTB_SR=PORTB;//Leitura do PORTB antes de habilitar a interrupção para evitar uma interrupção não desejada.
	RBIE=1;
	RBIF=0;
	cont=0;
	while(1){
		
		if(receber == 1){
			
			receber=0;
			TXREG = '\n';
			while(!TRMT){}
			char j;
				for(j=0;j<qtd_caracteres_recebidos;j++){
					TXREG = buffer_serial[j];
					while(!TRMT){}
						}
			
			TXREG = '\n';
			while(!TRMT){}
	
				for(cont=0;cont<qtd_caracteres_recebidos;cont++){

	
								if(testar_bit(FLAGS_1,TRANSICAO_ETAPA)){
	
										if(buffer_serial[cont] != PROXIMA_ETAPA) {
																setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
	
										resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
										ordem=0;
										etapa++;}
								
								else if(etapa == etapa_inicial){//Inicio da comunicação
											
				
											if(buffer_serial[cont] != INICIO) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
			
										setar_bit(FLAGS_1,TRANSICAO_ETAPA);
											}
				
								else if(etapa == etapa_recebe_funcao){

										    	funcao = buffer_serial[cont++];
													if(funcao<ABERTURA_PORTA || funcao>MUDAR_SENHA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

												conta = ((buffer_serial[cont]) - '0');
															
													if(!(conta<QTD_MAX_CONTAS)) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);
	
												setar_bit(FLAGS_1,TRANSICAO_ETAPA);
																
												}
			
								
				
								else if(etapa == etapa_login){//executa funcao
			
										for(ordem=0;senha[conta][ordem]!= 0;ordem++){
												if(senha[conta][ordem] != buffer_serial[cont++]) {
																setar_bit(FLAGS_1,ERRO_SENHA);
																TXREG = senha[conta][ordem]; while(!TRMT){}
																TXREG = buffer_serial[--cont]; while(!TRMT){}
																										}
													}
										cont--;
										setar_bit(FLAGS_1,TRANSICAO_ETAPA);
												
											}	
			
				
								else if(etapa == etapa_detalha_funcao){
											if(funcao == ABERTURA_PORTA || funcao == REQUERIMENTO_STATUS_ATUAL){

												for(ordem=0;ordem<2;ordem++){
													if( buffer_serial[cont++] != ('N'+(ordem))) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
														}
			
													setar_bit(FLAGS_1,TRANSICAO_ETAPA);
												}
								
											else if(funcao == REQUERIMENTO_HISTORICO){
															if(ordem==0){
																	endereco_inic_eeprom = (1794 + (buffer_serial[cont] *26));
																
															ordem++;
																}
			}
			//Não implementado
	
											else if(funcao == RECONFIGURAR_PIC){
													//ordem 0 ajuste de ano
													//ordem 1 ajuste de mes
													//ordem 2 ajuste de dia
													//ordem 3 ajuste de hora
													//ordem 4 ajuste de minuto
													//ordem 5 ajuste de segundo

													ptr_data= &data_atual.ano;

													for(ordem=0;ordem<6;ordem++){
															if(buffer_serial[cont] == IGNORAR) {//Pula para o próximo ajuste
																			ordem++;
																			cont+=2;} 
														
														*(ptr_data+ordem) = ascii_para_numero('0',buffer_serial[cont],buffer_serial[cont+1]);
														char temp = *(ptr_data+ordem);
														numero_para_ascii(temp);
														numero_para_ascii(ordem);
														cont+=2;}

														data_atual.dia_da_semana = dia_da_semana(data_atual.ano,data_atual.mes,data_atual.dia);
														setar_bit(FLAGS_1,TRANSICAO_ETAPA);
														cont--;
																}
	
											else if(funcao == MUDAR_SENHA){

													conta_a_ser_alterada = (buffer_serial[cont] - '0');
			
													if(	conta_a_ser_alterada != conta && (!(testar_bit(nivel_acesso,PERMISSAO_RECONFIGURAR_OUTRAS_CONTAS)))	){
																		setar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);
																					}
													
													for(ordem=0;ordem<(TAMANHO_SENHA-1);ordem++){
														cont++;

															if(buffer_serial[cont] == '<') {
																		if(ordem<5) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
					
																		else {
																			if(ordem<TAMANHO_SENHA-2) eeprom_write( ((conta_a_ser_alterada*16)+ordem) , 0);
																			break;}
															}
																					

															else{
																	
																senha[conta_a_ser_alterada][ordem] = buffer_serial[cont];
																eeprom_write( ((conta_a_ser_alterada*16)+ordem) ,buffer_serial[cont]);}

																}	
								
														setar_bit(FLAGS_1,TRANSICAO_ETAPA);}
						}
				
								else if(etapa == etapa_final){//Fim da comunicação
											if(buffer_serial[cont] != FIM) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
											enviar=1; receber=qtd_caracteres_recebidos=0;}
			
								
								
								if(FLAGS_1>3) {
												resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
												TXREG = '0' + etapa;
												etapa = etapa_inicial;	
												enviar=1;
												receber=qtd_caracteres_recebidos=0;}
	
						}
			}
		
		if(enviar==1){
			enviar=0;
			qtd_caracteres_recebidos=0;
			TXREG = '\n';
			while(!TRMT){}
			TXREG = INICIO;
			while(!TRMT){}

						if(FLAGS_1<4 && etapa == etapa_final){ //Não houve erros
										etapa = etapa_inicial;
										TXREG = 'O';
										while(!TRMT){}
										TXREG = 'K';
										while(!TRMT){}

												if(funcao == REQUERIMENTO_STATUS_ATUAL){
														numero_para_ascii(data_atual.ano);
														numero_para_ascii(data_atual.mes);
														numero_para_ascii(data_atual.dia_da_semana);
														numero_para_ascii(data_atual.dia);
														numero_para_ascii(data_atual.hora);
														numero_para_ascii(data_atual.minuto);
														numero_para_ascii(data_atual.segundo);
														numero_para_ascii(qtd_total_contas);
														numero_para_ascii(QTD_MAX_CONTAS);
														numero_para_ascii(SENSOR_ABERTURA_FECHADURA);}


												else if(funcao == MUDAR_SENHA){
													char i=0;	
														do{
															senha[conta_a_ser_alterada][i] = nova_senha[i];
															eeprom_write(((conta_a_ser_alterada*16) + i),nova_senha[i]);
															while(WR){}
															i++;} while(nova_senha[i-1]  && i<TAMANHO_SENHA);
														}
							
												else if(funcao == ABERTURA_PORTA){
														while(SENSOR_ABERTURA_FECHADURA == 0){
															//cont++; //quantidade de vezes que se tentou destravar a fechadura
															FECHADURA=1;
															delay_ms(325);
															FECHADURA=0;
																if(SENSOR_ABERTURA_FECHADURA == 0) delay_ms(100);
															}
												}

										}
						
						else{
						etapa = etapa_inicial;
						cont=qtd_caracteres_recebidos=0;

							if(testar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO)){ 
												TXREG = 'E';
												while(!TRMT){} 
												TXREG = 'N';
												while(!TRMT){}
												
												resetar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);}

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
											resetar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);}
								}
															


				TXREG=FIM;
				while(!TRMT){}}



		if((PORTB&0xF0) == 0xF0 && RBIE==0 && debounce==1){//Tratamento de debounce. Espera-se até que nenhum botão esteja pressionado e que o debounce esteja autorizado
																			//(existem situações em que RBIE=0 e não se quer fazer tratamento de debounce
					delay_ms(60);

						if(!qtd_vezes_mesma_tecla_pressionada && !TMR1ON) {//Condição inicial

								TMR1ON=1;
								ultimo_caractere_recebido=0;}

						if(caractere_recebido == ultimo_caractere_recebido){
								char caractere_a_exibir;
								caractere_a_exibir = ( ('a' + ((caractere_recebido-'1')*3))+ qtd_vezes_mesma_tecla_pressionada);
								TXREG = caractere_a_exibir;

								if(++qtd_vezes_mesma_tecla_pressionada == Letras_por_tecla || ( (qtd_vezes_mesma_tecla_pressionada>Letras_por_tecla-1) && caractere_recebido == '9')){
									TMR1ON=0;
									TMR1H=TMR1L=0;
									qtd_vezes_mesma_tecla_pressionada=0;}
								}
							
						else{TXREG = caractere_recebido;}

					ultimo_caractere_recebido=caractere_recebido;
					

					PORTB_SR=PORTB;//leitura do PORTB antes de ativar a interrupção para evitar uma interrupção não desejada.
					RBIE=1;
					debounce=0;
		}

		if(receber==0 && enviar==0 && RBIE){ //garante que o 18F4550 entre em modo idle com as interrupções ativadas(RBIE pode estar zerado pelo tratamento de debounce)
				SLEEP();
				NOP();}

}
}
