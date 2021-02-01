#include <glib.h>
#include <gmodule.h>

#include "InfoFatur.h"
#include "ListaFatur.h"

#ifndef FATURACAO
#define FATURACAO

typedef struct faturacao *Faturacao;

Faturacao init_faturacao();
Faturacao NewCompraProd (Faturacao ft,const char *prod);
Faturacao addInfoProd (Faturacao ft, Info_fatur fat);

GTree* getTreeFT (Faturacao ft);
void destroyFaturacao(Faturacao ft);

/** --------------QUERY 11 --------- */
typedef struct topNProd *TopNProd;
TopNProd init_getProds ();
gboolean aux (gpointer key, gpointer value, gpointer p);
char ** prodVendidos (Faturacao ft, int limite);
void destroy_topNProd (TopNProd p);

/**---------------------------------------*/
int nr_vendasMes(Faturacao ft, char* prod, int mes, int NP,int fil);
double FatMes(Faturacao ft, char* prod, int mes , int NP,int fil);

void salesByMonthGap (Faturacao ft, int min, int max, char*prod, int*vendas, double*cashMoney);

/** ----------- QUERY 4 --------------- */
typedef struct existFil *ExistFil;
ExistFil init_EF ();
void destroyExistfil(ExistFil e);
char** neverBoughtFat (Faturacao ft,int branchID);

#endif
