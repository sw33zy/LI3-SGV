#ifndef PRODUTOS
#define PRODUTOS

/**struct produtos*/
typedef struct produtos *Produtos;

/**funções que lidam com a struct*/
Produtos init_prod ();
Produtos insert_prod (Produtos p, const char *code);
Produtos sort_All (Produtos p);
char** get_AllP (Produtos p);
int get_nr_prods (Produtos p);
void destroyProds (Produtos p);

/**função que irá ser implementada na query 2 pra devolver a lista de elementos começados por uma dada letra*/
char** getProdByLetter (Produtos prod, char letter);

#endif