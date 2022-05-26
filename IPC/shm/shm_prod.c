/*
    La función main escribe el número de kbs especificados en una sección de memoria compartida.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>

#define MEM_SIZE 1024 * 1240000

char *create_data(int);
//numero de argumentos, lista de los argumentos
//nombre del archivo, 1
int main(int argc, char *argv[])
{
    if (argc > 2 || argc == 1)
    {
        printf("Incorrect number of arguments supplied.\n");
        exit(-1);
    }

    int kbs = atoi(argv[1]);

    char *data = create_data(kbs); // Genera los datos a enviar

    clock_t begin = clock(); // empieza a contabilizar

    key_t key = ftok("shm", 65); // genera una llave para la memoria compartida

    int shmid = shmget(key, MEM_SIZE, 0666 | IPC_CREAT); // crea la de memoria compartida

    if (shmid < 0)
    {
        printf("Error in shmget.\n");
        exit(-1);
    }

    char *str = (char *)shmat(shmid, 0, 0); // obtiene el apuntador a la memoria compartida

    if (str < 0)
    {
        printf("Error in shmat.\n");
        exit(-1);
    }

    strcpy(str, data); // escribe en la memoria compartida

    clock_t end = clock(); // termina de contabilizar

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; // tiempo de escritura

    printf("write time: %f segs.\n", time_spent);

    free(data); // libera la memoria de los datos
}

char *create_data(int kb)
{
    /*
        Crea un arreglo de chars de kb kilobytes y retorna el apuntador al arreglo.
    */
    char *data;
    int bytes = 1024 * kb + 1;
    data = (char *)malloc(bytes);
    for (int i = 0; i < bytes - 1; i++)
    {
        data[i] = 'a';
    }
    data[bytes - 1] = '\0';

    return data;
}