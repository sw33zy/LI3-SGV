#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/faturacao.h"


/** É neste módulo que construímos a estrutura para a Faturação Global de cada produto.*/

/**
* KEY: código dos produtos
* VALUE: LIfatur, lista ligada de Info_fatur's
*/
struct faturacao{
	GTree* produtos;
};


/** Função que inicializa. */
Faturacao init_faturacao(){
	Faturacao ft = calloc(1,sizeof(struct faturacao));
	ft -> produtos = g_tree_new_full((GCompareDataFunc)strcmp, NULL,g_free,destroyLIfatur);
	return ft;
}

/** Quando estamos a ler o ficheiro dos Produtos, criamos nodes na árvore em que o value é uma LIfatur com os campos todos a 0.  */
Faturacao NewCompraProd (Faturacao ft,const char *prod){ 
	Info_fatur fat = init_infoFatur_Prod(prod);
	LIfatur new = init_LIf (fat);
	g_tree_insert(ft->produtos,get_prodID(fat),new);
	return ft;
}


/** Nas vendas válidas, guardamos os dados necessarios numa info_Fatur fat. Procuramos o produto da info_Fatur na árvore.Depois de encontrar, temos o 
* seu value (LIfatur), percorremos cada Info_fatur deste , caso o mes corresponda ao da fat,entao o conteudo da fat é adicionado ao da Info_fatur
* onde estamos.Caso nenhum mês corresponda,adicionamos no final da LIfatur.     */
Faturacao addInfoProd (Faturacao ft, Info_fatur fat){   
	LIfatur value = g_tree_lookup (ft->produtos,get_prodID(fat));
	LIfatur prints = value;
	Info_fatur arv = getInfo_fatur(value);
	LIfatur aux;
	if(get_nr_vendasT(arv)==0){ 
		value = new_LIf(fat,value);
		arv = getInfo_fatur(value);	
	}
	else{
		while(value != NULL){
			arv = getInfo_fatur(value);
			if(compare(arv,fat)==0){									
				arv = add_information(arv,fat);
				break;
			}
			aux = value;
			value = lifaturNext(value);
		}
		if(value==NULL){
			aux = add_LIf (fat, aux);
			arv = getInfo_fatur(lifaturNext(aux));
		}
	}
	return ft;
}

/** Devolve a árvore da Faturação.*/
GTree* getTreeFT (Faturacao ft){
	return(ft->produtos);
}

/**Liberta a memória da estrutura da Faturação*/
void destroyFaturacao(Faturacao ft){
	g_tree_destroy(ft->produtos);
	free(ft);
}



/**  if NP == 0 então é normal ;if NP == 1 então é em promoção
* 	Indica o nº de vendas por mês de um produto numa determinada filial, em modo N ou P.
*/
int nr_vendasMes(Faturacao ft, char* prod, int mes, int NP,int fil){
	double res1P = 0;	
	double res1N = 0; 
	LIfatur value = g_tree_lookup (ft->produtos,prod);
	if (value==NULL) {
		return -1;
	}

	Info_fatur fat;
	while(value != NULL){
		fat = getInfo_fatur(value);
		if(get_mesFt(fat)==mes){
			if(NP==0){
				
				if(get_filFt(fat)==fil){
					res1N += get_nr_vendasN(fat);
				}
			}
			else{
				
				if(get_filFt(fat)==fil){
					res1P += get_nr_vendasP(fat);
					
				}
			}
		}
		value = lifaturNext(value);
	}
	
	if(NP==0){
		return res1N;
	}
	else{
		return res1P;
	}
}

/* if NP == 0 então é normal ;if NP == 1 então é em promoção
*  Indica a faturação de um produto, num determinado mês, numa certa filial em modo P ou N.
*/
double FatMes(Faturacao ft, char* prod, int mes , int NP,int fil){
	double res1P = 0;	/*PROMOÇÃO*/
	double res1N = 0; /*NORMAL*/
	LIfatur value = g_tree_lookup (ft->produtos,prod);
	Info_fatur fat ;
	while(value != NULL){
		fat = getInfo_fatur(value);
		if(get_mesFt(fat)==mes){
			if(NP==0){
				
				if(get_filFt(fat)==fil){
					res1N += get_FatN(fat);
				}
			}
			else{
				
				if(get_filFt(fat)==fil){
					res1P += get_FatP(fat);
					
				}
			}
		}
		value = lifaturNext(value);
	}
	
	if(NP==0){
		return res1N;
	}
	else{
		return res1P;
	}

}

/**
* função que soma todas as vendas e faturação que encontrar num dado intervalo de meses 
*/
void salesByMonthGap (Faturacao ft, int min, int max, char*prod, int*vendas, double*cashMoney) {
	int i; int j;
	j=max;
	LIfatur value = g_tree_lookup (ft->produtos,prod);
	Info_fatur fat ;
	

	for (i=min;i<=j;i++){
		LIfatur aux=value;
		while(aux != NULL){
			fat = getInfo_fatur(aux);
			if (get_mesFt(fat)==i) {
				*vendas+=get_nr_vendasT(fat);
				*cashMoney+=get_FatTotal(fat);
			}
			aux = lifaturNext(aux);
		}
		
	}
	
}

/*------------------QUERY 11----------------*/

/**Struct necessária para preencher um array de top N produtos que é retornado na função prodVendidos 
*/
struct topNProd{
	int maxanterior;
	char produtoatual[10];
	int max;
};

/**Inicialização da struct*/
TopNProd init_getProds (){
	TopNProd p = (TopNProd) calloc (1,sizeof(struct topNProd));
	p->maxanterior = 0;

	p->max = 0;

	return p;
}
/** Função que liberta a struct */
void destroy_topNProd (TopNProd p) {
	free(p);
	return p;
}

/**Função que permite aceder ao número de unidades vendidas*/
static int nrUnids(LIfatur lf){
	int res = 0;
	Info_fatur fat;
	while(lf != NULL){
		fat = getInfo_fatur(lf);
		res += get_unidT(fat);
		lf = lifaturNext(lf);
	}
	return res;
}


/**Função auxiliar da travessia que permite alocar na  struct o max da travessia
*e assim saber qual é o produto mais vendido, compara-se sempre com o maximo consultado anteriormente
*/
gboolean aux (gpointer key, gpointer value, gpointer p){
	
	TopNProd p1 = p;
	LIfatur value1 = value;  
	char* key1 = key;
	
    int quantidade = nrUnids (value1);

    	 	if ((quantidade < p1->maxanterior) || (p1->maxanterior == 0)) {
                if (quantidade>p1->max){
                     	strcpy (p1->produtoatual , key1);
 					    p1->max = quantidade;
                }
             }

  return FALSE;

}

/**  Função que usa o g_tree_foreach "limite" vezes, de forma a colocar no array produtos os N mais vendidos, onde N corresponde ao limite que o utilizador insere
* utiliza-se como auxiliar a aux e retorna a lista de produtos.
*    Além disso, liberta-se a memória da struct.*/
char ** prodVendidos (Faturacao ft, int limite) {
	TopNProd p = init_getProds();
	char ** prod = calloc (limite,sizeof(char*));

    int i=0;
    while (limite>0){
		g_tree_foreach (ft->produtos,aux,p);
   		p->maxanterior = p->max;
   		p->max = 0;
    	limite --;
    	prod[i] = strdup (p->produtoatual);
    	i++;
	}
	destroy_topNProd(p);
	return (prod);	
}




/*---------------------QUERY 4--------------------*/

/** Struct auxiliar*/
struct existFil{
	int filial;
	char* lres[100000];
};

ExistFil init_EF (){
	ExistFil e = (ExistFil) calloc (1,sizeof(struct existFil));
	e->filial = 0;
	return e;
}

void destroyExistfil(ExistFil e){
	free(e);
}

/**Função auxiliar que percorre a árvore, guardando numa lista na struct ExistFil os produtos que não foram comprados. */
static gboolean auxBF (gpointer key, gpointer value, gpointer p){

	char* chave = key;
	LIfatur valor = value;
	ExistFil res = p;
	Info_fatur fat;
	int i; 
	fat = getInfo_fatur(valor);
	for(i=0;res->lres[i]!=NULL;i++);
	if(res->filial==0){
		if(get_nr_vendasT(fat)==0){
			res->lres[i] = strdup(chave);
		}
	}
	else{
		int aux = 0;
		while(valor!=NULL){
			fat = getInfo_fatur(valor);
			if(res->filial==get_filFt(fat)){
				aux = 1;
				break;
			}
			valor = lifaturNext(valor);
		}
		if(aux==0) res->lres[i] = strdup(chave);
	}
	return FALSE;
}

/** Vê quais os produtos que nunca foram comprados numa certa Filial */
char** neverBoughtFat (Faturacao ft,int branchID){
	char ** lisRes = (char**) calloc(100000,sizeof(char*));
	ExistFil res = init_EF();
	res->filial = branchID;
	g_tree_foreach(ft->produtos,auxBF,res);
	int i;
	for(i=0;res->lres[i]!=NULL;i++){
		lisRes[i] = strdup(res->lres[i]);
	}
	destroyExistfil(res);
	return lisRes;
}
