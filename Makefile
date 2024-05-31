all: lista.o cabecalho.o funcoes_fornecidas.o gerencia-arquivo.o registro.o escreveBin.o interpreta-bin.o indice.o criarIndice.o percorreCsv.o registroIndice.o main.o
	gcc registro.o lista.o cabecalho.o gerencia-arquivo.o escreveBin.o interpreta-bin.o funcoes_fornecidas.o indice.o criarIndice.o percorreCsv.o registroIndice.o main.o -o gerencia-arquivo.exe -std=c99 -Wall
funcoes_fornecidas.o:
	gcc -c funcoes_fornecidas.c -o funcoes_fornecidas.o

lista.o:
	gcc -c lista.c -o lista.o

gerencia-arquivo.o:
	gcc -c gerencia-arquivo.c -o gerencia-arquivo.o

registro.o:
	gcc -c registro.c -o registro.o

escreveBin.o:
	gcc -c escreveBin.c -o escreveBin.o

interpreta-bin.o:
	gcc -c interpreta-bin.c -o interpreta-bin.o

cabecalho.o:
	gcc -c cabecalho.c -o cabecalho.o

indice.o:
	gcc -c indice.c -o indice.o

criarIndice.o:
	gcc -c criarIndice.c -o criarIndice.o

percorreCsv.o:
	gcc -c percorreCsv.c -o percorreCsv.o

registroIndice.o:
	gcc -c registroIndice.c -o registroIndice.o
	  
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o gerencia-arquivo

run:
	./gerencia-arquivo.exe

valgrind:
	valgrind --leak-check=full ./gerencia-arquivo.exe