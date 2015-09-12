#include <xc.h>
#include <string.h>
#include <stdio.h>
#include "encrypt.h"
#include "ascii.h"
#include "eeprom_interna.h"
#include "time.h"
#include "main.h"
#include "serial.h"
#include "lcd.h"
#include "flags.h"
#include "recebimento_dados.h"

//CONFIGURA��O 18F4550

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



char qtd_max_dias =31;
char nova_senha[TAMANHO_SENHA]; //armazena temporariamente a nova senha atribuida a conta para garantir que a senha atual n�o seja lida no meio do processo de altera��o

char senha[QTD_MAX_CONTAS][TAMANHO_SENHA+1]; //SENHA+1 para compensar o caractere \0 que a string precisa ter 
unsigned char buffer_serial[TAMANHO_BUFFER_SERIAL]; //Usado para receber dados pela porta serial
unsigned char buffer_teclado_matricial[TAMANHO_BUFFER_TECLADO_MATRICIAL]; // Usado para receber dados pelo teclado matricial
unsigned char qtd_caracteres_recebidos_serial=0; //contador para caracteres recebidos pela porta serial
unsigned char qtd_caracteres_recebidos_teclado=0; //contador para caracteres recebidos pelo teclado matricial 


//char dados_recebidos[41];
//char chave_criptografia[17];
//char texto_critografado[81];
//char texto_descriptografado[41];

struct Data{
	unsigned char ano;//0
	unsigned char mes;//1
	unsigned char dia;//2
	unsigned char hora;//3
	unsigned char minuto;//4
	unsigned char segundo;//5
	unsigned char dia_da_semana;//6
		}data_atual,data_recebida;
					//data_recebida n�o utilizada no momento 

unsigned char caractere_recebido = 0; //Caractere recebido pelo teclado matricial
unsigned char FLAGS_1=0; //Vide main.h para ver as flags de cada vari�vel
unsigned char FLAGS_2=0; //
unsigned char FLAGS_3=0; //
unsigned char PORTB_SR;// Shadow register para leitura do PORTB e atualiza��o do LATB
unsigned char num_interrupt_timer1=0;
unsigned char num_interrupt_caracter_por_asterisco=0;
unsigned char qtd_vezes_mesma_tecla_pressionada=0;
unsigned int endereco_inic_eeprom=5;
unsigned int endereco_final_eeprom=5;


char *ptr_data;


//REPRESENTA��O DO TECLADO MATRICIAL NO MODO_T9

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

		while(*string_a_zerar != NULL){
			*string_a_zerar=0;
			string_a_zerar++;}

}

void interrupt aux(void){

			if(TMR1IE && TMR1IF){ 
				TMR1IF=0;
				TMR1H=0xC0;//Equivalente a fazer TMR1+=0xC0,�j� que se est� deixando o TRMR1L correr

				if(MODO_BLUETOOTH){//O dispostivo iniciou comunica��o com o PIC mas ficou mais de 500ms sem termin�-la
						qtd_caracteres_recebidos_serial=0;
						setar_bit(FLAGS_1,ERRO_SESSAO_EXPIRADA);
						setar_bit(FLAGS_2,ENVIAR);
						TMR1ON=0;
						}

				

				else if(MODO_TECLADO_MATRICIAL && ++num_interrupt_timer1==5){//Passou-se 2,5s ap�s a primeira vez que o bot�o foi apertado.
					if(testar_bit(FLAGS_2,MODO_T9)){setar_bit(FLAGS_2,RECEBER);}
					lcd_gotoxy(LINHA2,qtd_caracteres_recebidos_teclado);
					printf("*");
					TMR1ON=0;
					num_interrupt_timer1=0;}
							
			}
			
			if(TMR0IE && TMR0IF){
					
					setar_bit(FLAGS_2,EXIBIR);
					setar_bit(FLAGS_3,ATUALIZAR_HORA_DISPLAY);
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

			

			if(RBIE && RBIF){
					char coluna,linha=0;
					PORTB_SR=(PORTB&0xF0);  //PORTB_SR n�o recebe os 4 primeiros bits do PORTB, pois � usado apenas para mudan�a de n�vel, que utiliza os 4 ultimos;
					RBIF=0;
					if(PORTB_SR != 0xF0) {
							RBIE=0;
							setar_bit(FLAGS_2,DEBOUNCE); //Tratamento de repique
							modo_teclado_matricial();
							LATDbits.LD0^=1;
	
							//detec��o de coluna
							if(COLUNA_1==0){coluna=1;} 

							else if(COLUNA_2==0){coluna=2;}

							else if(COLUNA_3==0){coluna=3;}

							else if(COLUNA_4==0){coluna=4;}

							else{coluna=0;}//Houve algum problema na detec��o de qual coluna est� a tecla pressionada
						
						
						TRISB&=0x0F; //TRISB 4 ultimos bits como sa�da, 4 primeiros inalterados; 
						LATB|=0xF0;  //LATB 4 ultimos bits em 1, 4 primeiros inalterados;
						

						while(PORTB&0xF0 !=	0xF0){}  //Prende-se o programa nesse la�o at� que os 4 ultimos bits do PORTB estejam de fato em 1
						while( (PORTD&0xF0) != 0){}  //Prende-se o programa at� que os 4 ultimos bits do PORTD tenham pelo menos 1 diferente de 1

						TRISD|=0xF0; //4 ultimos bits como entrada para se verificar qual deles est� em 1. 
						
						//LB4<>LD4, LB5<>LD5, LB6<>LD6,LB7<>LD7
	
							if(LINHA_1==1){linha=1;}

							else if(LINHA_2==1){linha=2;}

							else if(LINHA_3==1){linha=3;}

							else if(LINHA_4==1){linha=4;}
							
							else{linha=0;}//Houve algum problema na detec��o de qual linha est� a tecla pressionada

							if(linha && coluna){//N�o faz nada se houve algum erro na detec��o da linha ou da linha

								caractere_recebido = teclado_matricial(coluna,linha);
								
											}
						
							
					
						TRISB|=0xF0;//
						LATD&=0x0F;//
						TRISD&=0X0F; //

						while( (PORTD&0xF0) != 0x00){}//
						while( (PORTB&0xF0) != 0xF0){}// Configura��o inicial dos PORTS e TRISs
								
					}

					PORTB_SR=(PORTB&0xF0);}

			if(RCIE && RCIF){
					modo_bluetooth();

					if(OERR==1){
						setar_bit(FLAGS_1,ERRO_COMUNICACAO);
						char temp;
						do{ 
				            temp = RCREG; 
				            CREN = 0; 
				            CREN = 1;
							if(temp){}
 
				          }while(OERR);

						setar_bit(FLAGS_2,ENVIAR);
						resetar_bit(FLAGS_2,RECEBER);
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

								setar_bit(FLAGS_2,ENVIAR);
								resetar_bit(FLAGS_2,RECEBER);}
					
					else{							
							resetar_timer1(0xC0,0);
							buffer_serial[qtd_caracteres_recebidos_serial] = RCREG;
						
							TMR1ON=1;

							if(++qtd_caracteres_recebidos_serial == TAMANHO_BUFFER_SERIAL || buffer_serial[qtd_caracteres_recebidos_serial-1] == FIM){
									setar_bit(FLAGS_2,RECEBER);
									resetar_timer1(0xC0,0);}
						}

					RCIF=0;}

}


int main(void){

	//VARIAVEIS LOCAIS MAIN

	unsigned char ordem = 0;//usada para compararar uma sequ�ncia de dados recebidos com uma string.
	unsigned char etapa=0;
	unsigned char funcao=0;//utilizada para determinar qual fun��o o PIC vai executar (abrir porta, fornecer hist�rico, fornecer status atual)
	unsigned char conta=0;
	unsigned char conta_a_ser_alterada=0;
	unsigned char cont=0;
	unsigned char qtd_total_contas=0;	
	unsigned char ultimo_caractere_recebido=0;
	int contas_cadastradas=0; //16bits que correspondem cada um a uma conta cadastrada ou n�o. Exemplo: bit 7 indica se a conta 7 existe ou ainda n�o tem uma senha cadastrada
	//CONFIGURA��O OSCILADOR
	OSCCON=0XF0;

	//CONFIGURA��O INTERRUP��ES
	INTCON = 0b11100000;
	INTCON2 =0b00000000;
	PIE1=0b00100001;
	RCONbits.IPEN = 0;

	
	//CONFIGURA��O TIMER0(CONTAGEM HORAS)
	T0CON = 0b10000111;
	TMR0H=0xC2; //TMR0=34446(1 interrup��o = 1s para FOSC=16MHz)
	TMR0L= 0xF7;

	//CONFIGURA��O DAS PORTAS
	LATD=0; //4 primeiros bits = LEDs para debug(indicam se algo aconteceu, como o pressionamento do bot�o do teclado matricial ou o funcionamento do timer0(rel�gio) )
			//4 ultimos bits -> Teclado matricial
	
	
	TRISB=0xF0; // 4 ultimos bits-> teclado matricial
	TRISA=0x00;
	TRISE=0X04;
	LATB=0x0F; 
	TRISC=0xCF;
	TRISD=0x00;
	ADCON1=0XFF;
	CMCON=0X07;

	//CONFIGURA��O TIMER1(CONTAGEM DE TEMPO NO MODO_T9 E CONTAGEM DE TEMPO PARA SESSAO EXPIRADA)
	T1CON = 0b00001110;
	TMR1H=0XC0; //TMR1 = 49152 (1 interrup��o = 0.5s para cristal de 32,768khz)
	TMR1L=0;
	TMR1IE=0;

	//CONFIGURA��O INICIAL DA EEPROM
	if(eeprom_read(ENDERECO_INICIAL) == VALOR_INICIAL)	eeprom_config_inicial(); 

	config_serial(35); //SPBRG(vari�vel para baud rate) = 35;


	qtd_total_contas = verificar_num_contas();

	
	enviar_caractere_serial(NOVA_LINHA);

	numero_para_ascii(qtd_total_contas);

		for(conta=0;conta<qtd_total_contas;conta++){
				carregar_senha(conta,senha); 

				enviar_string_serial(&senha[conta][0]);//Envio por serial da senha e nivel de acesso para debug
				numero_para_ascii(nivel_acesso);
		
				setar_bit(contas_cadastradas,conta);
				}


	conta=0;
	RCIE=1;
	__delay_us(1);
	data_atual.ano=0;
	data_atual.mes= Janeiro;
	data_atual.dia=1;
	data_atual.dia_da_semana= dia_da_semana(data_atual.ano,data_atual.mes,data_atual.dia);
	data_atual.hora=0;
	data_atual.minuto=0;
	data_atual.segundo=0;
	PORTB_SR=PORTB;//Leitura do PORTB antes de habilitar a interrup��o para evitar uma interrup��o n�o desejada.
	RBIE=1;
	RBIF=0;
	cont=0;

	lcd_init(LCD_20X4);
	lcd_gotoxy(LINHA1,20);
	printf("%c",SENSOR_ABERTURA_FECHADURA);
	lcd_gotoxy(LINHA1,1);
	LCD_RS=1;
	printf("%d",PORTE);

	RCIE=0;
	delay_ms(600);
	enviar_string_serial("AT");
	delay_ms(600);
	enviar_string_serial("AT+NAMEMODULO2_V4");
	delay_ms(600);
	while(1){

		if(testar_bit(FLAGS_2,RECEBER)){ //OBSERVA��O: O PROTOCOLO SEGUIDO AO RECEBER OS DADOS PELA SERIAL E PELO TECLADO MATRICIAL S�O DIFERENTES, VIDE PROTOCOLO.TXT EM
																																	//CASO DE D�VIDAS
			
			resetar_bit(FLAGS_2,RECEBER);
			if(MODO_BLUETOOTH){

				enviar_caractere_serial(NOVA_LINHA);

				enviar_string_serial(buffer_serial);

				enviar_caractere_serial(NOVA_LINHA);

				char *ptr_caractere_recebido_serial = &buffer_serial[0];

				char i;
				//In�cio da an�lise dos dados recebidos
				for(i=0;i<qtd_caracteres_recebidos_serial;i++){
					if(FLAGS_1>1){
						break;}

					else if(*ptr_caractere_recebido_serial == PROXIMA_ETAPA){
					
						if(etapa == etapa_login && senha[conta][ordem]!= NULL) setar_bit(FLAGS_1,ERRO_SENHA);
						etapa++;
						ordem=0;}

					else if(etapa == etapa_inicial){
						if( (*ptr_caractere_recebido_serial) != INICIO) setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

					else if(etapa == etapa_recebe_funcao){//recebe-se a funcao a ser executada, conta a realizar o acesso e confirma-se se essa � a fechadura correta
					
						funcao = *ptr_caractere_recebido_serial++;
						

						if( (*ptr_caractere_recebido_serial) != NUMERO_DESSA_FECHADURA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

						conta = ascii_para_numero('0', *(++ptr_caractere_recebido_serial),*(++ptr_caractere_recebido_serial));

						
						

						if(conta> QTD_MAX_CONTAS || !(testar_bit(contas_cadastradas,conta)) ) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);

						if( FUNCAO_NAO_AUTORIZADA ){ //A conta n�o est� autorizada a realizar essa funcao
							setar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);} 	
						}

					else if(etapa == etapa_login){		
						if(*ptr_caractere_recebido_serial !=  senha[conta][ordem]) setar_bit(FLAGS_1,ERRO_SENHA);
		
						if(++ordem == TAMANHO_SENHA-1) setar_bit(FLAGS_1,ERRO_PROTOCOLO);

					}

					else if(etapa == etapa_detalha_funcao){

						if(funcao == ABERTURA_PORTA || funcao == REQUERIMENTO_STATUS_ATUAL){
							if(*ptr_caractere_recebido_serial != ('N'+ordem)) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
							ordem++;
						}

						else if(funcao >= MUDAR_SENHA_OUTRA_CONTA){ //Fun��es '6' e '7'. Fun��o '7' == alterar a senha da pr�pria conta

							if(!ordem) {
								if(funcao == MUDAR_SENHA_PROPRIA_CONTA) conta_a_ser_alterada=conta; 

								else{ conta_a_ser_alterada = ascii_para_numero(NULL,NULL,*ptr_caractere_recebido_serial++);}

							}

							nova_senha[ordem] = *ptr_caractere_recebido_serial;

							if(++ordem == TAMANHO_SENHA) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
						}
							
			
					}

					else if(etapa == etapa_final){
						if( (*ptr_caractere_recebido_serial) != FIM) setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

					
					ptr_caractere_recebido_serial++;
	
				

				}//Fim da an�lise dos dados recebidos
				
				
				qtd_caracteres_recebidos_serial=0;
				setar_bit(FLAGS_2,ENVIAR);
				
			}

				else if(MODO_TECLADO_MATRICIAL){
							
							if(testar_bit(FLAGS_2,MODO_T9)){
								resetar_timer1(0xC0,0);
								

								if(qtd_vezes_mesma_tecla_pressionada>0 && ultimo_caractere_recebido >='0' && ultimo_caractere_recebido<='9'){ //garante que somente caracteres dentro 
																																			  //desse intervalo sejam recebidos efetivamente

											buffer_teclado_matricial[qtd_caracteres_recebidos_teclado]= ('a' -1) + qtd_vezes_mesma_tecla_pressionada + (( ultimo_caractere_recebido - '1') * Letras_por_tecla) ;
											qtd_vezes_mesma_tecla_pressionada=0;
										
									if(ultimo_caractere_recebido != caractere_recebido) { 
														ultimo_caractere_recebido = caractere_recebido;
														TMR1ON=1; 
										//O recebimento ocorreu porque o usu�rio apertou, no modo t9, uma tecla diferente da anterior
										//Reativa-se o timer para que, caso  o usu�rio fique muito tempo sem digitar o programa considere como recebido o caractere
											}
									else ultimo_caractere_recebido=0;

												}

								else{ //se o modo_t9 estiver on mas o usu�rio apertou a tecla uma �nica vez para inserir um n�mero
										buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] = caractere_recebido;
										
									}
										
								}

								
							
						
							else{ //Se modo_t9 estiver off, n�o h� necessidade de fazer qualquer l�gica antes de armazen�-lo no buffer
									buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] = caractere_recebido;
								}

							
						
							qtd_vezes_mesma_tecla_pressionada=0;
							caractere_recebido=0;


							//compara��o com senha recebida
							printf("\n\n%s",buffer_teclado_matricial);

							if(buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] != FIM){

										if(qtd_caracteres_recebidos_teclado){			
											lcd_gotoxy(LINHA2,qtd_caracteres_recebidos_teclado); 
											printf("*%c",buffer_teclado_matricial[qtd_caracteres_recebidos_teclado]);
											TMR1ON=1;}
			
										else{
											lcd_gotoxy(LINHA2,(qtd_caracteres_recebidos_teclado+1));
											printf("%c",buffer_teclado_matricial[qtd_caracteres_recebidos_teclado]);
											TMR1ON=1;}
							}


							if(	buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] == FIM || ++qtd_caracteres_recebidos_teclado==(TAMANHO_BUFFER_TECLADO_MATRICIAL-1)){
		
										resetar_timer1(0xC0,0);//Reseta timer para evitar que o caractere F seja impresso ou que um asterisco seja por algum erro no programa
										buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] = 0;
										

										conta = ( ((buffer_teclado_matricial[0]-'0')*10)  + (buffer_teclado_matricial[1]-'0') );
										cont=2;

										if(!(conta<QTD_MAX_CONTAS)) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA); //N� da conta fora do intervalo

												//N� dentro do intervalo, mas a conta n�o existe.S� � feito exce��o a cadastro de contas, que																			
												//usa a fun��o de mudar senha de outra conta

												else if(funcao != MUDAR_SENHA_OUTRA_CONTA && (!testar_bit(contas_cadastradas,conta)) ){ 
													setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);} 

									  	//cont inicia em 2 porque a senha do usu�rio no buffer do teclado matricial inicia em
										//buffer_teclado_matricial[2]

										
										if(qtd_caracteres_recebidos_teclado<(TAMANHO_MINIMO_SENHA+2)){setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
										limpar_linha(LINHA2);
										
										while(cont<(TAMANHO_SENHA+2) && buffer_teclado_matricial[cont-2] != 0 && FLAGS_1<2){
											
											//enviar_caractere_serial(senha[conta][cont-2]);
											//enviar_caractere_serial(buffer_teclado_matricial[cont]);

											if(buffer_teclado_matricial[cont] != senha[conta][cont-2]){
												setar_bit(FLAGS_1,ERRO_SENHA);
												}

											cont++;
										}

										setar_bit(FLAGS_2,EXIBIR);
										setar_bit(FLAGS_2,ENVIAR);
										
							}				
						}

			}

		
		if(testar_bit(FLAGS_2,ENVIAR)){//Envio, ao usu�rio, do resultado do acesso(teclado matricial ou bluetooth). Aqui ser� enviado se ele conseguiu acesso e p�de abrir a porta.
			
								
			resetar_bit(FLAGS_2,ENVIAR);
			qtd_caracteres_recebidos_serial, qtd_caracteres_recebidos_teclado,cont=0;
			etapa = etapa_inicial;
			zerar_string(buffer_serial);
			zerar_string(buffer_teclado_matricial);
			

				if(MODO_TECLADO_MATRICIAL){

						if(FLAGS_1<2) { //N�o houve erros
												

												limpar_linha(LINHA3);
												printf("\n\nDestravando...");
												__delay_ms(49);
												delay_ms(800);	
												char tentativas=0;

													while(FECHADURA_TRAVADA){
														if(++tentativas == 6){ 
															setar_bit(FLAGS_1,ERRO_ABERTURA); //A fechadura n�o abriu ap�s 6 tentativas. N�o h� como saber, pelo atual software, a causa.
															break;}
	
														FECHADURA=1;
														delay_ms(350);
															if(FECHADURA_TRAVADA) delay_ms(100);//prepara��o para pr�xima tentativa 
														FECHADURA=0;
															}
												
														
												lcd_gotoxy(LINHA1,20);
												printf("%c",SENSOR_ABERTURA_FECHADURA);

												limpar_linha(LINHA3);								
												if(FECHADURA_TRAVADA){
														printf("\n\nErro de abertura");}
		
												else{
														printf("\n\nPorta aberta");}

										}

										else{//Houve erros, de senha ou de protocolo.
											limpar_linha(LINHA3);
												if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)) printf("\n\nErro de protocolo");

												else if(testar_bit(FLAGS_1,ERRO_IDENTIF_CONTA)) printf("\n\nConta nao existente");

												else if(testar_bit(FLAGS_1,ERRO_SENHA))	printf("\n\nSenha incorreta");}
				}				

		else{

					enviar_string_serial("\nI");

						if(!FLAGS_1){//N�o houve erros
										etapa = etapa_inicial;
										LATDbits.LD2^=1;
										enviar_string_serial("OK");

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


												else if(funcao == MUDAR_SENHA_PROPRIA_CONTA || funcao == MUDAR_SENHA_OUTRA_CONTA){
													
													setar_bit(contas_cadastradas,conta_a_ser_alterada); //seta-se o bit correspondente a conta que sera alterada para marcar
																										//que ela existe.Se j� existir mantem-se em 1.
													char i=0;
														do{
															senha[conta_a_ser_alterada][i] = nova_senha[i];
															eeprom_write(((conta_a_ser_alterada*16) + i),nova_senha[i]);
															while(WR){}
															i++;} while(nova_senha[i-1]  && i<TAMANHO_SENHA);
														}
							
												else if(funcao == ABERTURA_PORTA){
													 RD0=1;
													 	delay_ms(400);
													RD0=0;}

										}
						
						else{//Houve erros
							
							enviar_caractere_serial('E');
								if(testar_bit(FLAGS_1,ERRO_SESSAO_EXPIRADA)){
											enviar_string_serial("SE");}
							
								if(testar_bit(FLAGS_1,ERRO_ABERTURA)){
											enviar_caractere_serial('A');}
	
								if(testar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO)){
											enviar_caractere_serial('N');}
	
								if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)){ 		
											enviar_caractere_serial('P');}
	
								if(testar_bit(FLAGS_1,ERRO_COMUNICACAO)){
											enviar_caractere_serial('C');}
							
								if(testar_bit(FLAGS_1,ERRO_SENHA)){
											enviar_caractere_serial('S');}
					
								if(testar_bit(FLAGS_1,ERRO_IDENTIF_CONTA)){ 
											enviar_caractere_serial('I');}
							
						 FLAGS_1=0;}

							
															
				enviar_caractere_serial(FIM);	
				PORTB_SR = PORTB; //Reativa a interrup��o por mudan�a de n�vel ,liberando o acesso pelo teclado
				RBIE=1;
		}

		}

		if((PORTB&0xF0) == 0xF0 && RBIE==0 && testar_bit(FLAGS_2,DEBOUNCE) && MODO_TECLADO_MATRICIAL){//Tratamento de debounce. Espera-se at� que nenhum bot�o esteja pressionado e que o debounce esteja autorizado
																			//(existem situa��es em que RBIE=0 e n�o se quer fazer tratamento de debounce
					delay_ms(100);
						if(caractere_recebido < '0' || caractere_recebido > '9'){//Caracteres n�o s�o armazenados, pois s�o fora da faixa de 0 a 9.S�o utilizados para certas fun��es
																					//como indicar maiuscula, ativar modo_t9, etc.
									
									resetar_timer1(0xC0,0);	//Para evitar que o timer d� uma interrup��o e receba o caracter
									ultimo_caractere_recebido = caractere_recebido; //atualiza ultimo caractere recebido
									
						
							if(caractere_recebido == FIM){
								setar_bit(FLAGS_2,RECEBER);}
	
							else if(caractere_recebido == MODO_T9_ON_OFF){
								inverter_bit(FLAGS_2,MODO_T9);}
	
							else if(caractere_recebido == MAIUSCULA_MINUSCULA){
								inverter_bit(FLAGS_2,MAIUSCULA);}

							else if(caractere_recebido == VOLTAR_CARACTERE){//Retorna o indice do buffer em 1  p�e-se um zero nele para que se "retire" o caractere que tenha ali

								if(qtd_caracteres_recebidos_teclado) qtd_caracteres_recebidos_teclado--;
								buffer_teclado_matricial[qtd_caracteres_recebidos_teclado]=0;
								
								lcd_gotoxy(LINHA2,qtd_caracteres_recebidos_teclado); printf(" ");
								}			
						

						}


						else{
								if(testar_bit(FLAGS_2,MODO_T9)){//modo t9 on
									if(ultimo_caractere_recebido == caractere_recebido){
											if(++qtd_vezes_mesma_tecla_pressionada == Letras_por_tecla || ((qtd_vezes_mesma_tecla_pressionada==2) && caractere_recebido == '9')) 
												setar_bit(FLAGS_2,RECEBER);
												}
								

									else { //modo t9 off
										if(qtd_vezes_mesma_tecla_pressionada) setar_bit(FLAGS_2,RECEBER); 
										
										else ultimo_caractere_recebido = caractere_recebido; //atualiza ultimo caractere recebido
										}
								}

								else setar_bit(FLAGS_2,RECEBER);
									
						}
					
						
					while(PORTB&0xF0 != 0xF0){}

					if(testar_bit(FLAGS_2,MODO_T9)) {TMR1ON=1;}

					PORTB_SR=PORTB;//leitura do PORTB antes de ativar a interrup��o para evitar uma interrup��o n�o desejada.
					RBIE=1;
		}


		if(testar_bit(FLAGS_2,EXIBIR)){
			resetar_bit(FLAGS_2,EXIBIR);
			if(testar_bit(FLAGS_3,ATUALIZAR_HORA_DISPLAY)){
				printf("\n\n\n%02d:%02d:%02d-%02d.%02d.%02d",data_atual.hora,data_atual.minuto,data_atual.segundo, data_atual.dia,data_atual.mes,((data_atual.ano+15)%100) );
				resetar_bit(FLAGS_3,ATUALIZAR_HORA_DISPLAY);
			}
			

			}

			if( (!testar_bit(FLAGS_2,EXIBIR))&& (!testar_bit(FLAGS_2,RECEBER)) && (!testar_bit(FLAGS_2,ENVIAR)) && RBIE && RCIE){ //garante que o 18F4550 entre em modo idle com as interrup��es ativadas(RBIE pode estar zerado pelo tratamento de debounce)
				SLEEP();
				NOP();}



}
}
