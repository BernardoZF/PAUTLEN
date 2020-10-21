CC=gcc
CFLAGS= -g -Wall -pedantic -ansi

OBJECTSP1E1 = main_0_generacion.o generacion.o
OBJECTSP1E2 = main_generacion.o generacion.o
OBJECTSP1E3 = main_2_generacion.o generacion.o

all : main_0_generacion main_generacion main_2_generacion

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

generacion.o: generacion.c generacion.h
	$(CC) $(CFLAGS) -c generacion.c

clear:
		-rm -rf $(OBJECTSP1E1) $(OBJECTSP1E2) $(OBJECTSP1E3) *.exe *.asm

clean:
	-rm -rf $(OBJECTSP1E1) $(OBJECTSP1E2) $(OBJECTSP1E3) *.exe *.asm

runmain_0_generacion:
	./main_0_generacion main0.asm

runmain_generacion:
	./main_generacion main.asm

runmain_2_generacion:
	./main_2_generacion main2.asm
