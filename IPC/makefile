CC=gcc
CFLAGS=-g -Wall

# dirs 
files_dir = ./archivos/
shm_dir = ./shm/
named_pipes_dir = ./tuberias/
sockets_dir = ./pm/
unnamed_pipes_dir = ./unnamed_pipes/
builds_dir = ./builds/

# all: files shm named_pipes sockets unnamed_pipes
all: shm named_pipes

shm: shm_producer shm_consumer
named_pipes: npipes

shm_producer: $(shm_dir)shm_prod.c
	$(CC) $(CFLAGS) -o $(builds_dir)shm_producer $(shm_dir)shm_prod.c

shm_consumer: $(shm_dir)shm_cons.c
	$(CC) $(CFLAGS) -o $(builds_dir)shm_consumer $(shm_dir)shm_cons.c

clean: 
	rm consumer producer