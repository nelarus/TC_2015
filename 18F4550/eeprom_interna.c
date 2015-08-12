#include <xc.h>
#include "main.h"

void eeprom_config_inicial(void){
      unsigned char i;

      for(i=0;i<10;i++){
         eeprom_write(i,('0'+i));//Senha padrão da conta 0(admin): 0123456789
         eeprom_write(TAMANHO_SENHA+i,('a'+i));
         
         }
      eeprom_write(i,0);
      eeprom_write(TAMANHO_SENHA+i,0);//null da string de cada senha

      eeprom_write(((TAMANHO_SENHA*2)-1),0b11111101);
      }


char verificar_num_contas(void){
      char i;
      unsigned char qtd_contas=0;
      for(i=0;i<QTD_MAX_CONTAS;i++){
         if(eeprom_read(i*TAMANHO_SENHA) != 0xFF) {qtd_contas++;}
            }
      return (qtd_contas);}




void carregar_senha(char conta,char senha[][17]){
               TXREG = '\n';
               while(!TRMT);
               char i = 0;

                     do{
                        senha[conta][i] = eeprom_read((conta*TAMANHO_SENHA) + i);
                        TXREG= senha[conta][i];
                        while(!TRMT);
                        i++;} while( senha[conta][i-1] && i<(TAMANHO_SENHA-1));


               
               senha[conta][((conta*TAMANHO_SENHA)+ (TAMANHO_SENHA-1))]; 
               }
               