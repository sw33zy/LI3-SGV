#include <stdio.h>
#include <stdlib.h>
#include <../include/string.h>

#include "../include/Filial.h"
#include "../include/listaVendas.h"
#include "../include/view.h"
#include "../include/vendaInfo.h"

/**É aqui que construímos o "esqueleto" da estrutura responsável pela gestão de vendas de uma filial.*/

/**Construção da struct que contém uma estrutura AVL da biblioteca GLib.
*  A key da árvore é o código do cliente.
*  O value da árvore é a linked list de "Info_vendas" que contêm a informação de cada compra feita pelo cliente. 
*/
struct filial{
	GTree* info_vendas;
};

/** Struct auxiliar para responder à querie 9 e 11. */
struct clientesProd {
	char productId[40];
	char** listaC;
	char** listaT;
	int* nrCl;
	int* nrQt;
	int quantidade;
	int nrclientes;
	int fil;
};

/** Função de comparação para construir a árvore. */
static gint cmpgInfos (gconstpointer a, gconstpointer b){
	char* str_a = a;
	char* str_b = b;
    int result = strcmp(str_a,str_b);
    /*free(str_a);
    free(str_b); */
    return result;
}


/** Função que inicializa a struct filial */
Filial init_Filial(){
	Filial f = calloc(1,sizeof(struct filial));
	f->info_vendas = g_tree_new_full(cmpgInfos, NULL, g_free, destroyLIvenda);
	return f;
} 

/** Função que verifica se um cliente já existe na struct filial. Caso devolva 1, então o cliente já existe na filial, caso devolva 0, então o cliente não existe.
*/
int clientExists(Filial f, char* cliente){                     
	int res = 0;
	char* value = g_tree_lookup (f->info_vendas,cliente);
	if(value != NULL){
		res = 1; 
	}
	return res; 
}


/**Função que adiciona uma Info_venda à linked list de um cliente que já existe na filial em questão. */
static Filial addInfos (Filial f, Info_venda vd, char* cliente){  
	LIvenda value = g_tree_lookup (f->info_vendas,cliente);
	while(livendaNext(value)!= NULL){
		value = livendaNext(value);
	}
	
	value = addLI(vd,value);

	return f;
}

/** Primeiramente vê se o cliente já existe na Filial f, caso já exista vai apenas adicionar ao seu value(LIvenda) a Info_venda da nova
* compra , caso contrário insere um novo nodo com este cliente e uma LIvenda com a Info_venda da sua compra.
*/
Filial addInfo_venda(Filial f , Info_venda vd){          

	if(clientExists(f,get_cliente(vd))==0){  
		LIvenda new = init_LI(vd);
		g_tree_insert(f->info_vendas,get_cliente(vd),new);
	}
	else{									
		f = addInfos(f,vd,get_cliente(vd));
	}
	return f;
}

/**Função que devolve o número de unidades compradas por um dado cliente num dado mês,numa Filial f.*/
int getNrProdsByMonth(Filial f, char* cliente, int mes){
	int res=0;
	int i;
	LIvenda value = g_tree_lookup (f->info_vendas,cliente);
	if(value==NULL) {
		res=-1;
		return res;
	}
	Info_venda vd;
	for (i=0; value!= NULL; i++){
		vd = getCompra(value);
		if (get_mes(vd)==mes) {
			res+=get_unid(vd);
			
		}
		value = livendaNext(value);
	}
	
	return res;
}


/**Função que devolve a GTree de uma filial. */
GTree* getTree (Filial f){
	return(f->info_vendas);
}

/**Função que liberta o espaço de uma filial e remove as keys e values de uma GTree. */
void destroyFilial(Filial f){
	g_tree_destroy(f->info_vendas);
	free(f);
}



/* ---------------    QUERY 10 --------------------- */

/**Função que permite ir buscar o máximo sempre a seguir de uma lista de produtos através das unidades compradas, para a query 10 */
static Info_venda maxQ (LIvenda value, Info_venda max) {
	Info_venda vd;
	int quantidade = 0,maxQt =0,limite=0;
	limite = get_unid(max);
	while(value!= NULL){
		vd = getCompra(value);
		quantidade = get_unid (vd);
		if(quantidade < limite || limite == 0){
			if(quantidade > maxQt){
				max = getCompra(value);
				maxQt = quantidade;
			}
		}
		value = livendaNext(value);
	}
	
	return max;
}



/** Função que devolve uma lista de produtos, ordenada pela quantidade (usa a função maxQ para tal) e a merge para reunir todas as filiais */
ClientesProd getCompras_GlobMes (Filial f1, Filial f2, Filial f3, char* cliente, int mes) {
	ClientesProd c = init_clientesProd(10);
	char str[100];

	LIvenda l = g_tree_lookup (f1->info_vendas,cliente);							  
	LIvenda l1 = g_tree_lookup (f2->info_vendas,cliente);
	LIvenda l2 = g_tree_lookup (f3->info_vendas,cliente);
	LIvenda new = merge(l1,l2,l);
	LIvenda value = getComprasMes(new,mes);
	if(value==NULL) {
		c->listaC[0]="000";
		return c;
	}
	
	Info_venda max = init_info_venda();
	LIvenda aux = value;
	int i;
	for(i=0; value!=NULL; i++){
		max = maxQ(aux,max);
		value = livendaNext(value);
		c->listaC[i] = strdup(get_prod(max));
		sprintf(str,"%d",get_unid(max));
		c->listaT[i] = strdup(str);
		
} 

	return c;
	
}


/*------------------- QUERY 12 -------------------- */

/** Struct auxiliar */
struct lista {
	char* list[1000];
	int nr_of_lucro;
};


/** Função auxiliar de comparação para o qSort.*/
static int myCmp (const void* a, const void* b) {
	int int_a= *( (int*) a);
	int int_b= *( (int*) b);

	if(int_a==int_b) return 0;
	else if (int_a<int_b) return 1;
	else return -1;
}

/**função que devolve um array com o top n de uma filial gasto por ordem decrescente*/
int* spendingArray (Filial f, char* cliente,int n) {
	LIvenda value = g_tree_lookup (f->info_vendas,cliente);
	Info_venda vd ;
	int* res= (int*) calloc(1000,sizeof(int));
	int* r=(int*) calloc(n,sizeof(int));
	if(value==NULL){
		r[0]=-1;
		return r;
	}
	int i;
	for (i=0; value!= NULL;i++ ){
		vd=getCompra(value);
		int spend=get_preco(vd)*get_unid(vd);
		res[i]= spend;
		value = livendaNext(value);

	}
	qsort(res,i,sizeof(int),myCmp);
	for (i=0; i<n; i++){
		r[i]=res[i];
	}
	return r;
}


/**função que junta tres arrays de dimensão n, organiza os por ordem decrescente, e devolve os n gastos por ordem decrescente*/
int* topN(int* f1, int* f2, int* f3, int n){
	int* total= malloc (3*n*sizeof(int));
	int* top= malloc (n*sizeof(int));

	memcpy(total,f1,n*sizeof(int));
	memcpy(total+n,f2,n*sizeof(int));
	memcpy(total+(2*n),f3,n*sizeof(int));
	qsort(total,3*n,sizeof(int),myCmp);
	int i;
	for (i=0; i<n&&total[i]!=0; i++){
		top[i]=total[i];
	}

	return top;
}


Lista innit_lista (){
	Lista p = (Lista) calloc(1,sizeof(struct lista));
	p->nr_of_lucro=0;
	return p;

}

/**função que devolve uma cópia da lista da struct lista*/
char** get_AllL (Lista l,int limit){
	char **res = (char**) calloc((limit+1),sizeof(char*));
	int i;
	for (i=0;i<limit;i++){
		res[i]=strdup(l->list[i]);
	}
	return res;
}

/**função que insere um elemento num dado índice*/
Lista insert_lista (Lista p, const char *code,int j){
	p->list[j]=strdup(code);
	p->nr_of_lucro++;
	return p;
}

/**função que devolve o número de elementos na struct lista*/
int getNrL (Lista p){
	return p->nr_of_lucro;
}

void destroy_lista (Lista l){
	free(l);
}

/**função que procura num array de ints o produto que corresponde a esse gasto e, se encontrar, insere o no mesmo índice onde encontrou*/
Lista topNProducts (Filial f, char* client, int limit, int* r,Lista res) {
	LIvenda value = g_tree_lookup (f->info_vendas,client);
	Info_venda vd ;
	/*char **res = (char**) calloc(1000,sizeof(char*)); */
	int i;
	int j;
	for(i=0;value!=NULL;i++){
		vd=getCompra(value);
		for(j=0;j<limit;j++){
			if(get_lucro(vd)==r[j]){
				insert_lista(res,get_prod(vd),j);
				
			}
		}
		value = livendaNext(value);

	}
	return res;
}
 
/* -------------------------  Query 9  -----------------------           */

/*Função que inicializa a struct clientsProd, para a query 11, coloca-se 0 em fil e para a 9, -1. */
ClientesProd init_clientesProd (int q){
	ClientesProd c = (ClientesProd) calloc(3,sizeof(struct clientesProd));
	if(q==11){
		c->nrQt = (int*) calloc(3,sizeof(int)); 
		c->nrCl = (int*) calloc(3,sizeof(int)); 
		c->quantidade = 0;
		c->fil = 0; 
	}
	else{
		c->listaC = (char**) calloc(1000,sizeof(char*)); 
		c->listaT = (char**) calloc(1000,sizeof(char*));
		c->quantidade = 0;
		c->nrclientes = 0;
		c->fil = -1;
	}
	return c;
}

/*Função que destrói a struct ClientesProd conforme a query em questão, libertando, assim, memória. */
void destroy_clientesProd (ClientesProd p, int q) {
	if(q==11){
		free(p->nrQt);
		free(p->nrCl);
	}
	else{
		free(p->listaC);
		free(p->listaT);
	}
	free(p);
}


/**  Esta função é a auxiliar do g_tree_foreach.
*    Os inputs são a key e o value e um gpointer c, que corresponde à estrutura ClientesProd.
*    Apenas para a query 9, pois c1->fil foi inicializado com -1, avança-se com as listas de clientes e tipos para o final, de maneira a ser possível inserir no final das listas.
*    Dentro de um ciclo até o value ser NULL, e avançando sempre na lista ligada, verificamos inicialmente se se trata da query 9. Se sim, verificamos se o cliente (key) já foi inserido na lista.
*Se sim, passamos x=1 e verificamos se no índice desse cliente, o tipo inserido é o mesmo que aquele que iriamos inserir. Se assim for, guardamos numa variável esse caso (z=2), 
*de maneira a não voltar a inserir esse caso.
* 	 De seguida, verificamos se o produto que estamos a analisar é o mesmo do produto do value ( ou seja, se o cliente em análise, nesse value, comprou o produto) e se x for igual a 1,
 mas se z nao for igual a 2, adicionamos a key e o tipo, senão apenas incrementamos as unidades compradas no índice correspondente à filial, ou seja em 0 estão as unidades da filial 1, em 1 da 2 e
* em 2 da 3, por fim , aumenta-se a quantidade com as unidades.
*    Se for a primeira vez a analisar o cliente, então aumenta-se o número de clientes também.
*    O return é FALSE para que a travessia seja por toda a GTree.
 */
static gboolean auxForEach(gpointer key, gpointer value ,gpointer c) {
  	char* key1 = key;
  	ClientesProd c1 = c;
    LIvenda  value1 = value;
  	int i=0, x=0,j=0; int z=0;
  	char p;
  	Info_venda vd;
  	if(c1->fil == -1) for(i=0;(c1->listaC[i] != NULL) && (c1->listaT[i] != NULL);i++);
   
  
    while(value1!=NULL){
        vd=getCompra(value1);
        
        if(c1->fil == -1){
        	for(j=0; c1->listaC[j]!=NULL; j++) {
    			if (c1->listaC[j] == key1){
    				x=1;
    				char* p = get_tipo(vd);
    				if(strcmp (c1->listaT[j], p) == 0){
    	  			z=2;}
     	         }
       		   }	
       	     }
       
    	if((strcmp (get_prod (vd), c1->productId) == 0)&&(x==1) ){ 
  	    	if(c1->fil== -1 &&(z!=2) ){
  	    		c1->listaC[i] = key1;
  	    		c1->listaT[i] = get_tipo(vd);
  	    	}
  	   		else{
  	   			if(c1->fil==1)c1->nrQt[0]+= get_unid (vd);
				if(c1->fil==2)c1->nrQt[1]+= get_unid (vd);
				if(c1->fil==3)c1->nrQt[2]+= get_unid (vd);
  	   		}
			c1->quantidade += get_unid (vd);
			i++;
	    }
  		if ((strcmp (get_prod (vd), c1->productId) == 0)&&(x==0)) {
    		if(c1->fil== -1){ 
				c1->listaC[i] = key1;
				c1->nrclientes++;
				c1->listaT[i] = get_tipo(vd);
			}
			else{
				if(c1->fil==1){
					c1->nrCl[0]++;
					c1->nrQt[0]+= get_unid (vd);
				}
				if(c1->fil==2){
					c1->nrCl[1]++;
					c1->nrQt[1]+= get_unid (vd);
				}
				if(c1->fil==3){
					c1->nrCl[2]++;
					c1->nrQt[2]+= get_unid (vd);
				}
			}
			
  	   		c1->quantidade += get_unid (vd); 
  	   		i++;
  	    }
  		value1 = livendaNext(value1);
  	}
  
    /*destroyLIvenda(value1); 
    free(p);*/
return FALSE;
}

/**	Função que faz a travessia da árvore, através da função da biblioteca Glib g_tree_foreach, e utiliza a função auxForEach na travessia. 
*	O produto que é dado como input desta função é copiado para a estrutura ClientesProd.
*   O return da função é a estrutura ClientesProd.
*/
ClientesProd getListaClientP (Filial f, char* prod, ClientesProd c){
  			int i=0;
  			strcpy(c->productId, prod);
   	    	g_tree_foreach(f->info_vendas,auxForEach,c);

 	return c;
}

/*Funções "gets" para aceder aos vários campos da estrutura ClientesProd */
char** getListaC (ClientesProd c){
  	return (c->listaC);
}

char** getListaT (ClientesProd c){
	return (c->listaT);
}

int get_qt (ClientesProd c){
	return (c->quantidade);
}

int get_nrclientes (ClientesProd c){
	return (c->nrclientes);
}

char* getProdID (ClientesProd c){
	return (c->productId);
}

int getNrCL (ClientesProd c, int N) {
	return (c->nrCl[N]);
}
int getNrQt (ClientesProd c, int N) {
	return (c->nrQt[N]);
}

/*------------------------QUERY 6------------------------*/

/**Esta função indica os clientes que não compraram em cada filial.*/
int clientDontBuy (Filial f1, Filial f2, Filial f3, char** list){
	int res = 0;
	int i;
	for(i = 0; list[i]!=NULL; i++){
		if((g_tree_lookup(f1->info_vendas,list[i]) == NULL) &&
		   (g_tree_lookup(f2->info_vendas,list[i]) == NULL) &&
		   (g_tree_lookup(f3->info_vendas,list[i]) == NULL) ){
			res ++;
		}
	}
	return res;
}

/* ----------------------- Query 11 ------------------------------- */

/**Função que vai buscar a quantidade de clientes que comprou o produto em questão em cada filial.*/
ClientesProd topNValores (Filial f1, Filial f2, Filial f3, char*produto, ClientesProd cp){
	
    cp->fil =1;
    cp = getListaClientP(f1, produto, cp);
    cp->fil =2;
    cp = getListaClientP(f2, produto, cp);
    cp->fil =3;
	cp = getListaClientP(f3, produto, cp);

	return cp;
}


/* -------------------------------- FIM ------------------------ */
