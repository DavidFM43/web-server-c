CC=gcc
CFLAGS=-g -Wall

all: make_data server client

preprocess_dir = ./preprocess/
source_dir = ./src/

data: $(preprocess_dir)process_data.c $(preprocess_dir)csv_to_bin.o $(preprocess_dir)indexer.o 
	$(CC) $(CFLAGS) -o make_data $(preprocess_dir)process_data.c $(preprocess_dir)csv_to_bin.o $(preprocess_dir)indexer.o

make_data: data
	./make_data

indexer.o: $(preprocess_dir)indexer.c
	$(CC) $(CFLAGS) -c $(data_dir)indexer.c

csv_to_bin.o: $(preprocess_dir)csv_to_bin.c
	$(CC) $(CFLAGS) -c $(data_dir)csv_to_bin.c

server: $(source_dir)server.c
	$(CC) $(CFLAGS) -o server $(source_dir)server.c

client: $(source_dir)client.c
	$(CC) $(CFLAGS) -o client $(source_dir)client.c 

clean:
	rm $(preprocess_dir)*.o 
