opt subtitle "HI-TECH Software Omniscient Code Generator (Lite mode) build 10920"

opt pagewidth 120

	opt lm

	processor	16F690
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
# 5 "D:\Dropbox\Micros\2015\TC_2015\TC_2015.c"
	psect config,class=CONFIG,delta=2 ;#
# 5 "D:\Dropbox\Micros\2015\TC_2015\TC_2015.c"
	dw 0xFFFC & 0xFFF7 & 0xFFEF & 0xFFFF & 0xFFFF & 0xFFFF & 0xFCFF & 0xFBFF & 0xF7FF ;#
	FNCALL	_main,_eeprom_read
	FNCALL	_main,_eeprom_write
	FNROOT	_main
	FNCALL	intlevel1,_aux
	global	intlevel1
	FNROOT	intlevel1
	global	_tamanho_senha
psect	idataBANK0,class=CODE,space=0,delta=2
global __pidataBANK0
__pidataBANK0:
	file	"D:\Dropbox\Micros\2015\TC_2015\TC_2015.c"
	line	32

;initializer for _tamanho_senha
	retlw	0Ah
	global	_nova_senha
	global	_senha
	global	_data_atual
	global	_FLAGS_1
	global	_conta
	global	_nivel_acesso
	global	_dado_recebido
	global	_etapa
	global	_funcao
	global	_ordem
	global	_ultima_conta
	global	_enviar
	global	_TMR1
_TMR1	set	14
	global	_INTCON
_INTCON	set	11
	global	_PORTC
_PORTC	set	7
	global	_RCREG
_RCREG	set	26
	global	_T1CON
_T1CON	set	16
	global	_TXREG
_TXREG	set	25
	global	_CARRY
_CARRY	set	24
	global	_CREN
_CREN	set	196
	global	_FERR
_FERR	set	194
	global	_GIE
_GIE	set	95
	global	_OERR
_OERR	set	193
	global	_PEIE
_PEIE	set	94
	global	_RABIE
_RABIE	set	91
	global	_RABIF
_RABIF	set	88
	global	_RCIF
_RCIF	set	101
	global	_RX9
_RX9	set	198
	global	_SPEN
_SPEN	set	199
	global	_TMR1IF
_TMR1IF	set	96
	global	_OPTION_REG
_OPTION_REG	set	129
	global	_OSCCON
_OSCCON	set	143
	global	_PIE1
_PIE1	set	140
	global	_SPBRG
_SPBRG	set	153
	global	_SPBRGH
_SPBRGH	set	154
	global	_TRISA
_TRISA	set	133
	global	_TRISB
_TRISB	set	134
	global	_TRISC
_TRISC	set	135
	global	_BRG16
_BRG16	set	1243
	global	_BRGH
_BRGH	set	1218
	global	_RCIE
_RCIE	set	1125
	global	_SYNC
_SYNC	set	1220
	global	_TMR1IE
_TMR1IE	set	1120
	global	_TRMT
_TRMT	set	1217
	global	_TX9
_TX9	set	1222
	global	_TXEN
_TXEN	set	1221
	global	_TXIE
_TXIE	set	1124
	global	_ANSEL
_ANSEL	set	286
	global	_ANSELH
_ANSELH	set	287
	global	_EEADR
_EEADR	set	269
	global	_EEDATA
_EEDATA	set	268
	global	_EECON1
_EECON1	set	396
	global	_EECON2
_EECON2	set	397
	global	_RD
_RD	set	3168
	global	_WR
_WR	set	3169
	global	_WREN
_WREN	set	3170
	file	"TC_2015.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bitbssCOMMON,class=COMMON,bit,space=1
global __pbitbssCOMMON
__pbitbssCOMMON:
_enviar:
       ds      1

psect	bssCOMMON,class=COMMON,space=1
global __pbssCOMMON
__pbssCOMMON:
_dado_recebido:
       ds      1

_etapa:
       ds      1

_funcao:
       ds      1

_ordem:
       ds      1

_ultima_conta:
       ds      1

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_nova_senha:
       ds      16

_senha:
       ds      16

_data_atual:
       ds      6

_FLAGS_1:
       ds      1

_conta:
       ds      1

_nivel_acesso:
       ds      1

psect	dataBANK0,class=BANK0,space=1
global __pdataBANK0
__pdataBANK0:
	file	"D:\Dropbox\Micros\2015\TC_2015\TC_2015.c"
_tamanho_senha:
       ds      1

psect clrtext,class=CODE,delta=2
global clear_ram
;	Called with FSR containing the base address, and
;	W with the last address+1
clear_ram:
	clrwdt			;clear the watchdog before getting into this loop
clrloop:
	clrf	indf		;clear RAM location pointed to by FSR
	incf	fsr,f		;increment pointer
	xorwf	fsr,w		;XOR with final address
	btfsc	status,2	;have we reached the end yet?
	retlw	0		;all done for this memory range, return
	xorwf	fsr,w		;XOR again to restore value
	goto	clrloop		;do the next byte

; Clear objects allocated to BITCOMMON
psect cinit,class=CODE,delta=2
	clrf	((__pbitbssCOMMON/8)+0)&07Fh
; Clear objects allocated to COMMON
psect cinit,class=CODE,delta=2
	clrf	((__pbssCOMMON)+0)&07Fh
	clrf	((__pbssCOMMON)+1)&07Fh
	clrf	((__pbssCOMMON)+2)&07Fh
	clrf	((__pbssCOMMON)+3)&07Fh
	clrf	((__pbssCOMMON)+4)&07Fh
; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	bcf	status, 7	;select IRP bank0
	movlw	low(__pbssBANK0)
	movwf	fsr
	movlw	low((__pbssBANK0)+029h)
	fcall	clear_ram
; Initialize objects allocated to BANK0
	global __pidataBANK0
psect cinit,class=CODE,delta=2
	fcall	__pidataBANK0+0		;fetch initializer
	movwf	__pdataBANK0+0&07fh		
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_aux
?_aux:	; 0 bytes @ 0x0
	global	??_aux
??_aux:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 0 bytes @ 0x0
	global	?_eeprom_read
?_eeprom_read:	; 1 bytes @ 0x0
	ds	6
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	??_eeprom_read
??_eeprom_read:	; 0 bytes @ 0x0
	global	?_eeprom_write
?_eeprom_write:	; 1 bytes @ 0x0
	global	eeprom_write@value
eeprom_write@value:	; 1 bytes @ 0x0
	ds	1
	global	??_eeprom_write
??_eeprom_write:	; 0 bytes @ 0x1
	global	eeprom_read@addr
eeprom_read@addr:	; 1 bytes @ 0x1
	ds	1
	global	eeprom_write@addr
eeprom_write@addr:	; 1 bytes @ 0x2
	ds	1
	global	??_main
??_main:	; 0 bytes @ 0x3
	ds	2
	global	main@i
main@i:	; 1 bytes @ 0x5
	ds	1
	global	main@i_1611
main@i_1611:	; 1 bytes @ 0x6
	ds	1
;;Data sizes: Strings 0, constant 0, data 1, bss 46, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      6      12
;; BANK0           80      7      49
;; BANK1           80      0       0
;; BANK2           80      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   None.
;;
;; Critical Paths under _aux in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_eeprom_write
;;
;; Critical Paths under _aux in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _aux in BANK1
;;
;;   None.
;;
;; Critical Paths under _main in BANK2
;;
;;   None.
;;
;; Critical Paths under _aux in BANK2
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 2, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 4     4      0     453
;;                                              3 BANK0      4     4      0
;;                        _eeprom_read
;;                       _eeprom_write
;; ---------------------------------------------------------------------------------
;; (1) _eeprom_write                                         3     2      1      69
;;                                              0 BANK0      3     2      1
;; ---------------------------------------------------------------------------------
;; (1) _eeprom_read                                          2     2      0      31
;;                                              0 BANK0      2     2      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 1
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (2) _aux                                                  6     6      0       0
;;                                              0 COMMON     6     6      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _eeprom_read
;;   _eeprom_write
;;
;; _aux (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;SFR3                 0      0       0       4        0.0%
;;BITSFR3              0      0       0       4        0.0%
;;BANK2               50      0       0       7        0.0%
;;BITBANK2            50      0       0       6        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR1                 0      0       0       2        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;BANK1               50      0       0       5        0.0%
;;BITBANK1            50      0       0       4        0.0%
;;CODE                 0      0       0       0        0.0%
;;DATA                 0      0      3E      10        0.0%
;;ABS                  0      0      3D       8        0.0%
;;NULL                 0      0       0       0        0.0%
;;STACK                0      0       1       2        0.0%
;;BANK0               50      7      31       3       61.3%
;;BITBANK0            50      0       0       9        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR0              0      0       0       1        0.0%
;;COMMON               E      6       C       1       85.7%
;;BITCOMMON            E      0       1       0        7.1%
;;EEDATA             100      0       0       0        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 264 in file "D:\Dropbox\Micros\2015\TC_2015\TC_2015.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    6[BANK0 ] unsigned char 
;;  i               1    5[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       2       0       0
;;      Temps:          0       2       0       0
;;      Totals:         0       4       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_eeprom_read
;;		_eeprom_write
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"D:\Dropbox\Micros\2015\TC_2015\TC_2015.c"
	line	264
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	266
	
l5307:	
;TC_2015.c: 266: OSCCON=0b01110001;
	movlw	(071h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(143)^080h	;volatile
	line	269
	
l5309:	
;TC_2015.c: 269: ANSEL=0;
	bcf	status, 5	;RP0=0, select bank2
	bsf	status, 6	;RP1=1, select bank2
	clrf	(286)^0100h	;volatile
	line	270
	
l5311:	
;TC_2015.c: 270: ANSELH=0;
	clrf	(287)^0100h	;volatile
	line	271
;TC_2015.c: 271: TRISA=0b00011111;
	movlw	(01Fh)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(133)^080h	;volatile
	line	272
;TC_2015.c: 272: TRISB=0b00100000;
	movlw	(020h)
	movwf	(134)^080h	;volatile
	line	273
	
l5313:	
;TC_2015.c: 273: TRISC=0;
	clrf	(135)^080h	;volatile
	line	274
	
l5315:	
;TC_2015.c: 274: PORTC=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(7)	;volatile
	line	277
;TC_2015.c: 277: INTCON=0b11001000;
	movlw	(0C8h)
	movwf	(11)	;volatile
	line	278
	
l5317:	
;TC_2015.c: 278: OPTION_REG=0b00000000;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	clrf	(129)^080h	;volatile
	line	279
	
l5319:	
;TC_2015.c: 279: T1CON=0b00001111;
	movlw	(0Fh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(16)	;volatile
	line	280
	
l5321:	
;TC_2015.c: 280: TMR1=32768;
	movlw	low(08000h)
	movwf	(14)	;volatile
	movlw	high(08000h)
	movwf	((14))+1	;volatile
	line	281
	
l5323:	
;TC_2015.c: 281: PIE1=1;
	movlw	(01h)
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	movwf	(140)^080h	;volatile
	line	284
	
l5325:	
;TC_2015.c: 284: SYNC=0;
	bcf	(1220/8)^080h,(1220)&7
	line	285
	
l5327:	
;TC_2015.c: 285: BRGH=1;
	bsf	(1218/8)^080h,(1218)&7
	line	286
	
l5329:	
;TC_2015.c: 286: BRG16=1;
	bsf	(1243/8)^080h,(1243)&7
	line	287
;TC_2015.c: 287: SPBRGH=0;
	clrf	(154)^080h	;volatile
	line	288
	
l5331:	
;TC_2015.c: 288: SPBRG=16;
	movlw	(010h)
	movwf	(153)^080h	;volatile
	line	289
	
l5333:	
;TC_2015.c: 289: SPEN=1;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(199/8),(199)&7
	line	290
	
l5335:	
;TC_2015.c: 290: TX9=0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bcf	(1222/8)^080h,(1222)&7
	line	291
	
l5337:	
;TC_2015.c: 291: TXEN=1;
	bsf	(1221/8)^080h,(1221)&7
	line	292
	
l5339:	
;TC_2015.c: 292: TXIE=0;
	bcf	(1124/8)^080h,(1124)&7
	line	293
	
l5341:	
;TC_2015.c: 293: RCIE=1;
	bsf	(1125/8)^080h,(1125)&7
	line	294
	
l5343:	
;TC_2015.c: 294: PEIE=1;
	bsf	(94/8),(94)&7
	line	295
	
l5345:	
;TC_2015.c: 295: RX9=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(198/8),(198)&7
	line	296
	
l5347:	
;TC_2015.c: 296: CREN=1;
	bsf	(196/8),(196)&7
	line	298
	
l5349:	
;TC_2015.c: 298: TXREG = 'B';
	movlw	(042h)
	movwf	(25)	;volatile
	line	299
;TC_2015.c: 299: while(!TRMT){}
	goto	l992
	
l993:	
	
l992:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3661
	goto	u3660
u3661:
	goto	l992
u3660:
	goto	l995
	
l994:	
	line	300
;TC_2015.c: 300: while(1){
	
l995:	
	line	303
;TC_2015.c: 303: if(enviar==1){
	btfss	(_enviar/8),(_enviar)&7
	goto	u3671
	goto	u3670
u3671:
	goto	l996
u3670:
	line	304
	
l5351:	
;TC_2015.c: 304: enviar=0;
	bcf	(_enviar/8),(_enviar)&7
	line	305
;TC_2015.c: 305: if( (FLAGS_1 & (1<<0)) == 0 && (FLAGS_1 & (1<<1)) ==0){
	bcf	status, 5	;RP0=0, select bank0
	btfsc	(_FLAGS_1),(0)&7
	goto	u3681
	goto	u3680
u3681:
	goto	l997
u3680:
	
l5353:	
	btfsc	(_FLAGS_1),(1)&7
	goto	u3691
	goto	u3690
u3691:
	goto	l997
u3690:
	line	306
	
l5355:	
;TC_2015.c: 306: TXREG = 'O';
	movlw	(04Fh)
	movwf	(25)	;volatile
	line	307
;TC_2015.c: 307: while(!TRMT){}
	goto	l998
	
l999:	
	
l998:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3701
	goto	u3700
u3701:
	goto	l998
u3700:
	goto	l5357
	
l1000:	
	line	308
	
l5357:	
;TC_2015.c: 308: TXREG = 'K';
	movlw	(04Bh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	309
;TC_2015.c: 309: while(!TRMT){}}
	goto	l1001
	
l1002:	
	
l1001:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3711
	goto	u3710
u3711:
	goto	l1001
u3710:
	goto	l995
	
l1003:	
	goto	l995
	line	311
	
l997:	
	line	313
;TC_2015.c: 311: else{
;TC_2015.c: 313: if((FLAGS_1 & (1<<1))){
	btfss	(_FLAGS_1),(1)&7
	goto	u3721
	goto	u3720
u3721:
	goto	l5365
u3720:
	line	314
	
l5359:	
;TC_2015.c: 314: TXREG = 'E';
	movlw	(045h)
	movwf	(25)	;volatile
	line	315
;TC_2015.c: 315: while(!TRMT){}
	goto	l1006
	
l1007:	
	
l1006:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3731
	goto	u3730
u3731:
	goto	l1006
u3730:
	goto	l5361
	
l1008:	
	line	316
	
l5361:	
;TC_2015.c: 316: TXREG = 'P';
	movlw	(050h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	317
;TC_2015.c: 317: while(!TRMT){}
	goto	l1009
	
l1010:	
	
l1009:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3741
	goto	u3740
u3741:
	goto	l1009
u3740:
	goto	l5363
	
l1011:	
	line	318
	
l5363:	
;TC_2015.c: 318: (FLAGS_1 &= ~(1<<1));}
	movlw	(0FDh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	andwf	(_FLAGS_1),f
	goto	l5365
	
l1005:	
	line	320
	
l5365:	
;TC_2015.c: 320: if((FLAGS_1 & (1<<0))){
	btfss	(_FLAGS_1),(0)&7
	goto	u3751
	goto	u3750
u3751:
	goto	l5373
u3750:
	line	321
	
l5367:	
;TC_2015.c: 321: TXREG = 'E';
	movlw	(045h)
	movwf	(25)	;volatile
	line	322
;TC_2015.c: 322: while(!TRMT){}
	goto	l1013
	
l1014:	
	
l1013:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3761
	goto	u3760
u3761:
	goto	l1013
u3760:
	goto	l5369
	
l1015:	
	line	323
	
l5369:	
;TC_2015.c: 323: TXREG = 'S';
	movlw	(053h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	324
;TC_2015.c: 324: while(!TRMT){}
	goto	l1016
	
l1017:	
	
l1016:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3771
	goto	u3770
u3771:
	goto	l1016
u3770:
	goto	l5371
	
l1018:	
	line	325
	
l5371:	
;TC_2015.c: 325: (FLAGS_1 &= ~(1<<0));}
	movlw	(0FEh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	andwf	(_FLAGS_1),f
	goto	l5373
	
l1012:	
	line	327
	
l5373:	
;TC_2015.c: 327: if((FLAGS_1 & (1<<2))){
	btfss	(_FLAGS_1),(2)&7
	goto	u3781
	goto	u3780
u3781:
	goto	l995
u3780:
	line	328
	
l5375:	
;TC_2015.c: 328: TXREG = 'E';
	movlw	(045h)
	movwf	(25)	;volatile
	line	329
;TC_2015.c: 329: while(!TRMT){}
	goto	l1020
	
l1021:	
	
l1020:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3791
	goto	u3790
u3791:
	goto	l1020
u3790:
	goto	l5377
	
l1022:	
	line	330
	
l5377:	
;TC_2015.c: 330: TXREG = 'I';
	movlw	(049h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	331
;TC_2015.c: 331: while(!TRMT){}
	goto	l1023
	
l1024:	
	
l1023:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3801
	goto	u3800
u3801:
	goto	l1023
u3800:
	goto	l5379
	
l1025:	
	line	332
	
l5379:	
;TC_2015.c: 332: (FLAGS_1 &= ~(1<<0));}
	movlw	(0FEh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	andwf	(_FLAGS_1),f
	goto	l995
	
l1019:	
	goto	l995
	line	333
	
l1004:	
	line	335
;TC_2015.c: 333: }
;TC_2015.c: 335: }
	goto	l995
	line	337
	
l996:	
;TC_2015.c: 337: else if(RCIE==0){
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfsc	(1125/8)^080h,(1125)&7
	goto	u3811
	goto	u3810
u3811:
	goto	l1027
u3810:
	line	338
	
l5381:	
;TC_2015.c: 338: char i = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	clrf	(main@i)
	line	339
;TC_2015.c: 339: tamanho_senha=0;
	clrf	(_tamanho_senha)
	line	341
;TC_2015.c: 341: while( senha[i] && i<16){
	goto	l5389
	
l1029:	
	line	342
	
l5383:	
;TC_2015.c: 342: senha[i] = eeprom_read((conta*16) + i);
	movf	(_conta),w
	movwf	(??_main+0)+0
	movlw	04h
u3825:
	clrc
	rlf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u3825
	movf	(main@i),w
	addwf	0+(??_main+0)+0,w
	fcall	_eeprom_read
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+1)+0
	movf	(main@i),w
	addlw	_senha&0ffh
	movwf	fsr0
	movf	(??_main+1)+0,w
	bcf	status, 7	;select IRP bank0
	movwf	indf
	line	343
	
l5385:	
;TC_2015.c: 343: TXREG= senha[i];
	movf	(main@i),w
	addlw	_senha&0ffh
	movwf	fsr0
	movf	indf,w
	movwf	(25)	;volatile
	line	344
;TC_2015.c: 344: while(!TRMT);
	goto	l1030
	
l1031:	
	
l1030:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3831
	goto	u3830
u3831:
	goto	l1030
u3830:
	goto	l5387
	
l1032:	
	line	345
	
l5387:	
;TC_2015.c: 345: i++;}
	movlw	(01h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(main@i),f
	goto	l5389
	
l1028:	
	line	341
	
l5389:	
	movf	(main@i),w
	addlw	_senha&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf
	skipnz
	goto	u3841
	goto	u3840
u3841:
	goto	l5393
u3840:
	
l5391:	
	movlw	(010h)
	subwf	(main@i),w
	skipc
	goto	u3851
	goto	u3850
u3851:
	goto	l5383
u3850:
	goto	l5393
	
l1034:	
	goto	l5393
	
l1035:	
	line	346
	
l5393:	
;TC_2015.c: 346: nivel_acesso = eeprom_read((conta*16)+ (16-1));
	movf	(_conta),w
	movwf	(??_main+0)+0
	movlw	(04h)-1
u3865:
	clrc
	rlf	(??_main+0)+0,f
	addlw	-1
	skipz
	goto	u3865
	clrc
	rlf	(??_main+0)+0,w
	addlw	0Fh
	fcall	_eeprom_read
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+1)+0
	movf	(??_main+1)+0,w
	movwf	(_nivel_acesso)
	line	347
	
l5395:	
;TC_2015.c: 347: RCIE=1;
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	bsf	(1125/8)^080h,(1125)&7
	line	348
	
l5397:	
;TC_2015.c: 348: TXREG= 'C';
	movlw	(043h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	349
;TC_2015.c: 349: while(!TRMT);
	goto	l1036
	
l1037:	
	
l1036:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u3871
	goto	u3870
u3871:
	goto	l1036
u3870:
	goto	l995
	
l1038:	
	line	351
;TC_2015.c: 351: }
	goto	l995
	line	353
	
l1027:	
;TC_2015.c: 353: else if( (FLAGS_1 & (1<<7))){
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(_FLAGS_1),(7)&7
	goto	u3881
	goto	u3880
u3881:
	goto	l995
u3880:
	line	354
	
l5399:	
;TC_2015.c: 354: (FLAGS_1 &= ~(1<<7));
	movlw	(07Fh)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	andwf	(_FLAGS_1),f
	line	355
	
l5401:	
;TC_2015.c: 355: char i=0;
	clrf	(main@i_1611)
	line	356
	
l5403:	
;TC_2015.c: 356: tamanho_senha=0;
	clrf	(_tamanho_senha)
	line	357
;TC_2015.c: 357: while(nova_senha[i] && i<16){
	goto	l5411
	
l1042:	
	line	358
	
l5405:	
;TC_2015.c: 358: senha[i] = nova_senha[i];
	movf	(main@i_1611),w
	addlw	_nova_senha&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	movwf	(??_main+0)+0
	movf	(main@i_1611),w
	addlw	_senha&0ffh
	movwf	fsr0
	movf	(??_main+0)+0,w
	movwf	indf
	line	359
	
l5407:	
;TC_2015.c: 359: eeprom_write(((conta*16) + i),senha[i]);
	movf	(main@i_1611),w
	addlw	_senha&0ffh
	movwf	fsr0
	movf	indf,w
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	movwf	(?_eeprom_write)
	movf	(_conta),w
	movwf	(??_main+1)+0
	movlw	04h
u3895:
	clrc
	rlf	(??_main+1)+0,f
	addlw	-1
	skipz
	goto	u3895
	movf	(main@i_1611),w
	addwf	0+(??_main+1)+0,w
	fcall	_eeprom_write
	line	360
;TC_2015.c: 360: while(WR){}
	goto	l1043
	
l1044:	
	
l1043:	
	bsf	status, 5	;RP0=1, select bank3
	bsf	status, 6	;RP1=1, select bank3
	btfsc	(3169/8)^0180h,(3169)&7
	goto	u3901
	goto	u3900
u3901:
	goto	l1043
u3900:
	goto	l5409
	
l1045:	
	line	361
	
l5409:	
;TC_2015.c: 361: i++; tamanho_senha++;}
	movlw	(01h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(main@i_1611),f
	movlw	(01h)
	movwf	(??_main+0)+0
	movf	(??_main+0)+0,w
	addwf	(_tamanho_senha),f
	goto	l5411
	
l1041:	
	line	357
	
l5411:	
	movf	(main@i_1611),w
	addlw	_nova_senha&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf
	skipnz
	goto	u3911
	goto	u3910
u3911:
	goto	l995
u3910:
	
l5413:	
	movlw	(010h)
	subwf	(main@i_1611),w
	skipc
	goto	u3921
	goto	u3920
u3921:
	goto	l5405
u3920:
	goto	l995
	
l1047:	
	goto	l995
	
l1048:	
	goto	l995
	line	363
	
l1040:	
	goto	l995
	line	365
	
l1039:	
	goto	l995
	
l1026:	
	goto	l995
	
l1049:	
	line	300
	goto	l995
	
l1050:	
	line	366
	
l1051:	
	global	start
	ljmp	start
	opt stack 0
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,88
	global	_eeprom_write
psect	text214,local,class=CODE,delta=2
global __ptext214
__ptext214:

;; *************** function _eeprom_write *****************
;; Defined at:
;;		line 7 in file "C:\Program Files (x86)\HI-TECH Software\PICC\9.83\sources\eewrite.c"
;; Parameters:    Size  Location     Type
;;  addr            1    wreg     unsigned char 
;;  value           1    0[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  addr            1    2[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       1       0       0
;;      Locals:         0       1       0       0
;;      Temps:          0       1       0       0
;;      Totals:         0       3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text214
	file	"C:\Program Files (x86)\HI-TECH Software\PICC\9.83\sources\eewrite.c"
	line	7
	global	__size_of_eeprom_write
	__size_of_eeprom_write	equ	__end_of_eeprom_write-_eeprom_write
	
_eeprom_write:	
	opt	stack 6
; Regs used in _eeprom_write: [wreg+status,2+status,0]
;eeprom_write@addr stored from wreg
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(eeprom_write@addr)
	line	8
	
l2635:	
	goto	l2636
	
l2637:	
	
l2636:	
	bsf	status, 5	;RP0=1, select bank3
	bsf	status, 6	;RP1=1, select bank3
	btfsc	(3169/8)^0180h,(3169)&7
	goto	u3631
	goto	u3630
u3631:
	goto	l2636
u3630:
	goto	l5287
	
l2638:	
	
l5287:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(eeprom_write@addr),w
	bcf	status, 5	;RP0=0, select bank2
	bsf	status, 6	;RP1=1, select bank2
	movwf	(269)^0100h	;volatile
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(eeprom_write@value),w
	bcf	status, 5	;RP0=0, select bank2
	bsf	status, 6	;RP1=1, select bank2
	movwf	(268)^0100h	;volatile
	
l5289:	
	movlw	(03Fh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_eeprom_write+0)+0
	movf	(??_eeprom_write+0)+0,w
	bsf	status, 5	;RP0=1, select bank3
	bsf	status, 6	;RP1=1, select bank3
	andwf	(396)^0180h,f	;volatile
	
l5291:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(24/8),(24)&7
	
l5293:	
	btfss	(95/8),(95)&7
	goto	u3641
	goto	u3640
u3641:
	goto	l2639
u3640:
	
l5295:	
	bsf	(24/8),(24)&7
	
l2639:	
	bcf	(95/8),(95)&7
	bsf	status, 5	;RP0=1, select bank3
	bsf	status, 6	;RP1=1, select bank3
	bsf	(3170/8)^0180h,(3170)&7
	
l5297:	
	movlw	(055h)
	movwf	(397)^0180h	;volatile
	movlw	(0AAh)
	movwf	(397)^0180h	;volatile
	
l5299:	
	bsf	(3169/8)^0180h,(3169)&7
	
l5301:	
	bcf	(3170/8)^0180h,(3170)&7
	
l5303:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(24/8),(24)&7
	goto	u3651
	goto	u3650
u3651:
	goto	l2642
u3650:
	
l5305:	
	bsf	(95/8),(95)&7
	goto	l2642
	
l2640:	
	goto	l2642
	
l2641:	
	line	10
;	Return value of _eeprom_write is never used
	
l2642:	
	return
	opt stack 0
GLOBAL	__end_of_eeprom_write
	__end_of_eeprom_write:
;; =============== function _eeprom_write ends ============

	signat	_eeprom_write,8313
	global	_eeprom_read
psect	text215,local,class=CODE,delta=2
global __ptext215
__ptext215:

;; *************** function _eeprom_read *****************
;; Defined at:
;;		line 7 in file "eeread.c"
;; Parameters:    Size  Location     Type
;;  addr            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  addr            1    1[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       1       0       0
;;      Temps:          0       1       0       0
;;      Totals:         0       2       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text215
	file	"C:\Program Files (x86)\HI-TECH Software\PICC\9.83\sources\eeread.c"
	line	7
	global	__size_of_eeprom_read
	__size_of_eeprom_read	equ	__end_of_eeprom_read-_eeprom_read
	
_eeprom_read:	
	opt	stack 6
; Regs used in _eeprom_read: [wreg+status,2+status,0]
;eeprom_read@addr stored from wreg
	line	9
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(eeprom_read@addr)
	line	8
	
l1842:	
	line	9
# 9 "C:\Program Files (x86)\HI-TECH Software\PICC\9.83\sources\eeread.c"
clrwdt ;#
psect	text215
	line	10
	bsf	status, 5	;RP0=1, select bank3
	bsf	status, 6	;RP1=1, select bank3
	btfsc	(3169/8)^0180h,(3169)&7
	goto	u3621
	goto	u3620
u3621:
	goto	l1842
u3620:
	goto	l5283
	
l1843:	
	line	11
	
l5283:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(eeprom_read@addr),w
	bcf	status, 5	;RP0=0, select bank2
	bsf	status, 6	;RP1=1, select bank2
	movwf	(269)^0100h	;volatile
	movlw	(03Fh)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(??_eeprom_read+0)+0
	movf	(??_eeprom_read+0)+0,w
	bsf	status, 5	;RP0=1, select bank3
	bsf	status, 6	;RP1=1, select bank3
	andwf	(396)^0180h,f	;volatile
	bsf	(3168/8)^0180h,(3168)&7
	clrc
	btfsc	(3168/8)^0180h,(3168)&7
	setc
	movlw	0
	skipnc
	movlw	1

	bcf	status, 5	;RP0=0, select bank2
	bsf	status, 6	;RP1=1, select bank2
	movf	(268)^0100h,w	;volatile
	goto	l1844
	
l5285:	
	line	12
	
l1844:	
	return
	opt stack 0
GLOBAL	__end_of_eeprom_read
	__end_of_eeprom_read:
;; =============== function _eeprom_read ends ============

	signat	_eeprom_read,4217
	global	_aux
psect	text216,local,class=CODE,delta=2
global __ptext216
__ptext216:

;; *************** function _aux *****************
;; Defined at:
;;		line 130 in file "D:\Dropbox\Micros\2015\TC_2015\TC_2015.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1   BANK2
;;      Params:         0       0       0       0
;;      Locals:         0       0       0       0
;;      Temps:          6       0       0       0
;;      Totals:         6       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text216
	file	"D:\Dropbox\Micros\2015\TC_2015\TC_2015.c"
	line	130
	global	__size_of_aux
	__size_of_aux	equ	__end_of_aux-_aux
	
_aux:	
	opt	stack 6
; Regs used in _aux: [wreg-fsr0h+status,2+status,0]
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	movwf	(??_aux+2)
	movf	fsr0,w
	movwf	(??_aux+3)
	movf	pclath,w
	movwf	(??_aux+4)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	btemp+1,w
	movwf	(??_aux+5)
	ljmp	_aux
psect	text216
	line	132
	
i1l5021:	
;TC_2015.c: 132: if(RABIF==1 && RABIE==1){
	btfss	(88/8),(88)&7
	goto	u292_21
	goto	u292_20
u292_21:
	goto	i1l922
u292_20:
	
i1l5023:	
	btfss	(91/8),(91)&7
	goto	u293_21
	goto	u293_20
u293_21:
	goto	i1l922
u293_20:
	line	133
	
i1l5025:	
;TC_2015.c: 133: RABIF=0;}
	bcf	(88/8),(88)&7
	
i1l922:	
	line	135
;TC_2015.c: 135: if(TMR1IE==1 && TMR1IF ==1){
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1120/8)^080h,(1120)&7
	goto	u294_21
	goto	u294_20
u294_21:
	goto	i1l923
u294_20:
	
i1l5027:	
	line	136
	
i1l923:	
	line	138
;TC_2015.c: 136: }
;TC_2015.c: 138: if(RCIF==1 && RCIE==1){
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(101/8),(101)&7
	goto	u295_21
	goto	u295_20
u295_21:
	goto	i1l989
u295_20:
	
i1l5029:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1125/8)^080h,(1125)&7
	goto	u296_21
	goto	u296_20
u296_21:
	goto	i1l989
u296_20:
	line	140
	
i1l5031:	
;TC_2015.c: 140: if(OERR==1){
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfss	(193/8),(193)&7
	goto	u297_21
	goto	u297_20
u297_21:
	goto	i1l925
u297_20:
	line	141
	
i1l5033:	
;TC_2015.c: 141: (FLAGS_1 |= (1<<4));
	bsf	(_FLAGS_1)+(4/8),(4)&7
	line	142
	
i1l5035:	
;TC_2015.c: 142: TXREG = 'O';
	movlw	(04Fh)
	movwf	(25)	;volatile
	line	143
;TC_2015.c: 143: while(!TRMT){}
	goto	i1l926
	
i1l927:	
	
i1l926:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u298_21
	goto	u298_20
u298_21:
	goto	i1l926
u298_20:
	
i1l928:	
	line	144
;TC_2015.c: 144: CREN=0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(196/8),(196)&7
	line	145
;TC_2015.c: 145: CREN=1;
	bsf	(196/8),(196)&7
	line	147
;TC_2015.c: 147: }
	goto	i1l929
	line	149
	
i1l925:	
;TC_2015.c: 149: else if(FERR==1){
	btfss	(194/8),(194)&7
	goto	u299_21
	goto	u299_20
u299_21:
	goto	i1l5041
u299_20:
	line	150
	
i1l5037:	
;TC_2015.c: 150: (FLAGS_1 |= (1<<4));
	bsf	(_FLAGS_1)+(4/8),(4)&7
	line	151
	
i1l5039:	
;TC_2015.c: 151: TXREG = 'F';}
	movlw	(046h)
	movwf	(25)	;volatile
	goto	i1l929
	line	153
	
i1l930:	
	line	154
	
i1l5041:	
;TC_2015.c: 153: else{
;TC_2015.c: 154: dado_recebido = RCREG;
	movf	(26),w	;volatile
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	movwf	(_dado_recebido)
	line	156
;TC_2015.c: 156: TXREG = dado_recebido;
	movf	(_dado_recebido),w
	movwf	(25)	;volatile
	line	157
;TC_2015.c: 157: while(!TRMT){}
	goto	i1l932
	
i1l933:	
	
i1l932:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u300_21
	goto	u300_20
u300_21:
	goto	i1l932
u300_20:
	goto	i1l5043
	
i1l934:	
	line	158
	
i1l5043:	
;TC_2015.c: 158: TXREG = ('0' + etapa);
	movf	(_etapa),w
	addlw	030h
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	159
;TC_2015.c: 159: while(!TRMT){}
	goto	i1l935
	
i1l936:	
	
i1l935:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u301_21
	goto	u301_20
u301_21:
	goto	i1l935
u301_20:
	goto	i1l5045
	
i1l937:	
	line	160
	
i1l5045:	
;TC_2015.c: 160: TXREG = ('0' + ordem);
	movf	(_ordem),w
	addlw	030h
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	161
;TC_2015.c: 161: while(!TRMT){}
	goto	i1l938
	
i1l939:	
	
i1l938:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u302_21
	goto	u302_20
u302_21:
	goto	i1l938
u302_20:
	goto	i1l5047
	
i1l940:	
	line	162
	
i1l5047:	
;TC_2015.c: 162: TXREG = ('0' + 6);
	movlw	(036h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	163
;TC_2015.c: 163: while(!TRMT){}
	goto	i1l941
	
i1l942:	
	
i1l941:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u303_21
	goto	u303_20
u303_21:
	goto	i1l941
u303_20:
	goto	i1l5049
	
i1l943:	
	line	167
	
i1l5049:	
;TC_2015.c: 167: if(FLAGS_1) {
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_FLAGS_1),w
	skipz
	goto	u304_20
	goto	i1l5057
u304_20:
	line	168
	
i1l5051:	
;TC_2015.c: 168: (FLAGS_1 &= ~(1<<6));
	movlw	(0BFh)
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	andwf	(_FLAGS_1),f
	line	169
	
i1l5053:	
;TC_2015.c: 169: etapa = 0;
	clrf	(_etapa)
	line	170
	
i1l5055:	
;TC_2015.c: 170: enviar=1;}
	bsf	(_enviar/8),(_enviar)&7
	goto	i1l929
	line	172
;TC_2015.c: 172: else if(6){
	
i1l944:	
	line	173
	
i1l5057:	
;TC_2015.c: 173: if(dado_recebido != '>') {(FLAGS_1 |= (1<<1));}
	movf	(_dado_recebido),w
	xorlw	03Eh
	skipnz
	goto	u305_21
	goto	u305_20
u305_21:
	goto	i1l5061
u305_20:
	
i1l5059:	
	bsf	(_FLAGS_1)+(1/8),(1)&7
	goto	i1l5061
	
i1l947:	
	line	175
	
i1l5061:	
;TC_2015.c: 175: (FLAGS_1 &= ~(1<<6));
	movlw	(0BFh)
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	andwf	(_FLAGS_1),f
	line	176
	
i1l5063:	
;TC_2015.c: 176: ordem=0;
	clrf	(_ordem)
	line	177
;TC_2015.c: 177: etapa++;}
	movlw	(01h)
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	addwf	(_etapa),f
	goto	i1l929
	line	179
	
i1l946:	
	
i1l5065:	
;TC_2015.c: 179: else if(etapa == 0){
	movf	(_etapa),f
	skipz
	goto	u306_21
	goto	u306_20
u306_21:
	goto	i1l5071
u306_20:
	line	181
	
i1l5067:	
;TC_2015.c: 181: if(dado_recebido != 'I') {(FLAGS_1 |= (1<<1));}
	movf	(_dado_recebido),w
	xorlw	049h
	skipnz
	goto	u307_21
	goto	u307_20
u307_21:
	goto	i1l950
u307_20:
	
i1l5069:	
	bsf	(_FLAGS_1)+(1/8),(1)&7
	
i1l950:	
	line	183
;TC_2015.c: 183: (FLAGS_1 |= (1<<6));
	bsf	(_FLAGS_1)+(6/8),(6)&7
	line	184
;TC_2015.c: 184: }
	goto	i1l929
	line	186
	
i1l949:	
	
i1l5071:	
;TC_2015.c: 186: else if(etapa == 1){
	movf	(_etapa),w
	xorlw	01h
	skipz
	goto	u308_21
	goto	u308_20
u308_21:
	goto	i1l5093
u308_20:
	line	187
	
i1l5073:	
;TC_2015.c: 187: if(ordem==0){
	movf	(_ordem),f
	skipz
	goto	u309_21
	goto	u309_20
u309_21:
	goto	i1l953
u309_20:
	line	188
	
i1l5075:	
;TC_2015.c: 188: funcao = dado_recebido;
	movf	(_dado_recebido),w
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	movwf	(_funcao)
	line	189
;TC_2015.c: 189: if(funcao<'0' && funcao>'6') {(FLAGS_1 |= (1<<1));}}
	movlw	(030h)
	subwf	(_funcao),w
	skipnc
	goto	u310_21
	goto	u310_20
u310_21:
	goto	i1l5091
u310_20:
	
i1l5077:	
	movlw	(037h)
	subwf	(_funcao),w
	skipc
	goto	u311_21
	goto	u311_20
u311_21:
	goto	i1l5091
u311_20:
	
i1l5079:	
	bsf	(_FLAGS_1)+(1/8),(1)&7
	goto	i1l5091
	
i1l954:	
	goto	i1l5091
	line	191
	
i1l953:	
	line	192
;TC_2015.c: 191: else{
;TC_2015.c: 192: (FLAGS_1 |= (1<<6));
	bsf	(_FLAGS_1)+(6/8),(6)&7
	line	193
	
i1l5081:	
;TC_2015.c: 193: conta = (dado_recebido - '0');
	movf	(_dado_recebido),w
	addlw	0D0h
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	movwf	(_conta)
	line	194
	
i1l5083:	
;TC_2015.c: 194: if(!(conta<16)) (FLAGS_1 |= (1<<2));
	movlw	(010h)
	subwf	(_conta),w
	skipc
	goto	u312_21
	goto	u312_20
u312_21:
	goto	i1l5087
u312_20:
	
i1l5085:	
	bsf	(_FLAGS_1)+(2/8),(2)&7
	goto	i1l5091
	line	196
	
i1l956:	
	line	197
	
i1l5087:	
;TC_2015.c: 196: else{
;TC_2015.c: 197: if(conta != ultima_conta){
	movf	(_conta),w
	xorwf	(_ultima_conta),w
	skipnz
	goto	u313_21
	goto	u313_20
u313_21:
	goto	i1l958
u313_20:
	line	198
	
i1l5089:	
;TC_2015.c: 198: TXREG = 'P';
	movlw	(050h)
	movwf	(25)	;volatile
	line	199
;TC_2015.c: 199: while(!TRMT){}
	goto	i1l959
	
i1l960:	
	
i1l959:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u314_21
	goto	u314_20
u314_21:
	goto	i1l959
u314_20:
	
i1l961:	
	line	200
;TC_2015.c: 200: RCIE=0;}
	bcf	(1125/8)^080h,(1125)&7
	goto	i1l5091
	line	202
	
i1l958:	
;TC_2015.c: 202: else (FLAGS_1 |= (1<<6));
	bsf	(_FLAGS_1)+(6/8),(6)&7
	goto	i1l5091
	
i1l962:	
	goto	i1l5091
	line	203
	
i1l957:	
	goto	i1l5091
	line	204
	
i1l955:	
	line	206
	
i1l5091:	
;TC_2015.c: 203: }
;TC_2015.c: 204: }
;TC_2015.c: 206: ordem++;}
	movlw	(01h)
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	addwf	(_ordem),f
	goto	i1l929
	line	210
	
i1l952:	
	
i1l5093:	
;TC_2015.c: 210: else if(etapa == 2){
	movf	(_etapa),w
	xorlw	02h
	skipz
	goto	u315_21
	goto	u315_20
u315_21:
	goto	i1l5109
u315_20:
	line	212
	
i1l5095:	
;TC_2015.c: 212: TXREG = 'J';
	movlw	(04Ah)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(25)	;volatile
	line	213
;TC_2015.c: 213: while(!TRMT){}
	goto	i1l965
	
i1l966:	
	
i1l965:	
	bsf	status, 5	;RP0=1, select bank1
	bcf	status, 6	;RP1=0, select bank1
	btfss	(1217/8)^080h,(1217)&7
	goto	u316_21
	goto	u316_20
u316_21:
	goto	i1l965
u316_20:
	goto	i1l5097
	
i1l967:	
	line	214
	
i1l5097:	
;TC_2015.c: 214: TXREG = senha[ordem];
	movf	(_ordem),w
	addlw	_senha&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(25)	;volatile
	line	215
;TC_2015.c: 215: if(senha[ordem] != dado_recebido){
	movf	(_ordem),w
	addlw	_senha&0ffh
	movwf	fsr0
	movf	indf,w
	xorwf	(_dado_recebido),w
	skipnz
	goto	u317_21
	goto	u317_20
u317_21:
	goto	i1l5103
u317_20:
	line	216
	
i1l5099:	
;TC_2015.c: 216: if(senha[ordem+1] == (0)) (FLAGS_1 |= (1<<6));
	movf	(_ordem),w
	addlw	01h
	addlw	_senha&0ffh
	movwf	fsr0
	movf	indf,f
	skipz
	goto	u318_21
	goto	u318_20
u318_21:
	goto	i1l969
u318_20:
	
i1l5101:	
	bsf	(_FLAGS_1)+(6/8),(6)&7
	goto	i1l5103
	line	217
	
i1l969:	
;TC_2015.c: 217: else (FLAGS_1 |= (1<<0));
	bsf	(_FLAGS_1)+(0/8),(0)&7
	goto	i1l5103
	
i1l970:	
	goto	i1l5103
	line	218
	
i1l968:	
	line	219
	
i1l5103:	
;TC_2015.c: 218: }
;TC_2015.c: 219: ordem++;
	movlw	(01h)
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	addwf	(_ordem),f
	line	221
	
i1l5105:	
;TC_2015.c: 221: if(ordem == tamanho_senha) (FLAGS_1 |= (1<<6));
	movf	(_ordem),w
	xorwf	(_tamanho_senha),w
	skipz
	goto	u319_21
	goto	u319_20
u319_21:
	goto	i1l929
u319_20:
	
i1l5107:	
	bsf	(_FLAGS_1)+(6/8),(6)&7
	goto	i1l929
	
i1l971:	
	line	222
;TC_2015.c: 222: }
	goto	i1l929
	line	225
	
i1l964:	
	
i1l5109:	
;TC_2015.c: 225: else if(etapa == 3){
	movf	(_etapa),w
	xorlw	03h
	skipz
	goto	u320_21
	goto	u320_20
u320_21:
	goto	i1l5123
u320_20:
	line	226
	
i1l5111:	
;TC_2015.c: 226: if(funcao == '0'){
	movf	(_funcao),w
	xorlw	030h
	skipz
	goto	u321_21
	goto	u321_20
u321_21:
	goto	i1l929
u321_20:
	line	227
	
i1l5113:	
;TC_2015.c: 227: if(ordem == 2) {
	movf	(_ordem),w
	xorlw	02h
	skipz
	goto	u322_21
	goto	u322_20
u322_21:
	goto	i1l5117
u322_20:
	line	228
	
i1l5115:	
;TC_2015.c: 228: (FLAGS_1 |= (1<<6));
	bcf	status, 5	;RP0=0, select bank0
	bsf	(_FLAGS_1)+(6/8),(6)&7
	goto	i1l5117
	line	229
	
i1l975:	
	line	231
	
i1l5117:	
;TC_2015.c: 229: }
;TC_2015.c: 231: if( dado_recebido != ('N'+ordem)) (FLAGS_1 |= (1<<1));
	movf	(_ordem),w
	addlw	low(04Eh)
	movwf	(??_aux+0)+0
	movlw	high(04Eh)
	skipnc
	movlw	(high(04Eh)+1)&0ffh
	movwf	((??_aux+0)+0)+1
	movf	(_dado_recebido),w
	xorwf	0+(??_aux+0)+0,w
	iorwf	1+(??_aux+0)+0,w
	skipnz
	goto	u323_21
	goto	u323_20
u323_21:
	goto	i1l5121
u323_20:
	
i1l5119:	
	bcf	status, 5	;RP0=0, select bank0
	bsf	(_FLAGS_1)+(1/8),(1)&7
	goto	i1l5121
	
i1l976:	
	line	232
	
i1l5121:	
;TC_2015.c: 232: ordem++;
	movlw	(01h)
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	addwf	(_ordem),f
	goto	i1l929
	line	233
	
i1l974:	
	line	234
;TC_2015.c: 233: }
;TC_2015.c: 234: }
	goto	i1l929
	line	235
	
i1l973:	
	
i1l5123:	
;TC_2015.c: 235: else if(funcao == '1'){
	movf	(_funcao),w
	xorlw	031h
	skipz
	goto	u324_21
	goto	u324_20
u324_21:
	goto	i1l5127
u324_20:
	line	237
	
i1l5125:	
;TC_2015.c: 237: (FLAGS_1 |= (1<<6));}
	bcf	status, 5	;RP0=0, select bank0
	bsf	(_FLAGS_1)+(6/8),(6)&7
	goto	i1l929
	line	239
	
i1l978:	
	
i1l5127:	
;TC_2015.c: 239: else if(funcao == '2')(FLAGS_1 |= (1<<6));
	movf	(_funcao),w
	xorlw	032h
	skipz
	goto	u325_21
	goto	u325_20
u325_21:
	goto	i1l5131
u325_20:
	
i1l5129:	
	bcf	status, 5	;RP0=0, select bank0
	bsf	(_FLAGS_1)+(6/8),(6)&7
	goto	i1l929
	line	241
	
i1l980:	
	
i1l5131:	
;TC_2015.c: 241: else if(funcao == '6'){
	movf	(_funcao),w
	xorlw	036h
	skipz
	goto	u326_21
	goto	u326_20
u326_21:
	goto	i1l5145
u326_20:
	line	243
	
i1l5133:	
;TC_2015.c: 243: if(dado_recebido == (0)) (FLAGS_1 |= (1<<6));
	movf	(_dado_recebido),f
	skipz
	goto	u327_21
	goto	u327_20
u327_21:
	goto	i1l5137
u327_20:
	
i1l5135:	
	bcf	status, 5	;RP0=0, select bank0
	bsf	(_FLAGS_1)+(6/8),(6)&7
	goto	i1l929
	line	245
	
i1l983:	
	line	246
	
i1l5137:	
;TC_2015.c: 245: else{
;TC_2015.c: 246: nova_senha[ordem] = dado_recebido;
	movf	(_dado_recebido),w
	movwf	(??_aux+0)+0
	movf	(_ordem),w
	addlw	_nova_senha&0ffh
	movwf	fsr0
	movf	(??_aux+0)+0,w
	bcf	status, 7	;select IRP bank0
	movwf	indf
	line	247
	
i1l5139:	
;TC_2015.c: 247: ordem++;
	movlw	(01h)
	movwf	(??_aux+0)+0
	movf	(??_aux+0)+0,w
	addwf	(_ordem),f
	line	248
	
i1l5141:	
;TC_2015.c: 248: if(ordem == 14) { (FLAGS_1 |= (1<<6)); (FLAGS_1 |= (1<<7)); }
	movf	(_ordem),w
	xorlw	0Eh
	skipz
	goto	u328_21
	goto	u328_20
u328_21:
	goto	i1l929
u328_20:
	
i1l5143:	
	bcf	status, 5	;RP0=0, select bank0
	bsf	(_FLAGS_1)+(6/8),(6)&7
	bsf	(_FLAGS_1)+(7/8),(7)&7
	goto	i1l929
	
i1l985:	
	goto	i1l929
	line	249
	
i1l984:	
	line	251
;TC_2015.c: 249: }
;TC_2015.c: 251: }
	goto	i1l929
	line	253
	
i1l982:	
	
i1l5145:	
;TC_2015.c: 253: else if(etapa == 4){
	movf	(_etapa),w
	xorlw	04h
	skipz
	goto	u329_21
	goto	u329_20
u329_21:
	goto	i1l929
u329_20:
	line	254
	
i1l5147:	
;TC_2015.c: 254: if(dado_recebido != 'F') (FLAGS_1 |= (1<<1));
	movf	(_dado_recebido),w
	xorlw	046h
	skipnz
	goto	u330_21
	goto	u330_20
u330_21:
	goto	i1l988
u330_20:
	
i1l5149:	
	bcf	status, 5	;RP0=0, select bank0
	bsf	(_FLAGS_1)+(1/8),(1)&7
	
i1l988:	
	line	255
;TC_2015.c: 255: enviar=1;
	bsf	(_enviar/8),(_enviar)&7
	line	256
;TC_2015.c: 256: etapa = 0;}
	clrf	(_etapa)
	goto	i1l929
	
i1l987:	
	goto	i1l929
	line	259
	
i1l986:	
	goto	i1l929
	
i1l981:	
	goto	i1l929
	
i1l979:	
	goto	i1l929
	
i1l977:	
	goto	i1l929
	
i1l972:	
	goto	i1l929
	
i1l963:	
	goto	i1l929
	
i1l951:	
	goto	i1l929
	
i1l948:	
	goto	i1l929
	
i1l945:	
	goto	i1l929
	
i1l931:	
	
i1l929:	
	line	260
;TC_2015.c: 259: }
;TC_2015.c: 260: RCIF=0;}
	bcf	status, 5	;RP0=0, select bank0
	bcf	(101/8),(101)&7
	goto	i1l989
	
i1l924:	
	line	262
	
i1l989:	
	movf	(??_aux+5),w
	bcf	status, 5	;RP0=0, select bank0
	movwf	btemp+1
	movf	(??_aux+4),w
	movwf	pclath
	movf	(??_aux+3),w
	movwf	fsr0
	swapf	(??_aux+2)^0FFFFFF80h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_aux
	__end_of_aux:
;; =============== function _aux ends ============

	signat	_aux,88
psect	text217,local,class=CODE,delta=2
global __ptext217
__ptext217:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
