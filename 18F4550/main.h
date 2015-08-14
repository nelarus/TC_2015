
//PARAMETRO PARA FREQ DE OSCILAÇÃO
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif
//
//PARAMETRO PARA CONTAS
#ifndef QTD_MAX_CONTAS
#define QTD_MAX_CONTAS 16
#endif

#ifndef	TAMANHO_SENHA
#define TAMANHO_SENHA 16
#endif
//

//PARAMETRO PARA BUFFER SERIAL
#define TAMANHO_BUFFER_SERIAL 80
//

//PARAMETRO PARA BUFFER TECLADO MATRICIAL

#define TAMANHO_BUFFER_TECLADO_MATRICIAL 40


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
	

	#define NOVA_LINHA '\n'


	//TECLADO MATRICIAL
	#define MAIUSCULA_MINUSCULA '*'
	#define MODO_T9_ON_OFF 'A'
	#define MODO_DEBUG_ON_OFF '^'	//Se o caracter recebido for esse o programa irá ignorar o protocolo e entrar em modo de debug(a ser implementado)


//FLAGS NIVEL DE ACESSO
#define PERMISSAO_ABRIR_PORTA 0
#define PERMISSAO_REQUERIMENTO_HISTORICO 1
#define PERMISSAO_REQUERIMENTO_STATUS_ATUAL 2
#define PERMISSAO_RECONFIGURAR_PROPRIA_CONTA 3
#define PERMISSAO_RECONFIGURAR_PIC 4  
#define PERMISSAO_RECONFIGURAR_MODULO 5
#define PERMISSAO_MUDAR_SENHA_OUTRAS_CONTAS 6
#define PERMISSAO_MUDAR_PROPRIA_SENHA 7


//#DEFINE configurar_velocidade variavel=5;

//51: configurar_velocidade
//51: variavel=5:
//FLAGS_1;CORRESPONDÊNCIA DE BITS
#define ERRO_SENHA 6
#define ERRO_PROTOCOLO 7
#define ERRO_IDENTIF_CONTA 2
#define ERRO_NIVEL_DE_ACESSO 3
#define ERRO_COMUNICACAO 4  
#define ERRO_ABERTURA 5
#define TRANSICAO_ETAPA 0
#define ERRO_SESSAO_EXPIRADA 1

//FLAGS_2 CORRESPONDENCIA DE BITS
#define ENVIAR 0
#define RECEBER 1
#define MODO_BT_TECLADO 2
#define DEBOUNCE 3
#define MODO_T9 4
#define MAIUSCULA 5
#define MODO_DEBUG_ON 6

//FLAGS_3 CORRESPONDENCIA DE BITS
#define SESSAO_EXPIRADA 0

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
//

//VALOR DECIMAL DE CADA ETAPA E ORDEM DAS ETAPAS
#define etapa_inicial 0
#define etapa_recebe_funcao 1
#define etapa_login 2					
#define etapa_detalha_funcao 3
#define etapa_final 4
//

//MODOS DE RECEPÇÃO DE DADOS

#define MODO_TECLADO_MATRICIAL modo_bluetooth_teclado==1
#define MODO_BLUETOOTH modo_bluetooth_teclado==0
#define modo_teclado_matricial() modo_bluetooth_teclado=1;
#define modo_bluetooth() modo_bluetooth_teclado=0;
//

// OPERAÇÕES DE BIT
#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) 
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define inverter_bit(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
//

//Strings
#define ZERAR(STRING) memset(STRING,0,(strlen(STRING)))

//etc.
#define FECHADURA_TRAVADA SENSOR_ABERTURA_FECHADURA==0

#define DESTRAVAR_FECHADURA(TEMPO); FECHADURA=1;delay_ms(TEMPO);FECHADURA=0;

#define conta_admin 0
#define nivel_acesso senha[conta][TAMANHO_SENHA-1]


