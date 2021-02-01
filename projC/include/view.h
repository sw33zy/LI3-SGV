#include "Filial.h"

/**menus e outras ferramentas de apresentação.*/
void menu();
void acedeMenu();
void printLinha ();
void clear ();
void printMensagem (char* string);

/**Navegador*/
void listDivider (char** l, char* message);

/**funções que apresentam os resultados das queries*/
void showQuery2 (char** p);
void showQuery3 (double* r, char* productId);
void showQuery4(char** res);
void showQuery5 (char** p);
void showQuery6 (int* r);
void showQuery7 (int* r,char* clienteID);
void showQuery8 (double* r);
void showQuery9 (char** clientes, char** tipo, int nrcl);
void showQuery10 (char** clientes, char** quantidade);
void showQuery11 (char* p, int x, int y, int z , int i , int j,int w);
void showQuery12 (char** p);
void showQuery13 (char* ficheiroC, char* ficheiroP, char* ficheiroV, char* last_client, char* max_line, int max_linelen, int validas, int lidas, int prodVl, int clienVal);

/**funções que validam os inputs do utilizdor*/
char getValidOption();
int getValidFilial();
int getValidMes();


