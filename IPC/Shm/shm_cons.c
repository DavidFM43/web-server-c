#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

#define MEM_SIZE 1024 * 1240000

int main()
{
    key_t key = ftok("shm", 65); // genera una llave para la memoria compartida
  
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);// accede a la de memoria compartida
  
    if (shmid < 0 ){
        printf("Error in shmget.\n");
        exit(-1);
    }

    char* str = (char*) shmat(shmid, 0, 0); // obtiene el apuntador a la memoria compartida
  
    if (str < 0 ){
        printf("Error in shmat.\n");
        exit(-1);
    }

    printf("Data read from memory: %s\n", str); // lee los datos de la memoria compartida
      
    shmdt(str); // cierra la memoria compartida
    
    shmctl(shmid, IPC_RMID, NULL); // elimina la memoria compartida
     
}

