#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ListaFatur.h"
#include "../include/InfoFatur.h"

/**Módulo responsável pela construção e manuseamento das linked lists de structs Info_fatur's, que são utilizadas como "value" nos "nodes" da AVL da Faturação.*/

/**Estrutura da linked list de Info_fatur's.*/
struct lifatur{
	Info_fatur compras;
	struct lifatur *prox;
};

/** Incialização da linked list. */
LIfatur init_LIf (Info_fatur fat){
	LIfatur new = (LIfatur) calloc (1,sizeof (struct lifatur));
	new -> compras = fat;
	new -> prox = NULL;
	return new;
}

/** Adição de uma Info_fatur à linked list LIfatur. */
LIfatur add_LIf (Info_fatur fat, LIfatur lf){
	LIfatur new = (LIfatur) calloc (1,sizeof (struct lifatur));
	new-> compras = fat;
	new->prox=NULL;
	lf-> prox = new;
	return lf;
}

/** Função que liberta a memória de uma LIfatur.*/
void destroyLIfatur(LIfatur l){
    LIfatur temp;
    while (l != NULL){
        temp = l;
        l= l -> prox;
        free(temp);
    }
}

/** Substituição na LIfatur por uma nova Info_fatur. Fazemos isto quando estamos a ler o ficheiro de vendas e convertemos as informações de uma venda para uma
* struct Info_fatur. Como antes disto, na estrutura AVL apenas temos os códigos de produtos nos "nodes" mas com Linked Lists que têm unicamente uma Info_Fatur 
* com todos os campos a 0. Agora que temos Info_faturs desses mesmos produtos mas com campos preenchidos temos de substituir as suas linked lists na AVL por
* linked lists com estas novas Info_Fatur's. */
LIfatur new_LIf(Info_fatur fat,LIfatur lf){ 
	lf->compras = fat;
	lf->prox = NULL;
	return lf;
}

/** Função que nos dá acesso à primeira Info_fatur da linked list noutros módulos.*/
Info_fatur getInfo_fatur(LIfatur lf){ 
	return(lf->compras);
}

/**Função que nos permite ver qual a pŕoxima Info_fatur da lista noutro módulo.*/
LIfatur lifaturNext(LIfatur lf){
	return(lf->prox);
}
