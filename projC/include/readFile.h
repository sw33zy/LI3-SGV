#include "Filial.h"		/**Include da AVL da Filial.*/
#include "faturacao.h"	/**Include da AVL da Faturação.*/
#include "clientes.h"	/**Include da struct responsável pela struct do catálogo dos clientes.*/	
#include "produtos.h"   /**Include da struct responsável pela struct do catálogo dos produtos.*/   
#ifndef READ
#define READ


typedef struct ficheiro *Ficheiro;

/** Funções responsáveis pela leitura dos ficheiros dos produtos, clientes e vendas, respetivamente.*/
int productsP(char* filesFolderPathP, Produtos ps ,Faturacao ft);
int clientsC(char* fileFolderPathC, Clientes cs);
int read_sells (char* fileFolderPathV, char* fileFolderPathP, char* fileFolderPathC, Produtos ps, Clientes cls, Filial f1, Filial f2, Filial f3, Faturacao ft, Ficheiro f);

/** Inicializção e destruição da struct ficheiro. */
Ficheiro init_ficheiro ();
void destroyFicheiro (Ficheiro f);

/**Funções "get" para a struct ficheiro.*/
int get_lidas (Ficheiro f);
int get_max_linelen(Ficheiro f);
char* get_max_line(Ficheiro f);
char* get_last_cliente (Ficheiro f);
char* get_ficheiroV (Ficheiro f);
char* get_ficheiroP (Ficheiro f);
char* get_ficheiroC (Ficheiro f);
int get_validas (Ficheiro f);
int get_prodVal (Ficheiro f);
int get_clienVal (Ficheiro f);


#endif
