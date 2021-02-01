/** \mainpage
* Programa LI3 - SGV 
*     2019/2020
* Authors : Ema Dias; Leonardo Marreiros; Raquel Costa;
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>
#include <ctype.h>

#include "../include/readFile.h"
#include "../include/vendasValidas.h"  /**include que valida as vendas */
#include "../include/vendaInfo.h"	   /**include da struct infovenda */
#include "../include/InfoFatur.h"	   /**include da struct infoFatur */
#include "../include/view.h"		   /**inlude das funções que fazem  print de mensagens de erro*/

#include <glib.h>
#include <gmodule.h>

 
/**  
Neste módulo fazemos a leitura dos ficheiros escolhidos pelo utilizador do programa. 
*/

/** Esta função lê o ficheiro responsável pelos produtos. 
* 	À medida que lê cada linha, adiciona aquilo que leu numa linha à struct do Catálogo dos Produtos (Produtos ps) através da função "insert_prod", além disso 
* também cria um novo node da estrutura AVL em que a key desse mesmo node é o código do produto lido. 
*	Após adicionar todos os produtos lidos à struct "Produtos", vamos organizar por ordem alfabética o array da struct "Produtos", que contem todos os códigos,
* usando a função "sort_All", para mais à frente conseguirmos usar a procura binária. */
int productsP(char* filesFolderPathP, Produtos ps ,Faturacao ft) {
	char buffer[64];
	char prodID[40];

	FILE* f = fopen(filesFolderPathP, "r");
	
	if (f==NULL){
		printMensagem ("Ficheiro de Produtos Inexistente");
		return -1;
	}

	while(fgets(buffer,64,f)){
		strcpy(prodID ,(strtok (buffer, (" \n\r"))));
		ps = insert_prod(ps,prodID);
		ft = NewCompraProd(ft,prodID); 
	}
	
	ps = sort_All(ps);
	fclose(f);
	return get_nr_prods(ps);
}

/** Esta função funciona exatamente da mesma maneira que a anterior(productsP), a única diferença é que estamos apenas a tratar do catálogo dos clientes
* e dos respetivos códigos. */
int clientsC(char* fileFolderPathC, Clientes cs) {
	char buffer[64];

	FILE* f = fopen(fileFolderPathC, "r");
	
	if (f==NULL){
		printMensagem ("Ficheiro de Clientes Inexistente");
		return -1;
	}

	while(fgets(buffer,64,f)){
		cs = insert_client(cs, strtok(buffer, "\n\r"));
	}

	cs = sort_AllC(cs); 
	fclose(f);
	return get_nr_clients(cs);
}

/** Foi criada a stuct Ficheiro de modo a conseguirmos guardar todas as informações que precisamos, dos vários ficheiros, para apresentar ao utilizador na
* query 13. Guardamos as seguintes informações:
* 1. Path dos 3 ficheiros;
* 2. Código do último cliente;
* 3. Última linha do ficheiro das vendas;
* 4. Tamanho da últimha linha;
* 5. Número de vendas válidas;
* 6. Número de vendas lidas;
* 7. Número de códigos de Produto válidos no ficheiro de Vendas;
* 8. Número de códigos de Cliente válidos no ficheiro de Vendas.
 */
struct ficheiro {
	char ficheiroC [30];
	char ficheiroP [30];
	char ficheiroV [30];
	char last_client [20];
	char max_line [40];
	int max_linelen;
	int validas;
	int lidas;
	int prodVal;
	int clienVal;
};

/** Inicialização da struct Ficheiro */
Ficheiro init_ficheiro (){
	Ficheiro f = calloc (1 ,sizeof (struct ficheiro));
	f->validas = 0; 
	f->max_linelen = 0;
	f->lidas = 0;
	f->prodVal=0;
	f->clienVal=0;
	return f;
}

/** Funções do tipo "Get" de modo a termos acesso aos vários campos da struct noutros módulos. */
char* get_ficheiroC (Ficheiro f){
	return f->ficheiroC;
}
char* get_ficheiroV (Ficheiro f){
	return f->ficheiroV;
}
char* get_ficheiroP (Ficheiro f){
	return f->ficheiroP;
}
char* get_last_cliente (Ficheiro f){
	return f->last_client;
}
char* get_max_line(Ficheiro f){
	return f->max_line;
}
int get_max_linelen(Ficheiro f){
	return f->max_linelen;
}
int get_validas (Ficheiro f){
	return f->validas;
}
int get_lidas (Ficheiro f){
	return f->lidas;
}
int get_prodVal (Ficheiro f){
	return f->prodVal;
}
int get_clienVal (Ficheiro f){
	return f->clienVal;
}

/** Função que "destrói" a struct Ficheiro. */
void destroyFicheiro (Ficheiro f){
	free(f);
}

/** Esta função tem um papel fulcral. É ela que vai preencher as estruturas AVL's responsáveis pela faturação global e pela gestão de vendas em cada filial, 
* a stuct Ficheiro e os catálogos de Produtos e Clientes. Primeiramente, a função preenche dois arrays organizados alfabeticamente com os produtos e os clientes.
* Depois começa a ler o ficheiro das vendas linha a linha, passando a linha a uma função que irá verificar se todos os "campos" da linha são válidos. Portanto
* se o return dessa função for 0, podemos concluir que a linha da venda é válida e sendo assim podemos adicionar os campos dessa linha, agora já organizados em
* duas structs distintas, Info_Venda vd (responsável de armazenar as infos para a estrutura da Filial) e Info_Fatur fat (armazena para a estrutura da Faturação)
* às estruturas AVL's. */
int read_sells (char* fileFolderPathV, char* fileFolderPathP, char* fileFolderPathC, Produtos ps, Clientes cls, Filial f1, Filial f2, Filial f3, Faturacao ft,Ficheiro ficheiro){
	char buffer[1024];
	char line[40];
	char token[40];
	char last_client[40];

	char max_line[40];

	char aux[40];


    int max_linelen =0;
    int prod_num = productsP(fileFolderPathP,ps,ft); 
	int clien_num = clientsC(fileFolderPathC,cls);
	char **prods = get_AllP (ps);
	char **clients = get_AllC (cls);

	
	int res1=0, res2=0, res3=0;

	FILE *f = fopen(fileFolderPathV, "r");  
	if (f==NULL){
		printMensagem("Ficheiro de Vendas Inexistente");
		return -1;
	}

	Info_venda vd;
	Info_fatur fat;

	while(fgets(buffer,1024,f)){
		strcpy(line ,(strtok (buffer, ("\n\r"))));
		strcpy(token,line);

		vd = init_info_venda();
		fat = init_infoFatur();

		int rtotal = is_Valid(line,prods,clients,prod_num,clien_num,ficheiro->last_client,vd,fat);
		if(rtotal==0){
			if(strlen(token)>max_linelen){
				 max_linelen= strlen(token);
				strcpy(max_line,token);
			} 
			if(get_fil(vd) == 1){
				f1 = addInfo_venda(f1 , vd);
			} 
			if(get_fil(vd) == 2){
				f2 = addInfo_venda(f2 , vd);
			}

			if(get_fil(vd) == 3){
				f3 = addInfo_venda(f3 , vd);
			}
			ft=addInfoProd(ft,fat);
			ficheiro->validas ++;
		}
		else {	
			destroy_infoFatur(fat);
	 		destroy_infoVenda(vd);
	 	} 
		ficheiro->lidas++;
		
	}
	destroy_infoFatur(fat);
	destroy_infoVenda(vd);

    strcpy(ficheiro->ficheiroC, fileFolderPathC);
    strcpy (ficheiro->ficheiroP, fileFolderPathP);
    strcpy (ficheiro->ficheiroV, fileFolderPathV);
    strcpy (ficheiro->max_line,max_line);
    ficheiro->max_linelen = max_linelen;
    ficheiro->prodVal= get_nr_prods(ps);
    ficheiro->clienVal=get_nr_clients(cls);
  	fclose(f);

	return 0;
}