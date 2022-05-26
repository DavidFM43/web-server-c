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
echo "--------ARCHIVOS---------"
./builds/files