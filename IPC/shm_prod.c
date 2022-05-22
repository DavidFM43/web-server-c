#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

#define MEM_SIZE 1024 * 1240000

int main()
{
    key_t key = ftok("shmfile", 65);
  
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid < 0 ){
        printf("Error in shmget.\n");
        exit(-1);
    }

    char *ptr = (char *) shmat(shmid, 0, 0);
    
    if (ptr < 0 ){
        printf("Error in shmat.\n");
        exit(-1);
    }

    strcpy(ptr, "holamundo");

    printf("Se escribio %s\n", ptr);
}