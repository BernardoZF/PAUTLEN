CC = gcc -pedantic
CFLAGS = -Wall -g
OBJECTS = lex.yy.o y.tab.o compilador.o tablahash.o generacion.o tablasimbolos.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o alfa $(OBJECTS) 
compilador.o: compilador.c y.tab.h
	$(CC) $(CFLAGS) -c compilador.c
generacion.o: generador_codigo/generacion.c generador_codigo/generacion.h
	$(CC) $(CFLAGS) -c generador_codigo/generacion.c
tablahash.o: tabla_simbolos/tablahash.c tabla_simbolos/tablahash.h
	$(CC) $(CFLAGS) -c tabla_simbolos/tablahash.c
tablasimbolos.o: tabla_simbolos/tablasimbolos.c tabla_simbolos/tablasimbolos.h
	$(CC) $(CFLAGS) -c tabla_simbolos/tablasimbolos.c
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
	./misalida

compilar_ejemplos:
	rm -rf ejemplos_compilados
	mkdir ejemplos_compilados

	for file in condicionales factorial simple vectores ; do \
    ./alfa ejemplos_alfa/$$file.alfa misalida.asm ; \
	nasm -felf32 -g misalida.asm ; \
	gcc -o $$file -m32 misalida.o alfalib.o ; \
	mv $$file ejemplos_compilados ; \
done

runv:
	valgrind --leak-check=full --track-origins=yes -v ./alfa fibonacci.alfa misalida.asm