CC = gcc
FLAGS = -ansi -w -Wall -ggdb3 -Wextra -O2 -D_GNU_SOURCE 
PKG = `pkg-config --cflags --libs glib-2.0`
CFlags = -O2 -Wall

program: readFile.o vendasValidas.o vendaInfo.o listaVendas.o clientes.o produtos.o faturacao.o Filial.o SGV.o controller.o view.o InfoFatur.o ListaFatur.o
	gcc $(FLAGS) -o program readFile.o vendasValidas.o vendaInfo.o listaVendas.o clientes.o produtos.o faturacao.o Filial.o SGV.o controller.o view.o InfoFatur.o ListaFatur.o `pkg-config --cflags --libs glib-2.0`

controller.o:src/controller.c include/controller.h
	gcc $(FLAGS) -c src/controller.c $(PKG) -o controller.o

SGV.o: src/SGV.c include/SGV.h
	gcc $(FLAGS) -c src/SGV.c $(PKG) -o SGV.o

readFile.o: src/readFile.c include/readFile.h
	gcc $(FLAGS) -c src/readFile.c $(PKG) -o readFile.o 

vendasValidas.o: src/vendasValidas.c include/vendasValidas.h
	gcc $(FLAGS) -c src/vendasValidas.c $(PKG) -o vendasValidas.o 

vendaInfo.o: src/vendaInfo.c include/vendaInfo.h
	gcc $(FLAGS) -c -o vendaInfo.o src/vendaInfo.c

listaVendas.o: src/listaVendas.c include/listaVendas.h
	gcc $(FLAGS) -c src/listaVendas.c $(PKG) -o listaVendas.o 

InfoFatur.o: src/InfoFatur.c include/InfoFatur.h
	gcc $(FLAGS) -c -o InfoFatur.o src/InfoFatur.c

ListaFatur.o: src/ListaFatur.c include/ListaFatur.h
	gcc $(FLAGS) -c -o ListaFatur.o src/ListaFatur.c

clientes.o: src/clientes.c include/clientes.h
	gcc $(FLAGS) -c -o clientes.o src/clientes.c

produtos.o: src/produtos.c include/produtos.h
	gcc $(FLAGS) -c -o produtos.o src/produtos.c

faturacao.o: src/faturacao.c include/faturacao.h
	gcc $(FLAGS) -c src/faturacao.c $(PKG) -o faturacao.o

view.o: src/view.c include/view.h
	gcc $(FLAGS) -c src/view.c $(PKG) -o view.o 

Filial.o: src/Filial.c include/Filial.h
	gcc $(FLAGS) -c src/Filial.c $(PKG) -o Filial.o 

clean:
	rm program *.o

memcheck:
	valgrind --leak-check=full ./program