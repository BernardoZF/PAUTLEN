CC = -gcc
CFLAGS=-Wall

all : pruebaTabla

.PHONY: clean
clean:
	rm *.o
	rm pruebaTabla

val:
	valgrind --leak-check=full --track-origins=yes ./pruebaTabla entrada.txt misalida.txt

pruebaTabla: prueba_tabla.o hash.o tablasimbolos.o
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -o $@ $<  hash.o tablasimbolos.o

prueba_tabla.o: prueba_tabla.c
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -c -o $@ $< $(CFLAGS)

hash.o: hash.c
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -c -o $@ $< $(CFLAGS)

tablasimbolos.o: tablasimbolos.c
	@echo "#---------------------------"
	@echo "# Generando $@ "
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	$(CC) -c -o $@ $< $(CFLAGS)
