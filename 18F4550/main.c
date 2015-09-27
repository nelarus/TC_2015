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

//INICIO CONFIGURAÇÃO 18F4550

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
//


//VARIÁVEIS GLOBAIS

//MATRIZES
char nova_senha[TAMANHO_SENHA]; //armazena temporariamente a nova senha atribuida a conta para garantir que a senha atual não seja lida no meio do processo de alteração
char senha[QTD_MAX_CONTAS][TAMANHO_SENHA+3]; //SENHA+3 para compensar o caractere \0 que a string precisa ter(indice=16) e o caractere que representa o nivel de acesso(indice=17)
char parametro_configuracao_modulo_bt[TAMANHO_PARAMETRO_BT+1];

unsigned char buffer_serial[TAMANHO_BUFFER_SERIAL]; //Usado para receber dados pela porta serial
unsigned char buffer_teclado_matricial[TAMANHO_BUFFER_TECLADO_MATRICIAL]; // Usado para receber dados pelo teclado matricial
unsigned char qtd_caracteres_recebidos_serial=0; //contador para caracteres recebidos pela porta serial
unsigned char qtd_caracteres_recebidos_teclado=0; //contador para caracteres recebidos pelo teclado matricial 
char x=0;

//char dados_recebidos[41];
//char chave_criptografia[17];
//char texto_critografado[81];
//char texto_descriptografado[41];

//Fim declaração de matrizes

//Inicio Declaração de structs
Data data_recebida; //corpo declarado em time.h
//Fim Declaração de structs

//Inicio declaração de chars
unsigned char caractere_recebido = 0; //Caractere recebido pelo teclado matricial
unsigned char FLAGS_1=0; //Vide main.h para ver as flags de cada variável
unsigned char FLAGS_2=0; //
unsigned char FLAGS_3=0; //
unsigned char PORTB_SR;// Shadow register para leitura do PORTB e atualização do LATB
unsigned char num_interrupt_timer1=0;
unsigned char num_interrupt_caracter_por_asterisco=0;
char qtd_max_dias =31;
unsigned char qtd_vezes_mesma_tecla_pressionada=0;
//Fim declaração de chars

//Inicio declaração de inteiros
unsigned int endereco_inic_eeprom=5;
unsigned int endereco_final_eeprom=5;
//Fim declaração de inteiros




void zerar_string(char *string_a_zerar){

		while(*string_a_zerar != NULL){
			*string_a_zerar=0;
			string_a_zerar++;}

}

void interrupt aux(void){

			if(TMR1IE && TMR1IF){ 
				TMR1IF=0;
				resetar_timer1(0xC0,0);
				TMR1ON=1;

				if(MODO_BLUETOOTH){//O dispostivo iniciou comunicação com o PIC mas ficou mais de 500ms sem terminá-la
						qtd_caracteres_recebidos_serial=0;
						setar_bit(FLAGS_1,ERRO_SESSAO_EXPIRADA);
						setar_bit(FLAGS_2,ENVIAR);
						
						}

				else if(MODO_COMANDO_AT){
						resetar_bit(FLAGS_3,MODO_COMANDO_AT);
						qtd_caracteres_recebidos_serial=0;}

				else if(MODO_TECLADO_MATRICIAL){//Passou-se 2,5s após a primeira vez que o botão foi apertado.

					if(++num_interrupt_timer1==2){
						if(testar_bit(FLAGS_2,MODO_T9)){setar_bit(FLAGS_2,RECEBER);}
						lcd_gotoxy(LINHA3,qtd_caracteres_recebidos_teclado);
						printf("*");
						num_interrupt_timer1=0;}
					}
							
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
					PORTB_SR=(PORTB&0xF0);  //PORTB_SR não recebe os 4 primeiros bits do PORTB, pois é usado apenas para mudança de nível, que utiliza os 4 ultimos;
					RBIF=0;
					if(PORTB_SR != 0xF0) {
							RBIE=0;
							setar_bit(FLAGS_2,DEBOUNCE); //Tratamento de repique
							modo_teclado_matricial();
							LATDbits.LD0^=1;
	
							//detecção de coluna
							if(COLUNA_1==0){coluna=1;} 

							else if(COLUNA_2==0){coluna=2;}

							else if(COLUNA_3==0){coluna=3;}

							else if(COLUNA_4==0){coluna=4;}

							else{coluna=0;}//Houve algum problema na detecção de qual coluna está a tecla pressionada
						
						
						TRISB&=0x0F; //TRISB 4 ultimos bits como saída, 4 primeiros inalterados; 
						LATB|=0xF0;  //LATB 4 ultimos bits em 1, 4 primeiros inalterados;
						

						while(PORTB&0xF0 !=	0xF0){}  //Prende-se o programa nesse laço até que os 4 ultimos bits do PORTB estejam de fato em 1
						while( (PORTD&0xF0) != 0){}  //Prende-se o programa até que os 4 ultimos bits do PORTD tenham pelo menos 1 diferente de 1

						TRISD|=0xF0; //4 ultimos bits como entrada para se verificar qual deles está em 1. 
						
						//LB4<>LD4, LB5<>LD5, LB6<>LD6,LB7<>LD7
	
							if(LINHA_1==1){linha=1;}

							else if(LINHA_2==1){linha=2;}

							else if(LINHA_3==1){linha=3;}

							else if(LINHA_4==1){linha=4;}
							
							else{linha=0;}//Houve algum problema na detecção de qual linha está a tecla pressionada

							if(linha && coluna){//Não faz nada se houve algum erro na detecção da linha ou da linha

								caractere_recebido = teclado_matricial(coluna,linha);
								
											}						
					
						TRISB|=0xF0;//
						LATD&=0x0F;//
						TRISD&=0X0F; //

						while( (PORTD&0xF0) != 0x00){}//
						while( (PORTB&0xF0) != 0xF0){}// Configuração inicial dos PORTS e TRISs
								
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
					
					else{//Não ocorreu erros, recebe-se o dado					
							resetar_timer1(0xC0,0); 
							char RCREG_temp;
							RCREG_temp = RCREG;

//							if(MODO_COMANDO_AT){//No modo comando at o PIC recebe a resposta do módulo Bluetooth 
//																   //ao comando enviado anteriormente e repassa ao dispostivo sem realizar análise alguma
//								
//								TMR1ON=1;
//								if(++qtd_caracteres_recebidos_serial > 20 || !RCREG_temp) {//Considera o comando como encerrado ao receber 0 pela serial ou a resposta for maior do que 21 caracteres
//									resetar_bit(FLAGS_3,MODO_COMANDO_AT);
//									qtd_caracteres_recebidos_serial=0;
//									resetar_timer1(0xC0,0); 
//								}
//
//								enviar_caractere_serial(RCREG_temp);}
//								
//							else{
								buffer_serial[qtd_caracteres_recebidos_serial] = RCREG_temp;
								TMR1ON=1;
	
								if(++qtd_caracteres_recebidos_serial == TAMANHO_BUFFER_SERIAL || buffer_serial[qtd_caracteres_recebidos_serial-1] == FIM){
									setar_bit(FLAGS_2,RECEBER);
									resetar_timer1(0xC0,0);
								}
						
							//}

						}//Fim recebimento de dados

					RCIF=0;}

}


int main(void){

	//VARIAVEIS LOCAIS MAIN

	unsigned char ordem = 0;//usada para compararar uma sequência de dados recebidos com uma string.
	unsigned char etapa=0;
	unsigned char funcao=0;//utilizada para determinar qual função o PIC vai executar (abrir porta, fornecer histórico, fornecer status atual)
	unsigned char conta=0;
	unsigned char conta_a_ser_alterada=0;
	unsigned char comando_at=0;
	unsigned char cont=0;
	unsigned char qtd_total_contas=0;	
	unsigned char ultimo_caractere_recebido=0;
	unsigned char novo_nivel_acesso=0;
	int contas_cadastradas=0; //16bits que correspondem cada um a uma conta cadastrada ou não. Exemplo: bit 7 indica se a conta 7 existe ou ainda não tem uma senha cadastrada
	char *ptr_data;
	//CONFIGURAÇÃO OSCILADOR
	OSCCON=0XF0;

	//CONFIGURAÇÃO INTERRUPÇÕES
	INTCON = 0b11100000;
	INTCON2 =0b00000000;
	PIE1=0b00100001;
	RCONbits.IPEN = 0;
	
	//CONFIGURAÇÃO TIMER0(CONTAGEM HORAS)
	T0CON = 0b00000111;
	TMR0H=0xC2; //TMR0=34446(1 interrupção = 1s para FOSC=16MHz)
	TMR0L= 0xF7;

	//CONFIGURAÇÃO DAS PORTAS
	LATD=0; //4 primeiros bits = LEDs para debug(indicam se algo aconteceu, como o pressionamento do botão do teclado matricial ou o funcionamento do timer0(relógio) )
			//4 ultimos bits -> Teclado matricial
	
	
	TRISB=0xF0; // 4 ultimos bits-> teclado matricial
	TRISA=0x00;
	TRISE=0X04;
	LATB=0x00; 
	TRISC=0xCF;
	TRISD=0x00;
	ADCON1=0XFF;
	CMCON=0X07;

	//CONFIGURAÇÃO TIMER1(CONTAGEM DE TEMPO NO MODO_T9 E CONTAGEM DE TEMPO PARA SESSAO EXPIRADA)
	T1CON = 0b00001110;
	TMR1H=0XC0; //TMR1 = 49152 (1 interrupção = 0.5s para cristal de 32,768khz)
	TMR1L=0;
	TMR1IE=1;

	//CONFIGURAÇÃO INICIAL DA EEPROM
	if(eeprom_read(ENDERECO_INICIAL) == VALOR_INICIAL) eeprom_config_inicial(); 
	//
 
	
	config_serial(BAUD_115200);

	verificar_num_contas(&contas_cadastradas,&qtd_total_contas);

	enviar_caractere_serial(NOVA_LINHA);
	numero_para_ascii(contas_cadastradas);
	numero_para_ascii(qtd_total_contas);


		for(conta=0;conta<qtd_total_contas;conta++){//Carregamento das senhas
				carregar_senha(conta,senha); 

				enviar_string_serial(&senha[conta][0]);//Envio por serial da senha e nivel de acesso para debug
				numero_para_ascii(nivel_acesso);//

				setar_bit(contas_cadastradas,conta);
				}
	
	
	configurar_data_inicial();
	data_atual.mes=1;

	PORTB_SR=PORTB;//Leitura do PORTB antes de habilitar a interrupção para evitar uma interrupção não desejada.
	RBIE=1;
	RBIF=0;
	cont=0;

	lcd_init(LCD_20X4);
	lcd_gotoxy(LINHA1,20);
	printf("%c",SENSOR_ABERTURA_FECHADURA);
	lcd_gotoxy(LINHA4,1);
	printf("%02d:%02d:%02d-%02d.%02d.%02d",data_atual.hora,data_atual.minuto,data_atual.segundo, data_atual.dia,data_atual.mes,((data_atual.ano+15)%100) );

	while(1){
		lcd_gotoxy(LINHA1,20);
		printf("%c\r",SENSOR_ABERTURA_FECHADURA);//atualiza o status da fechadura no display e retorna o cursor para o início;
		printf("  Seja bem-vindo");
		if(!qtd_caracteres_recebidos_teclado) printf("\nAguardando login");
		

		if(testar_bit(FLAGS_2,RECEBER)){ //OBSERVAÇÃO: O PROTOCOLO SEGUIDO AO RECEBER OS DADOS PELA SERIAL E PELO TECLADO MATRICIAL SÃO DIFERENTES, VIDE PROTOCOLO.TXT EM
																																	//CASO DE DÚVIDAS
			
			resetar_bit(FLAGS_2,RECEBER);
			enviar_string_serial("qtd:");
			numero_para_ascii(qtd_caracteres_recebidos_serial);

			if(MODO_BLUETOOTH){

				enviar_caractere_serial(NOVA_LINHA);
				enviar_string_serial(buffer_serial); //Envio dos dados recebidos para debug
				enviar_caractere_serial(NOVA_LINHA);
				
				char *ptr_caractere_recebido_serial = &buffer_serial[0]; //Ponteiro para o caractere a ser analisado no momento
				if(buffer_serial[0] == 10) ptr_caractere_recebido_serial++;//Solução paliativa ao fato do aplicativo estar enviando 
																			//um caracter com valor inicial igual a decimal 10 antes do caractere de inicio

				char i=0;
				etapa=etapa_inicial;
				ordem=0;
				

				//Início da análise dos dados recebidos
				for(i=0;i<qtd_caracteres_recebidos_serial;i++){

					//if(!i) ptr_caractere_recebido_serial = &buffer_serial[1]; //garante que no inicio o ponteiro também esteja apontando para o inicio do buffer serial

					enviar_string_serial("\ni:");numero_para_ascii(i);
					enviar_caractere_serial(*ptr_caractere_recebido_serial);

					if(FLAGS_1){
						enviar_string_serial("\netapa_e:"); numero_para_ascii(etapa);numero_para_ascii(ordem);
						ordem=0;
						break;}

					else if(*ptr_caractere_recebido_serial == PROXIMA_ETAPA){
					
						if(etapa == etapa_login && senha[conta][ordem]!= NULL) setar_bit(FLAGS_1,ERRO_SENHA);
						etapa++;
						ordem=0;}

					else if(etapa == etapa_inicial){
						if( (*ptr_caractere_recebido_serial) != INICIO) setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

					else if(etapa == etapa_recebe_funcao){//recebe-se a funcao a ser executada, conta a realizar o acesso e confirma-se se essa é a fechadura correta
					
						funcao = *ptr_caractere_recebido_serial++;//recebe função a ser executada
						
						if( (*ptr_caractere_recebido_serial) != NUMERO_DESSA_FECHADURA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);} //Está se enviando uma mensagem a fechadura errada

						conta = ascii_para_numero('0', *(++ptr_caractere_recebido_serial),*(++ptr_caractere_recebido_serial));
						
					
						if(conta> QTD_MAX_CONTAS || !(testar_bit(contas_cadastradas,conta)) ) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);

						if( FUNCAO_NAO_AUTORIZADA ){ //A conta não está autorizada a realizar essa funcao
							setar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);} 	
						}


					else if(etapa == etapa_login){
		
						if(*ptr_caractere_recebido_serial !=  senha[conta][ordem]) setar_bit(FLAGS_1,ERRO_SENHA);
						//enviar_caractere_serial(senha[conta][ordem]);
		
						if(++ordem == TAMANHO_SENHA+1) { setar_bit(FLAGS_1,ERRO_PROTOCOLO); numero_para_ascii(ordem);}

					}


					else if(etapa == etapa_detalha_funcao){

						if(funcao == ABERTURA_PORTA || funcao == REQUERIMENTO_STATUS_ATUAL){
							
							if(*ptr_caractere_recebido_serial != ('N'+ordem)) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
							enviar_caractere_serial('N'+ordem);
							ordem++;
						}

						else if(funcao >= MUDAR_SENHA_OUTRA_CONTA){ //Funções '6' e '7'. Função '7' == alterar a senha da própria conta

							if(!ordem) {
								if(funcao == MUDAR_SENHA_PROPRIA_CONTA) conta_a_ser_alterada=conta; 

								else{ conta_a_ser_alterada = ascii_para_numero(NULL,NULL,*ptr_caractere_recebido_serial++);} //converte-se para decimal o caractere recebido e avança o ponteiro para o próximo caractere

							}

							nova_senha[ordem] = *ptr_caractere_recebido_serial;

							if(++ordem == TAMANHO_SENHA) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
						}

						else if(funcao == RECONFIGURAR_CONTA){
								conta_a_ser_alterada = ascii_para_numero(NULL,NULL,*ptr_caractere_recebido_serial++);
								novo_nivel_acesso = *ptr_caractere_recebido_serial;}

						
						else if(funcao == RECONFIGURAR_PIC){
								//ordem 0  = ano
								//ordem 1  = mes
								//ordem 2  = dia
								//ordem 3  = hora
								//ordem 4   = minuto
								//ordem 5  = segundo
								if(!ordem) ptr_data = &data_recebida.ano;
											
																				
								unsigned char novo_valor = ascii_para_numero(NULL,*ptr_caractere_recebido_serial, *(++ptr_caractere_recebido_serial));
								//Converte o caractere atual e o próximo de ascii para o valor decimal do parametro. Ex: altera-se hora para 23, recebe-se '2' e '3'

								if( ((ordem<ALTERAR_MINUTO) && novo_valor>60) ||  ((ordem == ALTERAR_MES)&& novo_valor>Dezembro) || ((ordem == ALTERAR_DIA) && novo_valor > qtd_max_dias) ) setar_bit(FLAGS_1,ERRO_VALOR_PARAMETRO);

								else {*ptr_data = novo_valor; numero_para_ascii(*(ptr_data+ordem));  numero_para_ascii(data_recebida.ano);}

								if(++ordem>ALTERAR_SEGUNDO+1) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
								
								else ptr_data++;

						
						}

					
						else if(funcao == RECONFIGURAR_MODULO){//Primeiro se recebe o comando a ser executado, depois o parametro
								if(!ordem){
									comando_at = *ptr_caractere_recebido_serial++;
									zerar_string(parametro_configuracao_modulo_bt);}

								parametro_configuracao_modulo_bt[ordem++] = *ptr_caractere_recebido_serial;

								if(ordem> (TAMANHO_PARAMETRO_BT+1)) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
								}
			
					}//Fim detalhamento função

					else if(etapa == etapa_final){
						if( (*ptr_caractere_recebido_serial) != FIM) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);enviar_string_serial("F-esp");numero_para_ascii((*ptr_caractere_recebido_serial) ); numero_para_ascii(*(ptr_caractere_recebido_serial-1));}
						break;//Sai do loop de recebimento de dados

					}

					
					ptr_caractere_recebido_serial++;
	
				

				}//Fim da análise dos dados recebidos
				
				
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
										//O recebimento ocorreu porque o usuário apertou, no modo t9, uma tecla diferente da anterior
										//Reativa-se o timer para que, caso  o usuário fique muito tempo sem digitar o programa considere como recebido o caractere
											}
									else ultimo_caractere_recebido=0;

												}

								else{ //se o modo_t9 estiver on mas o usuário apertou a tecla uma única vez para inserir um número
										buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] = caractere_recebido;
										
									}
										
								}

								
							
						
							else{ //Se modo_t9 estiver off, não há necessidade de fazer qualquer lógica antes de armazená-lo no buffer
									buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] = caractere_recebido;
								}

							
						
							qtd_vezes_mesma_tecla_pressionada=0;
							caractere_recebido=0;


							//comparação com senha recebida
							//printf("\r%d",qtd_caracteres_recebidos_teclado);
							

							

							if(qtd_caracteres_recebidos_teclado){			
								lcd_gotoxy(LINHA3,qtd_caracteres_recebidos_teclado); 
								printf("*%c",buffer_teclado_matricial[qtd_caracteres_recebidos_teclado]);
								TMR1ON=1;}
			
							else{
								limpar_linha(LINHA2);
								lcd_gotoxy(LINHA3,(qtd_caracteres_recebidos_teclado+1));
								printf("%c",buffer_teclado_matricial[qtd_caracteres_recebidos_teclado]);
								TMR1ON=1;}

							printf("\n%s",buffer_teclado_matricial);

							if(	buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] == FIM || ++qtd_caracteres_recebidos_teclado==(TAMANHO_BUFFER_TECLADO_MATRICIAL-1)){
		
										resetar_timer1(0xC0,0);//Reseta timer para evitar que o caractere F seja impresso ou que um asterisco seja por algum erro no programa
										buffer_teclado_matricial[qtd_caracteres_recebidos_teclado] = 0;
										

										conta = ( ((buffer_teclado_matricial[0]-'0')*10)  + (buffer_teclado_matricial[1]-'0') );
										cont=2;

										if( (conta>QTD_MAX_CONTAS) && (!testar_bit(contas_cadastradas,conta))) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA); //N° da conta fora do intervalo ou conta não cadastrada


									  	//cont inicia em 2 porque a senha do usuário no buffer do teclado matricial inicia em
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
										setar_bit(FLAGS_2,ENVIAR);
										
							}				
						}

			}

		
		if(testar_bit(FLAGS_2,ENVIAR)){//Envio, ao usuário, do resultado do acesso(teclado matricial ou bluetooth). Aqui será enviado se ele conseguiu acesso e pôde abrir a porta.
			
								
			resetar_bit(FLAGS_2,ENVIAR);
			qtd_caracteres_recebidos_serial,cont=0;
			qtd_caracteres_recebidos_teclado=0;
			
			zerar_string(buffer_serial);
			zerar_string(buffer_teclado_matricial);
			
				if(MODO_TECLADO_MATRICIAL){
						//printf("\r%02d",qtd_caracteres_recebidos_teclado); debug, veriicar qtd de caracteres recebidos;
						

						if(FLAGS_1<1) { //Não houve erros
												

												limpar_linha(LINHA3);
												printf("\n\nDestravando...");
												delay_ms(800);	
												char tentativas=0;
												RD2=1;//Fechadura

													while(FECHADURA_TRAVADA){
														if(++tentativas == 6){ 
															setar_bit(FLAGS_1,ERRO_ABERTURA); //A fechadura não abriu após 6 tentativas. Não há como saber, pelo atual software, a causa.
															break;}
	
													//	FECHADURA=1;
														delay_ms(350);
															if(FECHADURA_TRAVADA) delay_ms(100);//preparação para próxima tentativa 
															}
												
														
												lcd_gotoxy(LINHA1,20);
												printf("%c",SENSOR_ABERTURA_FECHADURA);

												limpar_linha(LINHA3);								
												if(FECHADURA_TRAVADA){
														printf("\n\nErro de abertura");}
		
												else{
														printf("\n\nPorta aberta");}
												
												//FECHADURA=0;
												delay_ms(5000);
												RD2=0;
												limpar_linha(LINHA3);

										}

										else{//Houve erros, de senha ou de protocolo.
											limpar_linha(LINHA3);
												if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)) printf("\n\nErro de protocolo");

												else if(testar_bit(FLAGS_1,ERRO_IDENTIF_CONTA)) printf("\n\nConta nao existente");

												else if(testar_bit(FLAGS_1,ERRO_SENHA))	printf("\n\nSenha incorreta");

												else printf("\n\nErro desconhecido");
										
										delay_ms(5000);
										FLAGS_1=0;//Zerar flags
										limpar_linha(LINHA3);
										}
				}				



				


				else if(MODO_BLUETOOTH){

					enviar_string_serial("\nI");

						if(!FLAGS_1 && etapa == etapa_final){//Não houve erros
										etapa = etapa_inicial;
										LATDbits.LD3^=1;
										enviar_string_serial("OK");//Indica que o acesso foi bem sucedido
										
										//O que será feito depende da função,algumas enviam dados,outras só executam ações
												if(funcao == REQUERIMENTO_STATUS_ATUAL){
														enviar_string_serial("\nano:");					numero_para_ascii(data_atual.ano);
														enviar_string_serial("\nmes:");					numero_para_ascii(data_atual.mes);
														enviar_string_serial("\ndia_semana:");			numero_para_ascii(data_atual.dia_da_semana);
														enviar_string_serial("\ndia:");					numero_para_ascii(data_atual.dia);
														enviar_string_serial("\nhora:");				numero_para_ascii(data_atual.hora);
														enviar_string_serial("\nminuto:");				numero_para_ascii(data_atual.minuto);
														enviar_string_serial("\nsegundo:");				numero_para_ascii(data_atual.segundo);
														enviar_string_serial("\nqtd_total_contas:");	numero_para_ascii(qtd_total_contas);
														enviar_string_serial("\nqtd_max_contas:");		numero_para_ascii(QTD_MAX_CONTAS);
														numero_para_ascii(SENSOR_ABERTURA_FECHADURA);}

												else if(funcao == RECONFIGURAR_PIC){
														parar_timer0_16bits(0xC2,0xF7); //TMR0=34446(1 interrupção = 1s para FOSC=16MHz)
														data_atual = data_recebida;
														data_atual.dia_da_semana = dia_da_semana(data_atual.ano,data_atual.mes,data_atual.dia);
														TMR0IE=1;
														

												}

												else if(funcao == RECONFIGURAR_CONTA){
														nivel_acesso_conta_a_ser_alterada = novo_nivel_acesso;}

												else if(funcao == RECONFIGURAR_MODULO){
														setar_bit(FLAGS_3,MODO_COMANDO_AT);
														enviar_string_serial(parametro_configuracao_modulo_bt);
														enviar_comando_at(comando_at,parametro_configuracao_modulo_bt);}


												else if(funcao == MUDAR_SENHA_PROPRIA_CONTA || funcao == MUDAR_SENHA_OUTRA_CONTA){
													
													setar_bit(contas_cadastradas,conta_a_ser_alterada); //seta-se o bit correspondente a conta que sera alterada para marcar
																										//que ela existe.Se já existir mantem-se em 1.
													char i=0;
														do{
															senha[conta_a_ser_alterada][i] = nova_senha[i];
															eeprom_write(((conta_a_ser_alterada*16) + i),nova_senha[i]);
															while(WR){}
															i++;} while(nova_senha[i-1]  && i<TAMANHO_SENHA);
														}
							
												else if(funcao == ABERTURA_PORTA){
														RD2=1;
													 //FECHADURA=1;//Alimenta-se da fechadura
													 	delay_ms(1200);//Tempo de abertura
														RD2=0;
													 //FECHADURA=0;//A alimentação da fechadura é interrompida
													}

										}
						
						else{//Houve erros
							etapa=etapa_inicial;
							enviar_caractere_serial('E');//Indica erro

								if(testar_bit(FLAGS_1,ERRO_VALOR_PARAMETRO)){//Um ou mais parametro recebido foi um inválido(fora da faixa aceita,ex: 64 segundos)
											enviar_caractere_serial('V');}

								if(testar_bit(FLAGS_1,ERRO_SESSAO_EXPIRADA)){//Mais de 0,5 segundos sem enviar nenhum caractere
											enviar_caractere_serial('X');}
							
								if(testar_bit(FLAGS_1,ERRO_ABERTURA)){//A porta não abriu após 5 tentativas
											enviar_caractere_serial('A');}
	
								if(testar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO)){//A conta não tinha autorização para executar a função pedida
											enviar_caractere_serial('N');}
	
								if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)){ //O PIC recebeu um caractere fora do esperado pelo protocolo	
											enviar_caractere_serial('P');}
	
								if(testar_bit(FLAGS_1,ERRO_COMUNICACAO)){//Erro de overrun ou frame
											enviar_caractere_serial('C');}
							
								if(testar_bit(FLAGS_1,ERRO_SENHA)){//Senha incorreta
											enviar_caractere_serial('S');}
					
								if(testar_bit(FLAGS_1,ERRO_IDENTIF_CONTA)){ //A conta que tentou acessar o sistema não existe
											enviar_caractere_serial('I');}
							
						 FLAGS_1=0;}

							
															
				enviar_caractere_serial(FIM);	
				PORTB_SR = PORTB; //Reativa a interrupção por mudança de nível ,liberando o acesso pelo teclado
				RBIE=1;
		}

		}

		if((PORTB&0xF0) == 0xF0 && RBIE==0 && testar_bit(FLAGS_2,DEBOUNCE) && MODO_TECLADO_MATRICIAL){//Tratamento de debounce. Espera-se até que nenhum botão esteja pressionado e que o debounce esteja autorizado
																			//(existem situações em que RBIE=0 e não se quer fazer tratamento de debounce
					delay_ms(100);
					if(caractere_recebido == VOLTAR_CARACTERE){//Retorna o indice do buffer em 1  põe-se um zero nele para que se "retire" o caractere que tenha ali
								RD3=1;
					}
						if(caractere_recebido < '0' || caractere_recebido > '9'){//Caracteres não são armazenados, pois são fora da faixa de 0 a 9.São utilizados para certas funções
																					//como indicar maiuscula, ativar modo_t9, etc.
									
									resetar_timer1(0xC0,0);	//Para evitar que o timer dê uma interrupção e receba o caracter
									ultimo_caractere_recebido = caractere_recebido; //atualiza ultimo caractere recebido
									
		
							if(caractere_recebido == FIM){
								setar_bit(FLAGS_2,RECEBER);}
	
							else if(caractere_recebido == MODO_T9_ON_OFF){
								inverter_bit(FLAGS_2,MODO_T9);}
	
							else if(caractere_recebido == MAIUSCULA_MINUSCULA){
								inverter_bit(FLAGS_2,MAIUSCULA);}

							else if(caractere_recebido == VOLTAR_CARACTERE && qtd_caracteres_recebidos_teclado){//Retorna o indice do buffer em 1  põe-se um zero nele para que se "retire" o caractere que tenha ali
							
								lcd_gotoxy(LINHA3,qtd_caracteres_recebidos_teclado); printf(" ");
								buffer_teclado_matricial[--qtd_caracteres_recebidos_teclado]=0;
								limpar_linha(LINHA2);
								printf("\n%s",buffer_teclado_matricial);
								}

							else if(caractere_recebido == LIMPAR_SENHA){//Retorna o indice do buffer em 1  põe-se um zero nele para que se "retire" o caractere que tenha ali
							
								
								qtd_caracteres_recebidos_teclado=0;
								zerar_string(buffer_teclado_matricial);
								limpar_linha(LINHA3);
								limpar_linha(LINHA2);
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

					PORTB_SR=PORTB;//leitura do PORTB antes de ativar a interrupção para evitar uma interrupção não desejada.
					RBIE=1;
		}


		if(testar_bit(FLAGS_2,EXIBIR)){//exibir algo no display lcd
			resetar_bit(FLAGS_2,EXIBIR);
			if(testar_bit(FLAGS_3,ATUALIZAR_HORA_DISPLAY)){
				lcd_gotoxy(LINHA4,1);
				printf("%02d:%02d:%02d-%02d.%02d.%02d   ",data_atual.hora,data_atual.minuto,data_atual.segundo, data_atual.dia,data_atual.mes,((data_atual.ano+15)%100) );
				resetar_bit(FLAGS_3,ATUALIZAR_HORA_DISPLAY);
			}
			

			}

		if( (!testar_bit(FLAGS_2,EXIBIR))&& (!testar_bit(FLAGS_2,RECEBER)) && (!testar_bit(FLAGS_2,ENVIAR)) && RBIE && RCIE){ //garante que o 18F4550 entre em modo idle com as interrupções ativadas(RBIE pode estar zerado pelo tratamento de debounce)
			SLEEP();
			NOP();}


}

}
