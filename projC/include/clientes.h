#ifndef CLIENTES
#define CLIENTES

/**struct clientes*/
typedef struct clientes *Clientes;

/**funções que lidam com a struct*/
Clientes init_client ();
Clientes insert_client (Clientes p, const char *code);
Clientes sort_AllC (Clientes p);
char** get_AllC (Clientes p);
int get_nr_clients (Clientes p);
void destroyClients (Clientes p);


#endif