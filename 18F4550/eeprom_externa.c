#include <xc.h>
#include "main.h"
#include "eeprom_externa.h"
#include "banco_de_dados.h"
#include "ascii.h"
#include "serial.h"
#include "time.h"
#include "recebimento_dados.h"
unsigned char myReadI2C( void )
{
if( ((SSPCON1&0x0F)==0x08) || ((SSPCON1&0x0F)==0x0B) )	//master mode only
  SSPCON2bits.RCEN = 1;           // enable master for 1 byte reception
  char x=0;
  while ( !SSPSTATbits.BF ){
		__delay_us(1);
		if(++x == 100) break;}    // wait until byte received  
  if(x==100) {
	enviar_string_serial("\n\rxxx\n\r");
	return 0x00;
		}
  
  else { return ( SSPBUF );}           // return with read byte 
}

void escrever_byte_eeprom_externa(char endereco_h, char endereco_l, char valor){
	IdleI2C();
	StartI2C();
	IdleI2C();
	putcI2C(ESCRITA_EEPROM);
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_h);	
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_l);
	__delay_us(20);
	IdleI2C();	
	putcI2C(valor);
	__delay_us(20);
	IdleI2C();
	StopI2C();
	IdleI2C();
}

char ler_byte_eeprom_externa(char endereco_h, char endereco_l){
	
	char valor_leitura;
	IdleI2C();
	StartI2C();
	IdleI2C();
	putcI2C(ESCRITA_EEPROM);
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_h);
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_l);
	__delay_us(20);
	StartI2C();
	IdleI2C();
	putcI2C(LEITURA_EEPROM);
	__delay_us(20);
	IdleI2C();
	valor_leitura = myReadI2C();
	NotAckI2C();
	StopI2C();
	return valor_leitura;
}

int ler_inteiro_eeprom_externa(int endereco_1){
	char endereco_h;
	char endereco_l;
	char valor_leitura_h;
	char valor_leitura_l;
	endereco_l  = endereco_1;
	endereco_h = (endereco_1 >> 8);

	StartI2C();
	IdleI2C();
	putcI2C(ESCRITA_EEPROM);
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_h);
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_l);
	__delay_us(20);
	StartI2C();
	IdleI2C();
	putcI2C(LEITURA_EEPROM);
	__delay_us(20);
	IdleI2C();  

	valor_leitura_h = ReadI2C();
	AckI2C();
	IdleI2C();
	valor_leitura_l = ReadI2C();
	NotAckI2C();
	StopI2C();

	return ((valor_leitura_h<<8)+ valor_leitura_l);}


void escrever_string_eeprom_externa(char endereco_h, char endereco_l, const char *string_a_escrever,char quantidade){
	IdleI2C();
	StartI2C();
	IdleI2C();
	putcI2C(ESCRITA_EEPROM);
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_h);	
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_l);
	__delay_us(20);
	IdleI2C();
	if(!quantidade){
		while(*string_a_escrever){
			putcI2C(*string_a_escrever);
			__delay_us(20);
			IdleI2C();
			string_a_escrever++;}
	}

	else{
		while(quantidade--){	
			putcI2C(*string_a_escrever);
			__delay_us(20);
			IdleI2C();
			string_a_escrever++;}
		}
	StopI2C();}

void ler_string_eeprom_externa(char endereco_h, char endereco_l,char *string_a_receber, char quantidade){
	char valor_leitura;
	StartI2C();
	IdleI2C();
	putcI2C(ESCRITA_EEPROM);
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_h);
	__delay_us(20);
	IdleI2C();
	putcI2C(endereco_l);
	IdleI2C();
	__delay_us(20);
	StartI2C();
	IdleI2C();
	putcI2C(LEITURA_EEPROM);
	__delay_us(20);
	IdleI2C();
	while(quantidade){
		IdleI2C();
		*string_a_receber++ = myReadI2C();

		if(--quantidade)AckI2C();
	}
	IdleI2C();
	NotAckI2C();
	StopI2C();
}


void registrar_acesso(char funcao,char conta, char dia,char hora, char minuto,char mes_atual, char ano_atual){
	int  endereco_fim_mes;//Endereço onde os registros do mês atual terminam, localizado no bloco 4
	int  endereco_indice_fim_mes; //Endereço do índice que tem o valor do endereço do fim do mês atual
	char registro_acesso[3];

	endereco_indice_fim_mes = ENDERECO_INICIAL_BLOCO3 + ( ((mes_atual)+ (ano_atual*12)) *2);

	ler_string_eeprom_externa(endereco_indice_fim_mes>>8, endereco_indice_fim_mes,&endereco_fim_mes,2);
	Resetar_COM_I2C();
	if(endereco_indice_fim_mes == 706) enviar_string_serial("\n706");
	if(endereco_fim_mes == ENDERECO_INICIAL_BLOCO4) enviar_string_serial("\n1376");
	
	registro_acesso[0] = conta<<4;
	registro_acesso[0] += funcao;
	registro_acesso[1] = dia<<3;
	registro_acesso[1] += (hora&0b00011100)>>2;
	
	
	registro_acesso[2] = (hora&0b00000011)<<6;
	registro_acesso[2]+= minuto;

	delay_ms(2);
	escrever_string_eeprom_externa(endereco_fim_mes>>8, endereco_fim_mes,&registro_acesso[0],3);
	delay_ms(20);
	escrever_byte_eeprom_externa( (endereco_fim_mes+2)>>8,(endereco_fim_mes+2),registro_acesso[2]);
	delay_ms(6);
	numero_para_ascii(	registro_acesso[0]);
	numero_para_ascii(	registro_acesso[1]);
	numero_para_ascii(	registro_acesso[2]);
	endereco_fim_mes+=3;
	numero_para_ascii(endereco_fim_mes>>8);
	numero_para_ascii(endereco_fim_mes);

	escrever_string_eeprom_externa(endereco_indice_fim_mes>>8, endereco_indice_fim_mes,&endereco_fim_mes,2);
	delay_ms(12);
	endereco_indice_fim_mes+=2;
	escrever_string_eeprom_externa(endereco_indice_fim_mes>>8, endereco_indice_fim_mes,&endereco_fim_mes,2);
	delay_ms(12);

	numero_para_ascii(ler_byte_eeprom_externa(706>>8,706));
	numero_para_ascii(ler_byte_eeprom_externa(707>>8,707));
	numero_para_ascii(ler_byte_eeprom_externa(708>>8,708));
	numero_para_ascii(ler_byte_eeprom_externa(709>>8,709));
	
	enviar_string_serial("\n\r");
}

void enviar_historico_acessos(char mes_inicial, char mes_final, char ano_inicial, char ano_final){

	int endereco_indice_segundo_mes;//variável usada para indicar se o indice do segundo mes(fev/2015) é maior que o primeiro(jan/2015), o que indica que há registros armazenados;
	ler_string_eeprom_externa( (ENDERECO_INICIAL_BLOCO3+2)>>8,(ENDERECO_INICIAL_BLOCO3+2),&endereco_indice_segundo_mes,2);
	Resetar_COM_I2C();

	if(endereco_indice_segundo_mes != ENDERECO_INICIAL_BLOCO4){
		int endereco_inicial = ENDERECO_INICIAL_BLOCO3 + (((mes_inicial-1)+ ano_inicial*12)*2);
		enviar_string_serial("\n\rAnt_leit:");
		numero_para_ascii(endereco_inicial>>8);
		numero_para_ascii(endereco_inicial);
		
		ler_string_eeprom_externa(endereco_inicial>>8,endereco_inicial,&endereco_inicial,2); //Pega o valor do índice correspondente a data inicial. Faz-se o mes-1 pois os meses começam em 1 no programa, mas na memória externa começam em 0
		Resetar_COM_I2C();
		
		
		enviar_string_serial("\n\rdep_leit:");
		numero_para_ascii(endereco_inicial>>8);
		numero_para_ascii(endereco_inicial);

		
		int endereco_final = ENDERECO_INICIAL_BLOCO3 + (((mes_final)+ ano_final*12)*2);
		
		enviar_string_serial("\n\rAnt_leit:");
		numero_para_ascii(endereco_final>>8);
		numero_para_ascii(endereco_final);
		ler_string_eeprom_externa(endereco_final>>8,endereco_final,&endereco_final,2); //Pega o valor do indice correspondente ao mês seguinte da data final.
																						//Pois esse valor indica quando os registros da data final terminam. 
																						//Ex: janeiro de 2016: termina no endereço do indice que corresponde a fevereiro de 2016
		
		
		Resetar_COM_I2C();
		
		enviar_string_serial("\n\rdep_leit:");
		numero_para_ascii(endereco_final>>8);
		numero_para_ascii(endereco_final);

		while(endereco_final == ENDERECO_INICIAL_BLOCO4){

		mes_final--;
		numero_para_ascii(mes_final);
		endereco_final = ENDERECO_INICIAL_BLOCO3 + (((mes_final)+ ano_final*12)*2);
		ler_string_eeprom_externa(endereco_final>>8,endereco_final,&endereco_final,2);	
		
		enviar_string_serial("\n\rdep_leit:");
		numero_para_ascii(endereco_final>>8);
		numero_para_ascii(endereco_final); 
		Resetar_COM_I2C();
		}


		enviar_string_serial("\n\r");
		int quantidade = endereco_final-endereco_inicial;
		
		char mes_acessos=mes_inicial;
		char ano_acessos=ano_inicial;
		int endereco_indice_proximo_mes = ENDERECO_INICIAL_BLOCO3 + (((mes_acessos)+ ano_acessos*12)*2);
		
		numero_para_ascii(endereco_indice_proximo_mes>>8);
		numero_para_ascii(endereco_indice_proximo_mes); 
		enviar_string_serial("\n\rEND_PROX_MES:");
		ler_string_eeprom_externa( (endereco_indice_proximo_mes>>8),endereco_indice_proximo_mes, &endereco_indice_proximo_mes,2);
		
		numero_para_ascii(endereco_indice_proximo_mes>>8);
		numero_para_ascii(endereco_indice_proximo_mes); 
		
		Resetar_COM_I2C();

		if(quantidade<=126){
				char dados_lidos[126];
				ler_string_eeprom_externa( (endereco_inicial>>8),endereco_inicial, &dados_lidos[0],quantidade);
				Resetar_COM_I2C();
				char i;

			enviar_string_serial("\n\r");
				for(i=0;i<quantidade;i+=3){

					if(!i || (endereco_inicial+i==endereco_indice_proximo_mes)){
							switch (mes_acessos){
								
							case Janeiro:
			enviar_string_serial("\n\rJaneiro");
							break;
							case Marco:
			enviar_string_serial("\n\rMarco");
							break;
							case Maio:
			enviar_string_serial("\n\rMaio");
							break;
							case Julho:
			enviar_string_serial("\n\rJulho");
							break;
							case Agosto:
			enviar_string_serial("\n\rAgosto");
							break;
							case Outubro:
			enviar_string_serial("\n\rOutubro");
							break;
							case Dezembro:
			enviar_string_serial("\n\rDezembro");
							break;
					
							case Fevereiro:
			enviar_string_serial("\n\rFevereiro");
							break;
					
							case Abril:
			enviar_string_serial("\n\rAbril");
							
							break;
							case Junho:
			enviar_string_serial("\n\rJunho");
							
							break;
							case Setembro:
			enviar_string_serial("\n\rSetembro");
							
							break;
							case Novembro:
			enviar_string_serial("\n\rNovembro");
							
							break;
							default:
							ano_acessos++;
							mes_acessos=Janeiro;
							
							break;

							}
						char ano_temp = (ano_acessos+15)/10;
						ano_temp = (ano_acessos+15) - ano_temp*10;
						enviar_string_serial(" de 20");
						enviar_caractere_serial('0'+ ((ano_acessos+15)/10));
						enviar_caractere_serial('0'+ ano_temp);

						if(i){
							numero_para_ascii(mes_acessos);
							endereco_indice_proximo_mes = ENDERECO_INICIAL_BLOCO3 + (((mes_acessos)+ ano_acessos*12)*2);
							
							numero_para_ascii(endereco_indice_proximo_mes>>8);
							numero_para_ascii(endereco_indice_proximo_mes); 

							ler_string_eeprom_externa( (endereco_indice_proximo_mes>>8),endereco_indice_proximo_mes, &endereco_indice_proximo_mes,2);
							enviar_string_serial("\n\rEND_PROX_MES:");
							numero_para_ascii(endereco_indice_proximo_mes>>8);
							numero_para_ascii(endereco_indice_proximo_mes); 
							Resetar_COM_I2C();
						}
						
						mes_acessos++;
						}
					enviar_string_serial("\n\rfuncao:");
					char funcao = dados_lidos[i]&0X0F;

					switch (funcao){
						case ABERTURA_PORTA - '0':
						enviar_string_serial("ABERTURA_PORTA");
						break;

						case  REQUERIMENTO_HISTORICO - '0':
						enviar_string_serial("REQUERIMENTO_HISTORICO");
						break;

						case REQUERIMENTO_STATUS_ATUAL - '0':
						enviar_string_serial("REQUERIMENTO_STATUS_ATUAL");
						break;

						case RECONFIGURAR_PIC - '0':
						enviar_string_serial(" RECONFIGURAR_PIC");
						break;

						case RECONFIGURAR_MODULO - '0':
						enviar_string_serial(" RECONFIGURAR_MODULO");
						break;

						case MUDAR_SENHA_OUTRA_CONTA - '0':
						enviar_string_serial("MUDAR_SENHA_OUTRA_CONTA");
						break;

						case MUDAR_SENHA_PROPRIA_CONTA- '0':
						enviar_string_serial("MUDAR_SENHA_PROPRIA_CONTA");
						break;

						case ATIVAR_MODO_DEBUG - '0':
						enviar_string_serial("ATIVAR_MODO_DEBUG");
						break;

						default:
						enviar_string_serial("FUNCAO_NAO_REGISTRADA");
						numero_para_ascii(funcao);
						break;	

					}
					enviar_string_serial("\n\rconta:");numero_para_ascii((dados_lidos[i]&0xF0)>>4);
					enviar_string_serial("\n\rdia:");numero_para_ascii((dados_lidos[i+1]&0b11111000)>>3);
					char hora_lida =  ((dados_lidos[i+1]&0b00000111)<<2);
					hora_lida+= ((dados_lidos[i+2]&0b11000000)>>6);
					
					enviar_string_serial("\n\rhora:");numero_para_ascii( hora_lida);
					enviar_string_serial("\n\rminuto"); numero_para_ascii(dados_lidos[i+2]&0b00111111);
					enviar_string_serial("\n\r");
				
	
				}
			
	
		}
	}

	else{
		enviar_string_serial("\n\rNao ha registros de acessos");}
}


void armazenar_senha_eeprom_externa(char nova_senha[],char senha_a_armazenar[][TAMANHO_SENHA+3],char conta){//armazena a nova senha na RAM e na eeprom externa
	char i=0;
	do{ //escreve a senha na eeprom
		senha_a_armazenar[conta][i] = nova_senha[i];
		i++;} while(nova_senha[i-1]  && i<(TAMANHO_SENHA-1));


	escrever_string_eeprom_externa(0x00,(conta*16),&senha_a_armazenar[conta][0],15);

}

void carregar_senhas(char senha_a_carregar[][TAMANHO_SENHA+1]){
	char num_conta=0;
	for(num_conta=0;num_conta<16;num_conta++){
		numero_para_ascii(num_conta);
		ler_string_eeprom_externa(0x00,num_conta*0x10, &senha_a_carregar[num_conta][0],15);
		Resetar_COM_I2C();
		senha_a_carregar[num_conta][TAMANHO_SENHA] = ler_byte_eeprom_externa(0x00,0x0F + (num_conta*0x10));
		}
}

void carregar_horarios_acesso(char horarios_a_carregar[][7][4]){
		
	char num_conta=0;
		for(num_conta=0;num_conta<16;num_conta++){
			int endereco_horarios = ENDERECO_INICIAL_BLOCO2 +(28*num_conta);
			ler_string_eeprom_externa(endereco_horarios>>8,endereco_horarios, &horarios_a_carregar[num_conta][0][0],28);
			Resetar_COM_I2C();
		}
}

void Resetar_COM_I2C(void){
	char i;
		SSPEN=0;
		PORTB=PORTB;
		WCOL=SSPOV=0;
		TRISBbits.TRISB1=0;
		TRISBbits.TRISB0=1;
		LATBbits.LATB1=1;
		char x=0;
		while(!RB0){
		TRISBbits.TRISB0=1;
		TRISBbits.TRISB1=1;
		__delay_us(10);
		TRISBbits.TRISB1=0;
		RB1=0;
		__delay_us(10);
		}
		SSPEN=1;
		OpenI2C(MASTER,SLEW_OFF);
		SSPADD =0x27;
	
}

void config_inicial_bloco2(void){
	char horario_conta0[28];
	char horario_conta1[28];
	char i;
	for(i=0;i<25;i+=4){
		horario_conta0[i]=0;
		horario_conta0[i+1]=0;
		horario_conta0[i+2]=24;
		horario_conta0[i+3]=0;
		}

	for(i=0;i<25;i+=4){
		horario_conta1[i]=5;
		horario_conta1[i+1]=14;
		horario_conta1[i+2]=15;
		horario_conta1[i+3]=17;
		}
	escrever_byte_eeprom_externa(0x02,0xA2,0X00);
	delay_ms(6);
	escrever_byte_eeprom_externa(0x02,0xA3,0X00);
	delay_ms(6);

	escrever_string_eeprom_externa(0x01,0x00,&horario_conta0[0],28);
	delay_ms(160);
	escrever_string_eeprom_externa(0x01,28,&horario_conta1[0],28);
	delay_ms(160);


}

void config_inicial_bloco3(void){}

void zerar_eeprom_externa(void){
	unsigned int m;
	for(m=0;m<32768;m++){
		if(ler_byte_eeprom_externa(m>>8,m) != 0x00){ 
			escrever_byte_eeprom_externa(m>>8,m,0x00);
			delay_ms(6);}
	}
}