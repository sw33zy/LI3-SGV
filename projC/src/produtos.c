#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "../include/produtos.h"

/**Módulo onde lidamos com a informação de todos os produtos, inserção e organização dos mesmos*/

struct produtos {
	char* lista[200000];
	int nr_of_prods;
} ;

/**função de inicialização da struct produtos*/
Produtos init_prod () {
	Produtos p = (Produtos) calloc (1,sizeof(struct produtos));
	p->nr_of_prods=0;
	return p;
}


/**função de inserção de um produto na lista de produtos*/
Produtos insert_prod (Produtos p, const char *code){
	p->lista[p->nr_of_prods++]=strdup(code);
	return p;
}

/**função de comparação utilizada na função qsort*/
static int myCmp (const void* a, const void* b) {
	return strcmp(*(const char**)a,*(const char**)b);
}

/**função que organiza a lista de elementos*/
Produtos sort_All (Produtos p){
	qsort(p->lista,p->nr_of_prods, sizeof(const char*), myCmp);
	return p;
}


/**função que devolve uma cópia da lista de produtos*/
char** get_AllP (Produtos p){
	char **res = (char**) calloc(((p->nr_of_prods)+1),sizeof(char*));
	int i;
	for (i=0;i<p->nr_of_prods;i++){
		res[i]=strdup(p->lista[i]);
	}
	return res;
}

/**função que devolve o número de produtos na lista*/
int get_nr_prods (Produtos p){
	return p->nr_of_prods;
}


/**função que devolve a lista de produtos começados por uma letra */
char** getProdByLetter (Produtos prod, char letter) {
	Produtos resultado = init_prod();
	char** res;
	int i;
	for (i=0; i< get_nr_prods(prod); i++) {

		char l=toupper(letter);
		char* position_ptr = strchr(prod->lista[i],l);
		int position = (position_ptr==NULL ? -1 : position_ptr - prod->lista[i]);

		if (position==0) insert_prod(resultado,prod->lista[i]);


	}
	res=get_AllP(resultado);
	destroyProds(resultado);
	return (res);
}


/**função que destroi a struct produtos*/
void destroyProds (Produtos p){
    /*free(p->lista);*/
	free (p);
}
