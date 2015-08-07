opt subtitle "Microchip Technology Omniscient Code Generator (PRO mode) build 201502162209"

opt pagewidth 120

	opt pm

	processor	18F4550
porta	equ	0F80h
portb	equ	0F81h
portc	equ	0F82h
portd	equ	0F83h
porte	equ	0F84h
lata	equ	0F89h
latb	equ	0F8Ah
latc	equ	0F8Bh
latd	equ	0F8Ch
late	equ	0F8Dh
trisa	equ	0F92h
trisb	equ	0F93h
trisc	equ	0F94h
trisd	equ	0F95h
trise	equ	0F96h
pie1	equ	0F9Dh
pir1	equ	0F9Eh
ipr1	equ	0F9Fh
pie2	equ	0FA0h
pir2	equ	0FA1h
ipr2	equ	0FA2h
t3con	equ	0FB1h
tmr3l	equ	0FB2h
tmr3h	equ	0FB3h
ccp1con	equ	0FBDh
ccpr1l	equ	0FBEh
ccpr1h	equ	0FBFh
adcon1	equ	0FC1h
adcon0	equ	0FC2h
adresl	equ	0FC3h
adresh	equ	0FC4h
sspcon2	equ	0FC5h
sspcon1	equ	0FC6h
sspstat	equ	0FC7h
sspadd	equ	0FC8h
sspbuf	equ	0FC9h
t2con	equ	0FCAh
pr2	equ	0FCBh
tmr2	equ	0FCCh
t1con	equ	0FCDh
tmr1l	equ	0FCEh
tmr1h	equ	0FCFh
rcon	equ	0FD0h
wdtcon	equ	0FD1h
lvdcon	equ	0FD2h
osccon	equ	0FD3h
t0con	equ	0FD5h
tmr0l	equ	0FD6h
tmr0h	equ	0FD7h
status	equ	0FD8h
fsr2	equ	0FD9h
fsr2l	equ	0FD9h
fsr2h	equ	0FDAh
plusw2	equ	0FDBh
preinc2	equ	0FDCh
postdec2	equ	0FDDh
postinc2	equ	0FDEh
indf2	equ	0FDFh
bsr	equ	0FE0h
fsr1	equ	0FE1h
fsr1l	equ	0FE1h
fsr1h	equ	0FE2h
plusw1	equ	0FE3h
preinc1	equ	0FE4h
postdec1	equ	0FE5h
postinc1	equ	0FE6h
indf1	equ	0FE7h
wreg	equ	0FE8h
fsr0	equ	0FE9h
fsr0l	equ	0FE9h
fsr0h	equ	0FEAh
plusw0	equ	0FEBh
preinc0	equ	0FECh
postdec0	equ	0FEDh
postinc0	equ	0FEEh
indf0	equ	0FEFh
intcon3	equ	0FF0h
intcon2	equ	0FF1h
intcon	equ	0FF2h
prod	equ	0FF3h
prodl	equ	0FF3h
prodh	equ	0FF4h
tablat	equ	0FF5h
tblptr	equ	0FF6h
tblptrl	equ	0FF6h
tblptrh	equ	0FF7h
tblptru	equ	0FF8h
pcl	equ	0FF9h
pclat	equ	0FFAh
pclath	equ	0FFAh
pclatu	equ	0FFBh
stkptr	equ	0FFCh
tosl	equ	0FFDh
tosh	equ	0FFEh
tosu	equ	0FFFh
clrc   macro
	bcf	status,0
endm
setc   macro
	bsf	status,0
endm
clrz   macro
	bcf	status,2
endm
setz   macro
	bsf	status,2
endm
skipnz macro
	btfsc	status,2
endm
skipz  macro
	btfss	status,2
endm
skipnc macro
	btfsc	status,0
endm
skipc  macro
	btfss	status,0
endm
pushw macro
	movwf postinc1
endm
pushf macro arg1
	movff arg1, postinc1
endm
popw macro
	movf postdec1,f
	movf indf1,w
endm
popf macro arg1
	movf postdec1,f
	movff indf1,arg1
endm
popfc macro arg1
	movff plusw1,arg1
	decfsz fsr1,f
endm
	global	__ramtop
	global	__accesstop
# 51 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SPPDATA equ 0F62h ;# 
# 70 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SPPCFG equ 0F63h ;# 
# 146 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SPPEPS equ 0F64h ;# 
# 219 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SPPCON equ 0F65h ;# 
# 244 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UFRM equ 0F66h ;# 
# 250 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UFRML equ 0F66h ;# 
# 327 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UFRMH equ 0F67h ;# 
# 366 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UIR equ 0F68h ;# 
# 421 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UIE equ 0F69h ;# 
# 476 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEIR equ 0F6Ah ;# 
# 526 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEIE equ 0F6Bh ;# 
# 576 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
USTAT equ 0F6Ch ;# 
# 635 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UCON equ 0F6Dh ;# 
# 685 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UADDR equ 0F6Eh ;# 
# 748 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UCFG equ 0F6Fh ;# 
# 829 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP0 equ 0F70h ;# 
# 960 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP1 equ 0F71h ;# 
# 1091 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP2 equ 0F72h ;# 
# 1222 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP3 equ 0F73h ;# 
# 1353 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP4 equ 0F74h ;# 
# 1484 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP5 equ 0F75h ;# 
# 1615 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP6 equ 0F76h ;# 
# 1746 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP7 equ 0F77h ;# 
# 1877 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP8 equ 0F78h ;# 
# 1964 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP9 equ 0F79h ;# 
# 2051 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP10 equ 0F7Ah ;# 
# 2138 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP11 equ 0F7Bh ;# 
# 2225 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP12 equ 0F7Ch ;# 
# 2312 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP13 equ 0F7Dh ;# 
# 2399 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP14 equ 0F7Eh ;# 
# 2486 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
UEP15 equ 0F7Fh ;# 
# 2573 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PORTA equ 0F80h ;# 
# 2729 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PORTB equ 0F81h ;# 
# 2838 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PORTC equ 0F82h ;# 
# 2991 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PORTD equ 0F83h ;# 
# 3111 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PORTE equ 0F84h ;# 
# 3362 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
LATA equ 0F89h ;# 
# 3497 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
LATB equ 0F8Ah ;# 
# 3629 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
LATC equ 0F8Bh ;# 
# 3744 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
LATD equ 0F8Ch ;# 
# 3876 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
LATE equ 0F8Dh ;# 
# 3978 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TRISA equ 0F92h ;# 
# 3983 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
DDRA equ 0F92h ;# 
# 4175 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TRISB equ 0F93h ;# 
# 4180 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
DDRB equ 0F93h ;# 
# 4396 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TRISC equ 0F94h ;# 
# 4401 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
DDRC equ 0F94h ;# 
# 4567 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TRISD equ 0F95h ;# 
# 4572 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
DDRD equ 0F95h ;# 
# 4788 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TRISE equ 0F96h ;# 
# 4793 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
DDRE equ 0F96h ;# 
# 4889 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
OSCTUNE equ 0F9Bh ;# 
# 4947 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PIE1 equ 0F9Dh ;# 
# 5035 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PIR1 equ 0F9Eh ;# 
# 5123 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
IPR1 equ 0F9Fh ;# 
# 5211 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PIE2 equ 0FA0h ;# 
# 5281 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PIR2 equ 0FA1h ;# 
# 5351 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
IPR2 equ 0FA2h ;# 
# 5421 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
EECON1 equ 0FA6h ;# 
# 5486 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
EECON2 equ 0FA7h ;# 
# 5492 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
EEDATA equ 0FA8h ;# 
# 5498 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
EEADR equ 0FA9h ;# 
# 5504 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
RCSTA equ 0FABh ;# 
# 5509 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
RCSTA1 equ 0FABh ;# 
# 5713 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TXSTA equ 0FACh ;# 
# 5718 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TXSTA1 equ 0FACh ;# 
# 6010 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TXREG equ 0FADh ;# 
# 6015 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TXREG1 equ 0FADh ;# 
# 6021 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
RCREG equ 0FAEh ;# 
# 6026 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
RCREG1 equ 0FAEh ;# 
# 6032 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SPBRG equ 0FAFh ;# 
# 6037 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SPBRG1 equ 0FAFh ;# 
# 6043 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SPBRGH equ 0FB0h ;# 
# 6049 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
T3CON equ 0FB1h ;# 
# 6171 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR3 equ 0FB2h ;# 
# 6177 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR3L equ 0FB2h ;# 
# 6183 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR3H equ 0FB3h ;# 
# 6189 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CMCON equ 0FB4h ;# 
# 6284 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CVRCON equ 0FB5h ;# 
# 6368 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ECCP1AS equ 0FB6h ;# 
# 6373 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCP1AS equ 0FB6h ;# 
# 6529 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ECCP1DEL equ 0FB7h ;# 
# 6534 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCP1DEL equ 0FB7h ;# 
# 6666 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
BAUDCON equ 0FB8h ;# 
# 6671 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
BAUDCTL equ 0FB8h ;# 
# 6845 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCP2CON equ 0FBAh ;# 
# 6908 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCPR2 equ 0FBBh ;# 
# 6914 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCPR2L equ 0FBBh ;# 
# 6920 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCPR2H equ 0FBCh ;# 
# 6926 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCP1CON equ 0FBDh ;# 
# 6931 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ECCP1CON equ 0FBDh ;# 
# 7087 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCPR1 equ 0FBEh ;# 
# 7093 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCPR1L equ 0FBEh ;# 
# 7099 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
CCPR1H equ 0FBFh ;# 
# 7105 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ADCON2 equ 0FC0h ;# 
# 7175 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ADCON1 equ 0FC1h ;# 
# 7265 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ADCON0 equ 0FC2h ;# 
# 7387 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ADRES equ 0FC3h ;# 
# 7393 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ADRESL equ 0FC3h ;# 
# 7399 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
ADRESH equ 0FC4h ;# 
# 7405 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SSPCON2 equ 0FC5h ;# 
# 7466 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SSPCON1 equ 0FC6h ;# 
# 7535 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SSPSTAT equ 0FC7h ;# 
# 7801 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SSPADD equ 0FC8h ;# 
# 7807 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
SSPBUF equ 0FC9h ;# 
# 7813 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
T2CON equ 0FCAh ;# 
# 7910 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PR2 equ 0FCBh ;# 
# 7915 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
MEMCON equ 0FCBh ;# 
# 8019 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR2 equ 0FCCh ;# 
# 8025 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
T1CON equ 0FCDh ;# 
# 8129 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR1 equ 0FCEh ;# 
# 8135 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR1L equ 0FCEh ;# 
# 8141 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR1H equ 0FCFh ;# 
# 8147 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
RCON equ 0FD0h ;# 
# 8295 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
WDTCON equ 0FD1h ;# 
# 8322 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
HLVDCON equ 0FD2h ;# 
# 8327 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
LVDCON equ 0FD2h ;# 
# 8591 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
OSCCON equ 0FD3h ;# 
# 8673 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
T0CON equ 0FD5h ;# 
# 8742 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR0 equ 0FD6h ;# 
# 8748 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR0L equ 0FD6h ;# 
# 8754 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TMR0H equ 0FD7h ;# 
# 8760 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
STATUS equ 0FD8h ;# 
# 8838 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR2 equ 0FD9h ;# 
# 8844 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR2L equ 0FD9h ;# 
# 8850 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR2H equ 0FDAh ;# 
# 8856 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PLUSW2 equ 0FDBh ;# 
# 8862 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PREINC2 equ 0FDCh ;# 
# 8868 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
POSTDEC2 equ 0FDDh ;# 
# 8874 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
POSTINC2 equ 0FDEh ;# 
# 8880 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
INDF2 equ 0FDFh ;# 
# 8886 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
BSR equ 0FE0h ;# 
# 8892 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR1 equ 0FE1h ;# 
# 8898 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR1L equ 0FE1h ;# 
# 8904 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR1H equ 0FE2h ;# 
# 8910 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PLUSW1 equ 0FE3h ;# 
# 8916 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PREINC1 equ 0FE4h ;# 
# 8922 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
POSTDEC1 equ 0FE5h ;# 
# 8928 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
POSTINC1 equ 0FE6h ;# 
# 8934 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
INDF1 equ 0FE7h ;# 
# 8940 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
WREG equ 0FE8h ;# 
# 8946 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR0 equ 0FE9h ;# 
# 8952 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR0L equ 0FE9h ;# 
# 8958 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
FSR0H equ 0FEAh ;# 
# 8964 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PLUSW0 equ 0FEBh ;# 
# 8970 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PREINC0 equ 0FECh ;# 
# 8976 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
POSTDEC0 equ 0FEDh ;# 
# 8982 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
POSTINC0 equ 0FEEh ;# 
# 8988 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
INDF0 equ 0FEFh ;# 
# 8994 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
INTCON3 equ 0FF0h ;# 
# 9085 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
INTCON2 equ 0FF1h ;# 
# 9161 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
INTCON equ 0FF2h ;# 
# 9297 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PROD equ 0FF3h ;# 
# 9303 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PRODL equ 0FF3h ;# 
# 9309 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PRODH equ 0FF4h ;# 
# 9315 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TABLAT equ 0FF5h ;# 
# 9323 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TBLPTR equ 0FF6h ;# 
# 9329 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TBLPTRL equ 0FF6h ;# 
# 9335 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TBLPTRH equ 0FF7h ;# 
# 9341 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TBLPTRU equ 0FF8h ;# 
# 9349 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PCLAT equ 0FF9h ;# 
# 9356 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PC equ 0FF9h ;# 
# 9362 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PCL equ 0FF9h ;# 
# 9368 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PCLATH equ 0FFAh ;# 
# 9374 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
PCLATU equ 0FFBh ;# 
# 9380 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
STKPTR equ 0FFCh ;# 
# 9455 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TOS equ 0FFDh ;# 
# 9461 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TOSL equ 0FFDh ;# 
# 9467 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TOSH equ 0FFEh ;# 
# 9473 "C:\Program Files (x86)\Microchip\xc8\v1.34\include\pic18f4550.h"
TOSU equ 0FFFh ;# 
	FNCALL	_main,_Busy_eep
	FNCALL	_main,_Read_b_eep
	FNCALL	_main,_Write_b_eep
	FNCALL	_main,_carregar_senha
	FNCALL	_main,_config_serial
	FNCALL	_main,_delay_ms
	FNCALL	_main,_eeprom_config_inicial
	FNCALL	_main,_numero_para_ascii
	FNCALL	_main,_verificar_num_contas
	FNCALL	_verificar_num_contas,_Read_b_eep
	FNCALL	_numero_para_ascii,___awdiv
	FNCALL	_numero_para_ascii,___lbdiv
	FNCALL	_numero_para_ascii,___wmul
	FNCALL	_eeprom_config_inicial,_Busy_eep
	FNCALL	_eeprom_config_inicial,_Write_b_eep
	FNCALL	_carregar_senha,_Read_b_eep
	FNROOT	_main
	FNCALL	_aux,_ascii_para_numero
	FNCALL	_aux,_teclado_matricial
	FNCALL	_aux,i2_numero_para_ascii
	FNCALL	i2_numero_para_ascii,i2___awdiv
	FNCALL	i2_numero_para_ascii,i2___lbdiv
	FNCALL	i2_numero_para_ascii,i2___wmul
	FNCALL	intlevel2,_aux
	global	intlevel2
	FNROOT	intlevel2
	global	_qtd_max_dias
psect	idataCOMRAM,class=CODE,space=0,delta=1,noexec
global __pidataCOMRAM
__pidataCOMRAM:
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	42

;initializer for _qtd_max_dias
	db	low(01Fh)
	global	_senha
	global	_ptr_data
	global	_FLAGS_1
	global	_PORTB_SR
	global	_buffer_serial
	global	_caractere_recebido
	global	_conta
	global	_dado_recebido
	global	_etapa
	global	_funcao
	global	_nivel_acesso
	global	_ordem
	global	_qtd_total_contas
	global	_ultima_conta
	global	_data_atual
	global	_enviar
	global	_nova_senha
	global	_ADCON1
_ADCON1	set	0xFC1
	global	_CMCON
_CMCON	set	0xFB4
	global	_EEADR
_EEADR	set	0xFA9
	global	_EECON1bits
_EECON1bits	set	0xFA6
	global	_EECON2
_EECON2	set	0xFA7
	global	_EEDATA
_EEDATA	set	0xFA8
	global	_INTCON
_INTCON	set	0xFF2
	global	_INTCON2
_INTCON2	set	0xFF1
	global	_INTCONbits
_INTCONbits	set	0xFF2
	global	_LATB
_LATB	set	0xF8A
	global	_LATBbits
_LATBbits	set	0xF8A
	global	_LATD
_LATD	set	0xF8C
	global	_LATDbits
_LATDbits	set	0xF8C
	global	_OSCCON
_OSCCON	set	0xFD3
	global	_PIE1
_PIE1	set	0xF9D
	global	_PORTAbits
_PORTAbits	set	0xF80
	global	_PORTB
_PORTB	set	0xF81
	global	_PORTBbits
_PORTBbits	set	0xF81
	global	_PORTCbits
_PORTCbits	set	0xF82
	global	_RCONbits
_RCONbits	set	0xFD0
	global	_RCREG
_RCREG	set	0xFAE
	global	_SPBRG
_SPBRG	set	0xFAF
	global	_T1CON
_T1CON	set	0xFCD
	global	_TMR1H
_TMR1H	set	0xFCF
	global	_TMR1L
_TMR1L	set	0xFCE
	global	_TRISB
_TRISB	set	0xF93
	global	_TRISC
_TRISC	set	0xF94
	global	_TRISD
_TRISD	set	0xF95
	global	_TXREG
_TXREG	set	0xFAD
	global	_BRG16
_BRG16	set	0x7DC3
	global	_BRGH
_BRGH	set	0x7D62
	global	_CREN
_CREN	set	0x7D5C
	global	_FERR
_FERR	set	0x7D5A
	global	_OERR
_OERR	set	0x7D59
	global	_RBIE
_RBIE	set	0x7F93
	global	_RBIF
_RBIF	set	0x7F90
	global	_RCIE
_RCIE	set	0x7CED
	global	_RCIF
_RCIF	set	0x7CF5
	global	_RX9
_RX9	set	0x7D5E
	global	_SPEN
_SPEN	set	0x7D5F
	global	_SYNC
_SYNC	set	0x7D64
	global	_TMR1IE
_TMR1IE	set	0x7CE8
	global	_TMR1IF
_TMR1IF	set	0x7CF0
	global	_TRMT
_TRMT	set	0x7D61
	global	_TX9
_TX9	set	0x7D66
	global	_TXCKP
_TXCKP	set	0x7DC4
	global	_TXEN
_TXEN	set	0x7D65
	global	_TXIE
_TXIE	set	0x7CEC
	global	_WR
_WR	set	0x7D31
; #config settings
global __CFG_PLLDIV$4
__CFG_PLLDIV$4 equ 0x0
global __CFG_FCMEN$OFF
__CFG_FCMEN$OFF equ 0x0
global __CFG_IESO$OFF
__CFG_IESO$OFF equ 0x0
global __CFG_FOSC$INTOSCIO_EC
__CFG_FOSC$INTOSCIO_EC equ 0x0
global __CFG_PWRT$ON
__CFG_PWRT$ON equ 0x0
global __CFG_BOR$OFF
__CFG_BOR$OFF equ 0x0
global __CFG_WDT$OFF
__CFG_WDT$OFF equ 0x0
global __CFG_CCP2MX$OFF
__CFG_CCP2MX$OFF equ 0x0
global __CFG_PBADEN$OFF
__CFG_PBADEN$OFF equ 0x0
global __CFG_MCLRE$ON
__CFG_MCLRE$ON equ 0x0
global __CFG_LPT1OSC$OFF
__CFG_LPT1OSC$OFF equ 0x0
global __CFG_STVREN$ON
__CFG_STVREN$ON equ 0x0
global __CFG_LVP$OFF
__CFG_LVP$OFF equ 0x0
global __CFG_XINST$OFF
__CFG_XINST$OFF equ 0x0
global __CFG_CP0$OFF
__CFG_CP0$OFF equ 0x0
global __CFG_CP1$OFF
__CFG_CP1$OFF equ 0x0
global __CFG_CP2$OFF
__CFG_CP2$OFF equ 0x0
global __CFG_CP3$OFF
__CFG_CP3$OFF equ 0x0
global __CFG_CPB$OFF
__CFG_CPB$OFF equ 0x0
global __CFG_CPD$OFF
__CFG_CPD$OFF equ 0x0
global __CFG_WRT0$OFF
__CFG_WRT0$OFF equ 0x0
global __CFG_WRT1$OFF
__CFG_WRT1$OFF equ 0x0
global __CFG_WRT2$OFF
__CFG_WRT2$OFF equ 0x0
global __CFG_WRT3$OFF
__CFG_WRT3$OFF equ 0x0
global __CFG_WRTB$OFF
__CFG_WRTB$OFF equ 0x0
global __CFG_WRTC$OFF
__CFG_WRTC$OFF equ 0x0
global __CFG_WRTD$OFF
__CFG_WRTD$OFF equ 0x0
global __CFG_EBTR0$OFF
__CFG_EBTR0$OFF equ 0x0
global __CFG_EBTR1$OFF
__CFG_EBTR1$OFF equ 0x0
global __CFG_EBTR2$OFF
__CFG_EBTR2$OFF equ 0x0
global __CFG_EBTR3$OFF
__CFG_EBTR3$OFF equ 0x0
global __CFG_EBTRB$OFF
__CFG_EBTRB$OFF equ 0x0
	file	"tc2015.as"
	line	#
psect	cinit,class=CODE,delta=1,reloc=2
global __pcinit
__pcinit:
global start_initialization
start_initialization:

global __initialization
__initialization:
psect	bitbssCOMRAM,class=COMRAM,bit,space=1,noexec
global __pbitbssCOMRAM
__pbitbssCOMRAM:
	global	_enviar
_enviar:
       ds      1
psect	bssCOMRAM,class=COMRAM,space=1,noexec
global __pbssCOMRAM
__pbssCOMRAM:
	global	_senha
_senha:
       ds      16
	global	_ptr_data
_ptr_data:
       ds      2
	global	_FLAGS_1
_FLAGS_1:
       ds      1
	global	_PORTB_SR
_PORTB_SR:
       ds      1
	global	_buffer_serial
_buffer_serial:
       ds      1
	global	_caractere_recebido
_caractere_recebido:
       ds      1
	global	_conta
_conta:
       ds      1
	global	_dado_recebido
_dado_recebido:
       ds      1
	global	_etapa
_etapa:
       ds      1
	global	_funcao
_funcao:
       ds      1
	global	_nivel_acesso
_nivel_acesso:
       ds      1
	global	_ordem
_ordem:
       ds      1
	global	_qtd_total_contas
_qtd_total_contas:
       ds      1
	global	_ultima_conta
_ultima_conta:
       ds      1
	global	_data_atual
_data_atual:
       ds      7
psect	dataCOMRAM,class=COMRAM,space=1,noexec
global __pdataCOMRAM
__pdataCOMRAM:
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	42
	global	_qtd_max_dias
_qtd_max_dias:
       ds      1
psect	bssBANK0,class=BANK0,space=1,noexec
global __pbssBANK0
__pbssBANK0:
	global	_nova_senha
_nova_senha:
       ds      16
	file	"tc2015.as"
	line	#
psect	cinit
; Clear objects allocated to BANK0 (16 bytes)
	global __pbssBANK0
lfsr	0,__pbssBANK0
movlw	16
clear_0:
clrf	postinc0,c
decf	wreg
bnz	clear_0
; Clear objects allocated to BITCOMRAM (1 bytes)
	global __pbitbssCOMRAM
clrf	(__pbitbssCOMRAM/8+0)&0xffh,c
; Clear objects allocated to COMRAM (37 bytes)
	global __pbssCOMRAM
lfsr	0,__pbssCOMRAM
movlw	37
clear_1:
clrf	postinc0,c
decf	wreg
bnz	clear_1
	line	#
; Initialize objects allocated to COMRAM (1 bytes)
	global __pidataCOMRAM
	; load TBLPTR registers with __pidataCOMRAM
	movlw	low (__pidataCOMRAM)
	movwf	tblptrl
	movlw	high(__pidataCOMRAM)
	movwf	tblptrh
	movlw	low highword(__pidataCOMRAM)
	movwf	tblptru
	tblrd*+ ;fetch initializer
	movff	tablat, __pdataCOMRAM+0		
psect cinit,class=CODE,delta=1
global end_of_initialization,__end_of__initialization

;End of C runtime variable initialization code

end_of_initialization:
__end_of__initialization:	GLOBAL	__Lmediumconst
	movlw	low highword(__Lmediumconst)
	movwf	tblptru
movlb 0
goto _main	;jump to C main() function
psect	cstackBANK0,class=BANK0,space=1,noexec
global __pcstackBANK0
__pcstackBANK0:
??_Busy_eep:	; 0 bytes @ 0x0
?_Write_b_eep:	; 0 bytes @ 0x0
?_delay_ms:	; 0 bytes @ 0x0
??_config_serial:	; 0 bytes @ 0x0
?_Read_b_eep:	; 1 bytes @ 0x0
?___lbdiv:	; 1 bytes @ 0x0
	global	?___wmul
?___wmul:	; 2 bytes @ 0x0
	global	___lbdiv@divisor
___lbdiv@divisor:	; 1 bytes @ 0x0
	global	delay_ms@delay_total
delay_ms@delay_total:	; 2 bytes @ 0x0
	global	Read_b_eep@badd
Read_b_eep@badd:	; 2 bytes @ 0x0
	global	Write_b_eep@badd
Write_b_eep@badd:	; 2 bytes @ 0x0
	global	___wmul@multiplier
___wmul@multiplier:	; 2 bytes @ 0x0
	ds   1
??___lbdiv:	; 0 bytes @ 0x1
	global	___lbdiv@dividend
___lbdiv@dividend:	; 1 bytes @ 0x1
	ds   1
??_Read_b_eep:	; 0 bytes @ 0x2
??_delay_ms:	; 0 bytes @ 0x2
??_verificar_num_contas:	; 0 bytes @ 0x2
??_carregar_senha:	; 0 bytes @ 0x2
	global	verificar_num_contas@i
verificar_num_contas@i:	; 1 bytes @ 0x2
	global	Write_b_eep@bdat
Write_b_eep@bdat:	; 1 bytes @ 0x2
	global	___lbdiv@counter
___lbdiv@counter:	; 1 bytes @ 0x2
	global	___wmul@multiplicand
___wmul@multiplicand:	; 2 bytes @ 0x2
	ds   1
??_Write_b_eep:	; 0 bytes @ 0x3
	global	Write_b_eep@GIE_BIT_VAL
Write_b_eep@GIE_BIT_VAL:	; 1 bytes @ 0x3
	global	___lbdiv@quotient
___lbdiv@quotient:	; 1 bytes @ 0x3
	global	delay_ms@temp
delay_ms@temp:	; 2 bytes @ 0x3
	ds   1
??_eeprom_config_inicial:	; 0 bytes @ 0x4
??___wmul:	; 0 bytes @ 0x4
	global	eeprom_config_inicial@i
eeprom_config_inicial@i:	; 1 bytes @ 0x4
	global	carregar_senha@i
carregar_senha@i:	; 1 bytes @ 0x4
	global	___wmul@product
___wmul@product:	; 2 bytes @ 0x4
	ds   2
	global	?___awdiv
?___awdiv:	; 2 bytes @ 0x6
	global	___awdiv@dividend
___awdiv@dividend:	; 2 bytes @ 0x6
	ds   2
	global	___awdiv@divisor
___awdiv@divisor:	; 2 bytes @ 0x8
	ds   2
??___awdiv:	; 0 bytes @ 0xA
	global	___awdiv@counter
___awdiv@counter:	; 1 bytes @ 0xA
	ds   1
	global	___awdiv@sign
___awdiv@sign:	; 1 bytes @ 0xB
	ds   1
	global	___awdiv@quotient
___awdiv@quotient:	; 2 bytes @ 0xC
	ds   2
??_numero_para_ascii:	; 0 bytes @ 0xE
	ds   1
	global	numero_para_ascii@temp2
numero_para_ascii@temp2:	; 1 bytes @ 0xF
	ds   1
	global	numero_para_ascii@numero
numero_para_ascii@numero:	; 1 bytes @ 0x10
	ds   1
	global	numero_para_ascii@temp1
numero_para_ascii@temp1:	; 1 bytes @ 0x11
	ds   1
??_main:	; 0 bytes @ 0x12
	ds   2
	global	main@i
main@i:	; 1 bytes @ 0x14
	ds   1
psect	cstackCOMRAM,class=COMRAM,space=1,noexec
global __pcstackCOMRAM
__pcstackCOMRAM:
?_Busy_eep:	; 0 bytes @ 0x0
?_numero_para_ascii:	; 0 bytes @ 0x0
?_config_serial:	; 0 bytes @ 0x0
?_eeprom_config_inicial:	; 0 bytes @ 0x0
?_verificar_num_contas:	; 0 bytes @ 0x0
?_carregar_senha:	; 0 bytes @ 0x0
?_aux:	; 0 bytes @ 0x0
?i2_numero_para_ascii:	; 0 bytes @ 0x0
?_ascii_para_numero:	; 1 bytes @ 0x0
?_teclado_matricial:	; 1 bytes @ 0x0
?i2___lbdiv:	; 1 bytes @ 0x0
?_main:	; 2 bytes @ 0x0
	global	?i2___wmul
?i2___wmul:	; 2 bytes @ 0x0
	global	ascii_para_numero@caractere2
ascii_para_numero@caractere2:	; 1 bytes @ 0x0
	global	teclado_matricial@linha
teclado_matricial@linha:	; 1 bytes @ 0x0
	global	i2___lbdiv@divisor
i2___lbdiv@divisor:	; 1 bytes @ 0x0
	global	i2___wmul@multiplier
i2___wmul@multiplier:	; 2 bytes @ 0x0
	ds   1
??_teclado_matricial:	; 0 bytes @ 0x1
??i2___lbdiv:	; 0 bytes @ 0x1
	global	ascii_para_numero@caractere1
ascii_para_numero@caractere1:	; 1 bytes @ 0x1
	global	teclado_matricial@coluna
teclado_matricial@coluna:	; 1 bytes @ 0x1
	global	i2___lbdiv@dividend
i2___lbdiv@dividend:	; 1 bytes @ 0x1
	ds   1
??_ascii_para_numero:	; 0 bytes @ 0x2
	global	ascii_para_numero@caractere3
ascii_para_numero@caractere3:	; 1 bytes @ 0x2
	global	teclado_matricial@temp
teclado_matricial@temp:	; 1 bytes @ 0x2
	global	i2___lbdiv@counter
i2___lbdiv@counter:	; 1 bytes @ 0x2
	global	i2___wmul@multiplicand
i2___wmul@multiplicand:	; 2 bytes @ 0x2
	ds   1
	global	ascii_para_numero@numero
ascii_para_numero@numero:	; 1 bytes @ 0x3
	global	teclado_matricial@caractere
teclado_matricial@caractere:	; 1 bytes @ 0x3
	global	i2___lbdiv@quotient
i2___lbdiv@quotient:	; 1 bytes @ 0x3
	ds   1
??i2___wmul:	; 0 bytes @ 0x4
	global	i2___wmul@product
i2___wmul@product:	; 2 bytes @ 0x4
	ds   2
	global	?i2___awdiv
?i2___awdiv:	; 2 bytes @ 0x6
	global	i2___awdiv@dividend
i2___awdiv@dividend:	; 2 bytes @ 0x6
	ds   2
	global	i2___awdiv@divisor
i2___awdiv@divisor:	; 2 bytes @ 0x8
	ds   2
??i2___awdiv:	; 0 bytes @ 0xA
	global	i2___awdiv@counter
i2___awdiv@counter:	; 1 bytes @ 0xA
	ds   1
	global	i2___awdiv@sign
i2___awdiv@sign:	; 1 bytes @ 0xB
	ds   1
	global	i2___awdiv@quotient
i2___awdiv@quotient:	; 2 bytes @ 0xC
	ds   2
??i2_numero_para_ascii:	; 0 bytes @ 0xE
	ds   1
	global	i2numero_para_ascii@numero
i2numero_para_ascii@numero:	; 1 bytes @ 0xF
	ds   1
	global	i2numero_para_ascii@temp2
i2numero_para_ascii@temp2:	; 1 bytes @ 0x10
	ds   1
	global	i2numero_para_ascii@temp1
i2numero_para_ascii@temp1:	; 1 bytes @ 0x11
	ds   1
??_aux:	; 0 bytes @ 0x12
	ds   8
	global	aux@temp
aux@temp:	; 1 bytes @ 0x1A
	ds   1
	global	aux@conta_a_ser_alterada
aux@conta_a_ser_alterada:	; 1 bytes @ 0x1B
	ds   1
	global	aux@coluna
aux@coluna:	; 1 bytes @ 0x1C
	ds   1
	global	aux@linha
aux@linha:	; 1 bytes @ 0x1D
	ds   1
;!
;!Data Sizes:
;!    Strings     0
;!    Constant    0
;!    Data        1
;!    BSS         53
;!    Persistent  0
;!    Stack       0
;!
;!Auto Spaces:
;!    Space          Size  Autos    Used
;!    COMRAM           95     30      69
;!    BANK0           160     21      37
;!    BANK1           256      0       0
;!    BANK2           256      0       0
;!    BANK3           256      0       0
;!    BANK4           256      0       0
;!    BANK5           256      0       0
;!    BANK6           256      0       0
;!    BANK7           256      0       0

;!
;!Pointer List with Targets:
;!
;!    ptr_data	PTR unsigned char  size(2) Largest target is 7
;!		 -> NULL(NULL[0]), data_atual.ano(COMRAM[1]), data_atual(COMRAM[7]), 
;!


;!
;!Critical Paths under _main in COMRAM
;!
;!    None.
;!
;!Critical Paths under _aux in COMRAM
;!
;!    _aux->i2_numero_para_ascii
;!    i2_numero_para_ascii->i2___awdiv
;!    i2___awdiv->i2___wmul
;!
;!Critical Paths under _main in BANK0
;!
;!    _main->_numero_para_ascii
;!    _verificar_num_contas->_Read_b_eep
;!    _numero_para_ascii->___awdiv
;!    ___awdiv->___wmul
;!    _eeprom_config_inicial->_Write_b_eep
;!    _carregar_senha->_Read_b_eep
;!
;!Critical Paths under _aux in BANK0
;!
;!    None.
;!
;!Critical Paths under _main in BANK1
;!
;!    None.
;!
;!Critical Paths under _aux in BANK1
;!
;!    None.
;!
;!Critical Paths under _main in BANK2
;!
;!    None.
;!
;!Critical Paths under _aux in BANK2
;!
;!    None.
;!
;!Critical Paths under _main in BANK3
;!
;!    None.
;!
;!Critical Paths under _aux in BANK3
;!
;!    None.
;!
;!Critical Paths under _main in BANK4
;!
;!    None.
;!
;!Critical Paths under _aux in BANK4
;!
;!    None.
;!
;!Critical Paths under _main in BANK5
;!
;!    None.
;!
;!Critical Paths under _aux in BANK5
;!
;!    None.
;!
;!Critical Paths under _main in BANK6
;!
;!    None.
;!
;!Critical Paths under _aux in BANK6
;!
;!    None.
;!
;!Critical Paths under _main in BANK7
;!
;!    None.
;!
;!Critical Paths under _aux in BANK7
;!
;!    None.

;;
;;Main: autosize = 0, tempsize = 2, incstack = 0, save=0
;;

;!
;!Call Graph Tables:
;!
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (0) _main                                                 3     3      0    4583
;!                                             18 BANK0      3     3      0
;!                           _Busy_eep
;!                         _Read_b_eep
;!                        _Write_b_eep
;!                     _carregar_senha
;!                      _config_serial
;!                           _delay_ms
;!              _eeprom_config_inicial
;!                  _numero_para_ascii
;!               _verificar_num_contas
;! ---------------------------------------------------------------------------------
;! (1) _verificar_num_contas                                 1     1      0     438
;!                                              2 BANK0      1     1      0
;!                         _Read_b_eep
;! ---------------------------------------------------------------------------------
;! (1) _numero_para_ascii                                    4     4      0    1563
;!                                             14 BANK0      4     4      0
;!                            ___awdiv
;!                            ___lbdiv
;!                             ___wmul
;! ---------------------------------------------------------------------------------
;! (2) ___wmul                                               6     2      4     392
;!                                              0 BANK0      6     2      4
;! ---------------------------------------------------------------------------------
;! (2) ___lbdiv                                              4     3      1     318
;!                                              0 BANK0      4     3      1
;! ---------------------------------------------------------------------------------
;! (2) ___awdiv                                              8     4      4     599
;!                                              6 BANK0      8     4      4
;!                             ___wmul (ARG)
;! ---------------------------------------------------------------------------------
;! (1) _eeprom_config_inicial                                1     1      0     691
;!                                              4 BANK0      1     1      0
;!                           _Busy_eep
;!                        _Write_b_eep
;! ---------------------------------------------------------------------------------
;! (2) _Write_b_eep                                          4     1      3     561
;!                                              0 BANK0      4     1      3
;! ---------------------------------------------------------------------------------
;! (2) _Busy_eep                                             0     0      0       0
;! ---------------------------------------------------------------------------------
;! (1) _delay_ms                                             5     3      2     299
;!                                              0 BANK0      5     3      2
;! ---------------------------------------------------------------------------------
;! (1) _config_serial                                        0     0      0       0
;! ---------------------------------------------------------------------------------
;! (1) _carregar_senha                                       3     3      0     500
;!                                              2 BANK0      3     3      0
;!                         _Read_b_eep
;! ---------------------------------------------------------------------------------
;! (2) _Read_b_eep                                           2     0      2     339
;!                                              0 BANK0      2     0      2
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 2
;! ---------------------------------------------------------------------------------
;! (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;! ---------------------------------------------------------------------------------
;! (3) _aux                                                 12    12      0    1459
;!                                             18 COMRAM    12    12      0
;!                  _ascii_para_numero
;!                  _teclado_matricial
;!                i2_numero_para_ascii
;! ---------------------------------------------------------------------------------
;! (4) i2_numero_para_ascii                                  4     4      0     927
;!                                             14 COMRAM     4     4      0
;!                          i2___awdiv
;!                          i2___lbdiv
;!                           i2___wmul
;! ---------------------------------------------------------------------------------
;! (5) i2___wmul                                             6     2      4     209
;!                                              0 COMRAM     6     2      4
;! ---------------------------------------------------------------------------------
;! (5) i2___lbdiv                                            4     3      1     188
;!                                              0 COMRAM     4     3      1
;! ---------------------------------------------------------------------------------
;! (5) i2___awdiv                                            8     4      4     352
;!                                              6 COMRAM     8     4      4
;!                           i2___wmul (ARG)
;! ---------------------------------------------------------------------------------
;! (4) _teclado_matricial                                    4     3      1     169
;!                                              0 COMRAM     4     3      1
;! ---------------------------------------------------------------------------------
;! (4) _ascii_para_numero                                    4     2      2     219
;!                                              0 COMRAM     4     2      2
;! ---------------------------------------------------------------------------------
;! Estimated maximum stack depth 5
;! ---------------------------------------------------------------------------------
;!
;! Call Graph Graphs:
;!
;! _main (ROOT)
;!   _Busy_eep
;!   _Read_b_eep
;!   _Write_b_eep
;!   _carregar_senha
;!     _Read_b_eep
;!   _config_serial
;!   _delay_ms
;!   _eeprom_config_inicial
;!     _Busy_eep
;!     _Write_b_eep
;!   _numero_para_ascii
;!     ___awdiv
;!       ___wmul (ARG)
;!     ___lbdiv
;!     ___wmul
;!   _verificar_num_contas
;!     _Read_b_eep
;!
;! _aux (ROOT)
;!   _ascii_para_numero
;!   _teclado_matricial
;!   i2_numero_para_ascii
;!     i2___awdiv
;!       i2___wmul (ARG)
;!     i2___lbdiv
;!     i2___wmul
;!

;! Address spaces:

;!Name               Size   Autos  Total    Cost      Usage
;!BIGRAM             7FF      0       0      21        0.0%
;!EEDATA             100      0       0       0        0.0%
;!BITBANK7           100      0       0      18        0.0%
;!BANK7              100      0       0      19        0.0%
;!BITBANK6           100      0       0      16        0.0%
;!BANK6              100      0       0      17        0.0%
;!BITBANK5           100      0       0      14        0.0%
;!BANK5              100      0       0      15        0.0%
;!BITBANK4           100      0       0      12        0.0%
;!BANK4              100      0       0      13        0.0%
;!BITBANK3           100      0       0      10        0.0%
;!BANK3              100      0       0      11        0.0%
;!BITBANK2           100      0       0       8        0.0%
;!BANK2              100      0       0       9        0.0%
;!BITBANK1           100      0       0       6        0.0%
;!BANK1              100      0       0       7        0.0%
;!BITBANK0            A0      0       0       4        0.0%
;!BANK0               A0     15      25       5       23.1%
;!BITCOMRAM           5F      0       1       0        1.1%
;!COMRAM              5F     1E      45       1       72.6%
;!BITSFR               0      0       0      40        0.0%
;!SFR                  0      0       0      40        0.0%
;!STACK                0      0       0       2        0.0%
;!NULL                 0      0       0       0        0.0%
;!ABS                  0      0      6A      20        0.0%
;!DATA                 0      0      6A       3        0.0%
;!CODE                 0      0       0       0        0.0%

	global	_main

;; *************** function _main *****************
;; Defined at:
;;		line 638 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1   20[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  2  360[None  ] int 
;; Registers used:
;;		wreg, fsr1l, fsr1h, fsr2l, fsr2h, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0
;;      Totals:         0       3       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels required when called:    5
;; This function calls:
;;		_Busy_eep
;;		_Read_b_eep
;;		_Write_b_eep
;;		_carregar_senha
;;		_config_serial
;;		_delay_ms
;;		_eeprom_config_inicial
;;		_numero_para_ascii
;;		_verificar_num_contas
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	text0,class=CODE,space=0,reloc=2
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	638
global __ptext0
__ptext0:
psect	text0
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	638
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:
;incstack = 0
	opt	stack 26
	line	641
	
l2757:
;main.c: 641: OSCCON = 0xF2;
	movlw	low(0F2h)
	movwf	((c:4051)),c	;volatile
	line	644
;main.c: 644: INTCON = 0b11000000;
	movlw	low(0C0h)
	movwf	((c:4082)),c	;volatile
	line	645
	
l2759:
;main.c: 645: INTCON2 =0b00000000;
	clrf	((c:4081)),c	;volatile
	line	646
;main.c: 646: PIE1=0b00100001;
	movlw	low(021h)
	movwf	((c:3997)),c	;volatile
	line	647
	
l2761:
;main.c: 647: RCONbits.IPEN = 0;
	bcf	((c:4048)),c,7	;volatile
	line	650
;main.c: 650: T1CON= 0b00001111;
	movlw	low(0Fh)
	movwf	((c:4045)),c	;volatile
	line	651
;main.c: 651: TMR1H=0X80;
	movlw	low(080h)
	movwf	((c:4047)),c	;volatile
	line	652
	
l2763:
;main.c: 652: TMR1L=0;
	clrf	((c:4046)),c	;volatile
	line	655
	
l2765:
;main.c: 655: LATD=0;
	clrf	((c:3980)),c	;volatile
	line	656
	
l2767:
;main.c: 656: LATB=0x00;
	clrf	((c:3978)),c	;volatile
	line	657
;main.c: 657: TRISB=0xF0;
	movlw	low(0F0h)
	movwf	((c:3987)),c	;volatile
	line	658
;main.c: 658: TRISC=0xC3;
	movlw	low(0C3h)
	movwf	((c:3988)),c	;volatile
	line	659
	
l2769:
;main.c: 659: TRISD=0x00;
	clrf	((c:3989)),c	;volatile
	line	660
	
l2771:
;main.c: 660: ADCON1=0XFF;
	setf	((c:4033)),c	;volatile
	line	661
;main.c: 661: CMCON=0X07;
	movlw	low(07h)
	movwf	((c:4020)),c	;volatile
	line	664
	
l2773:
;main.c: 664: if(Read_b_eep(0) == 0xFF) eeprom_config_inicial();
	movlw	high(0)
	movlb	0	; () banked
	movwf	((Read_b_eep@badd+1))&0ffh
	movlw	low(0)
	movwf	((Read_b_eep@badd))&0ffh
	call	_Read_b_eep	;wreg free
	xorlw	0FFh
	btfss	status,2
	goto	u3221
	goto	u3220
u3221:
	goto	l2777
u3220:
	
l2775:
	call	_eeprom_config_inicial	;wreg free
	line	665
	
l2777:
;main.c: 665: config_serial();
	call	_config_serial	;wreg free
	line	666
	
l2779:
;main.c: 666: verificar_num_contas();
	call	_verificar_num_contas	;wreg free
	line	667
	
l2781:; BSR set to: 0

;main.c: 667: carregar_senha();
	call	_carregar_senha	;wreg free
	line	669
	
l2783:
;main.c: 669: data_atual.ano=0;
	clrf	((c:_data_atual)),c
	line	670
	
l2785:
;main.c: 670: data_atual.mes=0;
	clrf	(0+((c:_data_atual)+01h)),c
	line	671
	
l2787:
;main.c: 671: data_atual.dia=0;
	clrf	(0+((c:_data_atual)+02h)),c
	line	672
	
l2789:
;main.c: 672: data_atual.dia_da_semana=0;
	clrf	(0+((c:_data_atual)+06h)),c
	line	673
	
l2791:
;main.c: 673: data_atual.hora=0;
	clrf	(0+((c:_data_atual)+03h)),c
	line	674
	
l2793:
;main.c: 674: data_atual.minuto=0;
	clrf	(0+((c:_data_atual)+04h)),c
	line	675
	
l2795:
;main.c: 675: data_atual.segundo=0;
	clrf	(0+((c:_data_atual)+05h)),c
	line	677
	
l2797:
;main.c: 677: ptr_data= &data_atual.ano;
		movlw	low(_data_atual)
	movwf	((c:_ptr_data)),c
	clrf	((c:_ptr_data+1)),c

	line	679
	
l2799:
;main.c: 679: PORTB_SR=PORTB;
	movff	(c:3969),(c:_PORTB_SR)	;volatile
	line	680
	
l2801:
;main.c: 680: RBIE=1;
	bsf	c:(32659/8),(32659)&7	;volatile
	line	681
	
l2803:
;main.c: 681: RBIF=0;
	bcf	c:(32656/8),(32656)&7	;volatile
	line	686
	
l2805:
;main.c: 686: if(enviar==1){
	btfss	(_enviar/8),c,(_enviar)&7
	goto	u3231
	goto	u3230
u3231:
	goto	l363
u3230:
	line	687
	
l2807:
;main.c: 687: enviar=0;
	bcf	(_enviar/8),c,(_enviar)&7
	line	689
	
l2809:
;main.c: 689: TXREG = '\n';
	movlw	low(0Ah)
	movwf	((c:4013)),c	;volatile
	line	690
;main.c: 690: while(!TRMT){}
	
l364:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3241
	goto	u3240
u3241:
	goto	l364
u3240:
	line	691
	
l2811:
;main.c: 691: TXREG = 'I';
	movlw	low(049h)
	movwf	((c:4013)),c	;volatile
	line	692
;main.c: 692: while(!TRMT){}
	
l367:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3251
	goto	u3250
u3251:
	goto	l367
u3250:
	line	694
	
l2813:
;main.c: 694: if(FLAGS_1<4){
		movlw	04h-0
	cpfslt	((c:_FLAGS_1)),c
	goto	u3261
	goto	u3260

u3261:
	goto	l370
u3260:
	line	695
	
l2815:
;main.c: 695: etapa = 0;
	clrf	((c:_etapa)),c
	line	696
	
l2817:
;main.c: 696: TXREG = 'O';
	movlw	low(04Fh)
	movwf	((c:4013)),c	;volatile
	line	697
;main.c: 697: while(!TRMT){}
	
l371:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3271
	goto	u3270
u3271:
	goto	l371
u3270:
	line	698
	
l2819:
;main.c: 698: TXREG = 'K';
	movlw	low(04Bh)
	movwf	((c:4013)),c	;volatile
	line	699
;main.c: 699: while(!TRMT){}
	
l374:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3281
	goto	u3280
u3281:
	goto	l374
u3280:
	line	701
	
l2821:
;main.c: 701: if(funcao == '2'){
		movlw	50
	xorwf	((c:_funcao)),c,w
	btfss	status,2
	goto	u3291
	goto	u3290

u3291:
	goto	l2825
u3290:
	line	702
	
l2823:
;main.c: 702: numero_para_ascii(data_atual.ano);
	movf	((c:_data_atual)),c,w
	
	call	_numero_para_ascii
	line	703
;main.c: 703: numero_para_ascii(data_atual.mes);
	movf	(0+((c:_data_atual)+01h)),c,w
	
	call	_numero_para_ascii
	line	704
;main.c: 704: numero_para_ascii(data_atual.hora);
	movf	(0+((c:_data_atual)+03h)),c,w
	
	call	_numero_para_ascii
	line	705
;main.c: 705: numero_para_ascii(data_atual.minuto);
	movf	(0+((c:_data_atual)+04h)),c,w
	
	call	_numero_para_ascii
	line	706
;main.c: 706: numero_para_ascii(data_atual.segundo);
	movf	(0+((c:_data_atual)+05h)),c,w
	
	call	_numero_para_ascii
	line	707
;main.c: 707: numero_para_ascii(qtd_total_contas);
	movf	((c:_qtd_total_contas)),c,w
	
	call	_numero_para_ascii
	line	708
;main.c: 708: numero_para_ascii(16);
	movlw	(010h)&0ffh
	
	call	_numero_para_ascii
	line	709
;main.c: 709: numero_para_ascii(PORTAbits.RA0);}
	btfsc	((c:3968)),c,0	;volatile
	goto	u3301
	goto	u3300
u3301:
	movlw	1
	goto	u3306
u3300:
	movlw	0
u3306:
	
	call	_numero_para_ascii
	goto	l2889
	line	712
	
l2825:
;main.c: 712: else if(funcao == '7'){
		movlw	55
	xorwf	((c:_funcao)),c,w
	btfss	status,2
	goto	u3311
	goto	u3310

u3311:
	goto	l2841
u3310:
	line	713
	
l2827:
;main.c: 713: char i=0;
	movlb	0	; () banked
	clrf	((main@i))&0ffh
	line	715
	
l2829:; BSR set to: 0

;main.c: 715: senha[i] = nova_senha[i];
	movf	((main@i))&0ffh,w
	addlw	low(_nova_senha)
	movwf	fsr2l
	clrf	fsr2h
	movf	((main@i))&0ffh,w
	addlw	low(_senha)
	movwf	fsr1l
	clrf	fsr1h
	movff	indf2,indf1
	line	716
	
l2831:; BSR set to: 0

;main.c: 716: (Busy_eep(), Write_b_eep(((conta*16) + i),senha[i]));
	call	_Busy_eep	;wreg free
	
l2833:
	movf	((c:_conta)),c,w
	movlb	0	; () banked
	movwf	(??_main+0+0)&0ffh
	clrf	(??_main+0+0+1)&0ffh

	swapf	(??_main+0+0)&0ffh
	swapf	(??_main+0+1)&0ffh
	movlw	0f0h
	andwf	(??_main+0+1)&0ffh
	movf	(??_main+0+0)&0ffh,w
	andlw	0fh
	iorwf	(??_main+0+1)&0ffh
	movlw	0f0h
	andwf	(??_main+0+0)&0ffh
	movf	((main@i))&0ffh,w
	addwf	(??_main+0+0)&0ffh,w
	movwf	((Write_b_eep@badd))&0ffh
	movlw	0
	addwfc	(??_main+0+1)&0ffh,w
	movwf	1+((Write_b_eep@badd))&0ffh
	movf	((main@i))&0ffh,w
	addlw	low(_senha)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	movwf	((Write_b_eep@bdat))&0ffh
	call	_Write_b_eep	;wreg free
	line	717
;main.c: 717: while(WR){}
	
l381:
	btfsc	c:(32049/8),(32049)&7	;volatile
	goto	u3321
	goto	u3320
u3321:
	goto	l381
u3320:
	line	718
	
l2835:
;main.c: 718: i++;} while(nova_senha[i-1] && i<16);
	movlb	0	; () banked
	incf	((main@i))&0ffh
	
l2837:; BSR set to: 0

	movf	((main@i))&0ffh,w
	addlw	low(_nova_senha+0FFh)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	btfsc	status,2
	goto	u3331
	goto	u3330
u3331:
	goto	l378
u3330:
	
l2839:; BSR set to: 0

		movlw	010h-1
	cpfsgt	((main@i))&0ffh
	goto	u3341
	goto	u3340

u3341:
	goto	l2829
u3340:
	goto	l2889
	line	721
	
l2841:
;main.c: 721: else if(funcao == '0'){
		movlw	48
	xorwf	((c:_funcao)),c,w
	btfss	status,2
	goto	u3351
	goto	u3350

u3351:
	goto	l378
u3350:
	goto	l2853
	line	722
;main.c: 723: cont++;
	
l390:
	line	724
;main.c: 724: PORTCbits.RC0=1;
	bsf	((c:3970)),c,0	;volatile
	line	725
	
l2845:
;main.c: 725: delay_ms(325);
	movlw	high(0145h)
	movlb	0	; () banked
	movwf	((delay_ms@delay_total+1))&0ffh
	movlw	low(0145h)
	movwf	((delay_ms@delay_total))&0ffh
	call	_delay_ms	;wreg free
	line	726
	
l2847:; BSR set to: 0

;main.c: 726: PORTCbits.RC0=0;
	bcf	((c:3970)),c,0	;volatile
	line	727
	
l2849:; BSR set to: 0

;main.c: 727: if(PORTAbits.RA0 == 0) delay_ms(100);
	btfsc	((c:3968)),c,0	;volatile
	goto	u3361
	goto	u3360
u3361:
	goto	l2853
u3360:
	
l2851:; BSR set to: 0

	movlw	high(064h)
	movwf	((delay_ms@delay_total+1))&0ffh
	movlw	low(064h)
	movwf	((delay_ms@delay_total))&0ffh
	call	_delay_ms	;wreg free
	line	722
	
l2853:
	btfss	((c:3968)),c,0	;volatile
	goto	u3371
	goto	u3370
u3371:
	goto	l390
u3370:
	goto	l2889
	line	731
	
l378:
;main.c: 728: }
;main.c: 729: }
;main.c: 731: }
	goto	l2889
	line	733
	
l370:
	line	735
;main.c: 733: else{
;main.c: 735: etapa = 0;
	clrf	((c:_etapa)),c
	line	736
;main.c: 736: if((FLAGS_1 & (1<<7))){
	
	btfss	((c:_FLAGS_1)),c,(7)&7
	goto	u3381
	goto	u3380
u3381:
	goto	l2865
u3380:
	line	737
	
l2855:
;main.c: 737: TXREG = 'E';
	movlw	low(045h)
	movwf	((c:4013)),c	;volatile
	line	738
;main.c: 738: while(!TRMT){}
	
l395:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3391
	goto	u3390
u3391:
	goto	l395
u3390:
	line	739
	
l2857:
;main.c: 739: TXREG = 'P';
	movlw	low(050h)
	movwf	((c:4013)),c	;volatile
	line	740
;main.c: 740: while(!TRMT){}
	
l398:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3401
	goto	u3400
u3401:
	goto	l398
u3400:
	line	741
	
l2859:
;main.c: 741: if(funcao == '7'){
		movlw	55
	xorwf	((c:_funcao)),c,w
	btfss	status,2
	goto	u3411
	goto	u3410

u3411:
	goto	l2863
u3410:
	line	742
	
l2861:
;main.c: 742: TXREG = 'S';
	movlw	low(053h)
	movwf	((c:4013)),c	;volatile
	line	743
;main.c: 743: while(!TRMT){}
	
l402:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3421
	goto	u3420
u3421:
	goto	l402
u3420:
	line	746
	
l2863:
;main.c: 744: }
;main.c: 746: (FLAGS_1 &= ~(1<<7));}
	bcf	(0+(7/8)+(c:_FLAGS_1)),c,(7)&7
	line	748
	
l2865:
;main.c: 748: if((FLAGS_1 & (1<<4))){
	
	btfss	((c:_FLAGS_1)),c,(4)&7
	goto	u3431
	goto	u3430
u3431:
	goto	l2873
u3430:
	line	750
	
l2867:
;main.c: 750: TXREG = 'E';
	movlw	low(045h)
	movwf	((c:4013)),c	;volatile
	line	751
;main.c: 751: while(!TRMT){}
	
l406:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3441
	goto	u3440
u3441:
	goto	l406
u3440:
	line	752
	
l2869:
;main.c: 752: TXREG = 'C';
	movlw	low(043h)
	movwf	((c:4013)),c	;volatile
	line	753
;main.c: 753: while(!TRMT){}
	
l409:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3451
	goto	u3450
u3451:
	goto	l409
u3450:
	line	754
	
l2871:
;main.c: 754: (FLAGS_1 &= ~(1<<4));}
	bcf	(0+(4/8)+(c:_FLAGS_1)),c,(4)&7
	line	757
	
l2873:
;main.c: 757: if((FLAGS_1 & (1<<6))){
	
	btfss	((c:_FLAGS_1)),c,(6)&7
	goto	u3461
	goto	u3460
u3461:
	goto	l2881
u3460:
	line	758
	
l2875:
;main.c: 758: TXREG = 'E';
	movlw	low(045h)
	movwf	((c:4013)),c	;volatile
	line	759
;main.c: 759: while(!TRMT){}
	
l413:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3471
	goto	u3470
u3471:
	goto	l413
u3470:
	line	760
	
l2877:
;main.c: 760: TXREG = 'S';
	movlw	low(053h)
	movwf	((c:4013)),c	;volatile
	line	761
;main.c: 761: while(!TRMT){}
	
l416:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3481
	goto	u3480
u3481:
	goto	l416
u3480:
	line	762
	
l2879:
;main.c: 762: (FLAGS_1 &= ~(1<<6));}
	bcf	(0+(6/8)+(c:_FLAGS_1)),c,(6)&7
	line	764
	
l2881:
;main.c: 764: if((FLAGS_1 & (1<<2))){
	
	btfss	((c:_FLAGS_1)),c,(2)&7
	goto	u3491
	goto	u3490
u3491:
	goto	l2889
u3490:
	line	765
	
l2883:
;main.c: 765: TXREG = 'E';
	movlw	low(045h)
	movwf	((c:4013)),c	;volatile
	line	766
;main.c: 766: while(!TRMT){}
	
l420:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3501
	goto	u3500
u3501:
	goto	l420
u3500:
	line	767
	
l2885:
;main.c: 767: TXREG = 'I';
	movlw	low(049h)
	movwf	((c:4013)),c	;volatile
	line	768
;main.c: 768: while(!TRMT){}
	
l423:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3511
	goto	u3510
u3511:
	goto	l423
u3510:
	line	769
	
l2887:
;main.c: 769: (FLAGS_1 &= ~(1<<2));}
	bcf	(0+(2/8)+(c:_FLAGS_1)),c,(2)&7
	line	774
	
l2889:
;main.c: 770: }
;main.c: 774: TXREG='F';
	movlw	low(046h)
	movwf	((c:4013)),c	;volatile
	line	775
;main.c: 775: while(!TRMT){}}
	
l426:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3521
	goto	u3520
u3521:
	goto	l426
u3520:
	goto	l429
	line	780
	
l363:
;main.c: 780: else if(RCIE==0){
	btfsc	c:(31981/8),(31981)&7	;volatile
	goto	u3531
	goto	u3530
u3531:
	goto	l429
u3530:
	line	781
	
l2891:
;main.c: 781: if(etapa == 1){
		decf	((c:_etapa)),c,w
	btfss	status,2
	goto	u3541
	goto	u3540

u3541:
	goto	l429
u3540:
	line	782
	
l2893:
;main.c: 782: carregar_senha();
	call	_carregar_senha	;wreg free
	line	784
	
l2895:
;main.c: 784: if((nivel_acesso & (1<<(funcao - '0')))){
	movff	(c:_funcao),??_main+0+0
	movlw	0D0h
	movlb	0	; () banked
	addwf	(??_main+0+0)&0ffh
	movlw	(01h)&0ffh
	movwf	(??_main+1+0)&0ffh
	incf	(??_main+0+0)&0ffh
	goto	u3554
u3555:
	bcf	status,0
	rlcf	((??_main+1+0))&0ffh
u3554:
	decfsz	(??_main+0+0)&0ffh
	goto	u3555
	movlb	0	; () banked
	movf	((??_main+1+0))&0ffh,w
	andwf	((c:_nivel_acesso)),c,w
	iorlw	0
	btfsc	status,2
	goto	u3561
	goto	u3560
u3561:
	goto	l2901
u3560:
	line	785
	
l2897:; BSR set to: 0

;main.c: 785: TXREG = 'C';
	movlw	low(043h)
	movwf	((c:4013)),c	;volatile
	line	786
;main.c: 786: while(!TRMT){}
	
l433:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3571
	goto	u3570
u3571:
	goto	l433
u3570:
	line	787
	
l2899:
;main.c: 787: (FLAGS_1 |= (1<<0));}
	bsf	(0+(0/8)+(c:_FLAGS_1)),c,(0)&7
	goto	l429
	line	790
	
l2901:; BSR set to: 0

;main.c: 789: else{
;main.c: 790: (FLAGS_1 |= (1<<3));}
	bsf	(0+(3/8)+(c:_FLAGS_1)),c,(3)&7
	line	800
	
l429:
;main.c: 797: }
;main.c: 800: PORTB_SR=PORTB;
	movff	(c:3969),(c:_PORTB_SR)	;volatile
	line	801
	
l2905:
;main.c: 801: if(PORTB_SR == 0xF0 && RBIE==0){
		movlw	240
	xorwf	((c:_PORTB_SR)),c,w
	btfss	status,2
	goto	u3581
	goto	u3580

u3581:
	goto	l2805
u3580:
	
l2907:
	btfsc	c:(32659/8),(32659)&7	;volatile
	goto	u3591
	goto	u3590
u3591:
	goto	l2805
u3590:
	line	802
	
l2909:
;main.c: 802: delay_ms(200);
	movlw	high(0C8h)
	movlb	0	; () banked
	movwf	((delay_ms@delay_total+1))&0ffh
	movlw	low(0C8h)
	movwf	((delay_ms@delay_total))&0ffh
	call	_delay_ms	;wreg free
	line	803
	
l2911:; BSR set to: 0

;main.c: 803: PORTB_SR=PORTB;
	movff	(c:3969),(c:_PORTB_SR)	;volatile
	line	804
	
l2913:; BSR set to: 0

;main.c: 804: RBIE=1;}
	bsf	c:(32659/8),(32659)&7	;volatile
	goto	l2805
	global	start
	goto	start
	opt stack 0
	line	807
GLOBAL	__end_of_main
	__end_of_main:
	signat	_main,90
	global	_verificar_num_contas

;; *************** function _verificar_num_contas *****************
;; Defined at:
;;		line 316 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    2[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       1       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_Read_b_eep
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text1,class=CODE,space=0,reloc=2
	line	316
global __ptext1
__ptext1:
psect	text1
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	316
	global	__size_of_verificar_num_contas
	__size_of_verificar_num_contas	equ	__end_of_verificar_num_contas-_verificar_num_contas
	
_verificar_num_contas:; BSR set to: 0

;incstack = 0
	opt	stack 26
	line	318
	
l2727:
;main.c: 317: char i;
;main.c: 318: for(i=0;i<16;i++){
	movlb	0	; () banked
	clrf	((verificar_num_contas@i))&0ffh
	line	319
	
l2733:; BSR set to: 0

;main.c: 319: if(Read_b_eep(i*16) != 255) qtd_total_contas++;
	movf	((verificar_num_contas@i))&0ffh,w
	mullw	010h
	movff	prodl,(Read_b_eep@badd)
	movff	prodh,(Read_b_eep@badd+1)
	call	_Read_b_eep	;wreg free
	xorlw	0FFh
	btfsc	status,2
	goto	u3161
	goto	u3160
u3161:
	goto	l201
u3160:
	
l2735:
	incf	((c:_qtd_total_contas)),c
	
l201:
	line	318
	movlb	0	; () banked
	incf	((verificar_num_contas@i))&0ffh
	
l2737:; BSR set to: 0

		movlw	010h-1
	cpfsgt	((verificar_num_contas@i))&0ffh
	goto	u3171
	goto	u3170

u3171:
	goto	l2733
u3170:
	line	321
	
l202:; BSR set to: 0

	return	;funcret
	opt stack 0
GLOBAL	__end_of_verificar_num_contas
	__end_of_verificar_num_contas:
	signat	_verificar_num_contas,88
	global	_numero_para_ascii

;; *************** function _numero_para_ascii *****************
;; Defined at:
;;		line 188 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;  numero          1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  numero          1   16[BANK0 ] unsigned char 
;;  temp1           1   17[BANK0 ] unsigned char 
;;  temp2           1   15[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         0       3       0       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0       0
;;      Totals:         0       4       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		___awdiv
;;		___lbdiv
;;		___wmul
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text2,class=CODE,space=0,reloc=2
	line	188
global __ptext2
__ptext2:
psect	text2
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	188
	global	__size_of_numero_para_ascii
	__size_of_numero_para_ascii	equ	__end_of_numero_para_ascii-_numero_para_ascii
	
_numero_para_ascii:; BSR set to: 0

;incstack = 0
	opt	stack 26
;numero_para_ascii@numero stored from wreg
	movlb	0	; () banked
	movwf	((numero_para_ascii@numero))&0ffh
	line	192
	
l2673:; BSR set to: 0

;main.c: 189: char temp1;
;main.c: 190: char temp2;
;main.c: 192: TXREG = '+';
	movlw	low(02Bh)
	movwf	((c:4013)),c	;volatile
	line	193
;main.c: 193: while(!TRMT){}
	
l149:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3101
	goto	u3100
u3101:
	goto	l149
u3100:
	line	195
	
l2675:
;main.c: 195: temp1 = numero/100;
	movlw	low(064h)
	movlb	0	; () banked
	movwf	((___lbdiv@divisor))&0ffh
	movf	((numero_para_ascii@numero))&0ffh,w
	
	call	___lbdiv
	movwf	((numero_para_ascii@temp1))&0ffh
	line	196
	
l2677:; BSR set to: 0

;main.c: 196: TXREG = '0'+ temp1;
	movf	((numero_para_ascii@temp1))&0ffh,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	197
;main.c: 197: while(!TRMT){}
	
l152:; BSR set to: 0

	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3111
	goto	u3110
u3111:
	goto	l152
u3110:
	line	199
	
l2679:; BSR set to: 0

;main.c: 199: temp2 = ((numero - temp1*100)/10);
	movff	(numero_para_ascii@temp1),(___wmul@multiplier)
	clrf	((___wmul@multiplier+1))&0ffh
	movlw	high(-100)
	movwf	((___wmul@multiplicand+1))&0ffh
	movlw	low(-100)
	movwf	((___wmul@multiplicand))&0ffh
	call	___wmul	;wreg free
	movf	((numero_para_ascii@numero))&0ffh,w
	addwf	(0+?___wmul)&0ffh,w
	movwf	((___awdiv@dividend))&0ffh
	movlw	0
	addwfc	(1+?___wmul)&0ffh,w
	movwf	1+((___awdiv@dividend))&0ffh
	movlw	high(0Ah)
	movwf	((___awdiv@divisor+1))&0ffh
	movlw	low(0Ah)
	movwf	((___awdiv@divisor))&0ffh
	call	___awdiv	;wreg free
	movf	(0+?___awdiv)&0ffh,w
	movwf	((numero_para_ascii@temp2))&0ffh
	line	200
	
l2681:; BSR set to: 0

;main.c: 200: TXREG = '0'+ temp2;
	movf	((numero_para_ascii@temp2))&0ffh,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	201
;main.c: 201: while(!TRMT){}
	
l155:; BSR set to: 0

	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3121
	goto	u3120
u3121:
	goto	l155
u3120:
	line	203
	
l2683:; BSR set to: 0

;main.c: 203: TXREG = '0'+ (numero - (temp2*10) - (temp1*100));
	movf	((numero_para_ascii@temp1))&0ffh,w
	mullw	09Ch
	movff	prodl,??_numero_para_ascii+0+0
	movf	((numero_para_ascii@temp2))&0ffh,w
	mullw	0F6h
	movf	(prodl),c,w
	addwf	(??_numero_para_ascii+0+0)&0ffh,w
	addwf	((numero_para_ascii@numero))&0ffh,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	204
;main.c: 204: while(!TRMT){}
	
l158:; BSR set to: 0

	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3131
	goto	u3130
u3131:
	goto	l158
u3130:
	line	206
	
l2685:; BSR set to: 0

;main.c: 206: TXREG = '+';
	movlw	low(02Bh)
	movwf	((c:4013)),c	;volatile
	line	207
;main.c: 207: while(!TRMT){}
	
l161:; BSR set to: 0

	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3141
	goto	u3140
u3141:
	goto	l161
u3140:
	line	208
	
l164:; BSR set to: 0

	return	;funcret
	opt stack 0
GLOBAL	__end_of_numero_para_ascii
	__end_of_numero_para_ascii:
	signat	_numero_para_ascii,4216
	global	___wmul

;; *************** function ___wmul *****************
;; Defined at:
;;		line 15 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\Umul16.c"
;; Parameters:    Size  Location     Type
;;  multiplier      2    0[BANK0 ] unsigned int 
;;  multiplicand    2    2[BANK0 ] unsigned int 
;; Auto vars:     Size  Location     Type
;;  product         2    4[BANK0 ] unsigned int 
;; Return value:  Size  Location     Type
;;                  2    0[BANK0 ] unsigned int 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh
;; Tracked objects:
;;		On entry : F/0
;;		On exit  : F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       4       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       6       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_numero_para_ascii
;; This function uses a non-reentrant model
;;
psect	text3,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\Umul16.c"
	line	15
global __ptext3
__ptext3:
psect	text3
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\Umul16.c"
	line	15
	global	__size_of___wmul
	__size_of___wmul	equ	__end_of___wmul-___wmul
	
___wmul:; BSR set to: 0

;incstack = 0
	opt	stack 26
	line	37
	
l2591:; BSR set to: 0

	movf	((___wmul@multiplier))&0ffh,w
	mulwf	((___wmul@multiplicand))&0ffh
	movff	prodl,(___wmul@product)
	movff	prodh,(___wmul@product+1)
	line	38
	movf	((___wmul@multiplier))&0ffh,w
	mulwf	(0+(___wmul@multiplicand+01h))&0ffh
	movf	(prodl),c,w
	addwf	((___wmul@product+1))&0ffh

	line	39
	movf	(0+(___wmul@multiplier+01h))&0ffh,w
	mulwf	((___wmul@multiplicand))&0ffh
	movf	(prodl),c,w
	addwf	((___wmul@product+1))&0ffh

	line	52
	
l2593:; BSR set to: 0

	movff	(___wmul@product),(?___wmul)
	movff	(___wmul@product+1),(?___wmul+1)
	line	53
	
l480:; BSR set to: 0

	return	;funcret
	opt stack 0
GLOBAL	__end_of___wmul
	__end_of___wmul:
	signat	___wmul,8314
	global	___lbdiv

;; *************** function ___lbdiv *****************
;; Defined at:
;;		line 4 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\lbdiv.c"
;; Parameters:    Size  Location     Type
;;  dividend        1    wreg     unsigned char 
;;  divisor         1    0[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  dividend        1    1[BANK0 ] unsigned char 
;;  quotient        1    3[BANK0 ] unsigned char 
;;  counter         1    2[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : F/0
;;		On exit  : F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       1       0       0       0       0       0       0       0
;;      Locals:         0       3       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       4       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_numero_para_ascii
;; This function uses a non-reentrant model
;;
psect	text4,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\lbdiv.c"
	line	4
global __ptext4
__ptext4:
psect	text4
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\lbdiv.c"
	line	4
	global	__size_of___lbdiv
	__size_of___lbdiv	equ	__end_of___lbdiv-___lbdiv
	
___lbdiv:; BSR set to: 0

;incstack = 0
	opt	stack 26
;___lbdiv@dividend stored from wreg
	movwf	((___lbdiv@dividend))&0ffh
	line	9
	
l2641:; BSR set to: 0

	clrf	((___lbdiv@quotient))&0ffh
	line	10
	
l2643:; BSR set to: 0

	movf	((___lbdiv@divisor))&0ffh,w
	btfsc	status,2
	goto	u3061
	goto	u3060
u3061:
	goto	l2663
u3060:
	line	11
	
l2645:; BSR set to: 0

	movlw	low(01h)
	movwf	((___lbdiv@counter))&0ffh
	line	12
	goto	l2651
	line	13
	
l2647:; BSR set to: 0

	bcf status,0
	rlcf	((___lbdiv@divisor))&0ffh

	line	14
	
l2649:; BSR set to: 0

	incf	((___lbdiv@counter))&0ffh
	line	12
	
l2651:; BSR set to: 0

	
	btfss	((___lbdiv@divisor))&0ffh,(7)&7
	goto	u3071
	goto	u3070
u3071:
	goto	l2647
u3070:
	line	17
	
l2653:; BSR set to: 0

	bcf status,0
	rlcf	((___lbdiv@quotient))&0ffh

	line	18
		movf	((___lbdiv@divisor))&0ffh,w
	subwf	((___lbdiv@dividend))&0ffh,w
	btfss	status,0
	goto	u3081
	goto	u3080

u3081:
	goto	l2659
u3080:
	line	19
	
l2655:; BSR set to: 0

	movf	((___lbdiv@divisor))&0ffh,w
	subwf	((___lbdiv@dividend))&0ffh
	line	20
	
l2657:; BSR set to: 0

	bsf	(0+(0/8)+(___lbdiv@quotient))&0ffh,(0)&7
	line	22
	
l2659:; BSR set to: 0

	bcf status,0
	rrcf	((___lbdiv@divisor))&0ffh

	line	23
	
l2661:; BSR set to: 0

	decfsz	((___lbdiv@counter))&0ffh
	
	goto	l2653
	line	25
	
l2663:; BSR set to: 0

	movf	((___lbdiv@quotient))&0ffh,w
	line	26
	
l916:; BSR set to: 0

	return	;funcret
	opt stack 0
GLOBAL	__end_of___lbdiv
	__end_of___lbdiv:
	signat	___lbdiv,8313
	global	___awdiv

;; *************** function ___awdiv *****************
;; Defined at:
;;		line 8 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\awdiv.c"
;; Parameters:    Size  Location     Type
;;  dividend        2    6[BANK0 ] int 
;;  divisor         2    8[BANK0 ] int 
;; Auto vars:     Size  Location     Type
;;  quotient        2   12[BANK0 ] int 
;;  sign            1   11[BANK0 ] unsigned char 
;;  counter         1   10[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    6[BANK0 ] int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : F/0
;;		On exit  : F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       4       0       0       0       0       0       0       0
;;      Locals:         0       4       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       8       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_numero_para_ascii
;; This function uses a non-reentrant model
;;
psect	text5,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\awdiv.c"
	line	8
global __ptext5
__ptext5:
psect	text5
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\awdiv.c"
	line	8
	global	__size_of___awdiv
	__size_of___awdiv	equ	__end_of___awdiv-___awdiv
	
___awdiv:; BSR set to: 0

;incstack = 0
	opt	stack 26
	line	14
	
l2597:; BSR set to: 0

	clrf	((___awdiv@sign))&0ffh
	line	15
	
l2599:; BSR set to: 0

	btfsc	((___awdiv@divisor+1))&0ffh,7
	goto	u3000
	goto	u3001

u3001:
	goto	l2605
u3000:
	line	16
	
l2601:; BSR set to: 0

	negf	((___awdiv@divisor))&0ffh
	comf	((___awdiv@divisor+1))&0ffh
	btfsc	status,0
	incf	((___awdiv@divisor+1))&0ffh
	line	17
	
l2603:; BSR set to: 0

	movlw	low(01h)
	movwf	((___awdiv@sign))&0ffh
	line	19
	
l2605:; BSR set to: 0

	btfsc	((___awdiv@dividend+1))&0ffh,7
	goto	u3010
	goto	u3011

u3011:
	goto	l2611
u3010:
	line	20
	
l2607:; BSR set to: 0

	negf	((___awdiv@dividend))&0ffh
	comf	((___awdiv@dividend+1))&0ffh
	btfsc	status,0
	incf	((___awdiv@dividend+1))&0ffh
	line	21
	
l2609:; BSR set to: 0

	movlw	(01h)&0ffh
	xorwf	((___awdiv@sign))&0ffh
	line	23
	
l2611:; BSR set to: 0

	clrf	((___awdiv@quotient))&0ffh
	clrf	((___awdiv@quotient+1))&0ffh
	line	24
	
l2613:; BSR set to: 0

	movf	((___awdiv@divisor))&0ffh,w
iorwf	((___awdiv@divisor+1))&0ffh,w
	btfsc	status,2
	goto	u3021
	goto	u3020

u3021:
	goto	l2633
u3020:
	line	25
	
l2615:; BSR set to: 0

	movlw	low(01h)
	movwf	((___awdiv@counter))&0ffh
	line	26
	goto	l2619
	line	27
	
l2617:; BSR set to: 0

	bcf	status,0
	rlcf	((___awdiv@divisor))&0ffh
	rlcf	((___awdiv@divisor+1))&0ffh
	line	28
	incf	((___awdiv@counter))&0ffh
	line	26
	
l2619:; BSR set to: 0

	
	btfss	((___awdiv@divisor+1))&0ffh,(15)&7
	goto	u3031
	goto	u3030
u3031:
	goto	l2617
u3030:
	line	31
	
l2621:; BSR set to: 0

	bcf	status,0
	rlcf	((___awdiv@quotient))&0ffh
	rlcf	((___awdiv@quotient+1))&0ffh
	line	32
	
l2623:; BSR set to: 0

		movf	((___awdiv@divisor))&0ffh,w
	subwf	((___awdiv@dividend))&0ffh,w
	movf	((___awdiv@divisor+1))&0ffh,w
	subwfb	((___awdiv@dividend+1))&0ffh,w
	btfss	status,0
	goto	u3041
	goto	u3040

u3041:
	goto	l2629
u3040:
	line	33
	
l2625:; BSR set to: 0

	movf	((___awdiv@divisor))&0ffh,w
	subwf	((___awdiv@dividend))&0ffh
	movf	((___awdiv@divisor+1))&0ffh,w
	subwfb	((___awdiv@dividend+1))&0ffh

	line	34
	
l2627:; BSR set to: 0

	bsf	(0+(0/8)+(___awdiv@quotient))&0ffh,(0)&7
	line	36
	
l2629:; BSR set to: 0

	bcf	status,0
	rrcf	((___awdiv@divisor+1))&0ffh
	rrcf	((___awdiv@divisor))&0ffh
	line	37
	
l2631:; BSR set to: 0

	decfsz	((___awdiv@counter))&0ffh
	
	goto	l2621
	line	39
	
l2633:; BSR set to: 0

	movf	((___awdiv@sign))&0ffh,w
	btfsc	status,2
	goto	u3051
	goto	u3050
u3051:
	goto	l2637
u3050:
	line	40
	
l2635:; BSR set to: 0

	negf	((___awdiv@quotient))&0ffh
	comf	((___awdiv@quotient+1))&0ffh
	btfsc	status,0
	incf	((___awdiv@quotient+1))&0ffh
	line	41
	
l2637:; BSR set to: 0

	movff	(___awdiv@quotient),(?___awdiv)
	movff	(___awdiv@quotient+1),(?___awdiv+1)
	line	42
	
l673:; BSR set to: 0

	return	;funcret
	opt stack 0
GLOBAL	__end_of___awdiv
	__end_of___awdiv:
	signat	___awdiv,8314
	global	_eeprom_config_inicial

;; *************** function _eeprom_config_inicial *****************
;; Defined at:
;;		line 308 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    4[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       1       0       0       0       0       0       0       0
;;Total ram usage:        1 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_Busy_eep
;;		_Write_b_eep
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text6,class=CODE,space=0,reloc=2
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	308
global __ptext6
__ptext6:
psect	text6
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	308
	global	__size_of_eeprom_config_inicial
	__size_of_eeprom_config_inicial	equ	__end_of_eeprom_config_inicial-_eeprom_config_inicial
	
_eeprom_config_inicial:; BSR set to: 0

;incstack = 0
	opt	stack 26
	line	310
	
l2709:
;main.c: 309: char i;
;main.c: 310: for(i=0;i<10;i++){
	movlb	0	; () banked
	clrf	((eeprom_config_inicial@i))&0ffh
	line	311
	
l2715:; BSR set to: 0

;main.c: 311: (Busy_eep(), Write_b_eep(i,('0'+i)));
	call	_Busy_eep	;wreg free
	
l2717:
	movff	(eeprom_config_inicial@i),(Write_b_eep@badd)
	movlb	0	; () banked
	clrf	((Write_b_eep@badd+1))&0ffh
	movf	((eeprom_config_inicial@i))&0ffh,w
	addlw	low(030h)
	movwf	((Write_b_eep@bdat))&0ffh
	call	_Write_b_eep	;wreg free
	line	310
	
l2719:
	movlb	0	; () banked
	incf	((eeprom_config_inicial@i))&0ffh
	
l2721:; BSR set to: 0

		movlw	0Ah-1
	cpfsgt	((eeprom_config_inicial@i))&0ffh
	goto	u3151
	goto	u3150

u3151:
	goto	l2715
u3150:
	line	313
	
l2723:; BSR set to: 0

;main.c: 312: }
;main.c: 313: (Busy_eep(), Write_b_eep(10,0));}
	call	_Busy_eep	;wreg free
	
l2725:
	movlw	high(0Ah)
	movlb	0	; () banked
	movwf	((Write_b_eep@badd+1))&0ffh
	movlw	low(0Ah)
	movwf	((Write_b_eep@badd))&0ffh
	movlw	low(0)
	movwf	((Write_b_eep@bdat))&0ffh
	call	_Write_b_eep	;wreg free
	
l196:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_eeprom_config_inicial
	__end_of_eeprom_config_inicial:
	signat	_eeprom_config_inicial,88
	global	_Write_b_eep

;; *************** function _Write_b_eep *****************
;; Defined at:
;;		line 30 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\write_B.c"
;; Parameters:    Size  Location     Type
;;  badd            2    0[BANK0 ] unsigned int 
;;  bdat            1    2[BANK0 ] unsigned char 
;; Auto vars:     Size  Location     Type
;;  GIE_BIT_VAL     1    3[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       3       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       4       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_eeprom_config_inicial
;;		_main
;; This function uses a non-reentrant model
;;
psect	text7,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\write_B.c"
	line	30
global __ptext7
__ptext7:
psect	text7
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\write_B.c"
	line	30
	global	__size_of_Write_b_eep
	__size_of_Write_b_eep	equ	__end_of_Write_b_eep-_Write_b_eep
	
_Write_b_eep:
;incstack = 0
	opt	stack 26
	line	32
	
l2573:; BSR set to: 0

	line	33
	movff	(Write_b_eep@badd),(c:4009)	;volatile
	line	34
	movff	(Write_b_eep@bdat),(c:4008)	;volatile
	line	35
	bcf	((c:4006)),c,7	;volatile
	line	36
	bcf	((c:4006)),c,6	;volatile
	line	37
	bsf	((c:4006)),c,2	;volatile
	line	38
	
l2575:; BSR set to: 0

	movlw	0
	btfsc	((c:4082)),c,7	;volatile
	movlw	1
	movwf	((Write_b_eep@GIE_BIT_VAL))&0ffh
	line	39
	
l2577:; BSR set to: 0

	bcf	((c:4082)),c,7	;volatile
	line	40
	
l2579:; BSR set to: 0

	movlw	low(055h)
	movwf	((c:4007)),c	;volatile
	line	41
	
l2581:; BSR set to: 0

	movlw	low(0AAh)
	movwf	((c:4007)),c	;volatile
	line	42
	
l2583:; BSR set to: 0

	bsf	((c:4006)),c,1	;volatile
	line	43
	
l474:; BSR set to: 0

	btfsc	((c:4006)),c,1	;volatile
	goto	u2981
	goto	u2980
u2981:
	goto	l474
u2980:
	
l476:; BSR set to: 0

	line	44
	btfsc	(Write_b_eep@GIE_BIT_VAL)&0ffh,0
	bra	u2995
	bcf	((c:4082)),c,7	;volatile
	bra	u2996
	u2995:
	bsf	((c:4082)),c,7	;volatile
	u2996:

	line	45
	bcf	((c:4006)),c,2	;volatile
	line	46
	
l477:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_Write_b_eep
	__end_of_Write_b_eep:
	signat	_Write_b_eep,8312
	global	_Busy_eep

;; *************** function _Busy_eep *****************
;; Defined at:
;;		line 12 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\busy_eep.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		None
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_eeprom_config_inicial
;;		_main
;; This function uses a non-reentrant model
;;
psect	text8,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\busy_eep.c"
	line	12
global __ptext8
__ptext8:
psect	text8
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\busy_eep.c"
	line	12
	global	__size_of_Busy_eep
	__size_of_Busy_eep	equ	__end_of_Busy_eep-_Busy_eep
	
_Busy_eep:
;incstack = 0
	opt	stack 26
	line	14
	
l2571:
	
l447:
	btfsc	((c:4006)),c,1	;volatile
	goto	u2971
	goto	u2970
u2971:
	goto	l447
u2970:
	line	15
	
l450:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_Busy_eep
	__end_of_Busy_eep:
	signat	_Busy_eep,88
	global	_delay_ms

;; *************** function _delay_ms *****************
;; Defined at:
;;		line 181 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;  delay_total     2    0[BANK0 ] unsigned int 
;; Auto vars:     Size  Location     Type
;;  temp            2    3[BANK0 ] unsigned int 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : F/0
;;		On exit  : F/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       2       0       0       0       0       0       0       0
;;      Locals:         0       2       0       0       0       0       0       0       0
;;      Temps:          0       1       0       0       0       0       0       0       0
;;      Totals:         0       5       0       0       0       0       0       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text9,class=CODE,space=0,reloc=2
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	181
global __ptext9
__ptext9:
psect	text9
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	181
	global	__size_of_delay_ms
	__size_of_delay_ms	equ	__end_of_delay_ms-_delay_ms
	
_delay_ms:
;incstack = 0
	opt	stack 27
	line	182
	
l2667:; BSR set to: 0

;main.c: 182: unsigned int temp = 0;
	clrf	((delay_ms@temp))&0ffh
	clrf	((delay_ms@temp+1))&0ffh
	line	183
;main.c: 183: while(temp < delay_total){
	goto	l143
	line	184
	
l2669:; BSR set to: 0

;main.c: 184: _delay((unsigned long)((1)*(8000000/4000.0)));
	movlw	3
movwf	(??_delay_ms+0+0)&0ffh,f
	movlw	152
u3607:
decfsz	wreg,f
	goto	u3607
	decfsz	(??_delay_ms+0+0)&0ffh,f
	goto	u3607

	line	185
	
l2671:
;main.c: 185: temp++;
	movlb	0	; () banked
	infsnz	((delay_ms@temp))&0ffh
	incf	((delay_ms@temp+1))&0ffh
	line	186
	
l143:; BSR set to: 0

	line	183
		movf	((delay_ms@delay_total))&0ffh,w
	subwf	((delay_ms@temp))&0ffh,w
	movf	((delay_ms@delay_total+1))&0ffh,w
	subwfb	((delay_ms@temp+1))&0ffh,w
	btfss	status,0
	goto	u3091
	goto	u3090

u3091:
	goto	l2669
u3090:
	line	186
	
l146:; BSR set to: 0

	return	;funcret
	opt stack 0
GLOBAL	__end_of_delay_ms
	__end_of_delay_ms:
	signat	_delay_ms,4216
	global	_config_serial

;; *************** function _config_serial *****************
;; Defined at:
;;		line 292 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       0       0       0       0       0       0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text10,class=CODE,space=0,reloc=2
	line	292
global __ptext10
__ptext10:
psect	text10
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	292
	global	__size_of_config_serial
	__size_of_config_serial	equ	__end_of_config_serial-_config_serial
	
_config_serial:; BSR set to: 0

;incstack = 0
	opt	stack 27
	line	293
	
l2687:
;main.c: 293: SYNC=0;
	bcf	c:(32100/8),(32100)&7	;volatile
	line	294
;main.c: 294: BRGH=1;
	bsf	c:(32098/8),(32098)&7	;volatile
	line	295
;main.c: 295: BRG16=1;
	bsf	c:(32195/8),(32195)&7	;volatile
	line	296
	
l2689:
;main.c: 296: SPBRG=16;
	movlw	low(010h)
	movwf	((c:4015)),c	;volatile
	line	297
	
l2691:
;main.c: 297: TX9=0;
	bcf	c:(32102/8),(32102)&7	;volatile
	line	298
	
l2693:
;main.c: 298: RX9=0;
	bcf	c:(32094/8),(32094)&7	;volatile
	line	299
	
l2695:
;main.c: 299: TXEN=1;
	bsf	c:(32101/8),(32101)&7	;volatile
	line	300
	
l2697:
;main.c: 300: RCIE=1;
	bsf	c:(31981/8),(31981)&7	;volatile
	line	301
	
l2699:
;main.c: 301: CREN=1;
	bsf	c:(32092/8),(32092)&7	;volatile
	line	302
	
l2701:
;main.c: 302: SPEN=1;
	bsf	c:(32095/8),(32095)&7	;volatile
	line	303
	
l2703:
;main.c: 303: TXCKP = 0;
	bcf	c:(32196/8),(32196)&7	;volatile
	line	304
	
l2705:
;main.c: 304: TXIE = 0;
	bcf	c:(31980/8),(31980)&7	;volatile
	line	305
	
l2707:
;main.c: 305: TX9 = 0;
	bcf	c:(32102/8),(32102)&7	;volatile
	line	306
	
l191:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_config_serial
	__end_of_config_serial:
	signat	_config_serial,88
	global	_carregar_senha

;; *************** function _carregar_senha *****************
;; Defined at:
;;		line 324 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  i               1    4[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         0       1       0       0       0       0       0       0       0
;;      Temps:          0       2       0       0       0       0       0       0       0
;;      Totals:         0       3       0       0       0       0       0       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_Read_b_eep
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text11,class=CODE,space=0,reloc=2
	line	324
global __ptext11
__ptext11:
psect	text11
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	324
	global	__size_of_carregar_senha
	__size_of_carregar_senha	equ	__end_of_carregar_senha-_carregar_senha
	
_carregar_senha:
;incstack = 0
	opt	stack 26
	line	325
	
l2739:
;main.c: 325: TXREG = '\n';
	movlw	low(0Ah)
	movwf	((c:4013)),c	;volatile
	line	326
;main.c: 326: while(!TRMT);
	
l205:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3181
	goto	u3180
u3181:
	goto	l205
u3180:
	
l207:
	line	327
;main.c: 327: char i = 0;
	movlb	0	; () banked
	clrf	((carregar_senha@i))&0ffh
	line	330
	
l2741:; BSR set to: 0

;main.c: 330: senha[i] = Read_b_eep((conta*16) + i);
	movf	((carregar_senha@i))&0ffh,w
	addlw	low(_senha)
	movwf	fsr2l
	clrf	fsr2h
	movf	((c:_conta)),c,w
	movwf	(??_carregar_senha+0+0)&0ffh
	clrf	(??_carregar_senha+0+0+1)&0ffh

	swapf	(??_carregar_senha+0+0)&0ffh
	swapf	(??_carregar_senha+0+1)&0ffh
	movlw	0f0h
	andwf	(??_carregar_senha+0+1)&0ffh
	movf	(??_carregar_senha+0+0)&0ffh,w
	andlw	0fh
	iorwf	(??_carregar_senha+0+1)&0ffh
	movlw	0f0h
	andwf	(??_carregar_senha+0+0)&0ffh
	movf	((carregar_senha@i))&0ffh,w
	addwf	(??_carregar_senha+0+0)&0ffh,w
	movwf	((Read_b_eep@badd))&0ffh
	movlw	0
	addwfc	(??_carregar_senha+0+1)&0ffh,w
	movwf	1+((Read_b_eep@badd))&0ffh
	call	_Read_b_eep	;wreg free
	movwf	indf2,c

	line	331
	
l2743:
;main.c: 331: TXREG= senha[i];
	movlb	0	; () banked
	movf	((carregar_senha@i))&0ffh,w
	addlw	low(_senha)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	movwf	((c:4013)),c	;volatile
	line	332
;main.c: 332: while(!TRMT);
	
l209:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	u3191
	goto	u3190
u3191:
	goto	l209
u3190:
	line	333
	
l2745:
;main.c: 333: i++;} while( senha[i-1] && i<(16-1));
	movlb	0	; () banked
	incf	((carregar_senha@i))&0ffh
	
l2747:; BSR set to: 0

	movf	((carregar_senha@i))&0ffh,w
	addlw	low(_senha+0FFh)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	btfsc	status,2
	goto	u3201
	goto	u3200
u3201:
	goto	l2751
u3200:
	
l2749:; BSR set to: 0

		movlw	0Fh-1
	cpfsgt	((carregar_senha@i))&0ffh
	goto	u3211
	goto	u3210

u3211:
	goto	l2741
u3210:
	line	335
	
l2751:; BSR set to: 0

;main.c: 335: nivel_acesso = Read_b_eep((conta*16)+ (16-1));
	movf	((c:_conta)),c,w
	movwf	(??_carregar_senha+0+0)&0ffh
	clrf	(??_carregar_senha+0+0+1)&0ffh

	swapf	(??_carregar_senha+0+0)&0ffh
	swapf	(??_carregar_senha+0+1)&0ffh
	movlw	0f0h
	andwf	(??_carregar_senha+0+1)&0ffh
	movf	(??_carregar_senha+0+0)&0ffh,w
	andlw	0fh
	iorwf	(??_carregar_senha+0+1)&0ffh
	movlw	0f0h
	andwf	(??_carregar_senha+0+0)&0ffh
	movlw	low(0Fh)
	addwf	(??_carregar_senha+0+0)&0ffh,w
	movwf	((Read_b_eep@badd))&0ffh
	movlw	high(0Fh)
	addwfc	(??_carregar_senha+0+1)&0ffh,w
	movwf	1+((Read_b_eep@badd))&0ffh
	call	_Read_b_eep	;wreg free
	movwf	((c:_nivel_acesso)),c
	line	336
	
l2753:
;main.c: 336: ultima_conta=conta;
	movff	(c:_conta),(c:_ultima_conta)
	line	337
	
l2755:
;main.c: 337: RCIE=1;}
	bsf	c:(31981/8),(31981)&7	;volatile
	
l215:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_carregar_senha
	__end_of_carregar_senha:
	signat	_carregar_senha,88
	global	_Read_b_eep

;; *************** function _Read_b_eep *****************
;; Defined at:
;;		line 23 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\read_B.c"
;; Parameters:    Size  Location     Type
;;  badd            2    0[BANK0 ] unsigned int 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : F/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       2       0       0       0       0       0       0       0
;;      Locals:         0       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         0       2       0       0       0       0       0       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_verificar_num_contas
;;		_carregar_senha
;;		_main
;; This function uses a non-reentrant model
;;
psect	text12,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\read_B.c"
	line	23
global __ptext12
__ptext12:
psect	text12
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\pic18\plib\EEP\read_B.c"
	line	23
	global	__size_of_Read_b_eep
	__size_of_Read_b_eep	equ	__end_of_Read_b_eep-_Read_b_eep
	
_Read_b_eep:
;incstack = 0
	opt	stack 26
	line	25
	
l2585:; BSR set to: 0

	movff	(Read_b_eep@badd),(c:4009)	;volatile
	line	26
	bcf	((c:4006)),c,6	;volatile
	line	27
	bcf	((c:4006)),c,7	;volatile
	line	28
	bsf	((c:4006)),c,0	;volatile
	line	29
	opt	asmopt_off
	nop
	opt	asmopt_on
	line	30
	opt	asmopt_off
	nop
	opt	asmopt_on
	line	31
	
l2587:
	movf	((c:4008)),c,w	;volatile
	line	32
	
l461:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_Read_b_eep
	__end_of_Read_b_eep:
	signat	_Read_b_eep,4217
	global	_aux

;; *************** function _aux *****************
;; Defined at:
;;		line 340 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;  temp            1   26[COMRAM] unsigned char 
;;  conta_a_ser_    1   27[COMRAM] unsigned char 
;;  linha           1   29[COMRAM] unsigned char 
;;  coluna          1   28[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr2l, fsr2h, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0
;;      Temps:          8       0       0       0       0       0       0       0       0
;;      Totals:        12       0       0       0       0       0       0       0       0
;;Total ram usage:       12 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_ascii_para_numero
;;		_teclado_matricial
;;		i2_numero_para_ascii
;; This function is called by:
;;		Interrupt level 2
;; This function uses a non-reentrant model
;;
psect	intcode,class=CODE,space=0,reloc=2
global __pintcode
__pintcode:
psect	intcode
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	340
	global	__size_of_aux
	__size_of_aux	equ	__end_of_aux-_aux
	
_aux:
;incstack = 0
	opt	stack 26
	movff	fsr2l+0,??_aux+4
	movff	fsr2h+0,??_aux+5
	movff	prodl+0,??_aux+6
	global	int_func
	call	int_func,f	;refresh shadow registers
psect	intcode_body,class=CODE,space=0,reloc=2
global __pintcode_body
__pintcode_body:
int_func:

	pop	; remove dummy address from shadow register refresh
	movff	prodh+0,??_aux+7
	line	342
	
i2l2149:
;main.c: 342: if(TMR1IE && TMR1IF){
	btfss	c:(31976/8),(31976)&7	;volatile
	goto	i2u188_41
	goto	i2u188_40
i2u188_41:
	goto	i2l218
i2u188_40:
	
i2l2151:
	btfss	c:(31984/8),(31984)&7	;volatile
	goto	i2u189_41
	goto	i2u189_40
i2u189_41:
	goto	i2l218
i2u189_40:
	line	343
	
i2l2153:
;main.c: 343: TMR1H=128;
	movlw	low(080h)
	movwf	((c:4047)),c	;volatile
	line	344
	
i2l2155:
;main.c: 344: if(++data_atual.segundo>59){
	incf	(0+((c:_data_atual)+05h)),c
		movlw	03Ch-1
	cpfsgt	(0+((c:_data_atual)+05h)),c
	goto	i2u190_41
	goto	i2u190_40

i2u190_41:
	goto	i2l219
i2u190_40:
	line	345
	
i2l2157:
;main.c: 345: data_atual.segundo=0;
	clrf	(0+((c:_data_atual)+05h)),c
	line	347
	
i2l2159:
;main.c: 347: if(++data_atual.minuto>59){
	incf	(0+((c:_data_atual)+04h)),c
		movlw	03Ch-1
	cpfsgt	(0+((c:_data_atual)+04h)),c
	goto	i2u191_41
	goto	i2u191_40

i2u191_41:
	goto	i2l219
i2u191_40:
	line	350
	
i2l2161:
;main.c: 350: data_atual.minuto=0;
	clrf	(0+((c:_data_atual)+04h)),c
	line	352
	
i2l2163:
;main.c: 352: if(++data_atual.hora>23){
	incf	(0+((c:_data_atual)+03h)),c
		movlw	018h-1
	cpfsgt	(0+((c:_data_atual)+03h)),c
	goto	i2u192_41
	goto	i2u192_40

i2u192_41:
	goto	i2l219
i2u192_40:
	line	354
	
i2l2165:
;main.c: 354: data_atual.hora=0;
	clrf	(0+((c:_data_atual)+03h)),c
	line	355
	
i2l2167:
;main.c: 355: if(++data_atual.dia_da_semana > 6) data_atual.dia_da_semana = 1;
	incf	(0+((c:_data_atual)+06h)),c
		movlw	07h-1
	cpfsgt	(0+((c:_data_atual)+06h)),c
	goto	i2u193_41
	goto	i2u193_40

i2u193_41:
	goto	i2l2171
i2u193_40:
	
i2l2169:
	movlw	low(01h)
	movwf	(0+((c:_data_atual)+06h)),c
	line	357
	
i2l2171:
;main.c: 357: if(++data_atual.dia > qtd_max_dias) {
	incf	(0+((c:_data_atual)+02h)),c
		movf	(0+((c:_data_atual)+02h)),c,w
	subwf	((c:_qtd_max_dias)),c,w
	btfsc	status,0
	goto	i2u194_41
	goto	i2u194_40

i2u194_41:
	goto	i2l219
i2u194_40:
	line	358
	
i2l2173:
;main.c: 358: data_atual.dia=0;
	clrf	(0+((c:_data_atual)+02h)),c
	line	360
;main.c: 360: switch(++data_atual.mes){
	goto	i2l2189
	line	364
	
i2l228:
	line	368
	
i2l2175:
;main.c: 362: case 2:
;main.c: 363: case 4:
;main.c: 364: case 6:
;main.c: 365: case 7:
;main.c: 366: case 9:
;main.c: 367: case 11:
;main.c: 368: qtd_max_dias=31;
	movlw	low(01Fh)
	movwf	((c:_qtd_max_dias)),c
	line	369
;main.c: 369: break;
	goto	i2l219
	line	372
	
i2l2177:
;main.c: 372: if(!((data_atual.ano+3)%4)) qtd_max_dias=29;
	movff	(c:_data_atual),??_aux+0+0
	movlw	03h
	addwf	(??_aux+0+0),c
	movlw	03h
	andwf	(??_aux+0+0),c
	btfss	status,2
	goto	i2u195_41
	goto	i2u195_40
i2u195_41:
	goto	i2l2181
i2u195_40:
	
i2l2179:
	movlw	low(01Dh)
	movwf	((c:_qtd_max_dias)),c
	goto	i2l219
	line	373
	
i2l2181:
;main.c: 373: else qtd_max_dias=28;
	movlw	low(01Ch)
	movwf	((c:_qtd_max_dias)),c
	goto	i2l219
	line	378
	
i2l238:
	line	380
	
i2l2183:
;main.c: 377: case 5:
;main.c: 378: case 8:
;main.c: 379: case 10:
;main.c: 380: qtd_max_dias=30;
	movlw	low(01Eh)
	movwf	((c:_qtd_max_dias)),c
	line	381
;main.c: 381: break;
	goto	i2l219
	line	384
	
i2l2185:
;main.c: 384: data_atual.ano++;
	incf	((c:_data_atual)),c
	line	385
;main.c: 385: break;}
	goto	i2l219
	line	360
	
i2l2189:
	incf	(0+((c:_data_atual)+01h)),c
	movf	(0+((c:_data_atual)+01h)),c,w
	; Switch size 1, requested type "space"
; Number of cases is 12, Range of values is 0 to 11
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           37    19 (average)
;	Chosen strategy is simple_byte

	xorlw	0^0	; case 0
	skipnz
	goto	i2l228
	xorlw	1^0	; case 1
	skipnz
	goto	i2l2177
	xorlw	2^1	; case 2
	skipnz
	goto	i2l2175
	xorlw	3^2	; case 3
	skipnz
	goto	i2l238
	xorlw	4^3	; case 4
	skipnz
	goto	i2l2175
	xorlw	5^4	; case 5
	skipnz
	goto	i2l2183
	xorlw	6^5	; case 6
	skipnz
	goto	i2l2175
	xorlw	7^6	; case 7
	skipnz
	goto	i2l2175
	xorlw	8^7	; case 8
	skipnz
	goto	i2l2183
	xorlw	9^8	; case 9
	skipnz
	goto	i2l2175
	xorlw	10^9	; case 10
	skipnz
	goto	i2l2183
	xorlw	11^10	; case 11
	skipnz
	goto	i2l2175
	goto	i2l2185

	line	390
	
i2l219:
	line	392
;main.c: 386: }
;main.c: 388: }
;main.c: 389: }
;main.c: 390: }
;main.c: 392: TMR1IF=0;}
	bcf	c:(31984/8),(31984)&7	;volatile
	
i2l218:
	line	394
;main.c: 394: if(RBIE && RBIF){
	btfss	c:(32659/8),(32659)&7	;volatile
	goto	i2u196_41
	goto	i2u196_40
i2u196_41:
	goto	i2l2247
i2u196_40:
	
i2l2191:
	btfss	c:(32656/8),(32656)&7	;volatile
	goto	i2u197_41
	goto	i2u197_40
i2u197_41:
	goto	i2l2247
i2u197_40:
	line	395
	
i2l2193:
	line	396
;main.c: 396: char linha=0;
	clrf	((c:aux@linha)),c
	line	397
;main.c: 397: PORTB_SR=PORTB;
	movff	(c:3969),(c:_PORTB_SR)	;volatile
	line	398
;main.c: 398: RBIF=0;
	bcf	c:(32656/8),(32656)&7	;volatile
	line	399
;main.c: 399: RBIE=0;
	bcf	c:(32659/8),(32659)&7	;volatile
	line	400
	
i2l2195:
;main.c: 400: if(PORTB_SR != 0xF0) {
		movlw	240
	xorwf	((c:_PORTB_SR)),c,w
	btfsc	status,2
	goto	i2u198_41
	goto	i2u198_40

i2u198_41:
	goto	i2l2245
i2u198_40:
	line	402
	
i2l2197:
;main.c: 402: if(RCIE){
	btfss	c:(31981/8),(31981)&7	;volatile
	goto	i2u199_41
	goto	i2u199_40
i2u199_41:
	goto	i2l2201
i2u199_40:
	line	403
	
i2l2199:
;main.c: 403: RCIE=0;
	bcf	c:(31981/8),(31981)&7	;volatile
	line	404
;main.c: 404: etapa = 0;
	clrf	((c:_etapa)),c
	line	405
;main.c: 405: ordem=0;}
	clrf	((c:_ordem)),c
	line	407
	
i2l2201:
;main.c: 407: LATDbits.LD0^=1;
	btg	((c:3980)),c,0	;volatile
	line	409
	
i2l2203:
;main.c: 409: if(PORTBbits.RB4==0){linha=1; LATBbits.LB4=0;}
	btfsc	((c:3969)),c,4	;volatile
	goto	i2u200_41
	goto	i2u200_40
i2u200_41:
	goto	i2l244
i2u200_40:
	
i2l2205:
	movlw	low(01h)
	movwf	((c:aux@linha)),c
	
i2l2207:
	bcf	((c:3978)),c,4	;volatile
	goto	i2l245
	line	411
	
i2l244:
;main.c: 411: else if(PORTBbits.RB5==0){linha=2;LATBbits.LB5=0;}
	btfsc	((c:3969)),c,5	;volatile
	goto	i2u201_41
	goto	i2u201_40
i2u201_41:
	goto	i2l246
i2u201_40:
	
i2l2209:
	movlw	low(02h)
	movwf	((c:aux@linha)),c
	
i2l2211:
	bcf	((c:3978)),c,5	;volatile
	goto	i2l245
	line	413
	
i2l246:
;main.c: 413: else if(PORTBbits.RB6==0){linha=3;LATBbits.LB6=0;}
	btfsc	((c:3969)),c,6	;volatile
	goto	i2u202_41
	goto	i2u202_40
i2u202_41:
	goto	i2l2217
i2u202_40:
	
i2l2213:
	movlw	low(03h)
	movwf	((c:aux@linha)),c
	
i2l2215:
	bcf	((c:3978)),c,6	;volatile
	goto	i2l245
	line	415
	
i2l2217:
;main.c: 415: else {linha=4;LATBbits.LB7=0;}
	movlw	low(04h)
	movwf	((c:aux@linha)),c
	
i2l2219:
	bcf	((c:3978)),c,7	;volatile
	
i2l245:
	line	417
;main.c: 417: TRISB=0x0F;
	movlw	low(0Fh)
	movwf	((c:3987)),c	;volatile
	line	419
	
i2l2221:
;main.c: 419: if(PORTBbits.RB0==0){coluna=1;}
	btfsc	((c:3969)),c,0	;volatile
	goto	i2u203_41
	goto	i2u203_40
i2u203_41:
	goto	i2l250
i2u203_40:
	
i2l2223:
	movlw	low(01h)
	movwf	((c:aux@coluna)),c
	goto	i2l2231
	line	421
	
i2l250:
;main.c: 421: else if(PORTBbits.RB1==0){coluna=2;}
	btfsc	((c:3969)),c,1	;volatile
	goto	i2u204_41
	goto	i2u204_40
i2u204_41:
	goto	i2l252
i2u204_40:
	
i2l2225:
	movlw	low(02h)
	movwf	((c:aux@coluna)),c
	goto	i2l2231
	line	423
	
i2l252:
;main.c: 423: else if(PORTBbits.RB2==0){coluna=3;}
	btfsc	((c:3969)),c,2	;volatile
	goto	i2u205_41
	goto	i2u205_40
i2u205_41:
	goto	i2l2229
i2u205_40:
	
i2l2227:
	movlw	low(03h)
	movwf	((c:aux@coluna)),c
	goto	i2l2231
	line	425
	
i2l2229:
;main.c: 425: else {coluna=4;}
	movlw	low(04h)
	movwf	((c:aux@coluna)),c
	line	428
	
i2l2231:
;main.c: 428: caractere_recebido = teclado_matricial(coluna,linha);
	movff	(c:aux@linha),(c:teclado_matricial@linha)
	movf	((c:aux@coluna)),c,w
	
	call	_teclado_matricial
	movwf	((c:_caractere_recebido)),c
	line	429
	
i2l2233:
;main.c: 429: TXREG = caractere_recebido;
	movff	(c:_caractere_recebido),(c:4013)	;volatile
	line	432
	
i2l2235:
;main.c: 432: LATB=0x00;
	clrf	((c:3978)),c	;volatile
	line	433
	
i2l2237:
;main.c: 433: TRISB=0xF0;
	movlw	low(0F0h)
	movwf	((c:3987)),c	;volatile
	line	436
	
i2l2239:
;main.c: 436: TXREG = '\n';
	movlw	low(0Ah)
	movwf	((c:4013)),c	;volatile
	line	437
	
i2l2241:
;main.c: 437: numero_para_ascii(linha);
	movf	((c:aux@linha)),c,w
	
	call	i2_numero_para_ascii
	line	438
	
i2l2243:
;main.c: 438: numero_para_ascii(coluna);
	movf	((c:aux@coluna)),c,w
	
	call	i2_numero_para_ascii
	line	441
	
i2l2245:
;main.c: 439: }
;main.c: 441: PORTB_SR=PORTB;}
	movff	(c:3969),(c:_PORTB_SR)	;volatile
	line	443
	
i2l2247:
;main.c: 443: if(RCIE && RCIF){
	btfss	c:(31981/8),(31981)&7	;volatile
	goto	i2u206_41
	goto	i2u206_40
i2u206_41:
	goto	i2l358
i2u206_40:
	
i2l2249:
	btfss	c:(31989/8),(31989)&7	;volatile
	goto	i2u207_41
	goto	i2u207_40
i2u207_41:
	goto	i2l358
i2u207_40:
	line	445
	
i2l2251:
;main.c: 445: if(OERR==1){
	btfss	c:(32089/8),(32089)&7	;volatile
	goto	i2u208_41
	goto	i2u208_40
i2u208_41:
	goto	i2l257
i2u208_40:
	line	446
	
i2l2253:
;main.c: 446: (FLAGS_1 |= (1<<4));
	bsf	(0+(4/8)+(c:_FLAGS_1)),c,(4)&7
	line	447
	
i2l2255:
;main.c: 447: TXREG = 'O';
	movlw	low(04Fh)
	movwf	((c:4013)),c	;volatile
	line	448
;main.c: 448: while(!TRMT){}
	
i2l258:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u209_41
	goto	i2u209_40
i2u209_41:
	goto	i2l258
i2u209_40:
	
i2l260:
	line	449
;main.c: 449: CREN=0;
	bcf	c:(32092/8),(32092)&7	;volatile
	line	450
;main.c: 450: CREN=1;
	bsf	c:(32092/8),(32092)&7	;volatile
	line	452
;main.c: 452: }
	goto	i2l261
	line	454
	
i2l257:
;main.c: 454: else if(FERR==1){
	btfss	c:(32090/8),(32090)&7	;volatile
	goto	i2u210_41
	goto	i2u210_40
i2u210_41:
	goto	i2l262
i2u210_40:
	line	455
	
i2l2257:
;main.c: 455: (FLAGS_1 |= (1<<4));
	bsf	(0+(4/8)+(c:_FLAGS_1)),c,(4)&7
	line	456
	
i2l2259:
;main.c: 456: SPEN=0;
	bcf	c:(32095/8),(32095)&7	;volatile
	line	457
	
i2l2261:
;main.c: 457: SPEN=1;
	bsf	c:(32095/8),(32095)&7	;volatile
	line	458
	
i2l2263:
;main.c: 458: if(RCREG){}
	movf	((c:4014)),c,w	;volatile
	line	459
	
i2l2265:
;main.c: 459: TXREG = 'F';
	movlw	low(046h)
	movwf	((c:4013)),c	;volatile
	line	460
;main.c: 460: while(!TRMT){}}
	
i2l264:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u211_41
	goto	i2u211_40
i2u211_41:
	goto	i2l264
i2u211_40:
	goto	i2l261
	line	462
	
i2l262:
	line	463
;main.c: 462: else{
;main.c: 463: dado_recebido = RCREG;
	movff	(c:4014),(c:_dado_recebido)	;volatile
	line	465
;main.c: 465: TXREG = dado_recebido;
	movff	(c:_dado_recebido),(c:4013)	;volatile
	line	466
;main.c: 466: while(!TRMT){}
	
i2l268:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u212_41
	goto	i2u212_40
i2u212_41:
	goto	i2l268
i2u212_40:
	line	467
	
i2l2267:
;main.c: 467: TXREG = ('0' + etapa);
	movf	((c:_etapa)),c,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	468
;main.c: 468: while(!TRMT){}
	
i2l271:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u213_41
	goto	i2u213_40
i2u213_41:
	goto	i2l271
i2u213_40:
	line	469
	
i2l2269:
;main.c: 469: TXREG = ('0' + ordem);
	movf	((c:_ordem)),c,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	470
;main.c: 470: while(!TRMT){}
	
i2l274:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u214_41
	goto	i2u214_40
i2u214_41:
	goto	i2l274
i2u214_40:
	line	471
	
i2l2271:
;main.c: 471: TXREG = ('0' + (FLAGS_1 & (1<<0)));
	movf	((c:_FLAGS_1)),c,w
	andlw	low(01h)
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	472
;main.c: 472: if(etapa ==3) { TXREG=funcao;while(!TRMT){}}
		movlw	3
	xorwf	((c:_etapa)),c,w
	btfss	status,2
	goto	i2u215_41
	goto	i2u215_40

i2u215_41:
	goto	i2l281
i2u215_40:
	
i2l2273:
	movff	(c:_funcao),(c:4013)	;volatile
	
i2l278:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u216_41
	goto	i2u216_40
i2u216_41:
	goto	i2l278
i2u216_40:
	line	473
	
i2l281:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u217_41
	goto	i2u217_40
i2u217_41:
	goto	i2l281
i2u217_40:
	
i2l283:
	line	477
;main.c: 477: if((FLAGS_1 & (1<<0))){
	
	btfss	((c:_FLAGS_1)),c,(0)&7
	goto	i2u218_41
	goto	i2u218_40
i2u218_41:
	goto	i2l2285
i2u218_40:
	line	478
	
i2l2275:
;main.c: 478: TXREG = ('X');
	movlw	low(058h)
	movwf	((c:4013)),c	;volatile
	line	479
;main.c: 479: while(!TRMT){}
	
i2l285:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u219_41
	goto	i2u219_40
i2u219_41:
	goto	i2l285
i2u219_40:
	line	481
	
i2l2277:
;main.c: 481: if(dado_recebido != '>') {
		movlw	62
	xorwf	((c:_dado_recebido)),c,w
	btfsc	status,2
	goto	i2u220_41
	goto	i2u220_40

i2u220_41:
	goto	i2l288
i2u220_40:
	line	482
	
i2l289:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u221_41
	goto	i2u221_40
i2u221_41:
	goto	i2l289
i2u221_40:
	line	483
	
i2l2281:
;main.c: 483: (FLAGS_1 |= (1<<7));}
	bsf	(0+(7/8)+(c:_FLAGS_1)),c,(7)&7
	
i2l288:
	line	485
;main.c: 485: (FLAGS_1 &= ~(1<<0));
	bcf	(0+(0/8)+(c:_FLAGS_1)),c,(0)&7
	line	486
	
i2l2283:
;main.c: 486: ordem=0;
	clrf	((c:_ordem)),c
	line	487
;main.c: 487: etapa++;}
	incf	((c:_etapa)),c
	goto	i2l2407
	line	489
	
i2l2285:
;main.c: 489: else if(etapa == 0){
	movf	((c:_etapa)),c,w
	btfss	status,2
	goto	i2u222_41
	goto	i2u222_40
i2u222_41:
	goto	i2l2291
i2u222_40:
	line	492
	
i2l2287:
;main.c: 492: if(dado_recebido != 'I') {(FLAGS_1 |= (1<<7));}
		movlw	73
	xorwf	((c:_dado_recebido)),c,w
	btfsc	status,2
	goto	i2u223_41
	goto	i2u223_40

i2u223_41:
	goto	i2l294
i2u223_40:
	
i2l2289:
	bsf	(0+(7/8)+(c:_FLAGS_1)),c,(7)&7
	
i2l294:
	line	494
;main.c: 494: (FLAGS_1 |= (1<<0));
	bsf	(0+(0/8)+(c:_FLAGS_1)),c,(0)&7
	line	495
;main.c: 495: }
	goto	i2l2407
	line	497
	
i2l2291:
;main.c: 497: else if(etapa == 1){
		decf	((c:_etapa)),c,w
	btfss	status,2
	goto	i2u224_41
	goto	i2u224_40

i2u224_41:
	goto	i2l2313
i2u224_40:
	line	498
	
i2l2293:
;main.c: 498: if(ordem==0){
	movf	((c:_ordem)),c,w
	btfss	status,2
	goto	i2u225_41
	goto	i2u225_40
i2u225_41:
	goto	i2l2303
i2u225_40:
	line	499
	
i2l2295:
;main.c: 499: funcao = dado_recebido;
	movff	(c:_dado_recebido),(c:_funcao)
	line	500
	
i2l2297:
;main.c: 500: if(funcao<'0' || funcao>'7') {(FLAGS_1 |= (1<<7));}
		movlw	030h-1
	cpfsgt	((c:_funcao)),c
	goto	i2u226_41
	goto	i2u226_40

i2u226_41:
	goto	i2l2301
i2u226_40:
	
i2l2299:
		movlw	038h-1
	cpfsgt	((c:_funcao)),c
	goto	i2u227_41
	goto	i2u227_40

i2u227_41:
	goto	i2l301
i2u227_40:
	
i2l2301:
	bsf	(0+(7/8)+(c:_FLAGS_1)),c,(7)&7
	goto	i2l301
	line	504
	
i2l2303:
;main.c: 503: else{
;main.c: 504: conta = (dado_recebido - '0');
	movf	((c:_dado_recebido)),c,w
	addlw	low(0D0h)
	movwf	((c:_conta)),c
	line	505
;main.c: 505: if(!(conta<16)) (FLAGS_1 |= (1<<2));
		movlw	010h-1
	cpfsgt	((c:_conta)),c
	goto	i2u228_41
	goto	i2u228_40

i2u228_41:
	goto	i2l2307
i2u228_40:
	
i2l2305:
	bsf	(0+(2/8)+(c:_FLAGS_1)),c,(2)&7
	goto	i2l301
	line	508
	
i2l2307:
;main.c: 507: else{
;main.c: 508: if(conta != ultima_conta){
	movf	((c:_ultima_conta)),c,w
xorwf	((c:_conta)),c,w
	btfsc	status,2
	goto	i2u229_41
	goto	i2u229_40

i2u229_41:
	goto	i2l2311
i2u229_40:
	line	509
	
i2l2309:
;main.c: 509: TXREG = 'P';
	movlw	low(050h)
	movwf	((c:4013)),c	;volatile
	line	510
;main.c: 510: while(!TRMT){}
	
i2l305:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u230_41
	goto	i2u230_40
i2u230_41:
	goto	i2l305
i2u230_40:
	
i2l307:
	line	511
;main.c: 511: RCIE=0;
	bcf	c:(31981/8),(31981)&7	;volatile
	line	512
;main.c: 512: }
	goto	i2l301
	line	514
	
i2l2311:
;main.c: 514: else (FLAGS_1 |= (1<<0));
	bsf	(0+(0/8)+(c:_FLAGS_1)),c,(0)&7
	line	516
	
i2l301:
	line	518
;main.c: 515: }
;main.c: 516: }
;main.c: 518: ordem++;}
	incf	((c:_ordem)),c
	goto	i2l2407
	line	522
	
i2l2313:
;main.c: 522: else if(etapa == 2){
		movlw	2
	xorwf	((c:_etapa)),c,w
	btfss	status,2
	goto	i2u231_41
	goto	i2u231_40

i2u231_41:
	goto	i2l2327
i2u231_40:
	line	524
	
i2l2315:
;main.c: 524: TXREG = 'J';
	movlw	low(04Ah)
	movwf	((c:4013)),c	;volatile
	line	525
;main.c: 525: while(!TRMT){}
	
i2l311:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u232_41
	goto	i2u232_40
i2u232_41:
	goto	i2l311
i2u232_40:
	line	526
	
i2l2317:
;main.c: 526: TXREG = senha[ordem];
	movf	((c:_ordem)),c,w
	addlw	low(_senha)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	movwf	((c:4013)),c	;volatile
	line	527
;main.c: 527: while(!TRMT){}
	
i2l314:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u233_41
	goto	i2u233_40
i2u233_41:
	goto	i2l314
i2u233_40:
	line	529
	
i2l2319:
;main.c: 529: if(senha[ordem] != dado_recebido){
	movf	((c:_ordem)),c,w
	addlw	low(_senha)
	movwf	fsr2l
	clrf	fsr2h
	movf	((c:_dado_recebido)),c,w
xorwf	postinc2,w
	btfsc	status,2
	goto	i2u234_41
	goto	i2u234_40

i2u234_41:
	goto	i2l317
i2u234_40:
	line	530
	
i2l2321:
;main.c: 530: (FLAGS_1 |= (1<<6));}
	bsf	(0+(6/8)+(c:_FLAGS_1)),c,(6)&7
	
i2l317:
	line	531
;main.c: 531: ordem++;
	incf	((c:_ordem)),c
	line	533
	
i2l2323:
;main.c: 533: if(senha[ordem] == (0)) (FLAGS_1 |= (1<<0));
	movf	((c:_ordem)),c,w
	addlw	low(_senha)
	movwf	fsr2l
	clrf	fsr2h
	movf	indf2,w
	btfss	status,2
	goto	i2u235_41
	goto	i2u235_40
i2u235_41:
	goto	i2l2407
i2u235_40:
	goto	i2l294
	
i2l318:
	line	535
;main.c: 535: }
	goto	i2l2407
	line	538
	
i2l2327:
;main.c: 538: else if(etapa == 3){
		movlw	3
	xorwf	((c:_etapa)),c,w
	btfss	status,2
	goto	i2u236_41
	goto	i2u236_40

i2u236_41:
	goto	i2l2397
i2u236_40:
	line	539
	
i2l2329:
;main.c: 539: if(funcao == '0' || funcao == '2'){
		movlw	48
	xorwf	((c:_funcao)),c,w
	btfsc	status,2
	goto	i2u237_41
	goto	i2u237_40

i2u237_41:
	goto	i2l2333
i2u237_40:
	
i2l2331:
		movlw	50
	xorwf	((c:_funcao)),c,w
	btfss	status,2
	goto	i2u238_41
	goto	i2u238_40

i2u238_41:
	goto	i2l2341
i2u238_40:
	line	541
	
i2l2333:
;main.c: 541: if(ordem == 2) {
		movlw	2
	xorwf	((c:_ordem)),c,w
	btfss	status,2
	goto	i2u239_41
	goto	i2u239_40

i2u239_41:
	goto	i2l2337
i2u239_40:
	goto	i2l2311
	line	545
	
i2l2337:
;main.c: 545: else if(dado_recebido != ('N'+(ordem))) {(FLAGS_1 |= (1<<7));}
	movf	((c:_dado_recebido)),c,w
	movwf	(??_aux+0+0)&0ffh,c
	clrf	(??_aux+0+0+1)&0ffh,c

	movf	((c:_ordem)),c,w
	movwf	(??_aux+2+0)&0ffh,c
	clrf	(??_aux+2+0+1)&0ffh,c

	movlw	04Eh
	addwf	(??_aux+2+0),c
	movlw	0
	addwfc	(??_aux+2+1),c
	movf	(??_aux+0+0),c,w
xorwf	(??_aux+2+0),c,w
	bnz	i2u240_40
movf	(??_aux+0+1),c,w
xorwf	(??_aux+2+1),c,w
	btfsc	status,2
	goto	i2u240_41
	goto	i2u240_40

i2u240_41:
	goto	i2l301
i2u240_40:
	goto	i2l2301
	line	550
	
i2l2341:
;main.c: 550: else if(funcao == '1'){
		movlw	49
	xorwf	((c:_funcao)),c,w
	btfss	status,2
	goto	i2u241_41
	goto	i2u241_40

i2u241_41:
	goto	i2l2347
i2u241_40:
	line	551
	
i2l2343:
;main.c: 552: endereco_inic_eeprom = (1794 + (dado_recebido *26));
	movf	((c:_ordem)),c,w
	btfss	status,2
	goto	i2u242_41
	goto	i2u242_40
i2u242_41:
	goto	i2l2407
i2u242_40:
	goto	i2l301
	line	559
	
i2l2347:
;main.c: 559: else if(funcao == '4'){
		movlw	52
	xorwf	((c:_funcao)),c,w
	btfss	status,2
	goto	i2u243_41
	goto	i2u243_40

i2u243_41:
	goto	i2l2371
i2u243_40:
	line	567
	
i2l2349:
;main.c: 567: if(ordem == 12){(FLAGS_1 |= (1<<0));}
		movlw	12
	xorwf	((c:_ordem)),c,w
	btfss	status,2
	goto	i2u244_41
	goto	i2u244_40

i2u244_41:
	goto	i2l2353
i2u244_40:
	
i2l2351:
	bsf	(0+(0/8)+(c:_FLAGS_1)),c,(0)&7
	goto	i2l2369
	line	569
	
i2l2353:
;main.c: 569: else if(dado_recebido == 'X') {ordem+=2;}
		movlw	88
	xorwf	((c:_dado_recebido)),c,w
	btfss	status,2
	goto	i2u245_41
	goto	i2u245_40

i2u245_41:
	goto	i2l2357
i2u245_40:
	
i2l2355:
	movlw	(02h)&0ffh
	addwf	((c:_ordem)),c
	goto	i2l2369
	line	572
	
i2l2357:
;main.c: 571: else{
;main.c: 572: if(ordem < 1 || ordem%2){buffer_serial = dado_recebido;}
	movf	((c:_ordem)),c,w
	btfsc	status,2
	goto	i2u246_41
	goto	i2u246_40
i2u246_41:
	goto	i2l338
i2u246_40:
	
i2l2359:
	
	btfss	((c:_ordem)),c,(0)&7
	goto	i2u247_41
	goto	i2u247_40
i2u247_41:
	goto	i2l2361
i2u247_40:
	
i2l338:
	movff	(c:_dado_recebido),(c:_buffer_serial)
	goto	i2l2367
	line	575
	
i2l2361:
;main.c: 574: else{
;main.c: 575: *ptr_data = ascii_para_numero(0,dado_recebido,buffer_serial);
	movff	(c:_dado_recebido),(c:ascii_para_numero@caractere2)
	movff	(c:_buffer_serial),(c:ascii_para_numero@caractere1)
	movlw	(0)&0ffh
	
	call	_ascii_para_numero
	movff	(c:_ptr_data),fsr2l
	movff	(c:_ptr_data+1),fsr2h
	movwf	indf2,c

	line	576
	
i2l2363:
;main.c: 576: char temp = *ptr_data;
	movff	(c:_ptr_data),fsr2l
	movff	(c:_ptr_data+1),fsr2h
	movf	indf2,w
	movwf	((c:aux@temp)),c
	line	577
	
i2l2365:
;main.c: 577: numero_para_ascii(temp);
	movf	((c:aux@temp)),c,w
	
	call	i2_numero_para_ascii
	line	579
	
i2l2367:
;main.c: 578: }
;main.c: 579: ordem++;
	incf	((c:_ordem)),c
	line	582
	
i2l2369:
;main.c: 580: }
;main.c: 582: ptr_data+= (ordem/2);
	bcf	status,0
	rrcf	((c:_ordem)),c,w
	addwf	((c:_ptr_data)),c
	movlw	0
	addwfc	((c:_ptr_data+1)),c
	line	587
;main.c: 587: }
	goto	i2l2407
	line	588
	
i2l2371:
;main.c: 588: else if(funcao == '7'){
		movlw	55
	xorwf	((c:_funcao)),c,w
	btfss	status,2
	goto	i2u248_41
	goto	i2u248_40

i2u248_41:
	goto	i2l2407
i2u248_40:
	line	592
	
i2l2373:
;main.c: 592: if(ordem==0){
	movf	((c:_ordem)),c,w
	btfss	status,2
	goto	i2u249_41
	goto	i2u249_40
i2u249_41:
	goto	i2l2381
i2u249_40:
	line	593
	
i2l2375:
;main.c: 593: unsigned char conta_a_ser_alterada = (dado_recebido - '0');
	movf	((c:_dado_recebido)),c,w
	addlw	low(0D0h)
	movwf	((c:aux@conta_a_ser_alterada)),c
	line	595
;main.c: 595: if(conta_a_ser_alterada != conta){
	movf	((c:_conta)),c,w
xorwf	((c:aux@conta_a_ser_alterada)),c,w
	btfsc	status,2
	goto	i2u250_41
	goto	i2u250_40

i2u250_41:
	goto	i2l318
i2u250_40:
	line	596
	
i2l2377:
;main.c: 596: if(!((nivel_acesso & (1<<6)))){
	
	btfsc	((c:_nivel_acesso)),c,(6)&7
	goto	i2u251_41
	goto	i2u251_40
i2u251_41:
	goto	i2l318
i2u251_40:
	line	597
	
i2l2379:
;main.c: 597: (FLAGS_1 |= (1<<3));}
	bsf	(0+(3/8)+(c:_FLAGS_1)),c,(3)&7
	goto	i2l2407
	line	601
	
i2l2381:
;main.c: 601: else if(dado_recebido == '<') {
		movlw	60
	xorwf	((c:_dado_recebido)),c,w
	btfss	status,2
	goto	i2u252_41
	goto	i2u252_40

i2u252_41:
	goto	i2l2389
i2u252_40:
	line	602
	
i2l2383:
;main.c: 602: if(ordem<5) (FLAGS_1 |= (1<<7));
		movlw	05h-0
	cpfslt	((c:_ordem)),c
	goto	i2u253_41
	goto	i2u253_40

i2u253_41:
	goto	i2l294
i2u253_40:
	
i2l2385:
	bsf	(0+(7/8)+(c:_FLAGS_1)),c,(7)&7
	goto	i2l2407
	line	608
	
i2l2389:
;main.c: 607: else{
;main.c: 608: nova_senha[ordem-1] = dado_recebido;
	movf	((c:_ordem)),c,w
	addlw	low(_nova_senha+0FFh)
	movwf	fsr2l
	clrf	fsr2h
	movff	(c:_dado_recebido),indf2

	line	609
	
i2l2391:
;main.c: 609: ordem++;
	incf	((c:_ordem)),c
	line	610
	
i2l2393:
;main.c: 610: if(ordem == (16-1)) {(FLAGS_1 |= (1<<0));}
		movlw	15
	xorwf	((c:_ordem)),c,w
	btfss	status,2
	goto	i2u254_41
	goto	i2u254_40

i2u254_41:
	goto	i2l318
i2u254_40:
	goto	i2l294
	line	616
	
i2l2397:
;main.c: 616: else if(etapa == 4){
		movlw	4
	xorwf	((c:_etapa)),c,w
	btfss	status,2
	goto	i2u255_41
	goto	i2u255_40

i2u255_41:
	goto	i2l318
i2u255_40:
	line	618
	
i2l2399:
;main.c: 618: if(dado_recebido != 'F') (FLAGS_1 |= (1<<7));
		movlw	70
	xorwf	((c:_dado_recebido)),c,w
	btfsc	status,2
	goto	i2u256_41
	goto	i2u256_40

i2u256_41:
	goto	i2l2403
i2u256_40:
	
i2l2401:
	bsf	(0+(7/8)+(c:_FLAGS_1)),c,(7)&7
	line	619
	
i2l2403:
;main.c: 619: enviar=1;
	bsf	(_enviar/8),c,(_enviar)&7
	line	620
	
i2l2405:
;main.c: 620: etapa = 0;}
	clrf	((c:_etapa)),c
	line	624
	
i2l2407:
;main.c: 624: if(FLAGS_1>3) {
		movlw	04h-1
	cpfsgt	((c:_FLAGS_1)),c
	goto	i2u257_41
	goto	i2u257_40

i2u257_41:
	goto	i2l261
i2u257_40:
	line	625
	
i2l2409:
;main.c: 625: (FLAGS_1 &= ~(1<<0));
	bcf	(0+(0/8)+(c:_FLAGS_1)),c,(0)&7
	line	626
	
i2l2411:
;main.c: 626: TXREG = '0' + etapa;
	movf	((c:_etapa)),c,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	627
;main.c: 627: while(!TRMT){}
	
i2l355:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u258_41
	goto	i2u258_40
i2u258_41:
	goto	i2l355
i2u258_40:
	
i2l357:
	line	628
;main.c: 628: etapa = 0;
	clrf	((c:_etapa)),c
	line	629
;main.c: 629: enviar=1;}
	bsf	(_enviar/8),c,(_enviar)&7
	line	632
	
i2l261:
	line	633
;main.c: 632: }
;main.c: 633: RCIF=0;}
	bcf	c:(31989/8),(31989)&7	;volatile
	line	635
	
i2l358:
	movff	??_aux+7,prodh+0
	movff	??_aux+6,prodl+0
	movff	??_aux+5,fsr2h+0
	movff	??_aux+4,fsr2l+0
	retfie f
	opt stack 0
GLOBAL	__end_of_aux
	__end_of_aux:
	signat	_aux,88
	global	i2_numero_para_ascii

;; *************** function i2_numero_para_ascii *****************
;; Defined at:
;;		line 188 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;  numero          1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  numero          1   15[COMRAM] unsigned char 
;;  numero_para_    1   17[COMRAM] unsigned char 
;;  numero_para_    1   16[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh, cstack
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         0       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0
;;      Temps:          1       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		i2___awdiv
;;		i2___lbdiv
;;		i2___wmul
;; This function is called by:
;;		_aux
;; This function uses a non-reentrant model
;;
psect	text14,class=CODE,space=0,reloc=2
	line	188
global __ptext14
__ptext14:
psect	text14
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	188
	global	__size_ofi2_numero_para_ascii
	__size_ofi2_numero_para_ascii	equ	__end_ofi2_numero_para_ascii-i2_numero_para_ascii
	
i2_numero_para_ascii:
;incstack = 0
	opt	stack 26
;i2numero_para_ascii@numero stored from wreg
	movwf	((c:i2numero_para_ascii@numero)),c
	line	192
	
i2l2135:
;main.c: 189: char temp1;
;main.c: 190: char temp2;
;main.c: 192: TXREG = '+';
	movlw	low(02Bh)
	movwf	((c:4013)),c	;volatile
	line	193
;main.c: 193: while(!TRMT){}
	
i2l149:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u183_41
	goto	i2u183_40
i2u183_41:
	goto	i2l149
i2u183_40:
	line	195
	
i2l2137:
;main.c: 195: temp1 = numero/100;
	movlw	low(064h)
	movwf	((c:i2___lbdiv@divisor)),c
	movf	((c:i2numero_para_ascii@numero)),c,w
	
	call	i2___lbdiv
	movwf	((c:i2numero_para_ascii@temp1)),c
	line	196
	
i2l2139:
;main.c: 196: TXREG = '0'+ temp1;
	movf	((c:i2numero_para_ascii@temp1)),c,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	197
;main.c: 197: while(!TRMT){}
	
i2l152:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u184_41
	goto	i2u184_40
i2u184_41:
	goto	i2l152
i2u184_40:
	line	199
	
i2l2141:
;main.c: 199: temp2 = ((numero - temp1*100)/10);
	movff	(c:i2numero_para_ascii@temp1),(c:i2___wmul@multiplier)
	clrf	((c:i2___wmul@multiplier+1)),c
	movlw	high(-100)
	movwf	((c:i2___wmul@multiplicand+1)),c
	movlw	low(-100)
	movwf	((c:i2___wmul@multiplicand)),c
	call	i2___wmul	;wreg free
	movf	((c:i2numero_para_ascii@numero)),c,w
	addwf	(0+?i2___wmul),c,w
	movwf	((c:i2___awdiv@dividend)),c
	movlw	0
	addwfc	(1+?i2___wmul),c,w
	movwf	1+((c:i2___awdiv@dividend)),c
	movlw	high(0Ah)
	movwf	((c:i2___awdiv@divisor+1)),c
	movlw	low(0Ah)
	movwf	((c:i2___awdiv@divisor)),c
	call	i2___awdiv	;wreg free
	movf	(0+?i2___awdiv),c,w
	movwf	((c:i2numero_para_ascii@temp2)),c
	line	200
	
i2l2143:
;main.c: 200: TXREG = '0'+ temp2;
	movf	((c:i2numero_para_ascii@temp2)),c,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	201
;main.c: 201: while(!TRMT){}
	
i2l155:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u185_41
	goto	i2u185_40
i2u185_41:
	goto	i2l155
i2u185_40:
	line	203
	
i2l2145:
;main.c: 203: TXREG = '0'+ (numero - (temp2*10) - (temp1*100));
	movf	((c:i2numero_para_ascii@temp1)),c,w
	mullw	09Ch
	movff	prodl,??i2_numero_para_ascii+0+0
	movf	((c:i2numero_para_ascii@temp2)),c,w
	mullw	0F6h
	movf	(prodl),c,w
	addwf	(??i2_numero_para_ascii+0+0),c,w
	addwf	((c:i2numero_para_ascii@numero)),c,w
	addlw	low(030h)
	movwf	((c:4013)),c	;volatile
	line	204
;main.c: 204: while(!TRMT){}
	
i2l158:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u186_41
	goto	i2u186_40
i2u186_41:
	goto	i2l158
i2u186_40:
	line	206
	
i2l2147:
;main.c: 206: TXREG = '+';
	movlw	low(02Bh)
	movwf	((c:4013)),c	;volatile
	line	207
;main.c: 207: while(!TRMT){}
	
i2l161:
	btfss	c:(32097/8),(32097)&7	;volatile
	goto	i2u187_41
	goto	i2u187_40
i2u187_41:
	goto	i2l161
i2u187_40:
	line	208
	
i2l164:
	return	;funcret
	opt stack 0
GLOBAL	__end_ofi2_numero_para_ascii
	__end_ofi2_numero_para_ascii:
	signat	i2_numero_para_ascii,88
	global	i2___wmul

;; *************** function i2___wmul *****************
;; Defined at:
;;		line 15 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\Umul16.c"
;; Parameters:    Size  Location     Type
;;  multiplier      2    0[COMRAM] unsigned int 
;;  multiplicand    2    2[COMRAM] unsigned int 
;; Auto vars:     Size  Location     Type
;;  __wmul          2    4[COMRAM] unsigned int 
;; Return value:  Size  Location     Type
;;                  2    0[COMRAM] unsigned int 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         4       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         6       0       0       0       0       0       0       0       0
;;Total ram usage:        6 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		i2_numero_para_ascii
;; This function uses a non-reentrant model
;;
psect	text15,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\Umul16.c"
	line	15
global __ptext15
__ptext15:
psect	text15
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\Umul16.c"
	line	15
	global	__size_ofi2___wmul
	__size_ofi2___wmul	equ	__end_ofi2___wmul-i2___wmul
	
i2___wmul:
;incstack = 0
	opt	stack 26
	line	37
	
i2l1919:
	movf	((c:i2___wmul@multiplier)),c,w
	mulwf	((c:i2___wmul@multiplicand)),c
	movff	prodl,(c:i2___wmul@product)
	movff	prodh,(c:i2___wmul@product+1)
	line	38
	movf	((c:i2___wmul@multiplier)),c,w
	mulwf	(0+((c:i2___wmul@multiplicand)+01h)),c
	movf	(prodl),c,w
	addwf	((c:i2___wmul@product+1)),c

	line	39
	movf	(0+((c:i2___wmul@multiplier)+01h)),c,w
	mulwf	((c:i2___wmul@multiplicand)),c
	movf	(prodl),c,w
	addwf	((c:i2___wmul@product+1)),c

	line	52
	
i2l1921:
	movff	(c:i2___wmul@product),(c:?i2___wmul)
	movff	(c:i2___wmul@product+1),(c:?i2___wmul+1)
	line	53
	
i2l480:
	return	;funcret
	opt stack 0
GLOBAL	__end_ofi2___wmul
	__end_ofi2___wmul:
	signat	i2___wmul,90
	global	i2___lbdiv

;; *************** function i2___lbdiv *****************
;; Defined at:
;;		line 4 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\lbdiv.c"
;; Parameters:    Size  Location     Type
;;  dividend        1    wreg     unsigned char 
;;  divisor         1    0[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  dividend        1    1[COMRAM] unsigned char 
;;  __lbdiv         1    3[COMRAM] unsigned char 
;;  __lbdiv         1    2[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         1       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		i2_numero_para_ascii
;; This function uses a non-reentrant model
;;
psect	text16,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\lbdiv.c"
	line	4
global __ptext16
__ptext16:
psect	text16
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\lbdiv.c"
	line	4
	global	__size_ofi2___lbdiv
	__size_ofi2___lbdiv	equ	__end_ofi2___lbdiv-i2___lbdiv
	
i2___lbdiv:
;incstack = 0
	opt	stack 26
;i2___lbdiv@dividend stored from wreg
	movwf	((c:i2___lbdiv@dividend)),c
	line	9
	
i2l1969:
	clrf	((c:i2___lbdiv@quotient)),c
	line	10
	
i2l1971:
	movf	((c:i2___lbdiv@divisor)),c,w
	btfsc	status,2
	goto	i2u167_41
	goto	i2u167_40
i2u167_41:
	goto	i2l1991
i2u167_40:
	line	11
	
i2l1973:
	movlw	low(01h)
	movwf	((c:i2___lbdiv@counter)),c
	line	12
	goto	i2l1979
	line	13
	
i2l1975:
	bcf status,0
	rlcf	((c:i2___lbdiv@divisor)),c

	line	14
	
i2l1977:
	incf	((c:i2___lbdiv@counter)),c
	line	12
	
i2l1979:
	
	btfss	((c:i2___lbdiv@divisor)),c,(7)&7
	goto	i2u168_41
	goto	i2u168_40
i2u168_41:
	goto	i2l1975
i2u168_40:
	line	17
	
i2l1981:
	bcf status,0
	rlcf	((c:i2___lbdiv@quotient)),c

	line	18
		movf	((c:i2___lbdiv@divisor)),c,w
	subwf	((c:i2___lbdiv@dividend)),c,w
	btfss	status,0
	goto	i2u169_41
	goto	i2u169_40

i2u169_41:
	goto	i2l1987
i2u169_40:
	line	19
	
i2l1983:
	movf	((c:i2___lbdiv@divisor)),c,w
	subwf	((c:i2___lbdiv@dividend)),c
	line	20
	
i2l1985:
	bsf	(0+(0/8)+(c:i2___lbdiv@quotient)),c,(0)&7
	line	22
	
i2l1987:
	bcf status,0
	rrcf	((c:i2___lbdiv@divisor)),c

	line	23
	
i2l1989:
	decfsz	((c:i2___lbdiv@counter)),c
	
	goto	i2l1981
	line	25
	
i2l1991:
	movf	((c:i2___lbdiv@quotient)),c,w
	line	26
	
i2l916:
	return	;funcret
	opt stack 0
GLOBAL	__end_ofi2___lbdiv
	__end_ofi2___lbdiv:
	signat	i2___lbdiv,89
	global	i2___awdiv

;; *************** function i2___awdiv *****************
;; Defined at:
;;		line 8 in file "C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\awdiv.c"
;; Parameters:    Size  Location     Type
;;  dividend        2    6[COMRAM] int 
;;  divisor         2    8[COMRAM] int 
;; Auto vars:     Size  Location     Type
;;  __awdiv         2   12[COMRAM] int 
;;  __awdiv         1   11[COMRAM] unsigned char 
;;  __awdiv         1   10[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  2    6[COMRAM] int 
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         4       0       0       0       0       0       0       0       0
;;      Locals:         4       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         8       0       0       0       0       0       0       0       0
;;Total ram usage:        8 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		i2_numero_para_ascii
;; This function uses a non-reentrant model
;;
psect	text17,class=CODE,space=0,reloc=2
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\awdiv.c"
	line	8
global __ptext17
__ptext17:
psect	text17
	file	"C:\Program Files (x86)\Microchip\xc8\v1.34\sources\common\awdiv.c"
	line	8
	global	__size_ofi2___awdiv
	__size_ofi2___awdiv	equ	__end_ofi2___awdiv-i2___awdiv
	
i2___awdiv:
;incstack = 0
	opt	stack 26
	line	14
	
i2l1925:
	clrf	((c:i2___awdiv@sign)),c
	line	15
	
i2l1927:
	btfsc	((c:i2___awdiv@divisor+1)),c,7
	goto	i2u161_40
	goto	i2u161_41

i2u161_41:
	goto	i2l1933
i2u161_40:
	line	16
	
i2l1929:
	negf	((c:i2___awdiv@divisor)),c
	comf	((c:i2___awdiv@divisor+1)),c
	btfsc	status,0
	incf	((c:i2___awdiv@divisor+1)),c
	line	17
	
i2l1931:
	movlw	low(01h)
	movwf	((c:i2___awdiv@sign)),c
	line	19
	
i2l1933:
	btfsc	((c:i2___awdiv@dividend+1)),c,7
	goto	i2u162_40
	goto	i2u162_41

i2u162_41:
	goto	i2l1939
i2u162_40:
	line	20
	
i2l1935:
	negf	((c:i2___awdiv@dividend)),c
	comf	((c:i2___awdiv@dividend+1)),c
	btfsc	status,0
	incf	((c:i2___awdiv@dividend+1)),c
	line	21
	
i2l1937:
	movlw	(01h)&0ffh
	xorwf	((c:i2___awdiv@sign)),c
	line	23
	
i2l1939:
	clrf	((c:i2___awdiv@quotient)),c
	clrf	((c:i2___awdiv@quotient+1)),c
	line	24
	
i2l1941:
	movf	((c:i2___awdiv@divisor)),c,w
iorwf	((c:i2___awdiv@divisor+1)),c,w
	btfsc	status,2
	goto	i2u163_41
	goto	i2u163_40

i2u163_41:
	goto	i2l1961
i2u163_40:
	line	25
	
i2l1943:
	movlw	low(01h)
	movwf	((c:i2___awdiv@counter)),c
	line	26
	goto	i2l1947
	line	27
	
i2l1945:
	bcf	status,0
	rlcf	((c:i2___awdiv@divisor)),c
	rlcf	((c:i2___awdiv@divisor+1)),c
	line	28
	incf	((c:i2___awdiv@counter)),c
	line	26
	
i2l1947:
	
	btfss	((c:i2___awdiv@divisor+1)),c,(15)&7
	goto	i2u164_41
	goto	i2u164_40
i2u164_41:
	goto	i2l1945
i2u164_40:
	line	31
	
i2l1949:
	bcf	status,0
	rlcf	((c:i2___awdiv@quotient)),c
	rlcf	((c:i2___awdiv@quotient+1)),c
	line	32
	
i2l1951:
		movf	((c:i2___awdiv@divisor)),c,w
	subwf	((c:i2___awdiv@dividend)),c,w
	movf	((c:i2___awdiv@divisor+1)),c,w
	subwfb	((c:i2___awdiv@dividend+1)),c,w
	btfss	status,0
	goto	i2u165_41
	goto	i2u165_40

i2u165_41:
	goto	i2l1957
i2u165_40:
	line	33
	
i2l1953:
	movf	((c:i2___awdiv@divisor)),c,w
	subwf	((c:i2___awdiv@dividend)),c
	movf	((c:i2___awdiv@divisor+1)),c,w
	subwfb	((c:i2___awdiv@dividend+1)),c

	line	34
	
i2l1955:
	bsf	(0+(0/8)+(c:i2___awdiv@quotient)),c,(0)&7
	line	36
	
i2l1957:
	bcf	status,0
	rrcf	((c:i2___awdiv@divisor+1)),c
	rrcf	((c:i2___awdiv@divisor)),c
	line	37
	
i2l1959:
	decfsz	((c:i2___awdiv@counter)),c
	
	goto	i2l1949
	line	39
	
i2l1961:
	movf	((c:i2___awdiv@sign)),c,w
	btfsc	status,2
	goto	i2u166_41
	goto	i2u166_40
i2u166_41:
	goto	i2l1965
i2u166_40:
	line	40
	
i2l1963:
	negf	((c:i2___awdiv@quotient)),c
	comf	((c:i2___awdiv@quotient+1)),c
	btfsc	status,0
	incf	((c:i2___awdiv@quotient+1)),c
	line	41
	
i2l1965:
	movff	(c:i2___awdiv@quotient),(c:?i2___awdiv)
	movff	(c:i2___awdiv@quotient+1),(c:?i2___awdiv+1)
	line	42
	
i2l673:
	return	;funcret
	opt stack 0
GLOBAL	__end_ofi2___awdiv
	__end_ofi2___awdiv:
	signat	i2___awdiv,90
	global	_teclado_matricial

;; *************** function _teclado_matricial *****************
;; Defined at:
;;		line 217 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;  coluna          1    wreg     unsigned char 
;;  linha           1    0[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  coluna          1    1[COMRAM] unsigned char 
;;  caractere       1    3[COMRAM] unsigned char 
;;  temp            1    2[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         1       0       0       0       0       0       0       0       0
;;      Locals:         3       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_aux
;; This function uses a non-reentrant model
;;
psect	text18,class=CODE,space=0,reloc=2
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	217
global __ptext18
__ptext18:
psect	text18
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	217
	global	__size_of_teclado_matricial
	__size_of_teclado_matricial	equ	__end_of_teclado_matricial-_teclado_matricial
	
_teclado_matricial:
;incstack = 0
	opt	stack 27
;teclado_matricial@coluna stored from wreg
	movwf	((c:teclado_matricial@coluna)),c
	line	219
	
i2l2023:
;main.c: 219: char temp = ((coluna-1)*4) + linha;
	movf	((c:teclado_matricial@coluna)),c,w
	mullw	04h
	movf	(prodl),c,w
	addwf	((c:teclado_matricial@linha)),c,w
	addlw	low(0FCh)
	movwf	((c:teclado_matricial@temp)),c
	line	222
;main.c: 220: char caractere;
;main.c: 222: switch(temp){
	goto	i2l2059
	line	224
	
i2l2025:
;main.c: 224: caractere = '*';
	movlw	low(02Ah)
	movwf	((c:teclado_matricial@caractere)),c
	line	225
;main.c: 225: break;
	goto	i2l2061
	line	228
	
i2l2027:
;main.c: 228: caractere = '0';
	movlw	low(030h)
	movwf	((c:teclado_matricial@caractere)),c
	line	229
;main.c: 229: break;
	goto	i2l2061
	line	232
	
i2l2029:
;main.c: 232: caractere = '#';
	movlw	low(023h)
	movwf	((c:teclado_matricial@caractere)),c
	line	233
;main.c: 233: break;
	goto	i2l2061
	line	236
	
i2l2031:
;main.c: 236: caractere = 'D';
	movlw	low(044h)
	movwf	((c:teclado_matricial@caractere)),c
	line	237
;main.c: 237: break;
	goto	i2l2061
	line	240
	
i2l2033:
;main.c: 240: caractere = '7';
	movlw	low(037h)
	movwf	((c:teclado_matricial@caractere)),c
	line	241
;main.c: 241: break;
	goto	i2l2061
	line	244
	
i2l2035:
;main.c: 244: caractere = '8';
	movlw	low(038h)
	movwf	((c:teclado_matricial@caractere)),c
	line	245
;main.c: 245: break;
	goto	i2l2061
	line	248
	
i2l2037:
;main.c: 248: caractere = '9';
	movlw	low(039h)
	movwf	((c:teclado_matricial@caractere)),c
	line	249
;main.c: 249: break;
	goto	i2l2061
	line	252
	
i2l2039:
;main.c: 252: caractere = 'C';
	movlw	low(043h)
	movwf	((c:teclado_matricial@caractere)),c
	line	253
;main.c: 253: break;
	goto	i2l2061
	line	256
	
i2l2041:
;main.c: 256: caractere = '4';
	movlw	low(034h)
	movwf	((c:teclado_matricial@caractere)),c
	line	257
;main.c: 257: break;
	goto	i2l2061
	line	260
	
i2l2043:
;main.c: 260: caractere = '5';
	movlw	low(035h)
	movwf	((c:teclado_matricial@caractere)),c
	line	261
;main.c: 261: break;
	goto	i2l2061
	line	264
	
i2l2045:
;main.c: 264: caractere = '6';
	movlw	low(036h)
	movwf	((c:teclado_matricial@caractere)),c
	line	265
;main.c: 265: break;
	goto	i2l2061
	line	268
	
i2l2047:
;main.c: 268: caractere = 'B';
	movlw	low(042h)
	movwf	((c:teclado_matricial@caractere)),c
	line	269
;main.c: 269: break;
	goto	i2l2061
	line	272
	
i2l2049:
;main.c: 272: caractere = '1';
	movlw	low(031h)
	movwf	((c:teclado_matricial@caractere)),c
	line	273
;main.c: 273: break;
	goto	i2l2061
	line	276
	
i2l2051:
;main.c: 276: caractere = '2';
	movlw	low(032h)
	movwf	((c:teclado_matricial@caractere)),c
	line	277
;main.c: 277: break;
	goto	i2l2061
	line	280
	
i2l2053:
;main.c: 280: caractere = '3';
	movlw	low(033h)
	movwf	((c:teclado_matricial@caractere)),c
	line	281
;main.c: 281: break;
	goto	i2l2061
	line	284
	
i2l2055:
;main.c: 284: caractere = 'A';
	movlw	low(041h)
	movwf	((c:teclado_matricial@caractere)),c
	line	285
;main.c: 285: break;
	goto	i2l2061
	line	222
	
i2l2059:
	movf	((c:teclado_matricial@temp)),c,w
	; Switch size 1, requested type "space"
; Number of cases is 16, Range of values is 1 to 16
; switch strategies available:
; Name         Instructions Cycles
; simple_byte           49    25 (average)
;	Chosen strategy is simple_byte

	xorlw	1^0	; case 1
	skipnz
	goto	i2l2025
	xorlw	2^1	; case 2
	skipnz
	goto	i2l2027
	xorlw	3^2	; case 3
	skipnz
	goto	i2l2029
	xorlw	4^3	; case 4
	skipnz
	goto	i2l2031
	xorlw	5^4	; case 5
	skipnz
	goto	i2l2033
	xorlw	6^5	; case 6
	skipnz
	goto	i2l2035
	xorlw	7^6	; case 7
	skipnz
	goto	i2l2037
	xorlw	8^7	; case 8
	skipnz
	goto	i2l2039
	xorlw	9^8	; case 9
	skipnz
	goto	i2l2041
	xorlw	10^9	; case 10
	skipnz
	goto	i2l2043
	xorlw	11^10	; case 11
	skipnz
	goto	i2l2045
	xorlw	12^11	; case 12
	skipnz
	goto	i2l2047
	xorlw	13^12	; case 13
	skipnz
	goto	i2l2049
	xorlw	14^13	; case 14
	skipnz
	goto	i2l2051
	xorlw	15^14	; case 15
	skipnz
	goto	i2l2053
	xorlw	16^15	; case 16
	skipnz
	goto	i2l2055
	goto	i2l2061

	line	289
	
i2l2061:
;main.c: 289: return caractere;
	movf	((c:teclado_matricial@caractere)),c,w
	line	290
	
i2l188:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_teclado_matricial
	__end_of_teclado_matricial:
	signat	_teclado_matricial,8313
	global	_ascii_para_numero

;; *************** function _ascii_para_numero *****************
;; Defined at:
;;		line 210 in file "D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
;; Parameters:    Size  Location     Type
;;  caractere3      1    wreg     unsigned char 
;;  caractere2      1    0[COMRAM] unsigned char 
;;  caractere1      1    1[COMRAM] unsigned char 
;; Auto vars:     Size  Location     Type
;;  caractere3      1    2[COMRAM] unsigned char 
;;  numero          1    3[COMRAM] unsigned char 
;; Return value:  Size  Location     Type
;;                  1    wreg      unsigned char 
;; Registers used:
;;		wreg, status,2, status,0, prodl, prodh
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMRAM   BANK0   BANK1   BANK2   BANK3   BANK4   BANK5   BANK6   BANK7
;;      Params:         2       0       0       0       0       0       0       0       0
;;      Locals:         2       0       0       0       0       0       0       0       0
;;      Temps:          0       0       0       0       0       0       0       0       0
;;      Totals:         4       0       0       0       0       0       0       0       0
;;Total ram usage:        4 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_aux
;; This function uses a non-reentrant model
;;
psect	text19,class=CODE,space=0,reloc=2
	line	210
global __ptext19
__ptext19:
psect	text19
	file	"D:\Dropbox\Micros\2015\teste\xc8_teste\main.c"
	line	210
	global	__size_of_ascii_para_numero
	__size_of_ascii_para_numero	equ	__end_of_ascii_para_numero-_ascii_para_numero
	
_ascii_para_numero:
;incstack = 0
	opt	stack 27
;ascii_para_numero@caractere3 stored from wreg
	movwf	((c:ascii_para_numero@caractere3)),c
	line	212
	
i2l2015:
;main.c: 211: char numero;
;main.c: 212: numero=((caractere3 - '0')*100);
	movf	((c:ascii_para_numero@caractere3)),c,w
	addlw	low(0D0h)
	mullw	064h
	movff	prodl,(c:ascii_para_numero@numero)
	line	213
;main.c: 213: numero+=((caractere2 - '0')*10);
	movf	((c:ascii_para_numero@caractere2)),c,w
	addlw	low(0D0h)
	mullw	0Ah
	movf	(prodl),c,w
	addwf	((c:ascii_para_numero@numero)),c
	line	214
	
i2l2017:
;main.c: 214: numero+=(caractere1 - '0');
	movf	((c:ascii_para_numero@caractere1)),c,w
	addlw	low(0D0h)
	addwf	((c:ascii_para_numero@numero)),c
	line	215
	
i2l2019:
;main.c: 215: return numero;}
	movf	((c:ascii_para_numero@numero)),c,w
	
i2l167:
	return	;funcret
	opt stack 0
GLOBAL	__end_of_ascii_para_numero
	__end_of_ascii_para_numero:
	signat	_ascii_para_numero,12409
	GLOBAL	__activetblptr
__activetblptr	EQU	2
	psect	intsave_regs,class=BIGRAM,space=1,noexec
	PSECT	rparam,class=COMRAM,space=1,noexec
	GLOBAL	__Lrparam
	FNCONF	rparam,??,?
	GLOBAL	___rparam_used
	___rparam_used EQU 1
	GLOBAL	___param_bank
	___param_bank EQU 16
GLOBAL	__Lparam, __Hparam
GLOBAL	__Lrparam, __Hrparam
__Lparam	EQU	__Lrparam
__Hparam	EQU	__Hrparam
	end
