#include "siparis.h"
#include <stdlib.h>
#include <string.h>

siparis TanimlaYeniSiparis(int _sKey, char* _Ad, char* _Malzeme, char* _Renk){
  siparis ret = (siparis)malloc(sizeof(struct STRUCTSIPARIS));
  ret->sKey = _sKey;
  ret->Ad = strdup(_Ad);
  ret->Malzeme = strdup(_Malzeme);
  ret->Renk = strdup(_Renk);
  return ret;
}

