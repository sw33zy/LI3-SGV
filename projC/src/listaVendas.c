#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/listaVendas.h"
#include "../include/vendaInfo.h"

/**Neste módulo construímos uma linked list com a struct Info_venda, que será posteriormente utilizada como "value" de cada "node" da estrutura AVL da Filial.*/

/** Construção da struct com a Info_venda, deste modo podemos "ligar" as Info_vendas do mesmo cliente. */
struct livenda{
	Info_venda compra;
	struct livenda *prox;
};

/** Incialização da linked list */
LIvenda init_LI(Info_venda vd){
	LIvenda new = (LIvenda) calloc (1,sizeof (struct livenda));
	new-> compra = vd;
	new-> prox = NULL;
	return new;
}

/** Adição de uma Info_venda à linked list LIvenda. */
LIvenda addLI(Info_venda vd ,LIvenda l){
	LIvenda new = (LIvenda) calloc (1,sizeof (struct livenda));
	new-> compra = vd;
	l-> prox = new;

	return l;
}

/** Função que liberta a memória de uma LIvenda.*/
void destroyLIvenda (LIvenda l){
	LIvenda temp;
	Info_venda vd;
    while (l != NULL){
       temp = l;
       /* vd = l -> compra;*/
        l = l -> prox;
       /*destroy_infoVenda(vd);*/
       free(temp);
    }
}

/**Funçao que nos dá acesso à primeira Info_venda da linked list noutros módulos.*/
Info_venda getCompra(LIvenda l){
	return(l->compra);
}

/**Função que nos permite ver qual a pŕoxima Info_venda da lista noutro módulo.*/
LIvenda livendaNext(LIvenda l){
	return(l->prox);
}

/**Função que copia uma linked list*/
static LIvenda LIvendaClone (LIvenda l) {
	LIvenda list = NULL, inicio=NULL;
	while(l!=NULL){
		LIvenda new = calloc (1,sizeof(struct livenda));
		new->compra=l->compra;
		new->prox=NULL;
		if(inicio==NULL) list=inicio=new;
		else {
			list=list->prox=new;
		}
		l=l->prox;
	}
	return inicio;

}

/** Função que junta 3 listas ligadas numa só. */
LIvenda merge (LIvenda l1, LIvenda l2,LIvenda l3){
	LIvenda aux1 = LIvendaClone (l1);
	LIvenda aux2 = LIvendaClone (l2);
	LIvenda aux3 = LIvendaClone (l3);
	LIvenda new = aux3;

	if(aux1 == NULL){
		new=aux2;
	}
	else if (aux2==NULL){
		new=aux1;
	}
	else if ((aux1 == NULL)&&(aux2==NULL)){
		new=NULL;
	}
	else{
		while(aux3->prox != NULL){
			aux3=aux3->prox;
		}
		while(aux1->prox != NULL){
			aux3->prox=aux1;
			aux3 = aux3->prox;
			aux1=aux1->prox;
		}
		while(aux2 != NULL){
			aux3->prox=aux2;
			aux3 = aux3->prox;
			aux2=aux2->prox;
		}
	}
	return new;
}

/**Funçao que nos devolve uma lista ligada com as Info_Vendas só daquele mês.*/
LIvenda getComprasMes(LIvenda l,int mes){
	Info_venda vd ;
	while(l !=NULL){
		if(get_mes(l->compra)==mes){
			vd = l->compra;
			break;
		}
		l = l-> prox;
	}
	LIvenda res = init_LI(vd);
	LIvenda aux = res;
	while(l != NULL){
		if(get_mes(l->compra)==mes){
			while(livendaNext(res)!= NULL){
				res = livendaNext(res);
			}
			res = addLI(l->compra,res);
		}
		l = l-> prox;
	}
	aux= aux->prox;
	return aux;
}
