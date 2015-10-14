

//PARAMETRO PARA BUFFER SERIAL
#define TAMANHO_BUFFER_SERIAL 80
//

//PARAMETRO PARA BUFFER TECLADO MATRICIAL

#define TAMANHO_BUFFER_TECLADO_MATRICIAL 18

//TAMANHO DE NOVO PARAMETRO DO MODULO BLUETOOTH(EXEMPLO:NOVO NOME)
#define TAMANHO_PARAMETRO_BT 16

//MODOS DE RECEPÇÃO DE DADOS
#define MODO_TECLADO_MATRICIAL testar_bit(FLAGS_3,MODO_TECLADO)
#define MODO_BLUETOOTH 	testar_bit(FLAGS_3,MODO_BT)
#define MODO_COMANDO_AT testar_bit(FLAGS_3,MODO_AT)
#define MODO_DEBUG testar_bit(FLAGS_3,MODO_DEBUG_ON)

#define modo_teclado_matricial() setar_bit(FLAGS_3,MODO_TECLADO); resetar_bit(FLAGS_3,MODO_BT)
#define modo_bluetooth() setar_bit(FLAGS_3,MODO_BT);resetar_bit(FLAGS_3,MODO_TECLADO)
#define modo_comando_at() setar_bit(FLAGS_3,MODO_AT)

#define desativar_modo_bluetooth() resetar_bit(FLAGS_3,MODO_BT)
#define desativar_modo_teclado_matricial() resetar_bit(FLAGS_3,MODO_TECLADO)

//


//CORRESPONDÊNCIA DE CARACTERES NA COMUNICAÇÃO SERIAL E RECEBIMENTO POR TECLADO MATRICIAL




	//FUNÇÕES DO SISTEMA
	#define ABERTURA_PORTA '0'
	#define REQUERIMENTO_HISTORICO '1'
	#define REQUERIMENTO_STATUS_ATUAL '2'
	#define RECONFIGURAR_CONTA '3' 
	#define RECONFIGURAR_PIC '4'
	#define RECONFIGURAR_MODULO '5'
	#define MUDAR_SENHA_OUTRA_CONTA '6'
	#define MUDAR_SENHA_PROPRIA_CONTA '7'
	#define ATIVAR_MODO_DEBUG '^'	//Ativa o modo debug no qual o PIC irá enviar ao dispositivo do programador os caracteres que o pic está recebendo e o que está ocorrendo internamente no programa
	#define REPASSAR_MENSAGEM 'R'

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
	#define MAIUSCULA_MINUSCULA '*' //alterna entre minuscula e maiuscula no recebimento de letras pelo teclado matricial
	#define MODO_T9_ON_OFF 'A'
	#define VOLTAR_CARACTERE 'C' //retorna em um caractere a senha(similar ao return de um teclado normal)
	#define LIMPAR_SENHA 'D'


//PINOS DO TECLADO MATRICIAL(LINHAS E COLUNAS)
#define COLUNA_1 PORTBbits.RB7
#define COLUNA_2	PORTBbits.RB6
#define COLUNA_3	PORTBbits.RB5
#define COLUNA_4 PORTBbits.RB4 
#define LINHA_1 PORTDbits.RD4
#define LINHA_2 PORTDbits.RD5
#define LINHA_3 PORTDbits.RD6
#define LINHA_4 PORTDbits.RD7
//É pela combinação de linha e coluna que se sabe qual caractere foi inserido

//PARAMETROS TECLADO MATRICIAL MODO T9
#define Letras_por_tecla 3


//VALOR DECIMAL DE CADA ETAPA E ORDEM DAS ETAPAS
#define etapa_inicial 0
#define etapa_identificacao 1
#define etapa_login 2					
#define etapa_detalha_funcao 3
#define etapa_final 4
//

//RECONFIGURAÇÃO DO PIC
#define ALTERAR_ANO 0
#define ALTERAR_MES 1
#define ALTERAR_DIA 2
#define ALTERAR_HORA 3
#define ALTERAR_MINUTO 4
#define ALTERAR_SEGUNDO 5

//PEDIDO STATUS ATUAL

#define STATUS_DATA testar_bit(pedido_status_1,0)
#define STATUS_PORTA testar_bit(pedido_status_1,1)
#define STATUS_RECONFIGURACAO_MODULO testar_bit(pedido_status_1,2)
#define STATUS_FLAGS testar_bit(pedido_status_1,3)
#define STATUS_EEPROM testar_bit(pedido_status_1,4)



//Fechadura

#define NUMERO_DESSA_FECHADURA '0'


//Nivel de acesso

#define FUNCAO_NAO_AUTORIZADA !testar_bit(nivel_acesso, ascii_para_numero(NULL,NULL,funcao))