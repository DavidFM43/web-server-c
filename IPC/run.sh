#!/bin/bash

echo "#####################################"
echo "IPC experimentos"
echo "#####################################"
echo 

echo "----MEMORIA COMPARTIDA----"
echo "1 kb"
./build/shm_producer 1
./build/shm_consumer
echo "10 kb"
./build/shm_producer 10
./build/shm_consumer
echo "100 kb"
./build/shm_producer 100
./build/shm_consumer
echo "1 mb"
./build/shm_producer 1000
./build/shm_consumer
echo "10 mb"
./build/shm_producer 10000
./build/shm_consumer
echo "100 mb"
./build/shm_producer 100000
./build/shm_consumer

echo 
echo
echo "--------ARCHIVOS----------"
./build/files

echo 
echo
echo "----TUBERIAS NOMBRADAS----"

echo "1 kb"
./build/named_pipes_producer 1 & ./build/named_pipes_consumer 1
echo "10 kb"
./build/named_pipes_producer 10 & ./build/named_pipes_consumer 10
echo "100 kb"
./build/named_pipes_producer 100 & ./build/named_pipes_consumer 100
echo "1 mb"
./build/named_pipes_producer 1000 & ./build/named_pipes_consumer 1000
echo "10 mb"
./build/named_pipes_producer 10000 & ./build/named_pipes_consumer 10000
echo "100 mb"
./build/named_pipes_producer 100000 & ./build/named_pipes_consumer 100000

echo 
echo
echo "----PASO DE MENSAJES----"

echo "1 kb"
./build/server 1 & ./build/client 1
echo "10 kb"
./build/server 10 & ./build/client 10
echo "100 kb"
./build/server 100 & ./build/client 100
echo "1 mb"
./build/server 1000 & ./build/client 1000
echo "10 mb"
./build/server 10000 & ./build/client 10000
echo "100 mb"
./build/server 100000 & ./build/client 100000


echo 
echo
echo "----TUBERIAS ORDINARIAS----"
./build/unnamed_pipes