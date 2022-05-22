#include <stdio.h>
#include <sys/shm.h>

#define MEM_SIZE 1024 * 1240000

int main()
{
    key_t key = ftok("shmfile", 65);
  
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
  
    char *str = (char *) shmat(shmid, 0, 0);
  
    printf("Data read from memory: %s\n", str);
      
    shmdt(str);
    
    shmctl(shmid, IPC_RMID, NULL);
     
}