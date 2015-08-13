
			if(MODO_BLUETOOTH){
		
					for(cont=0;cont<qtd_caracteres_recebidos_serial;cont++){
	
		
									if(testar_bit(FLAGS_1,TRANSICAO_ETAPA)){
		
											if(buffer_serial[cont] != PROXIMA_ETAPA) {
																	setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
		
											resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
											ordem=0;
											etapa++;}
									
									else if(etapa == etapa_inicial){//Inicio da comunicação
												
					
												if(buffer_serial[cont] != INICIO) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
				
												setar_bit(FLAGS_1,TRANSICAO_ETAPA);
												}
					
									else if(etapa == etapa_recebe_funcao){
	
											    	funcao = buffer_serial[cont++];
														if(funcao<ABERTURA_PORTA || funcao>MUDAR_SENHA) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
	
													conta = ((buffer_serial[cont]) - '0');
																
														if(!(conta<QTD_MAX_CONTAS)) setar_bit(FLAGS_1,ERRO_IDENTIF_CONTA);
		
													setar_bit(FLAGS_1,TRANSICAO_ETAPA);
																	
													}
				
									
					
									else if(etapa == etapa_login){//executa funcao
				
											for(ordem=0;senha[conta][ordem]!= 0;ordem++){

													if(senha[conta][ordem] != buffer_serial[cont++]) {
																	setar_bit(FLAGS_1,ERRO_SENHA);
													}

											}
											cont--;
											setar_bit(FLAGS_1,TRANSICAO_ETAPA);
													
												}	
				
					
									else if(etapa == etapa_detalha_funcao){
												if(funcao == ABERTURA_PORTA || funcao == REQUERIMENTO_STATUS_ATUAL){
	
													for(ordem=0;ordem<2;ordem++){
														if( buffer_serial[cont++] != ('N'+(ordem))) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
															}
				
														setar_bit(FLAGS_1,TRANSICAO_ETAPA);
													}
									
												else if(funcao == REQUERIMENTO_HISTORICO){
																if(ordem==0){
																		endereco_inic_eeprom = (1794 + (buffer_serial[cont] *26));
																	
																ordem++;
																	}
				}
				//Não implementado
		
												else if(funcao == RECONFIGURAR_PIC){
														//ordem 0 ajuste de ano
														//ordem 1 ajuste de mes
														//ordem 2 ajuste de dia
														//ordem 3 ajuste de hora
														//ordem 4 ajuste de minuto
														//ordem 5 ajuste de segundo
					
	
														ptr_data= &data_atual.ano;
	
														for(ordem=0;ordem<6;ordem++){
																if(buffer_serial[cont] == IGNORAR) {//Pula para o próximo ajuste
																				ordem++;
																				cont+=2;} 
															
															*(ptr_data+ordem) = ascii_para_numero('0',buffer_serial[cont],buffer_serial[cont+1]);
															char temp = *(ptr_data+ordem);
															numero_para_ascii(temp);
															numero_para_ascii(ordem);
															cont+=2;}
	
															data_atual.dia_da_semana = dia_da_semana(data_atual.ano,data_atual.mes,data_atual.dia);
															setar_bit(FLAGS_1,TRANSICAO_ETAPA);
															cont--;
																	}
		
												else if(funcao == MUDAR_SENHA){
	
														conta_a_ser_alterada = (buffer_serial[cont] - '0');
				
														if(	conta_a_ser_alterada != conta && (!(testar_bit(nivel_acesso,PERMISSAO_RECONFIGURAR_OUTRAS_CONTAS)))	){
																			setar_bit(FLAGS_1,ERRO_NIVEL_DE_ACESSO);
																						}
														
														for(ordem=0;ordem<(TAMANHO_SENHA-1);ordem++){
															cont++;
	
																if(buffer_serial[cont] == '<') {
																			if(ordem<5) setar_bit(FLAGS_1,ERRO_PROTOCOLO);
						
																			else {
																				if(ordem<TAMANHO_SENHA-2) eeprom_write( ((conta_a_ser_alterada*16)+ordem) , 0);
																				break;}
																}
																						
	
																else{
																		
																	senha[conta_a_ser_alterada][ordem] = buffer_serial[cont];
																	eeprom_write( ((conta_a_ser_alterada*16)+ordem) ,buffer_serial[cont]);}
	
																	}	
									
															setar_bit(FLAGS_1,TRANSICAO_ETAPA);}
							}
					
									else if(etapa == etapa_final){//Fim da comunicação
												if(buffer_serial[cont] != FIM) {setar_bit(FLAGS_1,ERRO_PROTOCOLO);}
												enviar=1; receber=qtd_caracteres_recebidos_serial=0;}
				
									
									
									if(FLAGS_1>3) {
													resetar_bit(FLAGS_1,TRANSICAO_ETAPA);
													enviar_caractere_serial( '0' + etapa);
													etapa = etapa_inicial;	
													enviar=1;
													receber=qtd_caracteres_recebidos_serial=0;}
		
																			}		