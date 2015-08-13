#include "main.h"
#include "time.h"
#include <xc.h>

void destravar_fechadura(int tempo1, int tempo2){
		FECHADURA=1;
		delay_ms(tempo1);
		FECHADURA=0;
		
		if(FECHADURA_TRAVADA){
					delay_ms(tempo2)}
		
		}
