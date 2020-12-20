CC = gcc -pedantic
CFLAGS = -Wall -g
OBJECTS = lex.yy.o y.tab.o compilador.o hash.o generacion.o tablasimbolos.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o alfa $(OBJECTS)
compilador.o: compilador.c y.tab.h
	$(CC) $(CFLAGS) -c compilador.c
generacion.o: generacion.c generacion.h
	$(CC) $(CFLAGS) -c generacion.c
hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c
tablasimbolos.o: tablasimbolos.c tablasimbolos.h
	$(CC) $(CFLAGS) -c tablasimbolos.c
lex.yy.o: lex.yy.c y.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c
y.tab.o: y.tab.c
	$(CC) $(CFLAGS) -c y.tab.c
lex.yy.c: alfa.l
	$ flex alfa.l
y.tab.h: alfa.y
	$ bison -d -y -v alfa.y

clean:
	rm -rf alfa lex.yy.c y.tab.c y.tab.h y.output ej alfa.tab.c alfa.tab.h misalida.asm misalida.o
	rm $(OBJECTS)


asm:
	nasm -felf32 -g misalida.asm
	gcc -o ej -m32 misalida.o alfalib.o
	./ej
