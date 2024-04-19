all: lista.o gerencia-arquivo.o registro.o main.o
	gcc registro.o lista.o gerencia-arquivo.o main.o -o gerencia-arquivo -std=c99 -Wall

lista.o:
	gcc -c lista.c -o lista.o

gerencia-arquivo.o:
	gcc -c gerencia-arquivo.c -o gerencia-arquivo.o

registro.o:
	gcc -c registro.c -o registro.o
	  
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o gerencia-arquivo

run:
	./gerencia-arquivo