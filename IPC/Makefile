CC=gcc
CFLAGS=-g -Wall

all: pipes_fork vel_arch 

vel_arch: Archivos.o
	$(CC) $(CFLAGS) -o Archivos Vel_archivos.o -lm

pipes_fork: name_pipe.o
	$(CC) $(CFLAGS) -o Pipes_fork name_pipe.o -lm

Pipes_fork.o: name_pipe.c
	$(CC) $(CFLAGS) -c name_pipe.c

Archivos.o: Vel_archivos.c
	$(CC) $(CFLAGS) -c Vel_archivos.c



clean:
	rm *.o Archivos Pipes_fork
