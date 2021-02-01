#define MAX 100 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "../include/controller.h"
#include "../include/SGV.h"
#include "../include/view.h"

/* http://cs.ecs.baylor.edu/~donahoo/tools/valgrind/messages.html -> site sobre mensagens do valgrind */

/** -----------------------------------------------------------------  *//**
*   Controller : Este módulo contém a main, e distribui, conforme a opção do utilizador, as queries,
* definidas no SGV. Os resultados são apresentados na view, e é neste módulo que se fazem as chamadas destas funções de apresentação ao utilizador de resultados. 
*/ 

/*   Função invocada quando o utilizador introduz o comando 1. 
*    Esta apresenta 2 opções, a primeira se o utilizador pretende utilizador os ficheiros default,
*a segunda se pretende inserir os seus próprios ficheiros 
*    A opção inserida é validada pela função getValidOption que está definida na view, e de seguida a função
* segue 2 caminhos, se selecionado A, chama a função loadSGVFromFiles, com os ficheiros Clientes.txt, Produtos.txt
* e Vendas_1M.txt, se selecionado B apresenta as mensagens para inserir os nomes dos 3 ficheiros e chama o loadSGVFromFile
* com esses mesmos ficheiros, através de fgets e sscanf. 
*    Por fim, permite voltar ao menu, através da mensagem inserida na função acedeMenu do módulo menu.*/ 
static void query_1 (SGV sgv) {
  char buf[100];
  char c1[30];
  char c2 [30];
  char c3[30];
  char opcao;
  printMensagem ("A- Pretende utilizar os ficheiros default");
  printMensagem ("B- Prentende utilizar os seus próprios ficheiros");
  opcao= getValidOption(); 

  if (opcao=='A') {
    printMensagem("\033[2J");
    printMensagem("\033[5m" "\033[1m" "LOADING...\n" "\033[0m");
    printMensagem("\x1B[?25l");
    clear();
    sgv = loadSGVFromFiles (sgv,"Clientes.txt","Produtos.txt","Vendas_1M.txt");
    printMensagem("\x1B[?25h");                    
  }

  if (opcao=='B') {
    printMensagem("Insira o nome do ficheiro dos clientes");
    fgets(buf,100,stdin);
    sscanf (buf," %s",c1);
    printMensagem("Insira o nome do ficheiro dos produtos");
    fgets(buf,100,stdin);
    sscanf (buf," %s",c2);
    printMensagem("Insira o nome do ficheiro das vendas");
    fgets(buf,100,stdin);
    sscanf(buf," %s",c3);
    printMensagem("\033[5m" "LOADING...\n" "\033[0m");
    printMensagem("\x1B[?25l");
    clear();
    sgv = loadSGVFromFiles (sgv,c1,c2,c3);
    printMensagem("\x1B[?25h");            
  }
  acedeMenu();
  
}
 
/**   Função invocada quando o utilizador insere o comando 2.
*     Esta função, invoca aquela que imprime a mensagem que pede ao utilizador a letra que pretende procurar e, de seguida,
* através de fgets e sscanf, invoca a show que apresenta o resultado, retornado pela função getProductsStartedByLetter com o input da letra.
*     Por fim, permite retornar ao menu (acedeMenu).  
*/
static void query_2 (SGV sgv) {
    char buf [100];
    char letra;
    char** res;
    int i;
    printMensagem("Insira a letra ");
    fgets(buf,100,stdin);
    sscanf(buf," %c",&letra);
    res=getProductsStartedByLetter (sgv,letra);
    showQuery2(res);
    for(i=1; res[i]!=NULL; i++){
    free(res[i]);
    }
    free(res);
    acedeMenu();
}

/** Função invocada quando o utlizador insere o comando 3.
*   Esta função invoca aquela que imprime a mensagem que pede ao utilizador o código produto que pretende e a que pede e valida o mês.
*   De seguida, invoca a show que apresenta a resposta retornada pela função getProdutctSaleAndProfit com os inputs obtidos com fgets e sscanf. */
static void query_3 (SGV sgv) {
    char buf[100];
    char c1 [30];
    int mes;
    double* res;
    int i;
    printMensagem("Insira o código do produto");
    fgets(buf,100,stdin);
    sscanf (buf, "%s",c1);
    mes=getValidMes();
    showQuery3(res=getProductSaleAndProfit (sgv, c1, mes), c1);
    free(res);
    acedeMenu();
}


/** Função invocada quando o utlizador insere o comando 4.
*   Esta função invoca a que imprime a mensagem que dá a opção do utilizador escolher valores totais ou por filial e valida a opção inserida.
*   De seguida, toma 2 caminhos, se selecionado B, invoca a função que valida a filial, e chama a função que apresenta os resultados da  getProductsNeverBought com essa mesma filial, 
* se selecionado A, faz o mesmo percurso mas insere como filial zero.
*   Liberta-se memória e permite o acesso ao menu novamente. */
static void query_4 (SGV sgv) {
  char opcao;
  int filial;
  char** res; int i;
  printMensagem("A- Pretende valores totais");
  printMensagem("B- Pretende valores por filial");
  opcao=getValidOption();
  if (opcao=='B'){
    filial=getValidFilial();
    showQuery4(res=getProductsNeverBought (sgv,filial)); 
  }
  else{
    filial =0;
    showQuery4(res=getProductsNeverBought (sgv,filial)); 
  }
 
  for(i=0; res[i]!=NULL; i++){
    free(res[i]);
  }
  free(res);
  acedeMenu();
}


/* Função invocada quando o utilizador insere o comando 5.
*  Esta função invoca a que apresenta os resultados da getClientesOfALLBranches.
*  Por fim, permite retornar o menu (acedeMenu).
*/
static void query_5 (SGV sgv) {
  char** res;
  int i;
  showQuery5 (res=getClientsOfALLBranches (sgv));
  for(i=0; res[i]!=NULL; i++){
    free(res[i]);
  }
  free(res);
  acedeMenu();
}

/** Função invocada quando o utilizador insere o comando 6.
*   Esta função invoca a que apresenta os resultados da getClientesProductsNeverBought.
*   Por fim, permite retornar o menu (acedeMenu). 
*/
static void query_6 (SGV sgv) {
  showQuery6(getClientsAndProductsNeverBoughtCount (sgv));
  acedeMenu();
}

/** Função invocada quando o utilizador insere o comando 7.
*   Esta função invoca aquela que imprime a mensagem onde é pedido o código de cliente.
*   Por fim, chama a função que apresenta os resultados retornados da função getProductsBoughtByClient com o input do cliente e permite voltar ao menu.
*/
static void query_7 (SGV sgv) {
    char buf [100];
    char c [30];
    int i;
    int* r;
    printMensagem("Insira o código do cliente");
    fgets(buf,100,stdin);
    sscanf (buf,"%s",c);
    showQuery7(r=getProductsBoughtByClient (sgv, c),c);
    free(r);
    acedeMenu();
}

/** Função invocada quando o utilizador insere o comando 8.
*   Esta função invoca a que imprime as mensagens onde se pede o limite superior e inferior e as que os validam.
*   Por fim, chama a show que apresenta os resultados da getSalesAndProfit com os meses respetivos e permite retomar o menu.
*/ 
static void query_8 (SGV sgv) {
    char buf [100];
    int mesmin;
    int mesmax;
    double* r;
    printMensagem("\n""\033[1m""Mês, limite inferior""\033[0m");
    mesmin=getValidMes();
    printMensagem ("\n""\033[1m""Mês, limite superior""\033[0m");
    mesmax=getValidMes();
    showQuery8(r= getSalesAndProfit (sgv, mesmin, mesmax));
    free(r);
    acedeMenu();    

}

/** Função invocada quando o utilizador insere o comando 9.
*   Esta função invoca a que imprime a mensagem onde se pede o código do produto em questão e a flial, posteriormente validada. 
*   Por fim, chama-se a show que apresenta os resultados que estão na estrutura ClientesProd, através de "gets" e liberta-se os elementos da estrutura referente à query 9. 
    Permite-se ainda, retomar o menu. 
*/ 
static void query_9 (SGV sgv) {
  char buf [100];
  char c [30];
  int filial;
  ClientesProd c1;
  printMensagem("Insira o código do produto");
  fgets(buf,100,stdin);
  sscanf (buf,"%s",c);
  filial=getValidFilial();
  c1=getProductsBuyers (sgv, c, filial);
  showQuery9(getListaC(c1), getListaT(c1), get_nrclientes(c1));
  destroy_clientesProd (c1,9);
  acedeMenu();
}


/** Função invocada quando o utilizador insere o comando 10.
*   São invoadas as funções que pedem o código do cliente e pede e valida o mês. 
*   Por fim, dá-se como input do show os campos de resultado da estrutura, através dos "gets".
*   Permite-se voltar ao menu. 
*/
static void query_10 (SGV sgv) {
  char buf [100];
  char c [30];
  int mes;
  ClientesProd c1;
  printMensagem("Insira o código do cliente ");
  fgets(buf,100,stdin);
  sscanf (buf,"%s",c);
  mes=getValidMes();
  c1=getClientFavoriteProducts (sgv, c, mes);
  showQuery10(getListaC(c1), getListaT(c1));
  destroy_clientesProd(c1,10);
  acedeMenu();
}

/** Função invocada quando o utilizador insere o comando 11.
*   Invoca a função que pede o limite de produtos que pretende o utilizador. 
*   De seguida obtem a lista de produtos, com tamanho limite, e produto a produto inicializa a estrutura ClientesProd e através do show retorna os resultados que são obtidos na topNValores.
*   Liberta a memória da estrutura ClientesProd referente à query 11 e do produto em análise.
*   Permite-se voltar ao menu 
*/  
static void query_11 (SGV sgv) {
  int i;
  char buf [100];
  int limit;
  printMensagem ("Insira o nº de produtos que pretende");
  fgets(buf,100,stdin);
  sscanf (buf,"%d",&limit);
  char** prods = getTopSeeledProducts (sgv, limit);
  for(i=0;i<limit;i++){
    ClientesProd aux = init_clientesProd(11);
    aux = topNValores (getFilial(sgv,1),getFilial(sgv,2),getFilial(sgv,3),prods[i],aux);
    showQuery11 (getProdID(aux),getNrCL(aux,0),getNrQt(aux,0),getNrCL(aux,1),getNrQt(aux,1),getNrCL(aux,2),getNrQt(aux,2));
    printf("%d\n",i);
    destroy_clientesProd(aux,11);
    free(prods[i]);
  }
  free(prods);
  acedeMenu();
}

/** Função invocada quando o utilizador insere o comando 12.
*   Invoca as funções que pedem o cliente e o limite e através da show apresenta os resultados da getClientTopProfitProducts com os inputs obtidos com o fgets e sscanf.
*   Permite-se voltar ao menu.
*/
static void query_12 (SGV sgv) {
    char buf [100];
    char c [30];
    int limit;
    char** res;
    printMensagem("Insira o código do cliente");
    fgets(buf,100,stdin);
    sscanf (buf,"%s",c);
    printMensagem("Insira o limite de produtos que pretende procurar");
    fgets(buf,100,stdin);
    sscanf (buf,"%d",&limit);
    showQuery12(res =getClientTopProfitProducts (sgv, c, limit));
  /*int i=0;
    for (i=1; res[i]!=NULL;i++) {
      free(res[i]);
      i++;              
    }                        
    free(res); */
    acedeMenu();
}

/** Função invocada quando o utiliador insere o comando 13
*   Através dos "gets" passa à show os resultados que foram preenchidos, na estrutura Ficheiro, na função getCurrentFilesInfo. 
*   Permite-se voltar ao menu. 
*/
static void query_13 (SGV sgv) {
  Ficheiro fi = init_ficheiro();
  fi = getCurrentFilesInfo (sgv);
  showQuery13 (get_ficheiroC(fi), get_ficheiroP(fi), get_ficheiroV(fi), get_last_cliente(fi),  get_max_line(fi),get_max_linelen(fi), get_validas(fi), get_lidas(fi), get_prodVal(fi), get_clienVal(fi));
  acedeMenu();
}


/** Função main do programa. 
*   Inicializa-se a estrutura SGV e dentro de um do while, apresenta-se o menu, até ao utilizador selecionar a opção 14 de saída do programa.
*   Acede à opção que o utilizador inseriu, através de fgets, e com um switch da opção, distribui-se pelos casos. Ou seja, conforme a opção inserida, chama-se as query_ que estão definidas
* para cada comando. 
*   No final, chama-se a função que liberta a memória da estrutura SGV.  
 */
int main() {  
 
  char buf [100];
  char aux [100];
  int x = 0;
  int choice;

  SGV sgv = init_sgv();
  clock_t start, end;
  double cpu_time_used;
        
  do {  
        clear();
        menu();
        fgets(buf,100,stdin);
        strcpy (aux,buf);
        choice=atoi(aux);
        start = clock();
        switch(choice)
        {   
            
            case 1:
            {
              if(x!=0) {
              destroySGV(sgv);
              sgv = init_sgv();
              }
              query_1(sgv);       
              x++;   
              break;         
            }
            case 2:  
             {  
                query_2(sgv);
                break;
            }
            case 3: 
            {   
                query_3(sgv);
                break;
            }
            case 4:  
            {   
                query_4(sgv); 
                break;
            }
            case 5: 
            {   
                query_5(sgv);
                break;
            }
            case 6:  
            {
                query_6(sgv);
                break;
            }
            case 7: 
            {    
                query_7(sgv);
                break;
            }
            case 8: 
            {   
                query_8(sgv);
                break; 
            }
            case 9:  
            {   
                query_9(sgv); 
                break;
            }
            case 10:
            {    
                 query_10(sgv);
                 break;
            }
            case 11: 
            {   
              query_11(sgv);
              break;
            }
            case 12: 
            {    
               query_12(sgv); 
               break;
            }
            case 13: 
            {   
                query_13(sgv);
                break;
            }
            case 14: {
                break;
            }
            default:printMensagem("Insira novamente a opção");
        }
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        fprintf(stderr, "CPU Time used to Answer Query:%f\n", cpu_time_used );
    }  
    while (choice != 14 );
     destroySGV (sgv);
     printMensagem("Muito obrigada! Até à próxima");
    return 0;
}




