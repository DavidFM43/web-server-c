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
all: shm named_pipes files

shm: shm_producer shm_consumer
named_pipes: npipes_consumer npipes_producer

files: $(files_dir)archivos.c
	$(CC) $(CFLAGS) -o $(builds_dir)files $(files_dir)archivos.c -lm

npipes_producer: $(named_pipes_dir)productor.c
	$(CC) $(CFLAGS) -o $(builds_dir)named_pipes_producer $(named_pipes_dir)productor.c
npipes_consumer: $(named_pipes_dir)receptor.c
	$(CC) $(CFLAGS) -o $(builds_dir)named_pipes_consumer $(named_pipes_dir)receptor.c

shm_producer: $(shm_dir)shm_prod.c
	$(CC) $(CFLAGS) -o $(builds_dir)shm_producer $(shm_dir)shm_prod.c
shm_consumer: $(shm_dir)shm_cons.c
	$(CC) $(CFLAGS) -o $(builds_dir)shm_consumer $(shm_dir)shm_cons.c

clean: 
	rm builds/*