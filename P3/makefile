CC = gcc
CFLAGS = -Wall -ansi -pedantic
EJ = alfa
LEX = lex.yy.c
TAB  = y.tab


all: flex bison
	@echo Compilado del ejercicio
	@$(CC) -Wall -o pruebaSintactico $(EJ).c $(LEX) $(TAB).c


.PHONY : clean run_1 run_2 run_3

clean :
	rm -rf pruebaSintactico
	rm -rf default.txt misalida1.txt misalida2.txt misalida3.txt
	rm -rf y.output
	rm -rf $(LEX)
	rm -rf $(TAB)*

flex:
	@flex alfa.l

bison:
	@bison -d -y -v alfa.y

run_1:
	@echo Ejecucion con entrada_sin_1.txt
	@./pruebaSintactico entrada_sin_1.txt misalida1.txt

run_2:
	@echo Ejecucion con entrada_sin_2.txt
	@./pruebaSintactico entrada_sin_2.txt misalida2.txt

run_3:
	@echo Ejecucion con entrada_sin_3.txt
	@./pruebaSintactico entrada_sin_3.txt misalida3.txt
