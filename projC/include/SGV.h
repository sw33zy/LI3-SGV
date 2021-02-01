#include "clientes.h"
#include "produtos.h"
#include "readFile.h"
#include "Filial.h"


typedef struct SGV *SGV;


SGV init_sgv () ;
SGV loadSGVFromFiles (SGV sgv, char* clientsFilePath, char* productFilePath, char* salesFilePath) ;
void destroySGV (SGV sgv);

Faturacao getFaturacao (SGV sgv);
Filial getFilial (SGV sgv, int f);

/** QUERIES */
char** getProductsStartedByLetter (SGV sgv, char letter);
double* getProductSaleAndProfit (SGV sgv, char* productId, int month);
char** getProductsNeverBought (SGV sgv, int branchID);
char** getClientsOfALLBranches (SGV sgv);
int* getClientsAndProductsNeverBoughtCount (SGV sgv );
int* getProductsBoughtByClient (SGV sgv, char* clientID);
double* getSalesAndProfit (SGV sgv, int minMonth, int maxMonth);
ClientesProd getProductsBuyers (SGV sgv, char* productID, int branch);
ClientesProd getClientFavoriteProducts (SGV sgv, char* clientID, int month);
char** getTopSeeledProducts (SGV sgv, int limit) ;
char** getClientTopProfitProducts (SGV sgv, char* clientID, int limit);
Ficheiro getCurrentFilesInfo (SGV sgv);

