#ifndef SIPARIS_H
#define SIPARIS_H

typedef int bool;

typedef struct STRUCTSIPARIS
{
	int sKey;
	char* Ad;
	char* Malzeme;
	char* Renk;
}* siparis;


siparis TanimlaYeniSiparis(int _sKey, char* _Ad, char* _Malzeme, char* _Renk);

#endif
