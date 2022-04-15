CC=gcc
CFLAGS=-g -Wall

all:preprocess

search_test: search_testing.c
	$(CC) $(CFLAGS) -o search_test search_testing.c

indexer.o: indexer.c
	$(CC) $(CFLAGS) -c indexer.c

csv_to_bin.o: csv_to_bin.c
	$(CC) $(CFLAGS) -c csv_to_bin.c

preprocess: preprocess.c csv_to_bin.o indexer.o
	$(CC) $(CFLAGS) -o preprocess_data preprocess.c csv_to_bin.o indexer.o

clean:
	rm *.o preprocess_data search_test