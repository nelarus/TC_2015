
#include <xc.h>
#include <delays.h>
#include <string.h>
#include "main.h"
#include "serial.h"
#include "encrypt.h"
#include "ascii.h"
#include "time.h"
#include "eeprom_interna.h"
#include "funcoes_serial.h"


#pragma config FOSC =  XTPLL_XT
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

#define conta_admin 0
#define nivel_acesso ((conta*TAMANHO_SENHA)+ (TAMANHO_SENHA-1))

char qtd_max_dias =31;
char nova_senha[TAMANHO_SENHA];
char senha[QTD_MAX_CONTAS][TAMANHO_SENHA+1];
unsigned char buffer_serial[TAMANHO_BUFFER_SERIAL]; //Usado para receber dados pela porta serial
unsigned char buffer_teclado_matricial[TAMANHO_BUFFER_TECLADO_MATRICIAL];
unsigned char qtd_caracteres_recebidos_serial=0;
unsigned char qtd_caracteres_recebidos_teclado=0;
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
unsigned char FLAGS_2=0;
unsigned char PORTB_SR;
unsigned char num_interrupt_timer1=0;
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


					
void zerar_string(char *string_a_zerar){
		memset(string_a_zerar,0, strlen(string_a_zerar));}





void interrupt aux(void){

			if(TMR1IE && TMR1IF){
				TMR1IF=0;
				TMR1H=0xC0;

				if(MODO_BLUETOOTH){//O dispostivo iniciou comunicação com o PIC mas ficou mais de 500ms sem terminá-la
						qtd_caracteres_recebidos_serial=0;
						setar_bit(FLAGS_1,ERRO_PROTOCOLO);
						enviar=1;
						TMR1ON=0;
						}


				else if(MODO_TECLADO_MATRICIAL && ++num_interrupt_timer1==10){//Passou-se 5s após a primeira vez que o botão foi apertado.
					receber=1;
					TMR1ON=0;
					num_interrupt_timer1=0;}
							
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
							modo_teclado_matricial()
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
								numero_para_ascii(coluna);

						
									if(caractere_recebido == MODO_T9_ON_OFF){
											inverter_bit(FLAGS_2,MODO_T9);}

									else if(caractere_recebido == MAIUSCULA_MINUSCULA){
											inverter_bit(FLAGS_2,MAIUSCULA);}
								
											}
						
									if(testar_bit(FLAGS_2,MODO_T9)) {TMR1ON=1;}
					
						TRISB|=0xF0;
						LATD&=0x0F;
						TRISD&=0X0F;

						while( (PORTD&0xF0) != 0x00){}
						while( (PORTB&0xF0) != 0xF0){}
								
					}

					PORTB_SR=(PORTB&0xF0);}

			if(RCIE && RCIF){
					modo_bluetooth();
					RBIE=0;

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
							TMR1ON=0;
							buffer_serial[qtd_caracteres_recebidos_serial] = RCREG;
							TMR1ON=1;
							LATDbits.LD0^=1;
							if(++qtd_caracteres_recebidos_serial == TAMANHO_BUFFER_SERIAL || buffer_serial[qtd_caracteres_recebidos_serial-1] == FIM){
									receber=1;
									TMR1ON=0;
									TMR1L=0;
									TMR1H=0xC0;}
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
	LATD=0; //4 primeiros bits = LEDs para debug(indicam se algo aconteceu, como o pressionamento do botão do teclado matricial ou o funcionamento do timer0(relógio) )
			//4 ultimos bits -> Teclado matricial
	
	
	TRISB=0xF0; // 4 ultimos bits-> teclado matricial
	LATB=0x0F; 
	TRISC=0xC3;
	TRISD=0x00;
	ADCON1=0XFF;
	CMCON=0X07;

	//CONFIGURAÇÃO TIMER1(CONTAGEM DE TEMPO NO MODO_T9)
	T1CON = 0b00001110;
	TMR1H=0XC0; //TMR1 = 49152 (1 interrupção = 0.5s para cristal de 32,768khz)
	TMR1L=0;


	if(eeprom_read(0) == 0xFF){eeprom_config_inicial();}

	configurar_serial(35);

	qtd_total_contas = verificar_num_contas();
	numero_para_ascii(qtd_total_contas);

		for(conta=0;conta<qtd_total_contas;conta++){
				carregar_senha(conta, senha);}

	conta=0;
	RCIE=1;

	data_atual.ano=0;
	data_atual.mes= Janeiro;
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

		if(receber == 1){ //OBSERVAÇÃO: O PROTOCOLO SEGUIDO AO RECEBER OS DADOS PELA SERIAL E PELO TECLADO MATRICIAL SÃO DIFERENTES, VIDE PROTOCOLO.TXT EM
																																	//CASO DE DÚVIDAS
			
			receber=0;
			if(MODO_BLUETOOTH){

				enviar_caractere_serial(NOVA_LINHA);

				enviar_string_serial(buffer_serial);

				enviar_caractere_serial(NOVA_LINHA);
		
					for(cont=0;cont<qtd_caracteres_recebidos_serial;cont++){
	
		
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
												enviar=1; receber=qtd_caracteres_recebidos_serial=0;}
				
									
									
									if(FLAGS_1>3) {
													resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
													enviar_caractere_serial( '0' + etapa);
													etapa = etapa_inicial;	
													enviar=1;
													receber=qtd_caracteres_recebidos_serial=0;}
		
																			}		
					}

				else if(MODO_TECLADO_MATRICIAL){

							if(testar_bit(FLAGS_2,MODO_T9)){

								enviar_caractere_serial(NOVA_LINHA);

								numero_para_ascii(ultimo_caractere_recebido);
								numero_para_ascii(qtd_vezes_mesma_tecla_pressionada);

								buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] = (caractere_recebido + (48*TMR1ON) + qtd_vezes_mesma_tecla_pressionada);
								qtd_vezes_mesma_tecla_pressionada=0;
								TMR1ON=0;
								TMR1H=0xC0;
								TMR1L=0;}

								
							


							else{ buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] = caractere_recebido;}

								enviar_caractere_serial( buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] );
								

							if(	buffer_serial[qtd_caracteres_recebidos_teclado] == FIM || ++qtd_caracteres_recebidos_teclado<TAMANHO_BUFFER_TECLADO_MATRICIAL){

										conta = ((buffer_teclado_matricial[0]*10) + buffer_teclado_matricial[1]);
										cont=2;
										
										while(cont<2+TAMANHO_SENHA && buffer_teclado_matricial[cont-2] != NULL){

											if(buffer_teclado_matricial[cont] != senha[conta][cont-2]){
												setar_bit(FLAGS_1,ERRO_SENHA);}

											cont++;
										}
							}				
										

				}

			}

		
		if(enviar==1){
			enviar=0;
			qtd_caracteres_recebidos_serial=0;
			etapa = etapa_inicial;
			cont=0;
			enviar_caractere_serial(NOVA_LINHA);
			enviar_caractere_serial(INICIO);

						if(FLAGS_1<4 && etapa == etapa_final){ //Não houve erros
										etapa = etapa_inicial;
										LATDbits.LD2^=1;

										char OK[] = {"OK"};
										enviar_string_serial(OK);

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
						
						LATDbits.LD3^=1;

							if(testar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO)){

												char EN[] = {"EN"};
												enviar_string_serial(EN); 
												resetar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);}

							if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)){ 

												char EP[] = {"EP"};
												enviar_string_serial(EP);
													if(funcao == MUDAR_SENHA){
																TXREG = 'S'; //indica que a nova senha tem menos que 6 caracteres;
																while(!TRMT){} 
														} 
												
												resetar_bit(FLAGS_1,ERRO_PROTOCOLO);}

							if(testar_bit(FLAGS_1,ERRO_COMUNICACAO)){
											
											char EC[] = {"EC"};
											enviar_string_serial(EC);
											resetar_bit(FLAGS_1,ERRO_COMUNICACAO);}
						
				
							if(testar_bit(FLAGS_1,ERRO_SENHA)){
											char ES[] = {"ES"};
											enviar_string_serial(ES);
											resetar_bit(FLAGS_1,ERRO_SENHA);}
				
							if(testar_bit(FLAGS_1,ERRO_IDENTIF_CONTA)){ 
											char EI[] = {"EI"};
											enviar_string_serial(EI);
											resetar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);}
								}
															


				enviar_caractere_serial(FIM);
				PORTB_SR = PORTB;
				RBIE=1;}



		if((PORTB&0xF0) == 0xF0 && RBIE==0 && debounce==1 && MODO_TECLADO_MATRICIAL){//Tratamento de debounce. Espera-se até que nenhum botão esteja pressionado e que o debounce esteja autorizado
																			//(existem situações em que RBIE=0 e não se quer fazer tratamento de debounce
					delay_ms(60);

						if(!(testar_bit(FLAGS_2,MODO_T9))){//Modo_t9 desativado, o caractere_recebido é armazenado diretamente
								receber=1;
							}

						else if(caractere_recebido == MODO_T9_ON_OFF ||caractere_recebido == MAIUSCULA_MINUSCULA){//Caracteres não são armazenadas
									NOP();}


						else if(caractere_recebido == ultimo_caractere_recebido){

								if(++qtd_vezes_mesma_tecla_pressionada > Letras_por_tecla || ( (qtd_vezes_mesma_tecla_pressionada>Letras_por_tecla-1) && caractere_recebido == '9')){
									TMR1ON=0;
									TMR1H=0xC0;
									qtd_vezes_mesma_tecla_pressionada=0;}

								else  ultimo_caractere_recebido= caractere_recebido; //atualiza ultimo caractere recebido

								}
							
						

						else if(testar_bit(FLAGS_2,MODO_T9)){ //caractere_recebido != do ultimo caractere recebido e modo t9 ativado

								if(qtd_vezes_mesma_tecla_pressionada>0) receber=1; 

								ultimo_caractere_recebido= caractere_recebido;//atualiza ultimo caractere recebido
								 
								
						}
					

					PORTB_SR=PORTB;//leitura do PORTB antes de ativar a interrupção para evitar uma interrupção não desejada.
					RBIE=1;
					debounce=0;
		}

			if(receber==0 && enviar==0 && RBIE && RCIE){ //garante que o 18F4550 entre em modo idle com as interrupções ativadas(RBIE pode estar zerado pelo tratamento de debounce)
				SLEEP();
				NOP();}

}
}
