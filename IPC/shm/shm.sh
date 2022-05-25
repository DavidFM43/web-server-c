#!/bin/bash
function shm(){
    echo Shared Memory IPC
    echo "1kb"
    ./producer 1
    ./consumer
    echo "10kb"
    ./producer 10
    ./consumer
    echo "100kb"
    ./producer 100
    ./consumer
    echo "1mb"
    ./producer 1000
    ./consumer
    echo "10mb"
    ./producer 10000
    ./consumer
    echo "100mb"
    ./producer 100000
    ./consumer
}
shm