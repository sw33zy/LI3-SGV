#include "../include/view.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
/* Este módulo é o módulo de apresentação, ou seja permite que haja interção com o utilizador.
// Apresenta-lhe o menu de opções que o programa tem, assim como as respostas às opções que o mesmo selecionou. */


/**menu do programa*/
void menu(){

    printf ("\033[0;33m"" \n **************************************************************** ""\033[0m");
    printf ("\033[1m""\n                 MENU: Selecione uma opção                         ""\033[0m");
    printf ("\033[0;33m"" \n **************************************************************** ""\033[0m");
    printf ("\n  1- Ler ficheiros");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n  2- Lista e nº de produtos começados por uma letra"); 
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n  3- Nº de vendas e o total faturado, de produto e mês");  
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n  4- Lista de produtos não adquiridos ");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n  5- Lista de clientes que compraram em todas as filiais");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n  6- Nº de clientes que não compraram e de produtos não comprados");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n  7- Tabela do nº total de produtos comprados dado um cliente");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n  8- Total de vendas e faturação de um intervalo de meses");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n  9- Lista e nº de clientes que compraram um produto");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n 10- Lista de produtos + comprados de um cliente num mês");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n 11- Lista de produtos + vendidos");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n 12- Lista de produtos em que um cliente gastou + dinheiro");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n 13- Resultados da leitura ");
    printf (" \n ---------------------------------------------------------------- ");
    printf ("\n 14- SAIR   "); 
    printf (" \n ----------------------------------------------------------------\n ");


}

/**função que é apresentada depois da exibição de cada query*/
void acedeMenu (){
    
    printf ("\033[0;33m""*****************************************************************\n""\033[0m");
    printf ("\033[1m""            Se pretende aceder ao menu : PRIMA ENTER             \n""\033[0m");
    printf ("\033[0;33m""*****************************************************************\n""\033[0m");

    while(getchar()!='\n');
    clear();
    
}   

/**Função que limpa o ecrã */
void clear () {
    printf("\e[2J\e[H");
}

/**Função que permite imprimir mensagens */
void printMensagem (char* string){
    printf (" %s\n", string);
}

/**Função que faz print de uma linha*/
void printLinha () {
    printf("\n\t===============================================================\t\n");
}




/**NAVEGADOR*/
/** Funçao que é utilizada para procurar por elemento na função listDivider*/
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

/**Função que funciona como um menu da função listDivider*/
static char proxPag(){
    char ch;
    printf("\033[1m""Pagina Seguinte       (P)\nVoltar ao Menu        (M)\nPagina Anterior       (O)\nEscolher Pagina       (E)\nVer quantidade total  (Q)\nProcurar por elemento (S)\n""\033[0m");
    
    while (((ch=getchar())!='P')&&(ch!='M')&&(ch!='O')&&(ch!='E')&&(ch!='Q')&&(ch!='S'));
    return ch;        
}


/**Função que divide uma lista de string. Seja o pages o número de paginas total, o j, o número da página atual, o k o número de strings por página e o t o número de elementos inseridos
* A cada iteração do ciclo o k é incrementado em 10 unidades de forma a posicionar o indice no local coerente com a página (k+n). Por exemplo, na página 3 o k seria 20, de forma a permitir
* ao ciclo apresentar os indices 20 a 30. Em relação ao "menu" da função, quando é escolhida a opção de regressar á página anterior, são subtraidas 10 unidades ao k anterior, ou seja, 
* se estivessemos na página 3, o k seria 20, ao escolher a opçao de ir para a página anterior, o k passaria a 10, exceto quando se encontra na primeira página onde não é mudado nenhum valor,
* apenas apresentado uma mensagem de aviso. Quando o utilizador pretende ir para a próxima página, nenhum elemento é alterado uma vez que o k é incrementado quando o ciclo de cada página
* termina, novamente, quando esta na ultima página, é apresentada uma mensagem de aviso e depois faz-se reset dos números para voltar à primeira página. Quando o utilizador pretende escolher
* uma página, obtemos os valores dessa página da seguinte forma: o k é obtido com a expressao (pagina escolhida)*10-10, ou seja, quando é escolhida a página 3, por exemplo, o k tem de ser 20
* o j é, obviamente, a página escolhida, e o número de elementos inseridos, t, é igual a (página ecolhida)*10; além disso, são eliminados casos em que o input é uma letra ou uma página inválida
* Finalmente, quando o utilizador pretende procurar um elemento dessa lista, é utilizada a função binarySearch para procurar esse elemento. Caso ele exista, encontrado o indice dele, os outros 
* valores são obtidos da seguinte forma: o número da página em que se encontra j, é igual a (indice/10)+1, por exemplo, um elemento encontrado na posição 23 do array, pertence à 3ª página
* e o k é encontrado de forma semelhante à da escolha de página, através do j. Quando o elemento não existe é apresentada uma mensagem de aviso e é apresentada a última página que foi exibida */
void listDivider (char** l, char* message) {
    printf("\033[2J");
    int i;
    for(i=0;l[i]!=NULL;i++);
    
    int pages= i / 10;
  
    if ((i%10)!=0) pages=pages+1;

    int j=1;
    int k=0;
    int t=0;
    char ch;
    int temp1=0;
    int temp2=0;
    int n;
    
    while(j<=pages&&t<i) {
    jump:
       temp1=t;
       printf("\033[1m""%s\n\n""\033[0m", message);
       for(n=0;n<10;n++&&t++){
            if(l[k+n]==NULL) break;
            else printf("\t%d. %s\n",n+k, l[k+n]);    
       } 
       temp2=k;
       k+=10;
       printf("\033[1m""\nPage <%d/%d> \n\n""\033[0m",j ,pages);
       j++;
       
       ch=proxPag();

       if(ch=='P') {
        
            if(j==pages+1) {
                j=1; t=0; k=0;
                printf("You are already on the last page!\nPress C to return to the first page\n");
                while (getchar()!='C');
                printf("\033[2J");
                goto jump;

        }
            else printf("\033[2J");
        }
       
       else if (ch=='M') break;

       else if (ch=='O') {
            if(j!=2){
                printf("\033[2J");
                k=temp2-10; j=j-2; t=temp1-10;
                
                goto jump;
            }
            else {
                printf("You are already on the first page!\nPress C to continue\n"); 
                while (getchar()!='C');
                printf("\033[2J");
            }


       }
       else if (ch=='E') {
            printf("\nEscolha o numero da pagina: ");
            int p;
            int f;
        jump2:   
            f=scanf("%d",&p);

            if (f==0) { 
                printf("Inseriu uma letra! Insira um número: ");
                while(getchar()!='\n');
                goto jump2;
            }
            if(p<1||p>pages){
                 printf("Pagina Invalida. Insira uma página entre 1 e %d.\n", pages);
                
                 goto jump2;
            }
            else {
                k=(p*10)-10;
                j=p;
                t=p*10;
                printf("\033[2J");
                goto jump;
            }


       }
       else if (ch=='Q') {
            printf("Quantidade Total: %d\n", i);
            printf("Press C to continue\n");
            while (getchar()!='C');
            
            printf("\033[2J");
            k=temp2; j=j-1; t=temp1;
            goto jump;
       
        }
        else if (ch=='S') {
            printf("\nEscolha o elemento a procurar: ");
            char p[15];
            int f;   
            scanf("%s",&p);
            

            f=binarySearch(l,p,i);

            if (f==-1){
                printf("Elemento não existe\n");
                printf("Press C to continue\n");
                while (getchar()!='C');
            
                printf("\033[2J");
                k=temp2; j=j-1; t=temp1;
                goto jump;
            }
            else{
                j=(f/10) + 1;
                k=(j*10)-10;
                t=j*10;
                printf("\033[2J");
                printf("Elemento encontrado na posição: %d!\n\n", f);
                goto jump;
            }

        }

    }
}


/**função que utiliza a função listDivider para apresentar o resultado da query2*/
void showQuery2 (char** p) {
    listDivider(p, "\xB2\xB2PRODUCT STARTED BY CHOSEN LETTER\xB2\xB2");
}

/**função que apresenta uma tabela com os resultados da query 3 Caso a primeira posição do array seja -1, significa que o produto não existe*/
void showQuery3 (double* r, char* productId){
    char* msgs[3];
    msgs[0]= "FILIAL 1";
    msgs[1]= "FILIAL 2";
    msgs[2]= "FILIAL 3";
    
    if((int)r[0]==-1) {
        printf("\033[1m" "\x1B[31m" "\nProduct does not exist!\n\n" "\033[0m");
        return;
    }
    printf("\033[1m""\t\t\t\xB2\xB2\xB2\xB2 BILLING: PRODUCT %s \xB2\xB2\xB2\xB2 \t\t""\033[0m", productId);
    printLinha();
    printf("\033[1m""\t  NR SALES N\t  NR SALES P\t   BILLED N\t     BILLED P\n""\033[0m");
    printLinha();

    int i=0, j=1, k=2, n=3;
    int m;
    for (m=0; m<3; m++) {
       printf("\033[1m""%s""\033[0m" "%8d %12d %19f %18f\n\n", msgs[m], (int) r[i], (int) r[j], r[k], r[n]);
       i+=4; j+=4; k+=4; n+=4;
    }
    printLinha();
    printf("\033[1m""%s""\033[0m" "%11d %12d %19f %18f\n\n", "TOTAL", (int) (r[0]+r[4]+r[8]), (int) (r[1]+r[5]+r[9]), r[2]+r[6]+r[10], r[3]+r[7]+r[11]);
}

/**função que utiliza a função listDivider para apresentar o resultado da query4*/
void showQuery4(char** res) {
    int i;
    listDivider(res, "\xB2\xB2PRODUCTS NOT BOUGHT\xB2\xB2");
}

/**função que utiliza a função listDivider para apresentar o resultado da query5*/
void showQuery5 (char** p) {
    listDivider(p, "\xB2\xB2 CLIENTS OF ALL BRANCHES\xB2\xB2");
}


/**função que apresenta os resultados da query 6*/
void showQuery6 (int* r) {
    printf("\033[1m" "\nNúmero de clientes que não compraram:" "\033[0m" " %d\n",r[0] );
    printf("\033[1m" "Número de produtos que não foram comprados:" "\033[0m" " %d\n\n", r[1] );
}

/**função que apresenta o resultado da query 7 numa tabela. Caso a primeira posição do array seja -1, significa que o cliente não existe
* Os indices do array correspondem a: 0-11, filial 1; 12-23, filial 2, 24-35,filial 3.*/
void showQuery7 (int* r, char* clientID) {
    if(r[0]==-1){
        printf("\033[1m" "\x1B[31m" "\nClient does not exist!\n\n" "\033[0m");
        return;
    }
    printf("\033[1m""\t\t    \xB2\xB2\xB2\xB2 PRODUCTS BOUGHT BY CLIENT %s \xB2\xB2\xB2\xB2 \t\t""\033[0m", clientID);
    printLinha();
    printf("\033[1m""\t MES\t FILIAL 1\t FILIAL 2\t FILIAL 3\t TOTAL\n""\033[0m");
    printLinha();

    int i=0;
    int m;
    for (m=1; m<13; m++ && i++) {
        printf("\t %-7d %-9d \t %-9d \t %-9d   \t %-10d\n\n ", m,r[i],r[i+12],r[i+24],r[i]+r[i+12]+r[i+24]);
    
  }
}

/**função que apresenta os resultados da query 8*/
void showQuery8 (double* r) {
    printf("\033[1m""\nVendas: " "\033[0m" "%d"  ,(int)r[0]);
    printf("\033[1m" " \nFaturação: " "\033[0m" "%f\n" , r[1]);
}

/**função que apresenta os resultados da query 9 numa tabela. Caso o primeiro elemento do array seja NULL, não existem compradores*/
void showQuery9 (char** clientes, char** tipo, int nrcl) {
    int i;
    
    printf("\033[1m""\n ========================\n");
    printf(" |  CLIENTS  |   TYPE   |");
    printf("\n ========================\n""\033[0m");

    if(tipo[0]==NULL){
        clientes[0]="Não há compradores";
        printf(" |  %s  |\n",clientes[0]);
        printf(" ------------------------\n");
    }

    else for(i=0; tipo[i] != NULL; i++){
        printf(" |   %s   |%6s    |\n",clientes[i],tipo[i]); 
        printf(" ------------------------\n");
        
    }
    printf("Nº de clientes : %d\n",nrcl);
    printf("\n\n");
}

/**função que apresenta os resultados da query 10 numa tabela horizontal. Caso o primeiro elemento do array seja igual a 000, o cliente não existe*/
void showQuery10 (char** clientes, char** quantidade) {
    int i,m;

    if(strcmp(clientes[0],"000")==0) {
        printf("\033[1m" "\x1B[31m" "\nClient does not exist!\n\n" "\033[0m");
        return;
    }

    for(i=0;clientes[i]!=NULL;i++);
    printf("\033[1m""\nPRODUTOS    |""\033[0m");
    for(m=0;m<i;m++){
        printf("%7s |",clientes[m]);
    }
    printf("\n------------|");
    for(m=0;m<i;m++){
        printf("--------|");
    }
    printf("\033[1m""\nQUANTIDADES |""\033[0m");
    for(m=0;m<i;m++){
        printf("%7s |",quantidade[m]);
    }
    printf("\n\n");
}

/**função que apresenta os resultados da query 11 numa tabela*/
void showQuery11 (char* p, int x, int y, int z , int i , int j,int w) {

        printf ("-------------------------------------------------------------------\n");
        printf ("    PRODUTO: |  Filial   |   Nº de clientes  |    Nº de unidades   \n");
        printf ("     %s  |     1     |          %d        |         %d     \n" ,p,x,y );
        printf ("             |     2     |          %d        |         %d     \n",z,i);
        printf ("             |     3     |          %d        |         %d     \n" ,j,w);
        printf ("  \n QUANTIDADE TOTAL: %d\n\n", (w+i+y));

}

/**função que utiliza a função listDivider para apresentar o resultado da query12*/
void showQuery12 (char** p) {
    listDivider(p,  "\xB2\xB2TOP PROFIT PRODUCTS BOUGHT\xB2\xB2");
}


/**função que apresenta os resultados da query 13*/
void showQuery13 (char* ficheiroC, char* ficheiroP, char* ficheiroV, char* last_client, char* max_line, int max_linelen, int validas, int lidas, int prodVl, int clienVal) {
    printLinha();
    printf("\033[1m""Ficheiro de clientes lido:""\033[0m"" %s\n", ficheiroC);
    printf("\033[1m""Ficheiro de produtos lido:""\033[0m"" %s\n", ficheiroP);
    printf("\033[1m""Ficheiro de vendas lido:""\033[0m"" %15s\n", ficheiroV);
    printLinha();
    printf("\033[1m""Ultimo cliente:""\033[0m"" %16s\n", last_client);
    printf("\033[1m""Linha mais longa:""\033[0m"" %39s\n", max_line);
    printf("\033[1m""Tamanho da linha mais longa, com /n/r:""\033[0m"" %d\n", max_linelen+2);
    printLinha();
    printf("\033[1m""Produtos válidos:""\033[0m"" %15d\n", prodVl);
    printf("\033[1m""Clientes válidos:""\033[0m"" %14d\n", clienVal);
    printf("\033[1m""Vendas válidas:""\033[0m"" %17d\n", validas);
    printf("\033[1m""Vendas lidas:""\033[0m"" %20d\n", lidas);

}

/*função que valida o input de uma opção: ou A ou B*/
char getValidOption() {
    char option;
    char buf[32];
    while (1){
        printf("Insert Valid input: ");
        fgets(buf,32,stdin);
        strtok(buf,"\n");
        if (strcmp(buf,"A")==0){ option='A'; break; }
        if (strcmp(buf,"B")==0){ option='B'; break; }

    }
    
    return option;
}

/**função que valida o input de uma filial: número entre 0 e 4*/
int getValidFilial() {
    int filial;
    char buf[32];
    while (1){
        printf("Insert Valid Branch: ");
        fgets(buf,32,stdin);
        strtok(buf,"\n");
        if(atoi(buf)>0&&atoi(buf)<4) {filial=atoi(buf); break;}

    }
    return filial;
}

/**função que valida o input de um mês: número entre 0 e 13*/
int getValidMes() {
    int mes;
    char buf[32];
    while (1){
        printf("Insert Valid Month: ");
        fgets(buf,32,stdin);
        strtok(buf,"\n");
        if(atoi(buf)>0&&atoi(buf)<13) {mes=atoi(buf); break;}

    }
    return mes;
}


