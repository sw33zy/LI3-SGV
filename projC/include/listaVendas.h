#include <glib.h>
#include <gmodule.h>

#include "vendaInfo.h"

#ifndef LIVENDA
#define LIVENDA

typedef struct livenda *LIvenda;

/**Funções que inicializam,adicionam e destroem uma linked list de structs Info_venda's. */
LIvenda init_LI();
LIvenda addLI(Info_venda vd ,LIvenda l);
void destroyLIvenda (LIvenda l);

/**Funções que usamos para percorrer a linked list noutros módulos.*/
Info_venda getCompra(LIvenda l);
LIvenda livendaNext(LIvenda l);

/**Função que junta 3 LIvendas numa só.*/
LIvenda merge (LIvenda l1, LIvenda l2,LIvenda l);

/**Função que nos devolve uma lista ligada das compras do respetivo mês.*/
LIvenda getComprasMes(LIvenda l,int mes);
#endif