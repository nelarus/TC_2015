#include <xc.h>
#include <delays.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

#pragma config FOSC =  INTOSCIO_EC
#pragma config PLLDIV = 4   //divide by 5 to give 4MHz to PLL 
#pragma config FCMEN = OFF   //no fail safe clock monitor 
#pragma config IESO = OFF   //oscillator switchover disabled 
#pragma config PWRT = ON           //oscillator power up timer enabled (release version only) 
#pragma config BOR = OFF      //hardware brown out reset 
#pragma config WDT = OFF   //watchdog timer disabled 
#pragma config MCLRE = ON    //MCLR pin enabled 
#pragma config LPT1OSC = OFF  //timer1 low power operation 
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
char senha[16][16];
char nova_senha[16];
const char teclado_matricial[4][4] = {'M','0','F','D','7','8','9','C','4','5','6','B','1','2','3','A'};



struct Data{
	char ano;//0
	char mes;//1
	char dia;//2
	char hora;//3
	char minuto;//4
	char segundo;//5
	char dia_da_semana;//6
		}data_atual,data_recebida;

unsigned char ordem = 0;//usada para compararar uma sequência de dados recebidos com uma string.
unsigned char etapa=0;
unsigned char dado_recebido = 0; //Dado recebido pela serial
unsigned char caractere_recebido = 0; //Caractere recebido pelo teclado matricial
unsigned char nivel_acesso;
unsigned char funcao=0;//utilizada para determinar qual função o PIC vai executar (abrir porta, fornecer histórico, fornecer status atual)
unsigned char conta=0;
unsigned char conta_a_ser_alterada=0;
unsigned char FLAGS_1=0;
unsigned char qtd_total_contas=0;
unsigned char buffer_serial; //variável auxiliar para converter strings de 2 caracteres para seu valor correspondente em decimal ('6'e'0' para 60)
unsigned char PORTB_SR;
unsigned char ultimo_caractere_recebido=0;
unsigned char cont=0;
unsigned int endereco_inic_eeprom=5;
unsigned int endereco_final_eeprom=5;
char *ptr_data;

bit enviar=0; //Permite o envio de mensagens de erro a central/usuário
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
  

//DIAS DA SEMANA: CORRESPONDÊNCIA DECIMAL
#define Domingo 0
#define Segunda 1
#define Terca 2
#define Quarta 3
#define Quinta 4
#define Sexta 5
#define Sabado 6


//MESES: CORRESPONDÊNCIA DECIMAL
#define Janeiro 0
#define Fevereiro 1
#define Marco 2
#define Abril 3  
#define Maio 4
#define Junho 5
#define Julho 6
#define Agosto 7
#define Setembro 8
#define Outubro 9
#define Novembro 10
#define Dezembro 11

//VALOR DECIMAL DE CADA ETAPA E ORDEM DAS ETAPAS
#define etapa_inicial 0
#define etapa_recebe_funcao 1
#define etapa_login 2					
#define etapa_detalha_funcao 3
#define etapa_final 4


//PARAMETROS DE CONFIGURAÇÃO DE CONTAS
#define QTD_MAX_CONTAS 16		
#define TAMANHO_SENHA 16
#define conta_admin 0

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

#define COLUNA_1 PORTBbits.RB0
#define COLUNA_2	PORTBbits.RB1
#define COLUNA_3	PORTBbits.RB2
#define COLUNA_4 PORTBbits.RB3   //Teclado matricial
#define LINHA_1 PORTBbits.RB4
#define LINHA_2 PORTBbits.RB5
#define LINHA_3 PORTBbits.RB6
#define LINHA_4 PORTBbits.RB7


#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) // OPERAÇÕES DE BIT
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))

void delay_ms(unsigned int delay_total){
    unsigned int temp = 0;
    while(temp < delay_total){
        __delay_ms(1);
        temp++;
    }}

void numero_para_ascii(char numero){
	char temp1;
	char temp2;

	TXREG = '+';
	while(!TRMT){}

	temp1 = numero/100;
	TXREG = '0'+ temp1;
	while(!TRMT){}

	temp2 = ((numero - temp1*100)/10);
	TXREG = '0'+ temp2;
	while(!TRMT){}

	TXREG = '0'+ (numero - (temp2*10) - (temp1*100));
	while(!TRMT){}

	TXREG = '+';
	while(!TRMT){}
}

char ascii_para_numero(char caractere3, char caractere2, char caractere1){
		char numero;
		numero=((caractere3 - '0')*100);
		numero+=((caractere2 - '0')*10);
		numero+=(caractere1 - '0');
		return numero;}


void config_serial(void){
		SYNC=0; //assincrono
		BRGH=1;
		BRG16=1;
		SPBRG=16;
		TX9=0;
		RX9=0;//tx e rx em 8 bits
		TXEN=1; //habilita transmissão
		RCIE=1; // interrupção por recepção
		CREN=1;
		SPEN=1;
		TXCKP = 0;
		TXIE = 0;
		TX9 = 0;
				}

void eeprom_config_inicial(void){
		char i;
		for(i=0;i<10;i++){
			eeprom_write(i,('0'+i));
			}
		eeprom_write(10,0);}


void verificar_num_contas(void){
		char i;
		for(i=0;i<QTD_MAX_CONTAS;i++){
			if(eeprom_read(i*TAMANHO_SENHA) != 255) qtd_total_contas++;
				}
								}


void carregar_senha(void){
					TXREG = '\n';
					while(!TRMT);
					char i = 0;

							do{
								senha[conta][i] = eeprom_read((conta*TAMANHO_SENHA) + i);
								TXREG= senha[conta][i];
								while(!TRMT);
								i++;} while( senha[i-1] && i<(TAMANHO_SENHA-1));

					nivel_acesso = eeprom_read((conta*TAMANHO_SENHA)+ (TAMANHO_SENHA-1));
					RCIE=1;}


void interrupt aux(void){

			if(TMR1IE && TMR1IF){
				TMR1H=128;
				if(++data_atual.segundo>59){
								data_atual.segundo=0; 

									if(++data_atual.minuto>59){


									data_atual.minuto=0;

											if(++data_atual.hora>23){ 

											data_atual.hora=0;
																if(++data_atual.dia_da_semana > Sabado) data_atual.dia_da_semana = Segunda;
																				
																if(++data_atual.dia > qtd_max_dias) {
																		data_atual.dia=0;
					
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
																				break;}
																									}  
					
					 												}	
																}
											}

				TMR1IF=0;}

			if(RBIE && RBIF){
					char coluna=0;
					char linha=0;
					PORTB_SR=PORTB;
					RBIF=0;
					if(PORTB_SR != 0xF0) {
							RBIE=0;
							debounce=1;
						LATDbits.LD0^=1;

							if(LINHA_1==0){linha=1; LATBbits.LB4=0;}

							else if(LINHA_2==0){linha=2;LATBbits.LB5=0;}

							else if(LINHA_3==0){linha=3;LATBbits.LB6=0;}

							else {linha=4;LATBbits.LB7=0;}

						TRISB=0x0F;
						
							if(COLUNA_1==0){coluna=1;}

							else if(COLUNA_2==0){coluna=2;}

							else if(COLUNA_3==0){coluna=3;}

							else {coluna=4;}

							
							TXREG = '\n';
							while(!TRMT){}
							numero_para_ascii(linha);
							numero_para_ascii(coluna);
							unsigned char caractere_temp;
							caractere_temp = teclado_matricial[linha][coluna];

								if(caractere_temp == MODO_T9_ON_OFF){modo_t9=~modo_t9;}

								else if(modo_t9){

										if(caractere_temp == MAIUSCULA_MINUSCULA) {maiuscula^=1;}

										else if(caractere_temp == ultimo_caractere_recebido) {
												if(++cont==4)cont=0;
												if(ultimo_caractere_recebido == '9' && cont==3)cont=0;  }
			
										else if(caractere_temp == FIM){
													if(!cont) caractere_recebido = ultimo_caractere_recebido;

													else caractere_recebido = (('a' + (cont-1) + ((ultimo_caractere_recebido - '1')*3))- maiuscula*32);
													ultimo_caractere_recebido=0;}
										else {
											ultimo_caractere_recebido = caractere_temp;
											cont=0;
										}
											}
								
								else{//modo_t9=0
										caractere_recebido = caractere_temp;}
			
						
						LATB=0x00;
						TRISB=0xF0;

							
					}

					PORTB_SR=PORTB;}

			if(RCIE && RCIF){
				
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
												if(funcao<ABERTURA_PORTA || funcao>MUDAR_SENHA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
												}
			
										else{
												conta = (dado_recebido - '0');
														if(!(conta<QTD_MAX_CONTAS)) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);
		
														else{
																setar_bit(FLAGS_1,TRANSICAO_ETAPA);
															}
											}
										
										ordem++;}
		
							
			
							else if(etapa == etapa_login){//executa funcao
		
										TXREG = 'J';
										while(!TRMT){}
										TXREG = senha[conta][ordem];
										while(!TRMT){}
		
										if(senha[conta][ordem] != dado_recebido){ 
															setar_bit(FLAGS_1,ERRO_SENHA);}
										ordem++;
										
										if(senha[conta][ordem] == NULL) setar_bit(FLAGS_1,TRANSICAO_ETAPA);
											
										}	
		
			
							else if(etapa == etapa_detalha_funcao){
										if(funcao == ABERTURA_PORTA || funcao == REQUERIMENTO_STATUS_ATUAL){
											
											if(ordem == 2){
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

										else if(funcao == RECONFIGURAR_PIC){
												//ordem 0 e 1 = ajuste de ano
												//ordem 2 e 3 = ajuste de mes
												//ordem 4 e 5 = ajuste de dia
												//ordem 6 e 7 = ajuste de hora
												//ordem 8 e 9 = ajuste de minuto
												//ordem 10 e 11 = ajuste de segundo

												if(dado_recebido == IGNORAR) {ordem+=2;} //Pula para o próximo ajuste
						
												else{
													if(ordem < 1 || ordem%2){buffer_serial = dado_recebido;}

													else{
															*ptr_data = ascii_para_numero(0,dado_recebido,buffer_serial);//buffer_serial = caractere2, dado_recebido = caractere1
															char temp = *ptr_data;
															numero_para_ascii(temp);
														}
													ordem++;
												}

											
												if(ordem == 12){
														setar_bit(FLAGS_1,TRANSICAO_ETAPA);
														ptr_data = &data_atual.ano;}

												else ptr_data+= (ordem/2);}

										else if(funcao == MUDAR_SENHA){
												//Para testes o fim da string será dado como '<' em vez de null	
		
												
												if(ordem==0){
															conta_a_ser_alterada = (dado_recebido - '0');
		
															if(conta_a_ser_alterada != conta){
																if(!(testar_bit(nivel_acesso,PERMISSAO_RECONFIGURAR_OUTRAS_CONTAS))){
																			setar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);}
																	}
															}
												
												else if(dado_recebido == '<') {
															if(ordem<5) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
		
															else setar_bit(FLAGS_1,TRANSICAO_ETAPA);
															}
			
												else{
													nova_senha[ordem-1] = dado_recebido;
													ordem++;
														if(ordem == (TAMANHO_SENHA-1)) {setar_bit(FLAGS_1,TRANSICAO_ETAPA);}
													}	
							
																	}
							}
			
							else if(etapa == etapa_final){//Fim da comunicação
										if(dado_recebido != FIM) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
										enviar=1;
										TXREG = '0' + enviar;
										while(!TRMT){}
										etapa = etapa_inicial;
										numero_para_ascii(FLAGS_1);}
		
							
							
							if(FLAGS_1>3) { 
											resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
											TXREG = '0' + etapa;
											while(!TRMT){}
											etapa = etapa_inicial;	
											enviar=1;}
			
			
						}
					RCIF=0;}

}


int main(void){

	//CONFIGURAÇÃO OSCILADOR
	OSCCON = 0xF2;

	//CONFIGURAÇÃO INTERRUPÇÕES
	INTCON = 0b11100000;
	INTCON2 =0b00000000;
	PIE1=0b00100001;
	RCONbits.IPEN = 0;

	//CONFIGURAÇÃO TIMER1(CONTAGEM HORAS)
	T1CON=	 0b00001111;
	TMR1H=0X80; //TMR1=32768(1 interrupção = 1s)
	TMR1L=0;
	
	//CONFIGURAÇÃO TIMER0(CONTAGEM DE TEMPO NO MODO_T9)
	T0CON = 0b10000111;
	TMR0H=0xC2; //TMR0=49991(1 interrupção = 2s)
	TMR0L= 0xF7;

	//CONFIGURAÇÃO DAS PORTAS
	LATD=0;
	LATB=0x00;
	TRISB=0xF0;
	TRISC=0xC3;
	TRISD=0x00;
	ADCON1=0XFF;
	CMCON=0X07;


	if(eeprom_read(0) == 0xFF) eeprom_config_inicial();
	config_serial();
	verificar_num_contas();
	
	char i;
		for(i=0;i<qtd_total_contas;i++){
			carregar_senha();
			conta++;}
	conta=0;

	data_atual.ano=0;
	data_atual.mes=0;
	data_atual.dia=0;
	data_atual.dia_da_semana=0;
	data_atual.hora=0;
	data_atual.minuto=0;
	data_atual.segundo=0;
	
	ptr_data= &data_atual.ano;

	PORTB_SR=PORTB;//Leitura do PORTB antes de habilitar a interrupção para evitar uma interrupção não desejada.
	RBIE=1;
	RBIF=0;

	while(1){
		

		if(enviar==1){
			enviar=0;
			LATDbits.LD2=1;
			TXREG = '\n';
			while(!TRMT){}
			TXREG = INICIO;
			while(!TRMT){}

						if(FLAGS_1<4){ //Não houve erros
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


		if(PORTB == 0xF0 && RBIE==0 && debounce==1){//Tratamento de debounce. Espera-se até que nenhum botão esteja pressionado e que o debounce esteja autorizado
																			//(existem situações em que RBIE=0 e não se quer fazer tratamento de debounce
					delay_ms(200);
					PORTB_SR=PORTB;//leitura do PORTB antes de ativar a interrupção para evitar uma interrupção não desejada.
					RBIE=1;
					debounce=0;
					if(caractere_recebido){
							TXREG = caractere_recebido;
							caractere_recebido=0;}}

}
}