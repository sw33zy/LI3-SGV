#include <glib.h>
#include <gmodule.h>

#include "vendaInfo.h"

#ifndef FILIAL
#define FILIAL

/** ------- FILIAL ----------*/

typedef struct filial *Filial;

Filial init_Filial();
void destroyFilial(Filial f);
GTree* getTree (Filial f);

int clientExists(Filial f, char* cliente);
Filial addInfo_venda(Filial f , Info_venda vd);
int getNrProdsByMonth(Filial f, char* cliente, int mes);

/**-----------	QUERY 12 --------------- */

typedef struct lista *Lista;

Lista innit_lista ();
void destroy_lista (Lista l);

int* spendingArray (Filial f, char* cliente, int n);
int* topN(int* f1, int* f2, int* f3, int n);
Lista topNProducts (Filial f, char* client, int limit, int* r,Lista res);

char** get_AllL (Lista l, int limit);
int getNrL (Lista p);

/**---------- QUERY 9 e 11 ----------*/
typedef struct clientesProd *ClientesProd;

ClientesProd init_clientesProd (int q);
void destroy_clientesProd (ClientesProd p, int q);

ClientesProd getListaClientP (Filial f,char *prod,ClientesProd c);

char** getListaC (ClientesProd c);
char** getListaT (ClientesProd c);
int get_qt (ClientesProd c);
char* getProdID (ClientesProd c);
int getNrCL (ClientesProd c, int N);
int get_nrclientes (ClientesProd c);
int getNrQt (ClientesProd c, int N);

ClientesProd topNValores (Filial f1, Filial f2, Filial f3, char*produto, ClientesProd cp);

/** -------- QUERY 10 --------*/

ClientesProd getCompras_GlobMes (Filial f1, Filial f2, Filial f3, char* cliente, int mes);

/**------------- QUERY 6 ------------- */

int clientDontBuy (Filial f1, Filial f2, Filial f3, char** list);



#endif
