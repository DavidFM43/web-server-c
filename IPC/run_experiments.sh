#!/bin/bash

echo "#####################################"
echo "IPC experimentos"
echo "#####################################"
echo 

echo "----MEMORIA COMPARTIDA----"
echo "1 kb"
./builds/shm_producer 1
./builds/shm_consumer
echo "10 kb"
./builds/shm_producer 10
./builds/shm_consumer
echo "100 kb"
./builds/shm_producer 100
./builds/shm_consumer
echo "1 mb"
./builds/shm_producer 1000
./builds/shm_consumer
echo "10 mb"
./builds/shm_producer 10000
./builds/shm_consumer
echo "100 mb"
./builds/shm_producer 100000
./builds/shm_consumer

echo 
echo
echo "--------ARCHIVOS----------"
./builds/files

echo 
echo
echo "----TUBERIAS NOMBRADAS----"

echo "1 kb"
./builds/named_pipes_producer 1 & ./builds/named_pipes_consumer 1
echo "10 kb"
./builds/named_pipes_producer 10 & ./builds/named_pipes_consumer 10
echo "100 kb"
./builds/named_pipes_producer 100 & ./builds/named_pipes_consumer 100
echo "1 mb"
./builds/named_pipes_producer 1000 & ./builds/named_pipes_consumer 1000
echo "10 mb"
./builds/named_pipes_producer 10000 & ./builds/named_pipes_consumer 10000
echo "100 mb"
./builds/named_pipes_producer 100000 & ./builds/named_pipes_consumer 100000