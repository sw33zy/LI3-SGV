#ifndef INFO_VENDA
#define INFO_VENDA


typedef struct info_venda *Info_venda;

/** Estas 3 funções inicializam, adicionam e destroem a struct, respetivamente. */
Info_venda init_info_venda();
Info_venda insert_info_venda(Info_venda linha,char* cl,char* pd,char pr[],char unid[] ,char tipo[] ,char mes[] ,char fil[]);
void destroy_infoVenda (Info_venda v);

/**Funções do tipo Get para a struct*/
char* get_cliente(Info_venda linha);
char* get_prod(Info_venda linha);
double get_preco(Info_venda linha);
int get_unid(Info_venda linha);
int get_mes(Info_venda linha);
int get_fil(Info_venda linha);
int get_lucro(Info_venda linha);
char* get_tipo(Info_venda linha);

#endif