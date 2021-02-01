#include "InfoFatur.h"

#ifndef LIFATUR
#define LIFATUR


typedef struct lifatur *LIfatur;

/**Funções que inicializam,adicionam e destroem uma linked list de structs Info_fatur's.*/
LIfatur init_LIf (Info_fatur fat);
LIfatur add_LIf (Info_fatur fat, LIfatur lf);
void destroyLIfatur(LIfatur l);

/**Substitui o conteúdo de uma linked list por uma nova struct Info_Fatur.*/
LIfatur new_LIf(Info_fatur fat,LIfatur lf);

/**Funções que usamos para percorrer a linked list noutros módulos.*/
Info_fatur getInfo_fatur(LIfatur lf);
LIfatur lifaturNext(LIfatur lf);

#endif