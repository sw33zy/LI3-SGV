#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/vendaInfo.h"

/** Módulo responsável pela criação da estrutura que irá ser utilizada para preencher a AVL da Filial.*/

/** Struct que armazena as informações de uma linha de venda. Contém:
* 1. Código do cliente (para sabermos a quem pertence a venda);
* 2. Código do produto;
* 3. Preço do produto;
* 4. Número de unidades compradas;
* 5. Tipo de venda (N ou P);
* 6. Mês da venda;
* 7. Filial. 
*/
struct info_venda{
	char cliente[40];
	char produto[40];
	double preco;
	int unid;
	char tipo[40];
	int mes;
	int fil;
};

/**Função que inicializa a struct info_venda. */
Info_venda init_info_venda(){
	Info_venda linha = (Info_venda) calloc(1,sizeof(struct info_venda));
	linha->preco = (double) 0;
	linha->unid = 0;
	strcpy(linha->tipo ,"\0");
	linha->mes = 0;
	linha->fil = 0;
	return linha;
}

/**Função que liberta a memória armazenada pela struct info_venda. */
void destroy_infoVenda (Info_venda v){
    free(v);
}
 
/**Função que insere os valores de cada "campo" de uma linha de venda na struct info_venda. */
Info_venda insert_info_venda(Info_venda linha,char* cl,char* pd,char pr[],char unid[] ,char tipo[] ,char mes[] ,char fil[]){
	strcpy(linha->cliente,cl);
	strcpy(linha->produto,pd);
	linha->preco = atof(pr);
	linha->unid = atoi(unid);
	strcpy(linha->tipo,tipo);
	linha->mes = atoi(mes);
	linha->fil = atoi(fil);
	return linha;
}

/**Funções que permitem aceder aos campos da struct info_venda noutros módulos. */
char* get_cliente(Info_venda linha){
	return (linha->cliente);
}

char* get_prod(Info_venda linha){
	return(linha->produto);
}

double get_preco(Info_venda linha){
	return(linha->preco);
}

int get_unid(Info_venda linha){
	return (linha->unid);
}

int get_mes(Info_venda linha){
	return(linha->mes);
}

int get_fil(Info_venda linha){
	return (linha->fil);
}

int get_lucro(Info_venda linha){
	return ((linha->unid) * (linha->preco));
}
char* get_tipo(Info_venda linha){
	return (linha->tipo);
}
