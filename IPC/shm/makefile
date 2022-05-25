CC=gcc
CFLAGS=-g -Wall

all: prod cons 

prod: shm_prod.c
	$(CC) $(CFLAGS) -o producer shm_prod.c

cons: shm_cons.c
	$(CC) $(CFLAGS) -o consumer shm_cons.c

clean: 
	rm consumer producer