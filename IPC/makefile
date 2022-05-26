CC=gcc
CFLAGS=-g -Wall

# dirs 
files_dir = ./archivos/
shm_dir = ./shm/
pipes_dir = ./tuberias/
sockets_dir = ./pm/
builds_dir = ./builds/

# all: files shm named_pipes sockets unnamed_pipes
all: shm named_pipes files

shm: shm_producer shm_consumer
named_pipes: npipes_consumer npipes_producer unnamed_pipes

files: $(files_dir)archivos.c
	$(CC) $(CFLAGS) -o $(builds_dir)files $(files_dir)archivos.c -lm

unnamed_pipes: $(pipes_dir)unnamed_pipes.c
	$(CC) $(CFLAGS) -o $(builds_dir)unnamed_pipes_producer $(pipes_dir)unnamed_pipes.c -lm

npipes_producer: $(pipes_dir)productor.c
	$(CC) $(CFLAGS) -o $(builds_dir)named_pipes_producer $(pipes_dir)productor.c
npipes_consumer: $(pipes_dir)receptor.c
	$(CC) $(CFLAGS) -o $(builds_dir)named_pipes_consumer $(pipes_dir)receptor.c

shm_producer: $(shm_dir)shm_prod.c
	$(CC) $(CFLAGS) -o $(builds_dir)shm_producer $(shm_dir)shm_prod.c
shm_consumer: $(shm_dir)shm_cons.c
	$(CC) $(CFLAGS) -o $(builds_dir)shm_consumer $(shm_dir)shm_cons.c

clean: 
	rm builds/*