CC=gcc
CFLAGS=-g -Wall

preprocess_dir = ./src/preprocess/
source_dir = ./src/
build_dir = ./bin/


run_server: server 
	clear
	$(build_dir)server

run_client: client 
	clear
	$(build_dir)client

data: preprocess_data 
	$(preprocess_dir)transform
	$(preprocess_dir)index
	rm $(preprocess_dir)transform $(preprocess_dir)index

server: $(source_dir)server.c
	$(CC) $(CFLAGS) -o $(build_dir)server $(source_dir)server.c

client: $(source_dir)client.c
	$(CC) $(CFLAGS) -o $(build_dir)client $(source_dir)client.c 

preprocess_data: unzip transform index

index: $(preprocess_dir)index_data.c
	$(CC) $(CFLAGS) -o $(preprocess_dir)index $(preprocess_dir)index_data.c

unzip: ./data/raw/travel_data.csv.zip
ifeq (,$(wildcard ./data/raw/travel_data.csv))
	unzip ./data/raw/travel_data.csv.zip -d data/raw
endif

transform: $(preprocess_dir)csv2bin.c
	$(CC) $(CFLAGS) -o $(preprocess_dir)transform $(preprocess_dir)csv2bin.c

clean:
	rm ./data/processed/rides.bin ./data/processed/source_id_table.bin
	rm $(build_dir)client $(build_dir)server 
