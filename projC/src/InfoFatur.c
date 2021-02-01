#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/InfoFatur.h"

/** Módulo responsável pela criação da estrutura que irá ser utilizada para preencher a AVL da Faturação Global.*/

/** Esta struct armazena certas informações adquiridas através da leitura de uma linha de venda válida.Portanto, guarda os seguintes campos:
* 1.Código do produto (de modo a sabermos a que node correspondente podemos adicionar esta Info_fatur);
* 2.Mês de compra;
* 3.Filial;
* 4.Número de vendas deste produto em modo N;
* 5.Número de vendas deste produto em modo P;
* 6.Número de vendas no total, isto é N+P;
* 7.Faturação Global deste produto em modo P;
* 8.Faturação Global deste produto em modo N;
* 9.Faturação Global no total;
* 10.Unidades adquiridas deste produto no total.
*/
struct info_fatur{
	char produto[40];
	int mes;
	int fil;
	int nr_vendasN;
	int nr_vendasP;
	int nr_vendasTotal;
	double fatP;
	double fatN;
	double fatTotal;
	int unidT;
};

/** Inicialização da struct Info_fatur, com maior parte dos campos a 0.
*	NOTA: produtos que não foram comprados vão ter estes campos a 0. */
Info_fatur init_infoFatur(){ 
	Info_fatur p = (Info_fatur) calloc(1,sizeof(struct info_fatur));
	p->mes = 0;
	p->fil = 0;
	p->nr_vendasN = 0;
	p->nr_vendasP = 0;
	p->fatP = 0;
	p->fatN = 0;
	p->nr_vendasTotal = 0;
	p->fatTotal = 0;
	p->unidT = 0;

	return p;
}

/** Inicialização da struct Info_fatur mas com o campo do código do produto já preenchido. Usamos esta função para adicionar apenas os produtos do catálogo à AVL
* da faturação mas os campos da Info_Fatur vazios pois nesta fase ainda não temos acesso às vendas realizadas de cada produto. */
Info_fatur init_infoFatur_Prod(const char *prod){
	Info_fatur p = init_infoFatur();
	strcpy(p->produto,prod);

	return p;
}

/** Liberta a memória da struct*/
void destroy_infoFatur (Info_fatur p) {
	free(p);
}

/** Quando já temos acesso às informações de cada venda, e sabemos que a venda é válida, adicionamos os dados da linha de venda à info_fatur do produto em causa*/
Info_fatur insert_infoFatur(Info_fatur p, char* pd, char unid[],char pr[] ,char tipo[] ,char mes[],char fil[]){ 
	strcpy(p->produto,pd);
	if(strcmp("N",tipo) == 0){
		(p->fatN) += (atof(pr)*atoi(unid));
		(p->nr_vendasN)++;
	}
	else {
		(p->fatP) += (atof(pr)*atoi(unid));
		(p->nr_vendasP)++;
	}
	(p->mes) = atoi(mes);
	(p->fil) = atoi(fil);
	(p->fatTotal) = (p->fatP) + (p->fatN);
	(p->nr_vendasTotal)++;
	(p->unidT) = atoi(unid);
	return p;
}

/** Compara duas info_faturs's, caso ambas tenham informações sobre o mesmo produto, iremos verificar se essas informações são do mesmo mês e da mesma filial,
* se isto se confirmar então o return será 0, caso contrário devolve 1. Esta função será utilizada para depois adicionar as informações de duas info_faturs para
* os casos em que esta função devolve 0.*/
int compare(Info_fatur p, Info_fatur f){ 
	if(strcmp(p->produto,f->produto)==0){
		if(p->mes==f->mes){
			if(p->fil==f->fil){
				return 0;
			}
		}
	}
	return 1;
}

/** Adiciona as informações de duas Info_Fatur's. */
Info_fatur add_information(Info_fatur fat,Info_fatur info){ 
	fat->nr_vendasTotal += info->nr_vendasTotal;
	fat->nr_vendasP += info->nr_vendasN;
	fat->nr_vendasN += info->nr_vendasP;
	fat->fatN += info->fatN;
	fat->fatP += info->fatP;
	fat->fatTotal += info->fatTotal;
	fat->unidT += info->unidT;
	return fat;
}

/** Funções do tipo "get" que nos dão acesso aos campos desta struct noutros módulos. */
char* get_prodID(Info_fatur fat){
	return(fat->produto);
}

int get_mesFt(Info_fatur fat){
	return(fat->mes);
}

int get_filFt(Info_fatur fat){
	return(fat->fil);
}

int get_nr_vendasT(Info_fatur fat){
	return(fat->nr_vendasTotal);
}

int get_nr_vendasN(Info_fatur fat){
	return(fat->nr_vendasN);
}

int get_nr_vendasP(Info_fatur fat){
	return(fat->nr_vendasP);
}

double get_FatN(Info_fatur fat){
	return(fat->fatN);
}

double get_FatP(Info_fatur fat){
	return(fat->fatP);
}

double get_FatTotal(Info_fatur fat){
	return(fat->fatTotal);
}

int get_unidT(Info_fatur fat){
	return(fat->unidT);
}
