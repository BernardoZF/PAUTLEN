CC = gcc
CFLAGS = -Wall -ansi -pedantic
EJ = alfa
LEX = lex.yy.c

all:
	@flex $(EJ).l
	$(CC) $(CFLAGS) -o pruebaMorfo $(EJ).c $(LEX)

.PHONY: clean run_1 run_2 run_3

clean:
	rm -rf pruebaMorfo
	rm -rf default.txt misalida1.txt misalida2.txt misalida3.txt
	rm -rf $(LEX)

run_1:
	@echo Ejecucion con entrada1.txt
	@./pruebaMorfo entrada1.txt misalida1.txt

run_2:
	@echo Ejecucion con entrada2.txt
	@./pruebaMorfo entrada2.txt misalida2.txt

run_3:
	@echo Ejecucion con entrada3.txt
	@./pruebaMorfo entrada3.txt misalida3.txt
