all: gerencia-arquivo.exe

gerencia-arquivo.exe: cabecalho.o removidos.o funcoes_fornecidas.o gerencia-arquivo.o registro.o escreveBin.o interpreta-bin.o indice.o criarIndice.o percorreCsv.o registroIndice.o inserirDado.o registroArvoreB.o cabecalhoArvoreB.o arvoreB.o main.o
	gcc registro.o cabecalho.o removidos.o gerencia-arquivo.o escreveBin.o interpreta-bin.o funcoes_fornecidas.o indice.o criarIndice.o percorreCsv.o registroIndice.o inserirDado.o registroArvoreB.o cabecalhoArvoreB.o arvoreB.o main.o -o gerencia-arquivo.exe -std=c99 -Wall

removidos.o:
	gcc -c removidos.c -o removidos.o

funcoes_fornecidas.o:
	gcc -c funcoes_fornecidas.c -o funcoes_fornecidas.o

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

inserirDado.o:
	gcc -c inserirDado.c -o inserirDado.o

registroArvoreB.o:
	gcc -c registroArvoreB.c -o registroArvoreB.o

cabecalhoArvoreB.o:
	gcc -c cabecalhoArvoreB.c -o cabecalhoArvoreB.o

arvoreB.o:
	gcc -c arvoreB.c -o arvoreB.o
	  
main.o:
	gcc -c main.c -o main.o

debug: CFLAGS += -g
debug: clean gerencia-arquivo.exe

clean:
	rm *.o gerencia-arquivo.exe

run:
	./gerencia-arquivo.exe

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./gerencia-arquivo.exe
