#define MAX 100 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../include/SGV.h"


#include "../include/clientes.h"   /*faz import da struct dos clientes*/
#include "../include/produtos.h"   /*faz import da struct dos produtos*/
#include "../include/Filial.h"     /*faz import da struct da Filial*/
#include "../include/faturacao.h"  /*faz import da struct da faturacao*/
#include "../include/view.h"       /*prints das respostas às queries*/



/* O Módulo sgv permite reunir todos os módulos de estruturas (clientes, produtos, filial, faturacao ), assim como a informação que se reúne com a análise de ficheiros
*  Neste módulo, implementamos as queries e construirmos para tal a struct SGV. 
*/

/*Struct que agrega todas as estruturas */
struct SGV {            
  Clientes clientes;    
  Produtos produtos;    
  Filial f1,f2,f3;
  Faturacao ft;
  Ficheiro f;           

};


/*Função que inicializa a struct sgv*/
SGV init_sgv (Ficheiro f) {
    SGV sgv = (SGV) calloc (3,sizeof(struct SGV));
    sgv->clientes = init_client();
    sgv->produtos = init_prod();
    sgv->f1 = init_Filial();
    sgv->f2 = init_Filial();
    sgv->f3 = init_Filial();
    sgv->ft = init_faturacao();
    sgv->f = init_ficheiro();
    return sgv;     
}

/** Funções que permitem obter os campos da struct SGV 
*/
Faturacao getFaturacao (SGV sgv){
  return(sgv->ft);
}

Filial getFilial (SGV sgv, int f){
  if (f==1) return sgv->f1;
  if (f==2) return sgv->f2;
  if (f==3) return sgv->f3;
}

/*Função que destrói a estrutura SGV */
void destroySGV (SGV sgv) {
      destroyClients(sgv->clientes);
      destroyProds (sgv->produtos);
      destroyFilial(sgv->f1);
      destroyFilial(sgv->f2);
      destroyFilial(sgv->f3);
      destroyFaturacao(sgv->ft);
      destroyFicheiro(sgv->f);
      free(sgv);

}


/**Query 1
* Load dos Ficheiros.
*/
SGV loadSGVFromFiles (SGV sgv, char* clientsFilePath, char* productFilePath, char* salesFilePath) {   

    char x;
     x =read_sells (salesFilePath, productFilePath, clientsFilePath,sgv->produtos,sgv->clientes, sgv->f1, sgv->f2, sgv->f3, sgv->ft,sgv->f); 
     if (x==0) printMensagem("\x1B[32m""\n\nFICHEIROS CARREGADOS!");
    return sgv;
}



/**Query 2
* função que chama a função getProdByLetter definida em produtos.c para devolver a lista de produtos começados por uma dada letra.
* caso a lista seja vazia, é adicionado esse caso ao primeiro índice
*/
char** getProductsStartedByLetter (SGV sgv, char letter) {  
    
    char ** resultado;
    resultado = getProdByLetter (sgv->produtos,letter); 
    if (resultado[0]==NULL) resultado[0]= "Não existem produtos começados por essa letra"; 

 return resultado;
}


/**Query 3
* Módulos necessários: Faturação            
* Utiliza a função nr_vendasMes para obter o número de vendas num mês para um certo produto. 
*/
double* getProductSaleAndProfit (SGV sgv, char* productId, int month) { 
  double* r= calloc(12,sizeof(double));
  

  int z = nr_vendasMes(sgv->ft,productId,month,0,1);
  if(z==-1) {
    r[0]=(double) z;
    return r;
  }
  r[0]= (double) z;
  int z1 = nr_vendasMes(sgv->ft,productId,month,1,1);
  r[1]= (double) z1;
  double i = FatMes(sgv->ft,productId,month,0,1);
  r[2]=i;
  double i1 = FatMes(sgv->ft,productId,month,1,1);
  r[3]=i1;
  
 
  int j = nr_vendasMes(sgv->ft,productId,month,0,2);
  r[4]=(double) j;
  int j1 = nr_vendasMes(sgv->ft,productId,month,1,2);
  r[5]=(double) j1;
  double w = FatMes(sgv->ft,productId,month,0,2);
  r[6]=w;
  double w1 = FatMes(sgv->ft,productId,month,1,2);
  r[7]=w1;
 
  int p = nr_vendasMes(sgv->ft,productId,month,0,3);
  r[8]=(double) p;
  int p1 = nr_vendasMes(sgv->ft,productId,month,1,3);
  r[9]=(double) p1; 
  double u = FatMes(sgv->ft,productId,month,0,3);
  r[10]=u;
  double u1 = FatMes(sgv->ft,productId,month,1,3);
  r[11]=u1;
  
  return r;
}

/**Query 4
* Módulos necessários: Faturação
* Devolve uma lista com os produtos não  comprados numa certa filial ou globalmente.
* 0 -> Global ; != 0 -> Filial f
*/
char** getProductsNeverBought (SGV sgv, int branchID) {  
  char ** lisRes ;
  lisRes = neverBoughtFat(sgv->ft,branchID);
  return lisRes;
}


/*Query 5
* Módulos necessários: Clientes e Filial
* Devolve a lista com os clientes que compraram em todas as Filiais.
* Se o cliente existir nas 3 filiais , então é adicionado à lista.
*/
char** getClientsOfALLBranches (SGV sgv) {   

  char ** list = (char**) calloc(get_nr_clients(sgv->clientes),sizeof(char*)); 
  char ** clCat = get_AllC(sgv->clientes);

  int res = 0, j=0;
  int i;
  for(i=0; clCat[i] != NULL; i++){
    res = 0;
    res += (clientExists(sgv->f1,clCat[i]));
    res += (clientExists(sgv->f2,clCat[i]));
    res += (clientExists(sgv->f3,clCat[i]));
    if(res == 3){
      list[j]=strdup(clCat[i]);
      j++;
    }
  }
  for(i=0;clCat[i]!=NULL;i++) free (clCat[i]);
  free(clCat);  
  return list;
}



/**Query 6
* Módulos necessários : filial e faturação
* Usando a "clientDontBuy" obtemos o número de clientes que nunca compraram.
* E usando a "neverBoughtFat" obtemos a lista dos produtos que nunca foram comprados.(Função já usada anteriormente)
*/
int* getClientsAndProductsNeverBoughtCount (SGV sgv ){
    int i;  
    char ** clCat = get_AllC(sgv->clientes);
    char ** lisRes;
    int* r = calloc (2,sizeof(int));
    int res = clientDontBuy(sgv->f1,sgv->f2,sgv->f3,clCat);
    lisRes = neverBoughtFat(sgv->ft,0);
    int res2;
    for(res2=0;lisRes[res2]!=NULL;res2++);
    r[0]=res;
    r[1]=res2;

    for(i=0;clCat[i]!=NULL;i++) free (clCat[i]);
    free(clCat);
    for(i=0;lisRes[i]!=NULL;i++) free (lisRes[i]);
    free(lisRes);

    return r;
}



/**Query 7
* Módulos necessários : filial
* Utiliza a função getNrProdsByMonth (Filial f, char* cliente, int mes) definida em Filial.c
* O resultado de cada filial é divido pelo array da seguinte forma 0-filial1, 1-filial2, 2-filial3, 3-filial1, 4-filial2..... etc de forma a dar return a apenas um array
*/
int* getProductsBoughtByClient (SGV sgv, char* clientID){ 
 
  
  int* r = calloc(36,sizeof(int)); 
  int i=0;
  int i2=12;
  int i3=24;
  int m;
  for (m=1; m<13; m++) {
    
    int r1 = getNrProdsByMonth(sgv->f1, clientID, m);
    if(r1==-1) {
      r[0]=-1;
      return r;
    } 
    r[i++]=r1;
    int r2 = getNrProdsByMonth(sgv->f2, clientID, m); r[i2++]=r2;
    int r3 = getNrProdsByMonth(sgv->f3, clientID, m); r[i3++]=r3;

  }
  
  return r;
}


/**Query8
* Utiliza a função salesByMonthGap definida em faturacao.c
* É utilizado um array de doubles para dar return dos resultados; no indice 0 fazemos cast das vendas para double (posterior cast back no módulo view) ; no indice 1 é guardada a faturação
*/
double* getSalesAndProfit (SGV sgv, int minMonth, int maxMonth){  
  
  int vendas=0;
  double cashMoney=0;
  int i;
  char**p=get_AllP(sgv->produtos);
  double* r= calloc(2,sizeof(float));
  for(i=0; p[i]!=NULL;i++){
    salesByMonthGap (sgv->ft, minMonth, maxMonth, p[i],&vendas,&cashMoney);
  }
  
  r[0]=(double) vendas;
  r[1]= cashMoney;
  
  return r;
}


/**Query 9 : Módulos necessários : filial
   De maneira, a ser possível obter os códigos e nº total de clientes, assim como o tipo de compra, é invocada a função getListaClienteP.
   Para tal, iniciliza-se a estrutura ClientesProd, onde se vai alocar as respostas da função, e executa-se 3 if, para as 3 possibilidades de filial.
   O return é a estrutura ClientesProd.
*/
ClientesProd getProductsBuyers (SGV sgv, char* productID, int branch){ 
  
  ClientesProd c1 = init_clientesProd(9);

  if (branch==1) {
  c1 = getListaClientP(sgv->f1,productID,c1);
  }
   if (branch==2) {
  c1 = getListaClientP(sgv->f2,productID,c1);
  }
   if (branch==3) {
  c1 =  getListaClientP(sgv->f3,productID,c1);
  }
    
  return c1;    
}



/**Query 10   Módulos necessários : filial  
*  Para a lista de produtos ordenada por quantidade de um dado cliente, num dado mês, utilizamos a função getCompras_GloMes e demos como return a struct ClientesProd, onde são preenchidas as repostas. 
*/
ClientesProd getClientFavoriteProducts (SGV sgv, char* clientID, int month){ 

  ClientesProd c ;
  c=getCompras_GlobMes (sgv->f1, sgv->f2,sgv->f3,clientID, month);

  return c;
}


/** Query 11   Módulos necessários : filial e faturação
*   Para obter a lista de topN produtos invocamos a função prodVendidos e retornamos a lista.
* As restantes informações de cada produto é completada no controller.  */
char** getTopSeeledProducts (SGV sgv, int limit) { 
  
  char ** prod = prodVendidos(sgv->ft,limit); 
  return prod; 
}


/** Query 12  Módulos necessários : filial  
*   São utilizadas as funções spendingArray, topN e topNProducts do filial.c
*   São criados 3 array com os lucros organizados, é feito um merge destes 3 array e o resultado é um array com o tamanho limit com os lucros por ordem descrescente
*   Este array é depois utilizado e atualizado para cada filial o que resulta nuum array de produtos correspondente aos lucros do array ft
*   Novamente é adicionado um caso particular para quando o cliente é inexistente.
*/
char** getClientTopProfitProducts (SGV sgv, char* clientID, int limit){
  
  Lista yolo = innit_lista();
  
  int*f1 =spendingArray(sgv->f1, clientID, limit);
  int*f2 =spendingArray(sgv->f2, clientID, limit);
  int*f3 =spendingArray(sgv->f3, clientID, limit);

  int*ft = topN (f1,f2,f3,limit);

  yolo = topNProducts(sgv->f1,clientID,limit,ft,yolo);
  yolo = topNProducts(sgv->f2,clientID,limit,ft,yolo);
  yolo = topNProducts(sgv->f3,clientID,limit,ft,yolo);
  
  char** res= get_AllL(yolo,getNrL(yolo));
  if(f1[0]==-1){
    res[0]="Cliente inexistente"; 
  }

  destroy_lista(yolo);
  return res;
}


/** Query 13  respostas da Query 1
*   Esta função utiliza a struct Ficheiro para apresentar as respostas da leitura ao utilizador.
*   Deste modo,  na query 1 (LoadSGVFromFiles) ao mesmo tempo que carrega os ficheiros, aloca na struct o nome dos mesmos, 
* aloca também o número de vendas lidas e o de válidas, e além disso ainda informa o nº de clientes e produtos válidos, o último cliente e a linha de venda mais longa e respetivo tamanho.
    Assim, nesta query apenas se dá return da struct que já fora preenchida.
*/
Ficheiro getCurrentFilesInfo (SGV sgv){ 
  return sgv->f; 
} 




