#include <xc.h>
#include "configuracao_pic.h"


void configurar_oscilador(void){
	OSCCON=0XF0;}

void configurar_interrupcoes(void){
	INTCON = 0b11100000;
	INTCON2 =0b00000000;
	PIE1=0b00100001;
	RCONbits.IPEN = 0;}


void configurar_portas(void){
	LATD=0; //4 primeiros bits = LEDs para debug(indicam se algo aconteceu, como o pressionamento do botão do teclado matricial ou o funcionamento do timer0(relógio) )
			//4 ultimos bits -> Teclado matricial
	
	
	TRISB=0xFC; // 4 ultimos bits-> teclado matricial
	TRISA=0x00;
	TRISE=0X04;
	TRISE2=1;
	LATB=0x00; 
	TRISC=0xCF;
	TRISD=0x00;
	ADCON1=0XFF;
	CMCON=0X07;}