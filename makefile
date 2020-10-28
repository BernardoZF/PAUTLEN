CC=gcc
CFLAGS= -g -Wall -pedantic -ansi

OBJECTSP1E1 = main_0_generacion.o generacion.o
OBJECTSP1E2 = main_generacion.o generacion.o
OBJECTSP1E3 = main_2_generacion.o generacion.o
OBJECTSP1E4 = main_ifelse.o generacion.o
OBJECTSP1E5 = main_while_vectores.o generacion.o
OBJECTSP1E6 = main_funciones.o generacion.o

all : main_0_generacion main_generacion main_2_generacion main_ifelse main_while_vectores main_funciones

main_0_generacion: $(OBJECTSP1E1)
	$(CC) $(CFLAGS) -o main_0_generacion $(OBJECTSP1E1)

main_0_generacion.o: main_0_generacion.c generacion.h
	$(CC) $(CFLAGS) -c main_0_generacion.c

main_generacion: $(OBJECTSP1E2)
	$(CC) $(CFLAGS) -o main_generacion $(OBJECTSP1E2)

main_generacion.o: main_generacion.c generacion.h
	$(CC) $(CFLAGS) -c main_generacion.c

main_2_generacion: $(OBJECTSP1E3)
	$(CC) $(CFLAGS) -o main_2_generacion $(OBJECTSP1E3)

main_2_generacion.o: main_2_generacion.c generacion.h
	$(CC) $(CFLAGS) -c main_2_generacion.c

main_ifelse: $(OBJECTSP1E4)
	$(CC) $(CFLAGS) -o main_ifelse $(OBJECTSP1E4)

main_ifelse.o: main_ifelse.c generacion.h
	$(CC) $(CFLAGS) -c main_ifelse.c

main_while_vectores: $(OBJECTSP1E5)
		$(CC) $(CFLAGS) -o main_while_vectores $(OBJECTSP1E5)

main_while_vectores.o: main_while_vectores.c generacion.h
		$(CC) $(CFLAGS) -c main_while_vectores.c

main_funciones: $(OBJECTSP1E6)
			$(CC) $(CFLAGS) -o main_funciones $(OBJECTSP1E6)

main_funciones.o: main_funciones.c generacion.h
			$(CC) $(CFLAGS) -c main_funciones.c

generacion.o: generacion.c generacion.h
	$(CC) $(CFLAGS) -c generacion.c

clear:
		-rm -rf $(OBJECTSP1E1) $(OBJECTSP1E2) $(OBJECTSP1E3) *.exe *.asm

clean:
	-rm -rf $(OBJECTSP1E1) $(OBJECTSP1E2) $(OBJECTSP1E3) *.exe *.asm

runmain_0_generacion:
	./main_0_generacion main0.asm
	nasm -g -felf32 main0.asm -o main0.o
	gcc -g -m32 alfalib.o main0.o -o main0
	./main0

runmain_generacion:
	./main_generacion main.asm
	nasm -g -felf32 main.asm -o main.o
	gcc -g -m32 alfalib.o main.o -o main
	./main

runmain_2_generacion:
	./main_2_generacion main2.asm
	nasm -g -felf32 main2.asm -o main2.o
	gcc -g -m32 alfalib.o main2.o -o main2
	./main2

runmain_ifelse:
	./main_ifelse mainifelse.asm
	nasm -g -felf32 mainifelse.asm -o mainifelse.o
	gcc -g -m32 alfalib.o mainifelse.o -o mainifelse
	./mainifelse

runmain_while_vectores:
	./main_while_vectores main_whilevectores.asm
	nasm -g -felf32 main_whilevectores.asm -o main_whilevectores.o
	gcc -g -m32 alfalib.o main_whilevectores.o -o main_whilevectores
	./main_whilevectores

runmain_funciones:
	./main_funciones mainfunciones.asm
	nasm -g -felf32 mainfunciones.asm -o mainfunciones.o
	gcc -g -m32 alfalib.o mainfunciones.o -o mainfunciones
	./main_funciones
