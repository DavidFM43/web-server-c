#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

#define MEM_SIZE 1024 * 1240000

char* create_data(int);

int main()
{
    key_t key = ftok("shm", 65);
  
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid < 0 ){
        printf("Error in shmget.\n");
        exit(-1);
    }

    char* str = (char *) shmat(shmid, 0, 0);
    
    if (str < 0 ){
        printf("Error in shmat.\n");
        exit(-1);
    }

    char* data = create_data(1);

    strcpy(str, data);

    printf("Data written in memory: %s\n", str);

    free(data);
}

char* create_data(int kb){

    char *data;
    int bytes = 1024*kb + 1;
    data = (char*) malloc(bytes);
    for (int i = 0; i < bytes - 1; i++) 
    {
        data[i] = 'a';
    }
    data[bytes - 1] = '\0';

    return data;
}