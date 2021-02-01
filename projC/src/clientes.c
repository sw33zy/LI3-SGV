#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "../include/clientes.h"

/**Módulo onde lidamos com a informação de todos os clientes, inserção e organização dos mesmos*/
struct clientes {
	char* lista[20000];
	int nr_of_clients;
} ;

/**função de inicialização da struct clientes*/
Clientes init_client () {
	Clientes p = (Clientes) calloc (1,sizeof(struct clientes));
	p->nr_of_clients=0;
	return p;
}

/**função de inserção de um produto na lista de clientes*/
Clientes insert_client (Clientes p, const char *code){
	p->lista[p->nr_of_clients++] = strdup(code); 
	return p;
}

/**função de comparação utilizada na função qsort*/
static int myCmp (const void* a, const void* b) {
	return strcmp(*(const char**)a,*(const char**)b);
}

/**função que organiza a lista de elementos*/
Clientes sort_AllC (Clientes p){
	qsort(p->lista,p->nr_of_clients, sizeof(const char*), myCmp);
	return p;
}

/**função que devolve uma cópia da lista de clientes*/
char** get_AllC (Clientes p){
	char **res = (char**) calloc(((p->nr_of_clients)+1),sizeof(char*));
	int i;
	for (i=0;i<p->nr_of_clients;i++){
		res[i]=strdup(p->lista[i]);
	}
	return res;
}

/**função que devolve o número de clientes na lista*/
int get_nr_clients (Clientes p){
	return p->nr_of_clients;
}

/**função que destroi a struct clientes*/
void destroyClients (Clientes p){
    /*free (p->lista); */
	free (p);
}