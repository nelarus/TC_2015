

//PARAMETRO PARA BUFFER SERIAL
#define TAMANHO_BUFFER_SERIAL 80
//

//PARAMETRO PARA BUFFER TECLADO MATRICIAL

#define TAMANHO_BUFFER_TECLADO_MATRICIAL 40

//MODOS DE RECEPÇÃO DE DADOS
#define MODO_TECLADO_MATRICIAL testar_bit(FLAGS_3,MODO_BT)
#define MODO_BLUETOOTH (!(testar_bit(FLAGS_3,MODO_TECLADO)))
#define modo_teclado_matricial() setar_bit(FLAGS_3,MODO_TECLADO)
#define modo_bluetooth() resetar_bit(FLAGS_3,MODO_BT)
//

//CORRESPONDÊNCIA DE CARACTERES NA COMUNICAÇÃO SERIAL E RECEBIMENTO POR TECLADO MATRICIAL

	#define MODO_DEBUG_ON_OFF '^'	//Se o caracter recebido for esse o programa irá ignorar o protocolo e entrar em modo de debug(a ser implementado)

	//FUNÇÕES DO SISTEMA
	#define ABERTURA_PORTA '0'
	#define REQUERIMENTO_HISTORICO '1'
	#define REQUERIMENTO_STATUS_ATUAL '2'
	#define RECONFIGURAR_CONTA '3' 
	#define RECONFIGURAR_PIC '4'
	#define RECONFIGURAR_MODULO '5'
	#define MUDAR_SENHA_OUTRA_CONTA '6'
	#define MUDAR_SENHA_PROPRIA_CONTA '7'
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
	//RECEBIMENTO DE SENHAS
	#define FIM_DE_SENHA '<'

	//TECLADO MATRICIAL
	#define MAIUSCULA_MINUSCULA '*' //alterna entre minuscula e maiuscula no recebimento de letras pelo teclado matricial
	#define MODO_T9_ON_OFF 'A'
	#define VOLTAR_CARACTERE 'D' //retorna em um caractere a senha(similar ao return de um teclado normal)


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
#define etapa_recebe_funcao 1
#define etapa_login 2					
#define etapa_detalha_funcao 3
#define etapa_final 4
//

//PARAMETROS DA FECHADURA
#define ID_DESSA_FECHADURA '0'