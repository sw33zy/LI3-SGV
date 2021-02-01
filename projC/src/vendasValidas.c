#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "../include/vendasValidas.h"
#include "../include/vendaInfo.h"

#include "../include/Filial.h"


/** Esta função efetua a procura binária nos catálogos dos produtos e dos clientes, para validar os códigos */
static int binarySearch(char *arr[], char *token, int n){ 

        int l = 0 ; 
        int r = n - 1; 
        while (l <= r){ 
            int m = l + (r - l) / 2; 
  

        if ((strcmp(token,arr[m]))==0) 
            return m;
 
 			int i=0;
 			while (token[i] == (arr[m][i])){
 				i++;
 			}
            if (token[i] > (arr[m][i])) 
                l = m + 1;
  
          
            else
                r = m - 1; 
        } 
  
        return -1; 
} 

/** Função que valida o produto, utilizando a função binarySearch 
    Retorna 0 se for válido, ou seja se pretence ao catálogo e 1 caso contrário*/
static int val_prod (char *token, char *prods[], int prods_len){ 
	int n=0;
	n = binarySearch(prods,token,prods_len);
	if (n == -1)
		return 1;
	if(strcmp(prods[n],token) == 0){
		return 0;
	} 

	else 
		return 1;	
}

/** Função que valida o cliente, utilizando a função binarySearch 
    Retorna 0 se for válido, ou seja se pretence ao catálogo e 1 caso contrário*/
static int val_client (char *token, char *clients[], int client_len) {

	int n=0;
	n = binarySearch(clients,token,client_len);
	if(n == -1) 
		return 1;
	if(strcmp(clients[n],token) == 0){
		return 0;
	}
	 
	else 
		return 1;
}

/**Função que verifica se o preço é válido.
* Retorna 0 se for o preço for válido, ou seja se estiver contido no intervalo [0,999.99] e 1 caso contrário. */
static int val_preco (char* preco){
    int resultado=1;
    double valor = strtod(preco,NULL);
    if ((valor<=999.99)&& (valor>=0)){
    	resultado=0;
    }
    else 
    	resultado=1;
    
    return resultado;
}

/**Função que verifica se o tipo de compra é válido.
* Retorna 0 se for válido, ou seja se for N ou P e 1 caso contrário */
static int val_tipo (char* tipo){   int resultado=1;
	char* promo = "P";
	char* notpromo = "N";
	if ( (strcmp(promo,tipo)) == 0 || (strcmp (notpromo,tipo)) ==0)
		resultado=0;

	else
		resultado=1;
	return resultado;
}

/**Função que verifica se as unidades são válidas.
* Retorna 0 se for válido, ou seja se estiver contido no intervalo [0,200] e 1 caso contrário.*/
static int val_unid (char* unidades){     
	int resultado=1; 
    int valor = atol (unidades);
    if ((valor>=0) && (valor <=200))
        	resultado=0;
	else
		resultado=1;
    return resultado;
}


/**Função que verifica se o mês é válido.
*  Retorna 0 se for válido ou seja se estiver contido no intervalo [1,12] e 1 caso contrário */ 
static int val_mes (char* mes){ 
	int resultado=1;  
    int valor = atol (mes);
    if ((valor>=1) && (valor<= 12)){
  	    resultado=0;
    }

    else {
   		resultado=1;}
    return resultado;
}

/**Função que verifica se a filial é válida.
* Retorna 0 se for válida, ou seja se for 1,2 ou 3 e 1 caso contrário. */

static int val_fil (char* filial){
	int resultado=1;
	int valor = atol (filial); 
	if (valor==1 || valor==2 || valor==3){
		resultado=0;
	}

	else {
		 resultado=1;
	}
	return resultado;
}


/*------------------------------------------------------------------------ */


/** Função que valida uma linha, ou seja percorre os campos das mesmas, enquanto o token não for NULL, conforme o local onde estamos na linha, chamamos as funções que validam os campos, no final
* somamos todos os returns das funções que validam e apenas se o total for zero é que consideramos que a linha é valida. Se for válida inserimos os valores dos campos nas respetivas structs através das funções insert_info_venda e insert_infoFatur. */
int is_Valid(char *line,char** prods,char** client,int len_p,int len_c, char* last_client, Info_venda vd, Info_fatur fat){

	char aux[40];
	char *token;


	char pd[40];
	char pr[40];
	char unid[40];
	char tipo[40];
	char cl[40];
	char mes[40];
	char fil[40];
	

	int i=0;
	int rprod=1,rclient=1,rpreco=1,rtipo=1,runid=1,rtotal=1,rmes=1,rfil=1;

	token = strtok (line, (" \n\r"));
	strcpy(aux ,token);
	rprod = val_prod(aux,prods,len_p);

	if(rprod==0){
		i=0;
	    strcpy(pd,token);

		while(token != NULL){
			if (i==4) {
				rclient = val_client(token,client,len_c);
				if(rclient==0){
					strcpy(last_client,token); 
					strcpy(cl,token);
				}
				else break;
			}
			if (i==1){
				rpreco = val_preco(token);
				if(rpreco==0){
					strcpy(pr,token);
				}
				else break;
			}
			if (i==2){
				runid = val_unid(token);
				if(runid!=0) break;
				else strcpy(unid,token);
			}
			if (i==3){
				rtipo = val_tipo(token);
				if (rtipo!=0) break;
				else strcpy(tipo,token);
			}
			if (i==5){
				rmes = val_mes(token);
				if(rmes!=0) break;
				else strcpy(mes,token);
			}
			if (i==6){
				rfil = val_fil(token);
				if(rfil!=0) break;
				else strcpy (fil,token);
			}
			token = strtok (NULL, (" "));
			i++;
		}
	}
	rtotal=rpreco+rprod+rclient+rtipo+runid+rmes+rfil;
	if(rtotal==0){
		vd = insert_info_venda(vd,cl,pd,pr,unid,tipo,mes,fil);
		fat = insert_infoFatur(fat,pd,unid,pr,tipo,mes,fil);
	}


	return rtotal;
}

