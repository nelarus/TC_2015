void configurar_oscilador(void);

void configurar_interrupcoes(void);

void configurar_portas(void);


//RENOMEA��O DOS PINOS DAS PORTAS E DOS LATCHES
#define FECHADURA LATBbits.LB0    //Destravamento ou n�o da fechadura
#define SENSOR_ABERTURA_FECHADURA PORTBbits.RB3 //Sensor magn�tico(reed switch)
#define SENSOR_ABERTURA_CAIXA PORTBbits.RB2 //reed switch que indica que a caixa em que o circuito est� alojado foi aberta

#define FECHADURA_TRAVADA SENSOR_ABERTURA_FECHADURA==0
#define DESTRAVAR_FECHADURA() FECHADURA=1
#define TRAVAR_FECHADURA() FECHADURA=0

