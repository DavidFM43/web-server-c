CC=gcc
CFLAGS=-g -Wall

all: vel_arch

vel_arch: Archivos.o
	$(CC) $(CFLAGS) -o Archivos Vel_archivos.o -lm

Archivos.o: Vel_archivos.c
	$(CC) $(CFLAGS) -c Vel_archivos.c

clean:
	rm *.o Archivos
