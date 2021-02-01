#ifndef INFO_FATUR
#define INFO_FATUR


typedef struct info_fatur *Info_fatur;

/**Funções que inicializam a struct de duas formas diferentes, dependo das nossas necessidades.*/
Info_fatur init_infoFatur();
Info_fatur init_infoFatur_Prod(const char *prod);

/**Liberta a memória da struct. */
void destroy_infoFatur (Info_fatur fat);

/**Função que converte as informações de uma linha de venda para a struct. */
Info_fatur insert_infoFatur(Info_fatur p, char* pd, char unid[],char pr[] ,char tipo[] ,char mes[],char fil[]);

/**Duas funções que se complementam, uma compara duas Info_Fatur's devolvendo 0 ou 1. A outra combina as informações de duas Info_Fatur's (depende do resultado
da função compare). Ambas são chamadas noutro módulo.*/
int compare(Info_fatur p, Info_fatur f);
Info_fatur add_information(Info_fatur fat,Info_fatur info);

/** Funções do tipo "get" para a struct. */
char* get_prodID(Info_fatur fat);
int get_mesFt(Info_fatur fat);
int get_filFt(Info_fatur fat);
int get_nr_vendasT(Info_fatur fat);
int get_nr_vendasN(Info_fatur fat);
int get_nr_vendasP(Info_fatur fat);
double get_FatN(Info_fatur fat);
double get_FatP(Info_fatur fat);
double get_FatTotal(Info_fatur fat);
int get_unidT(Info_fatur fat);

#endif