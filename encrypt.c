// file: encrypt.c
// date: 1/18/2007

/*
Text Encryption for PIC microcontrollers
Freely distributable in this original form.
(c) 1/18/2007 Pasan Hettiarachchi
(c) Microsolutions
Any questions or comments?  admin@microsolutions.info 
*/


/* this version was made based on Alex Pukall's C version of pc1 encryption algorithm

	http://membres.multimania.fr/pc1/
*/


#include <string.h>

#include "encrypt.h"



		unsigned short pkax,pkbx,pkcx,pkdx,pksi,pktmp,x1a2;
		unsigned short pkres,pki,inter,cfc,cfd,compte;
		unsigned short x1a0[8];
		unsigned char cle[17];
		short pkc;

		

		
	
		void initCipher()
		{
			int j;
			for (j=0;j<=16;j++)	{
				cle[j]=0;
			}
			for (j=0;j<=8;j++)	{
				x1a0[j]=0;
			}

			pkax=0;
			pkbx=0;
			pkcx=0;
			pkdx=0;
			pksi=0;
			pktmp=0;
			x1a2=0;
			pkres=0;
			pki=0;
			inter=0;
			cfc=0;
			cfd=0;
			compte=0;
			pkc=0;

		}

 

void clearCypher()
{
	int j;
			for (j=0;j<=16;j++)	{
				cle[j]=0;
			}
			for (j=0;j<=8;j++)	{
				x1a0[j]=0;
			}

			pkax=0;
			pkbx=0;
			pkcx=0;
			pkdx=0;
			pksi=0;
			pktmp=0;
			x1a2=0;
			pkres=0;
			pki=0;
			inter=0;
			cfc=0;
			cfd=0;
			compte=0;
			pkc=0;

}
void encodeCypher()
{

	pkdx=x1a2+pki;
	pkax=x1a0[pki];
	pkcx=0x015a;
	pkbx=0x4e35;

	pktmp=pkax;
	pkax=pksi;
	pksi=pktmp;

	pktmp=pkax;
	pkax=pkdx;
	pkdx=pktmp;

	if (pkax!=0)	{
		pkax=pkax*pkbx;
	}

	pktmp=pkax;
	pkax=pkcx;
	pkcx=pktmp;

	if (pkax!=0)	{
		pkax=pkax*pksi;
		pkcx=pkax+pkcx;
	}

	pktmp=pkax;
	pkax=pksi;
	pksi=pktmp;
	pkax=pkax*pkbx;
	pkdx=pkcx+pkdx;

	pkax++;

	x1a2=pkdx;
	x1a0[pki]=pkax;

	pkres=pkax^pkdx;
	pki++;
}
void assembleCypher(void)
{
	x1a0[0]= ( cle[0]*256 )+ cle[1];
	encodeCypher();
	inter=pkres;

	x1a0[1]= x1a0[0] ^ ( (cle[2]*256) + cle[3] );
	encodeCypher();
	inter=inter^pkres;

	x1a0[2]= x1a0[1] ^ ( (cle[4]*256) + cle[5] );
	encodeCypher();
	inter=inter^pkres;

	x1a0[3]= x1a0[2] ^ ( (cle[6]*256) + cle[7] );
	encodeCypher();
	inter=inter^pkres;


	x1a0[4]= x1a0[3] ^ ( (cle[8]*256) + cle[9] );
	encodeCypher();
	inter=inter^pkres;

	x1a0[5]= x1a0[4] ^ ( (cle[10]*256) + cle[11] );
	encodeCypher();
	inter=inter^pkres;

	x1a0[6]= x1a0[5] ^ ( (cle[12]*256) + cle[13] );
	encodeCypher();
	inter=inter^pkres;

	x1a0[7]= x1a0[6] ^ ( (cle[14]*256) + cle[15] );
	encodeCypher();
	inter=inter^pkres;

	pki=0;
}

void ascii_encrypt128(char *in, char *key,char ascCipherText[])
{
	int count, k=0;
	short pkd, pke;
	if(k){}

	clearCypher();

	for (count=0;count<16;count++) {
		cle[count]=key[count];
	}
	cle[count]='\0';


	for (count=0;count<40;count++) {
		pkc=in[count];

		assembleCypher();
		cfc=inter>>8;
		cfd=inter&255;

		for (compte=0;compte<=15;compte++) {
			cle[compte]=cle[compte]^pkc;
		}
		pkc = pkc ^ (cfc^cfd);

		pkd =(pkc >> 4);
		pke =(pkc & 15);

		*ascCipherText = 0x61+pkd; k++; ascCipherText++;
		*ascCipherText = 0x61+pke; k++; ascCipherText++;
	}
	*ascCipherText = '\0';

}

void ascii_decrypt128(char *in, char *key,char 	plainText[])
{
	int count, k=0;
	short pkd, pke;

	clearCypher();

	for (count=0;count<16;count++) {
		cle[count]=key[count];
	}
	cle[count]='\0';

	
	for (count=0;count<40;count++) {
		pkd =in[k]; k++;
		pke =in[k]; k++;

		pkd=pkd-0x61;
		pkd=pkd<<4;

		pke=pke-0x61;
		pkc=pkd+pke;

		assembleCypher();
		cfc=inter>>8;
		cfd=inter&255;

		pkc = pkc ^ (cfc^cfd);

		for (compte=0;compte<=15;compte++)
		{
			cle[compte]=cle[compte]^pkc;
		}
		*plainText = pkc; plainText++;

	}
	*plainText = '\0';

}





