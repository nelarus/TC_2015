// file: encrypt.h
// date: 1/18/2007

/*
Text Encryption for PIC microcontrollers
Freely distributable in this original form.
(c) 1/18/2007 Pasan Hettiarachchi
(c) Microsolutions
Any questions or comments?  admin@microsolutions.info 



this version was made based on Alex Pukall's C version of pc1 encryption algorithm

	http://membres.multimania.fr/pc1/
*/


#ifndef __ENCRYPT_H
#define __ENCRYPT_H

	void clearCypher(void);
	void encodeCypher(void);
	void assembleCypher(void);

	void ascii_encrypt128(char *in, char *key,char ascCipherText[]);
	void ascii_decrypt128(char *in, char *key,char ascCipherText[]);

	
	void initCipher(void);

#endif
