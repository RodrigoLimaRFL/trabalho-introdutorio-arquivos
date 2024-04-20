all: lista.o cabecalho.o funcoes_fornecidas.o gerencia-arquivo.o registro.o interpreta-bin.o main.o
	gcc registro.o lista.o cabecalho.o gerencia-arquivo.o interpreta-bin.o funcoes_fornecidas.o main.o -o gerencia-arquivo -std=c99 -Wall

funcoes_fornecidas.o:
	gcc -c funcoes_fornecidas.c -o funcoes_fornecidas.o

lista.o:
	gcc -c lista.c -o lista.o

gerencia-arquivo.o:
	gcc -c gerencia-arquivo.c -o gerencia-arquivo.o

registro.o:
	gcc -c registro.c -o registro.o

interpreta-bin.o:
	gcc -c interpreta-bin.c -o interpreta-bin.o

cabeçalho.o:
	gcc -c cabeçalho.c -o cabeçalho.o
	  
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o gerencia-arquivo

run:
	./gerencia-arquivo