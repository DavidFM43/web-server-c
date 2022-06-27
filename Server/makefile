CC=gcc
CFLAGS=-g -Wall

all: server client

preprocess_dir = ./preprocess/
source_dir = ./src/

preprocess: $(preprocess_dir)preprocess.c $(preprocess_dir)csv_to_bin.o $(preprocess_dir)indexer.o 
	$(CC) $(CFLAGS) -o preprocess_data $(preprocess_dir)preprocess.c $(preprocess_dir)csv_to_bin.o $(preprocess_dir)indexer.o

indexer.o: $(preprocess_dir)indexer.c
	$(CC) $(CFLAGS) -c $(preprocess_dir)indexer.c

csv_to_bin.o: $(preprocess_dir)csv_to_bin.c
	$(CC) $(CFLAGS) -c $(preprocess_dir)csv_to_bin.c

server: $(source_dir)p2-server.c
	$(CC) $(CFLAGS) -o server $(source_dir)p2-server.c

client: $(source_dir)p2-client.c
	$(CC) $(CFLAGS) -o client $(source_dir)p2-client.c -lncurses

clean:
	rm $(preprocess_dir)*.o server client preprocess_data 
