CC=gcc
CFLAGS=-g -Wall

# dirs 
files_dir = ./archivos/
shm_dir = ./shm/
pipes_dir = ./tuberias/
sockets_dir = ./paso_mensajes/

build_dir = ./build/

# all: files shm named_pipes sockets unnamed_pipes
all: shm pipes files sockets 

sockets: client server
shm: shm_producer shm_consumer
pipes: npipes_consumer npipes_producer unnamed_pipes

client: $(sockets_dir)client.c
	$(CC) $(CFLAGS) -o $(build_dir)client $(sockets_dir)client.c

server: $(sockets_dir)server.c
	$(CC) $(CFLAGS) -o $(build_dir)server $(sockets_dir)server.c 

files: $(files_dir)archivos.c
	$(CC) $(CFLAGS) -o $(build_dir)files $(files_dir)archivos.c -lm

unnamed_pipes: $(pipes_dir)unnamed_pipes.c
	$(CC) $(CFLAGS) -o $(build_dir)unnamed_pipes $(pipes_dir)unnamed_pipes.c -lm

npipes_producer: $(pipes_dir)productor.c
	$(CC) $(CFLAGS) -o $(build_dir)named_pipes_producer $(pipes_dir)productor.c
npipes_consumer: $(pipes_dir)receptor.c
	$(CC) $(CFLAGS) -o $(build_dir)named_pipes_consumer $(pipes_dir)receptor.c

shm_producer: $(shm_dir)shm_prod.c
	$(CC) $(CFLAGS) -o $(build_dir)shm_producer $(shm_dir)shm_prod.c
shm_consumer: $(shm_dir)shm_cons.c
	$(CC) $(CFLAGS) -o $(build_dir)shm_consumer $(shm_dir)shm_cons.c

clean: 
	rm build/* myfifo