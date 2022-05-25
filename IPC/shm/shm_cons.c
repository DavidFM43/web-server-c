#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>

#define MEM_SIZE 1024 * 1240000

int main()
{

    clock_t begin = clock(); // empieza a contabilizar

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

    shmdt(str); // cierra la memoria compartida
    
    shmctl(shmid, IPC_RMID, NULL); // elimina la memoria compartida


    clock_t end = clock(); // termina de contabilizar

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // tiempo de escritura

    printf("read time: %f segs.\n", time_spent);
}

