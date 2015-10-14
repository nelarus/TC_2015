#include <xc.h>
#include <string.h>
#include <stdio.h>
#include "encrypt.h"
#include "ascii.h" //Convers�o de formato X a ASCII ou de ASCII a X (Ex.: Coordenadas do teclado matricial para caracteres ascii e convers�o de valor decimal para caractere ascii
#include "eeprom_interna.h" //Acesso da eeprom interna conforme banco de dados implementado
#include "time.h"
#include "main.h"
#include "serial.h" 
#include "lcd.h"
#include "flags.h" //defini��es de flags
#include "recebimento_dados.h" //Fun��es do sistema, defini��es do protocolo,etc.
#include "contas.h"//Tamanho de conta, defini��es sobre n�vel de acesso
#include "configuracao_pic.h" //Configura��o de oscilador, perif�ricos, ports e defini��es sobre pinos e ports

//INICIO CONFIGURA��O 18F4550

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


//VARI�VEIS GLOBAIS

//MATRIZES
char nova_senha[TAMANHO_SENHA]; //armazena temporariamente a nova senha atribuida a conta para garantir que a senha atual n�o seja lida no meio do processo de altera��o
char senha[QTD_MAX_CONTAS][TAMANHO_SENHA+3]; //SENHA+3 para compensar o caractere \0 que a string precisa ter(indice=16) e o caractere que representa o nivel de acesso(indice=17)

unsigned char buffer_serial[TAMANHO_BUFFER_SERIAL]; //Usado para receber dados pela porta serial
unsigned char *ptr_buffer_serial = &buffer_serial[0];
unsigned char buffer_teclado_matricial[TAMANHO_BUFFER_TECLADO_MATRICIAL]; // Usado para receber dados pelo teclado matricial
unsigned char qtd_caracteres_recebidos_serial=0; //contador para caracteres recebidos pela porta serial
unsigned char qtd_caracteres_recebidos_teclado=0; //contador para caracteres recebidos pelo teclado matricial 

//char dados_recebidos[41];
//char chave_criptografia[17];
//char texto_critografado[81];
//char texto_descriptografado[41];

//Fim declara��o de matrizes

//Inicio Declara��o de structs
Data data_recebida; //corpo declarado em time.h

//Inicio declara��o de chars
unsigned char caractere_recebido = 0; //Caractere recebido pelo teclado matricial
unsigned char FLAGS_1=0; //
unsigned char FLAGS_2=0; //vide flags.h
unsigned char FLAGS_3=0; //
unsigned char PORTB_SR;// Shadow register para leitura do PORTB e atualiza��o do LATB
unsigned char num_interrupt_timer1=0;
unsigned char num_interrupt_caracter_por_asterisco=0;
char qtd_max_dias =31;
unsigned char qtd_vezes_mesma_tecla_pressionada=0;
unsigned int  TMR0_inicial;
//Fim declara��o de chars

//Inicio declara��o de inteiros
unsigned int endereco_inic_eeprom=5;
unsigned int endereco_final_eeprom=5;
//Fim declara��o de inteiros

void zerar_string(char *string_a_zerar){

		while(*string_a_zerar != NULL){
			*string_a_zerar=0;
			string_a_zerar++;}

}


unsigned char ascii_para_numero_debug(char caractere3, char caractere2, char caractere1){

		if(caractere3 == NULL) caractere3 = '0'; 
		if(caractere2 == NULL) caractere2 = '0';
		numero_para_ascii(caractere3);
		numero_para_ascii(caractere2);
		numero_para_ascii(caractere1);
		unsigned char numero;
		numero=((caractere3 - '0')*100);
		enviar_string_serial("n1"); numero_para_ascii(numero);
		numero+=((caractere2 - '0')*10);
		
		enviar_string_serial("n2"); numero_para_ascii(numero);
		numero+=(caractere1 - '0');
		
		enviar_string_serial("n3"); numero_para_ascii(numero);
		return numero;
}
void interrupt aux(void){

			if(TMR1IE && TMR1IF){ 
				TMR1IF=0;
				resetar_timer1(0xC0,0);
				
				if(MODO_BLUETOOTH){//O dispostivo iniciou comunica��o com o PIC mas ficou mais de 500ms sem termin�-la
						qtd_caracteres_recebidos_serial=0;
						setar_bit(FLAGS_1,ERRO_SESSAO_EXPIRADA);
						setar_bit(FLAGS_2,ENVIAR);
						}

				if(MODO_TECLADO_MATRICIAL){
				
					if(++num_interrupt_timer1==2){//Passou-se 1s ap�s a primeira vez que o bot�o foi apertado.
						if(testar_bit(FLAGS_2,MODO_T9)){setar_bit(FLAGS_2,RECEBER);}
						lcd_gotoxy(LINHA3,qtd_caracteres_recebidos_teclado);
						printf("*");
						num_interrupt_timer1=0;}

					else{//N�o se passou o tempo, ativa-se o timer1 novamente
						TMR1ON=1;}
					}
							
			}
			
			if(TMR0IE && TMR0IF){
					
					setar_bit(FLAGS_2,ATUALIZAR_DISPLAY);
					TMR0H = 0xC2;
					TMR0L+=0xF7;
					TMR0IF=0;
					LATDbits.LD3^=1;
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

					if(	!qtd_caracteres_recebidos_serial){
						modo_bluetooth();		
						resetar_timer1(0xC0,0);
						TMR1ON=1;
						ptr_buffer_serial=&buffer_serial[0];
					}

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
					
					else{//N�o ocorreu erros, recebe-se o dado	
							
							*ptr_buffer_serial++ = RCREG;
							qtd_caracteres_recebidos_serial++;

								if(MODO_COMANDO_AT == DESATIVADO){
									if(qtd_caracteres_recebidos_serial == TAMANHO_BUFFER_SERIAL || ( (*(ptr_buffer_serial-1) == FIM) && (*(ptr_buffer_serial-2)== PROXIMA_ETAPA)) ){
										setar_bit(FLAGS_2,RECEBER);
										resetar_timer1(0xC0,0);
									}
								}

								else{
									if(*(ptr_buffer_serial-1) == 10) {
										setar_bit(FLAGS_2,RECEBER);
										
									RD2=1;}
	
									}

						}//Fim recebimento de dados

					RCIF=0;}
}


int main(void){

	//VARIAVEIS LOCAIS MAIN

	unsigned char ordem = 0;//usada para indicar a ordem em que a string a ser analisada est� naquela etapa.
	unsigned char etapa=0;
	unsigned char funcao=0;//utilizada para determinar qual fun��o o PIC vai executar (abrir porta, fornecer hist�rico, fornecer status atual)
	unsigned char conta=0;
	unsigned char conta_a_ser_alterada=0;
	unsigned char comando_at=0;
	unsigned char qtd_total_contas=0;	
	unsigned char ultimo_caractere_recebido=0;
	unsigned char novo_nivel_acesso=0;
	char pedido_status_1=0;//Quais informa��es o PIC ir� enviar ao ser pedido o status atual
	int contas_cadastradas=0; //16bits que correspondem cada um a uma conta cadastrada ou n�o. Exemplo: bit 7 indica se a conta 7 existe ou ainda n�o tem uma senha cadastrada
	char *ptr_data;

	char parametro_configuracao_modulo_bt[TAMANHO_PARAMETRO_BT+1];

	 configurar_oscilador();	
	 configurar_interrupcoes();	
	 configurar_timer0();	
	 configurar_portas();	
	 configurar_timer1();

	//CONFIGURA��O INICIAL DA EEPROM
	if(eeprom_read(ENDERECO_INICIAL) == VALOR_INICIAL) eeprom_config_inicial(); 
	//
	
	
	MODULO_BT=LIGAR;

	config_serial(BAUD_19200);
	baud_de_operacao = BAUD_19200;

	delay_ms(100);
	enviar_mensagem_inicializacao();
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

	PORTB_SR=PORTB;//Leitura do PORTB antes de habilitar a interrup��o para evitar uma interrup��o n�o desejada.
	RBIE=1;
	RBIF=0;

	lcd_init(LCD_20X4);

	lcd_gotoxy(LINHA1,20);
	printf("%c",SENSOR_ABERTURA_FECHADURA);

	setar_bit(FLAGS_2,ATUALIZAR_DISPLAY);
	while(1){

		if(testar_bit(FLAGS_2,RECEBER)){ //OBSERVA��O: O PROTOCOLO SEGUIDO AO RECEBER OS DADOS PELA SERIAL E PELO TECLADO MATRICIAL S�O DIFERENTES, VIDE PROTOCOLO.TXT EM
																																	//CASO DE D�VIDAS
			
			resetar_bit(FLAGS_2,RECEBER);	
			char *ptr_caractere_recebido_serial = &buffer_serial[0]; //Ponteiro para o caractere a ser analisado no momento

			if(MODO_DEBUG){
				enviar_string_serial("qtd:"); numero_para_ascii(qtd_caracteres_recebidos_serial);
			}

			if(MODO_COMANDO_AT){
				char i=0;

				for(i=0;i<qtd_caracteres_recebidos_serial;i++){
					if(buffer_serial[i] == 'O' && buffer_serial[i+1] == 'K') {
						setar_bit(FLAGS_3,SUCESSO_ENVIO_COMANDO_AT);}
				}

				setar_bit(FLAGS_2,ENVIAR);
				enviar_string_serial(buffer_serial);}

			else if(MODO_BLUETOOTH){

				if(MODO_DEBUG){
					enviar_caractere_serial(NOVA_LINHA);
					enviar_string_serial(buffer_serial);
					enviar_caractere_serial(NOVA_LINHA);
				}

				if(buffer_serial[0] == 10) ptr_caractere_recebido_serial++;//Solu��o paliativa ao fato do aplicativo estar enviando 
																			//um caracter com valor inicial igual a decimal 10 antes do caractere de inicio

				char i=0;
				etapa=etapa_inicial;
				ordem=0;
				

				//In�cio da an�lise dos dados recebidos
				for(i=0;i<qtd_caracteres_recebidos_serial;i++){

					if(MODO_DEBUG){
						enviar_string_serial("\ni:");numero_para_ascii(i);
						enviar_caractere_serial(*ptr_caractere_recebido_serial);
					}

					if(FLAGS_1){
						if(MODO_DEBUG){
							enviar_string_serial("\netapa_e:"); 
							numero_para_ascii(etapa);
							numero_para_ascii(ordem);
						}
						ordem=0;
						break;}

					else if(*ptr_caractere_recebido_serial == PROXIMA_ETAPA){
					
						if( (*(ptr_caractere_recebido_serial-1)) == PROXIMA_ETAPA) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
					
						else if(etapa == etapa_login && senha[conta][ordem]!= NULL) setar_bit(FLAGS_1,ERRO_SENHA);

						else if(++etapa > etapa_final) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
						ordem=0;}


					else if(etapa == etapa_inicial){
						if( (*ptr_caractere_recebido_serial) != INICIO) setar_bit(FLAGS_1,ERRO_PROTOCOLO);}

					else if(etapa == etapa_identificacao){//recebe-se a funcao a ser executada, conta a realizar o acesso e confirma-se se essa � a fechadura correta
					
						if(!ordem) funcao = *ptr_caractere_recebido_serial;//recebe fun��o a ser executada
						
						else if(ordem==1){
							if( (*ptr_caractere_recebido_serial) != NUMERO_DESSA_FECHADURA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);} //Est� se enviando uma mensagem a fechadura errada
						}

						else if(ordem==2){
							conta = ascii_para_numero('0', *ptr_caractere_recebido_serial,*(++ptr_caractere_recebido_serial));
							if(conta> QTD_MAX_CONTAS || !(testar_bit(contas_cadastradas,conta)) ) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);
	
							if( FUNCAO_NAO_AUTORIZADA && nivel_acesso != NIVEL_ACESSO_MAXIMO){ //A conta n�o est� autorizada a realizar essa funcao.
								setar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);} 	
						}

						ordem++;

					}	
					else if(etapa == etapa_login){
		
						if(*ptr_caractere_recebido_serial !=  senha[conta][ordem]) setar_bit(FLAGS_1,ERRO_SENHA);
						//enviar_caractere_serial(senha[conta][ordem]);
		
						if(++ordem == TAMANHO_SENHA+1) { setar_bit(FLAGS_1,ERRO_PROTOCOLO); numero_para_ascii(ordem);}

					}


					else if(etapa == etapa_detalha_funcao){

						if(funcao == ABERTURA_PORTA || funcao == ATIVAR_MODO_DEBUG){
							
							if(*ptr_caractere_recebido_serial != ('N'+ordem)) setar_bit(FLAGS_1,ERRO_PROTOCOLO);

							if(MODO_DEBUG) {//Se o modo debug estiver ativado, envia o caractere esperado no detalhamento da fun��o
								enviar_caractere_serial('N'+ordem);
							}
							ordem++;
						}

						else if(funcao == REQUERIMENTO_STATUS_ATUAL){
							
							if(MODO_DEBUG){//No modo debug a especifica��o de quais informa��es ,referentes ao status atual ,est�o sendo pedidas � feita por enviar em ascii um valor entre '0'0'0' e '2''5''5'.
											//No modo normal simplesmente se envia um char de valor entre 0 decimal e 255 decimal
									pedido_status_1 = ascii_para_numero( *ptr_caractere_recebido_serial, *(ptr_caractere_recebido_serial+1),*(ptr_caractere_recebido_serial+2));
									
									ptr_caractere_recebido_serial+=2;}
							else {
								pedido_status_1 = *ptr_caractere_recebido_serial;}
						}

						else if(funcao >= MUDAR_SENHA_OUTRA_CONTA){ //Fun��es '6' e '7'. Fun��o '7' == alterar a senha da pr�pria conta

							if(!ordem) {
								if(funcao == MUDAR_SENHA_PROPRIA_CONTA) conta_a_ser_alterada=conta; 

								else{ conta_a_ser_alterada = ascii_para_numero(NULL,NULL,*ptr_caractere_recebido_serial++);} //converte-se para decimal o caractere recebido e avan�a o ponteiro para o pr�ximo caractere
							}

							nova_senha[ordem] = *ptr_caractere_recebido_serial;

							if(++ordem == TAMANHO_SENHA) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
						}

						else if(funcao == RECONFIGURAR_CONTA){
								conta_a_ser_alterada = ascii_para_numero(NULL,NULL,*ptr_caractere_recebido_serial++);


							
							if(MODO_DEBUG){
									novo_nivel_acesso = ascii_para_numero( *ptr_caractere_recebido_serial, *(ptr_caractere_recebido_serial+1),*(ptr_caractere_recebido_serial+2));
									
									ptr_caractere_recebido_serial+=2;}
							else {
								novo_nivel_acesso = *ptr_caractere_recebido_serial;}
								}

						
						else if(funcao == RECONFIGURAR_PIC){
								//ordem 0  = ano
								//ordem 1  = mes
								//ordem 2  = dia
								//ordem 3  = hora
								//ordem 4   = minuto
								//ordem 5  = segundo
								if(!ordem) ptr_data = &data_recebida.ano;
											
																				
								unsigned char novo_valor = ascii_para_numero(NULL,*ptr_caractere_recebido_serial, *(++ptr_caractere_recebido_serial));
								//Converte o caractere atual e o pr�ximo de ascii para o valor decimal do parametro. Ex: altera-se hora para 23, recebe-se '2' e '3'

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

			
					}//Fim detalhamento fun��o

					else if(etapa == etapa_final){
						if( (*ptr_caractere_recebido_serial) != FIM) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);enviar_string_serial("F-esp");numero_para_ascii((*ptr_caractere_recebido_serial) ); numero_para_ascii(*(ptr_caractere_recebido_serial-1));}
						break;

					}

					
					ptr_caractere_recebido_serial++;
	
				

				}
				
				
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
										
									if(ultimo_caractere_recebido != caractere_recebido) { //O recebimento ocorreu porque o usu�rio apertou, no modo t9, uma tecla diferente da anterior
														ultimo_caractere_recebido = caractere_recebido;
														TMR1ON=1; //Reativa-se o timer para que, caso  o usu�rio fique muito tempo sem digitar o programa considere como recebido o caractere
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
							desativar_modo_teclado_matricial();

							conta = ( ((buffer_teclado_matricial[0]-'0')*10)  + (buffer_teclado_matricial[1]-'0') );
							ordem=2;//cont inicia em 2 porque a senha do usu�rio no buffer do teclado matricial inicia em buffer_teclado_matricial[2]


								if( (conta>QTD_MAX_CONTAS) && (!testar_bit(contas_cadastradas,conta))) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA); //N� da conta fora do intervalo ou conta n�o cadastrada
									  
								if(qtd_caracteres_recebidos_teclado<(TAMANHO_MINIMO_SENHA+2)){setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
										
										while(ordem<(TAMANHO_SENHA+2) && buffer_teclado_matricial[ordem-2] != 0 && FLAGS_1<2){
											
											//enviar_caractere_serial(senha[conta][cont-2]);
											//enviar_caractere_serial(buffer_teclado_matricial[cont]);

											if(buffer_teclado_matricial[ordem] != senha[conta][ordem-2]){
												setar_bit(FLAGS_1,ERRO_SENHA);
												}

											ordem++;
										}
										setar_bit(FLAGS_2,ENVIAR);
										
							}				
						}

			}

		
		if(testar_bit(FLAGS_2,ENVIAR)){//Envio, ao usu�rio, do resultado do acesso(teclado matricial ou bluetooth). Aqui ser� enviado se ele conseguiu acesso e p�de abrir a porta.
			
								
			resetar_bit(FLAGS_2,ENVIAR);
			ptr_buffer_serial = &buffer_serial[0];
			zerar_string(buffer_serial);
			zerar_string(buffer_teclado_matricial);
				
				if(MODO_TECLADO_MATRICIAL){
						
						qtd_caracteres_recebidos_teclado=0;
						limpar_linha(LINHA2);limpar_linha(LINHA3);
						desativar_modo_teclado_matricial();

						if(!FLAGS_1) { //N�o houve erros
												

												printf("\n\nDestravando...");
												delay_ms(800);	
												char tentativas=0;
												RD2=1;//Fechadura

													while(FECHADURA_TRAVADA){
														if(++tentativas == 6){ 
															setar_bit(FLAGS_1,ERRO_ABERTURA); //A fechadura n�o abriu ap�s 6 tentativas. N�o h� como saber, pelo atual software, a causa.
															break;}
	
													//	FECHADURA=1;
														delay_ms(350);
															if(FECHADURA_TRAVADA) delay_ms(100);//prepara��o para pr�xima tentativa 
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
												if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)) printf("\n\nErro de protocolo");

												else if(testar_bit(FLAGS_1,ERRO_IDENTIF_CONTA)) printf("\n\nConta nao existente");

												else if(testar_bit(FLAGS_1,ERRO_SENHA))	printf("\n\nSenha incorreta");

												else printf("\n\nErro desconhecido -%d-",FLAGS_1);
										
										delay_ms(5000);
										FLAGS_1=0;//Zerar flags
										limpar_linha(LINHA3);
										}
				}				



				
				

				if(MODO_COMANDO_AT){
						sair_modo_at(testar_bit(FLAGS_3,VERSAO_MODULO));
						if(testar_bit(FLAGS_3,SUCESSO_ENVIO_COMANDO_AT)){}
						resetar_bit(FLAGS_3,SUCESSO_ENVIO_COMANDO_AT);

						if(MODO_COMANDO_AT==DESATIVADO)RD2=0;}


				else if(MODO_BLUETOOTH){
					
					qtd_caracteres_recebidos_serial;
					desativar_modo_bluetooth();
					enviar_string_serial("\nI");

						if(!FLAGS_1 && etapa == etapa_final){//N�o houve erros
										etapa = etapa_inicial;
										LATDbits.LD3^=1;
										enviar_string_serial("OK");//Indica que o acesso foi bem sucedido
										
										//O que ser� feito depende da fun��o,algumas enviam dados,outras s� executam a��es

												
												if(funcao == ATIVAR_MODO_DEBUG){
														inverter_bit(FLAGS_3,MODO_DEBUG_ON);}

												else if(funcao == REQUERIMENTO_STATUS_ATUAL){
														numero_para_ascii(pedido_status_1);

														if(STATUS_DATA){
															enviar_string_serial("\n\rano:");					numero_para_ascii(data_atual.ano);
															enviar_string_serial("\n\rmes:");					numero_para_ascii(data_atual.mes);
															enviar_string_serial("\n\rdia_semana:");			numero_para_ascii(data_atual.dia_da_semana);
															enviar_string_serial("\n\rdia:");					numero_para_ascii(data_atual.dia);
															enviar_string_serial("\n\rhora:");					numero_para_ascii(data_atual.hora);
															enviar_string_serial("\n\rminuto:");				numero_para_ascii(data_atual.minuto);
															enviar_string_serial("\n\rsegundo:");				numero_para_ascii(data_atual.segundo);
															enviar_string_serial("\n\rqtd_total_contas:");		numero_para_ascii(qtd_total_contas);
															enviar_string_serial("\n\rqtd_max_contas:");		numero_para_ascii(QTD_MAX_CONTAS);
														}

														if(STATUS_PORTA){
															enviar_string_serial("\nPorta");
															if(FECHADURA_TRAVADA)enviar_string_serial(" fechada"); else enviar_string_serial(" aberta");}

														if(STATUS_RECONFIGURACAO_MODULO) enviar_string_serial("\n\rModulo nao explodiu");

														if(STATUS_FLAGS){
															if(MODO_DEBUG){
															enviar_string_serial("\n\rFLAGS_1"); numero_para_ascii(FLAGS_1);
															enviar_string_serial("\n\rFLAGS_2"); numero_para_ascii(FLAGS_2);
															enviar_string_serial("\n\rFLAGS_3"); numero_para_ascii(FLAGS_3);
															}
														
															else{enviar_string_serial("\n\rAtive modo debug");}

															}

														if(STATUS_EEPROM){
															if(MODO_DEBUG){
																int i;
																for(i=0;i<=0xFF;i++){
																	if(!(i%16)) {enviar_string_serial("\n\n\r");}
																	numero_para_ascii(eeprom_read(i));}
																}

															else{enviar_string_serial("\n\rAtive modo debug");}
														}	
												}
															
												else if(funcao == RECONFIGURAR_PIC){
														parar_timer0_16bits(0xC2,0xF7); //TMR0=34446(1 interrup��o = 1s para FOSC=16MHz)
														data_atual = data_recebida;
														data_atual.dia_da_semana = dia_da_semana(data_atual.ano,data_atual.mes,data_atual.dia);
														TMR0IE=1;
														

												}

												else if(funcao == RECONFIGURAR_CONTA){
														nivel_acesso_conta_a_ser_alterada = novo_nivel_acesso;

														numero_para_ascii(novo_nivel_acesso);

														armazenar_novo_nivel_de_acesso(nivel_acesso_conta_a_ser_alterada, conta_a_ser_alterada);}

												else if(funcao == RECONFIGURAR_MODULO){
														entrar_modo_at(testar_bit(FLAGS_3,VERSAO_MODULO));
														delay_ms(800);
														enviar_comando_at(comando_at,parametro_configuracao_modulo_bt,testar_bit(FLAGS_3,VERSAO_MODULO) );
												}


												else if(funcao == MUDAR_SENHA_PROPRIA_CONTA || funcao == MUDAR_SENHA_OUTRA_CONTA){
													
													setar_bit(contas_cadastradas,conta_a_ser_alterada); //seta-se o bit correspondente a conta que sera alterada para marcar
																										//que ela existe.Se j� existir mantem-se em 1.

													armazenar_senha(nova_senha,senha,conta_a_ser_alterada);
														}
							
												else if(funcao == ABERTURA_PORTA){
														
													 DESTRAVAR_FECHADURA();
													 delay_ms(500);
													 TRAVAR_FECHADURA();

													 if(FECHADURA_TRAVADA){
														setar_bit(FLAGS_1,ERRO_ABERTURA);
														setar_bit(FLAGS_2,ENVIAR);}
													}

										}
						
						else{//Houve erros
							etapa=etapa_inicial;
							enviar_caractere_serial('E');//Indica erro

								if(testar_bit(FLAGS_1,ERRO_VALOR_PARAMETRO)){//Um ou mais parametro recebido foi um inv�lido(fora da faixa aceita,ex: 64 segundos)
											enviar_caractere_serial('V');}

								if(testar_bit(FLAGS_1,ERRO_SESSAO_EXPIRADA)){//Mais de 0,5 segundos sem enviar nenhum caractere
											enviar_caractere_serial('X');}
							
								if(testar_bit(FLAGS_1,ERRO_ABERTURA)){//A porta n�o abriu ap�s 5 tentativas
											enviar_caractere_serial('A');}
	
								if(testar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO)){//A conta n�o tinha autoriza��o para executar a fun��o pedida
											enviar_caractere_serial('N');}
	
								if(testar_bit(FLAGS_1,ERRO_PROTOCOLO)){ //O PIC recebeu um caractere fora do esperado pelo protocolo	
											enviar_caractere_serial('P');}
	
								if(testar_bit(FLAGS_1,ERRO_COMUNICACAO)){//Erro de overrun ou frame
											enviar_caractere_serial('C');}
							
								if(testar_bit(FLAGS_1,ERRO_SENHA)){//Senha incorreta
											enviar_caractere_serial('S');}
					
								if(testar_bit(FLAGS_1,ERRO_IDENTIF_CONTA)){ //A conta que tentou acessar o sistema n�o existe
											enviar_caractere_serial('I');}
							
						 FLAGS_1=0;}

							
															
				enviar_caractere_serial(FIM);
				funcao=0;
				PORTB_SR = PORTB; //Reativa a interrup��o por mudan�a de n�vel ,liberando o acesso pelo teclado
				RBIE=1;
		}

		}

		if((PORTB&0xF0) == 0xF0 && RBIE==0 && testar_bit(FLAGS_2,DEBOUNCE) && MODO_TECLADO_MATRICIAL){//Tratamento de debounce. Espera-se at� que nenhum bot�o esteja pressionado e que o debounce esteja autorizado
																			//(existem situa��es em que RBIE=0 e n�o se quer fazer tratamento de debounce
					delay_ms(100);
					if(caractere_recebido == VOLTAR_CARACTERE){//Retorna o indice do buffer em 1  p�e-se um zero nele para que se "retire" o caractere que tenha ali
								RD3=1;
					}
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

							else if(caractere_recebido == VOLTAR_CARACTERE && qtd_caracteres_recebidos_teclado){//Retorna o indice do buffer em 1  p�e-se um zero nele para que se "retire" o caractere que tenha ali
							
								lcd_gotoxy(LINHA3,qtd_caracteres_recebidos_teclado); printf(" ");
								buffer_teclado_matricial[--qtd_caracteres_recebidos_teclado]=0;
								limpar_linha(LINHA2);
								printf("\n%s",buffer_teclado_matricial);
								}

							else if(caractere_recebido == LIMPAR_SENHA){//Retorna o indice do buffer em 1  p�e-se um zero nele para que se "retire" o caractere que tenha ali
							
								
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

					PORTB_SR=PORTB;//leitura do PORTB antes de ativar a interrup��o para evitar uma interrup��o n�o desejada.
					RBIE=1;
		}


		if(testar_bit(FLAGS_2,ATUALIZAR_DISPLAY)){//exibir algo no display lcd
			resetar_bit(FLAGS_2,ATUALIZAR_DISPLAY);

				if(lcd_type == LCD_16X2){}
				
				lcd_gotoxy(LINHA1,20);
				printf("%c\r",SENSOR_ABERTURA_FECHADURA);//atualiza o status da fechadura no display e retorna o cursor para o in�cio;
				printf("  Seja bem-vindo");

				if(!qtd_caracteres_recebidos_teclado) printf("\nAguardando login");

				if(qtd_max_linhas_lcd == 4){ 
					lcd_gotoxy(qtd_max_linhas_lcd,1);

					if(qtd_max_colunas_lcd == 20) printf("%02d:%02d:%02d-%02d.%02d.%02d   ",data_atual.hora,data_atual.minuto,data_atual.segundo, data_atual.dia,data_atual.mes,((data_atual.ano+15)%100) );
				
					else{
						 printf("%02d:%02d-%02d.%02d.%02d",data_atual.hora,data_atual.minuto,data_atual.dia,data_atual.mes,((data_atual.ano+15)%100) );

						if((data_atual.segundo%2)){lcd_gotoxy(qtd_max_linhas_lcd,3);printf(" ");}
						}	
				}
		
			}

		if( (!testar_bit(FLAGS_2,ATUALIZAR_DISPLAY))&& (!testar_bit(FLAGS_2,RECEBER)) && (!testar_bit(FLAGS_2,ENVIAR)) && RBIE && RCIE ){ //garante que o 18F4550 entre em modo idle com as interrup��es ativadas(RBIE pode estar zerado pelo tratamento de debounce)
			SLEEP();
			NOP();}


}

}
