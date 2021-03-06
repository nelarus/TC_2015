#ifndef _XTAL_FREQ
#define _XTAL_FREQ 16000000
#endif

//BUFFERS
#define TAMANHO_BUFFER_SERIAL 80
#define TAMANHO_BUFFER_TECLADO_MATRICIAL 40

//PARAMETROS DE CONFIGURA��O DE CONTAS
#define QTD_MAX_CONTAS 16      
#define TAMANHO_SENHA 16
#define conta_admin 0
#define nivel_acesso ((conta*TAMANHO_SENHA)+ (TAMANHO_SENHA-1))

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
  
//PARAMETROS TECLADO MATRICIAL MODO T9
#define Letras_por_tecla 3

//DIAS DA SEMANA: CORRESPOND�NCIA DECIMAL
#define Domingo 0
#define Segunda 1
#define Terca 2
#define Quarta 3
#define Quinta 4
#define Sexta 5
#define Sabado 6


//MESES: CORRESPOND�NCIA DECIMAL
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




//MODOS DE RECEP��O DE DADOS

#define MODO_TECLADO_MATRICIAL modo_bluetooth_teclado==1
#define MODO_BLUETOOTH modo_bluetooth_teclado==1
#define modo_teclado_matricial() modo_bluetooth_teclado=1;
#define modo_bluetooth() modo_bluetooth_teclado=0;

//CORRESPOND�NCIA DE CARACTERES NA COMUNICA��O SERIAL E RECEBIMENTO POR TECLADO MATRICIAL

   //FUN��ES DO SISTEMA
   #define ABERTURA_PORTA '0'
   #define REQUERIMENTO_HISTORICO '1'
   #define REQUERIMENTO_STATUS_ATUAL '2'
   #define RECONFIGURAR_CONTA '3' 
   #define RECONFIGURAR_PIC '4'
   #define RECONFIGURAR_MODULO '5'
   #define MUDAR_SENHA '7'   

   //OUTROS CARACTERES
   #define INICIALIZAR '*' //INDICA QUE O PIC INICIALIZOU OU REINICIALIZOU.
   #define PROXIMA_ETAPA '>' //TRANSI��O ENTRE ETAPAS
   #define IGNORAR 'X' //Indica que a a��o que deveria ser executa n�o ser� mais. Ex: Reconfigura��o de conta: N�o ser� feito o ajuste de hora
   #define PAUSAR 'P'
   #define CONTINUAR 'C' //PAUSA PARA CARREGAMENTO DE SENHA DA EEPROM E SINALIZA��O PARA CONTINAR
   #define OVERRUN 'O'
   #define FRAME_ERROR 'F'  //CARACTERES PARA INDICAR ERRO NA COMUNICA��O SERIAL
   #define INICIO 'I'      //INICIO  DA COMUNICA��O SERIAL
   #define FIM 'F'         // FIM DA COMUNICA��O SERIAL. 
                                          //No modo teclado matricial usa-se para auxiliar na inser��o de letras quando modo_t9=1;
                                          //Ex: Para inserir a letra 'a' se aperta '1' duas vezes e por fim '#'(que aqui corresponder� a 'F')
   

   #define MAIUSCULA_MINUSCULA 'M'
   #define MODO_T9_ON_OFF 'A'
   #define MODO_DEBUG '^'   //Se o caracter recebido for esse o programa ir� ignorar o protocolo e entrar em modo de debug(a ser implementado)


//FLAGS NIVEL DE ACESSO
#define PERMISSAO_ABRIR_PORTA 0
#define PERMISSAO_REQUERIMENTO_HISTORICO 1
#define PERMISSAO_REQUERIMENTO_STATUS_ATUAL 2
#define PERMISSAO_RECONFIGURAR_PROPRIA_CONTA 3
#define PERMISSAO_RECONFIGURAR_PIC 4  
#define PERMISSAO_RECONFIGURAR_MODULO 5
#define PERMISSAO_RECONFIGURAR_OUTRAS_CONTAS 6
#define PERMISSAO_MUDAR_PROPRIA_SENHA 7


//FLAGS_1;CORRESPOND�NCIA DE BITS
#define ERRO_SENHA 6
#define ERRO_PROTOCOLO 7
#define ERRO_IDENTIF_CONTA 2
#define ERRO_NIVEL_DE_ACESSO 3
#define ERRO_COMUNICACAO 4  
#define ERRO_DESCONHECIDO 5
#define TRANSICAO_ETAPA 0
#define TROCA_SENHA 1

//FLAGS_2;CORRESPOND�NCIA DE BITS
#define MODO_T9 0
#define MAIUSCULA 1

//RENOMEA��O DOS PINOS DAS PORTAS E DOS LATCHES
#define LED PORTCbits.RC5         //Mostra que a contagem de horas est� funcionando
#define FECHADURA PORTCbits.RC0    //Destravamento ou n�o da fechadura
#define SENSOR_ABERTURA_FECHADURA PORTAbits.RA0 //Sensor magn�tico(reed switch)

#define COLUNA_1 PORTBbits.RB7
#define COLUNA_2   PORTBbits.RB6
#define COLUNA_3   PORTBbits.RB5
#define COLUNA_4 PORTBbits.RB4   //Teclado matricial
#define LINHA_1 PORTDbits.RD4
#define LINHA_2 PORTDbits.RD5
#define LINHA_3 PORTDbits.RD6
#define LINHA_4 PORTDbits.RD7


#define setar_bit(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define resetar_bit(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT)) // OPERA��ES DE BIT
#define testar_bit(ADDRESS,BIT) (ADDRESS & (1<<BIT))
#define inverter_bit(ADDRESS,BIT) (ADDRESS ^= (1<<BIT) )

#define NOVA_LINHA '\n'
